#include "left_panel.h"

LeftPanel::LeftPanel(QWidget *parent, TrainSimulationHandler *trainSimulation)
    : QWidget(parent), m_buttonLayout(nullptr), m_inputPanel(nullptr),
      m_trainSimulation(trainSimulation) {
  m_mainLayout = new QVBoxLayout(this);
  m_mainLayout->setContentsMargins(0, 0, 0, 0);
  m_mainLayout->setSpacing(0);
  setupHeader();

  QWidget *buttonContainer = new QWidget(this);
  m_buttonLayout = new QVBoxLayout(buttonContainer);
  m_buttonLayout->setContentsMargins(8, 0, 8, 8);
  m_buttonLayout->setSpacing(8);
  m_buttonLayout->setAlignment(Qt::AlignCenter);

  setupInputPageButtons();
  createRunButton();
  setupOutputPageButtons();
  QScrollArea *scrollArea = new QScrollArea(this);
  scrollArea->setWidget(buttonContainer);
  scrollArea->setWidgetResizable(true);
  scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scrollArea->setFrameShape(QFrame::NoFrame);

  m_mainLayout->addWidget(scrollArea);
  setFixedWidth(320);
  setLayout(m_mainLayout);

  setStyleSheet("QWidget {"
                "    background-color: " +
                Colors::Secondary500.name() +
                ";"
                "}"
                "QScrollArea {"
                "    background-color: " +
                Colors::Secondary500.name() +
                ";"
                "}"
                "QFrame[frameShape=\"4\"] {"
                "    background-color: " +
                Colors::Secondary300.name() +
                ";"
                "    color: transparent;"
                "}");
}

void LeftPanel::emitNavigateSignal(int pageIndex) {
  emit navigateToPage(pageIndex);
}

void LeftPanel::createRunButton() {
  QWidget *runButtonWidget = new QWidget();
  QStackedLayout *stackedLayout = new QStackedLayout(runButtonWidget);
  stackedLayout->setSpacing(8);

  ButtonAction *runButtonV = new ButtonAction(this, "Run");
  runButtonV->setEnabled(true);
  runButtonV->setSize(132, 40);

  ButtonAction *runStaticButtonV = new ButtonAction(this, "Static Run");
  runStaticButtonV->setEnabled(true);
  runStaticButtonV->setSize(132, 40);

  ButtonAction *runButtonH = new ButtonAction(this, "Run");
  runButtonH->setEnabled(true);
  runButtonH->setSize(132, 40);

  ButtonAction *runStaticButtonH = new ButtonAction(this, "Static Run");
  runStaticButtonH->setEnabled(true);
  runStaticButtonH->setSize(132, 40);

  QWidget *verticalContainer = new QWidget(runButtonWidget);
  m_runVButtonLayout = new QVBoxLayout(verticalContainer);
  m_runVButtonLayout->setSpacing(4);
  m_runVButtonLayout->setContentsMargins(0, 0, 0, 0);
  m_runVButtonLayout->setAlignment(Qt::AlignCenter);
  m_runVButtonLayout->addWidget(runButtonV);
  m_runVButtonLayout->addWidget(runStaticButtonV);

  QWidget *horizontalContainer = new QWidget(runButtonWidget);
  m_runHButtonLayout = new QHBoxLayout(horizontalContainer);
  m_runHButtonLayout->setSpacing(4);
  m_runHButtonLayout->setContentsMargins(0, 0, 0, 0);
  m_runHButtonLayout->setAlignment(Qt::AlignCenter);
  m_runHButtonLayout->addWidget(runButtonH);
  m_runHButtonLayout->addWidget(runStaticButtonH);

  stackedLayout->addWidget(horizontalContainer);
  stackedLayout->addWidget(verticalContainer);
  stackedLayout->setCurrentIndex(0);

  connect(m_buttonToggle, &QPushButton::clicked, this,
          [this, stackedLayout, runButtonH, runStaticButtonH]() {
            m_isCollapsed = !m_isCollapsed;
            if (m_isCollapsed) {
              runButtonH->setSize(70, 40);
              runStaticButtonH->setSize(70, 40);
            } else {
              runButtonH->setSize(132, 40);
              runStaticButtonH->setSize(132, 40);
            }
            m_inputPanel->toggleCollapse(m_isCollapsed);
            m_outputPanel->toggleCollapse(m_isCollapsed);
            m_buttonToggle->toggleCollapse();
            stackedLayout->setCurrentIndex(m_isCollapsed ? 1 : 0);
            setFixedWidth(m_isCollapsed ? 160 : 320);
          });
  auto setupDynamicRunHandler = [this](ButtonAction *runBtn,
                                       ButtonAction *staticBtn) {
    return [this, runBtn, staticBtn]() {
      if (!m_trainSimulation->validateCsvVariables()) {
        MessageBoxWidget messagebox(
            "Alert", "Station distance is empty. Please upload station data",
            MessageBoxWidget::Warning);
        return;
      }
      QFuture<void> future = QtConcurrent::run([this]() {
        m_isSimulationError = false;
        m_trainSimulation->simulateDynamicTrainMovement();
      });
      updateButtonState(future, runBtn, staticBtn);
    };
  };

  auto setupStaticRunHandler = [this](ButtonAction *runBtn,
                                      ButtonAction *staticBtn) {
    return [this, runBtn, staticBtn]() {
      QFuture<void> future = QtConcurrent::run([this]() {
        m_isSimulationError = false;
        m_trainSimulation->simulateStaticTrainMovement();
      });
      updateButtonState(future, runBtn, staticBtn);
    };
  };

  connect(runButtonV, &ButtonAction::clicked, this,
          setupDynamicRunHandler(runButtonV, runStaticButtonV));
  connect(runStaticButtonV, &ButtonAction::clicked, this,
          setupStaticRunHandler(runButtonV, runStaticButtonV));
  connect(runButtonH, &ButtonAction::clicked, this,
          setupDynamicRunHandler(runButtonH, runStaticButtonH));
  connect(runStaticButtonH, &ButtonAction::clicked, this,
          setupStaticRunHandler(runButtonH, runStaticButtonH));

  m_buttonLayout->addWidget(runButtonWidget);
}

void LeftPanel::setupInputPageButtons() {
  m_inputPanel = new LeftPanelInputs(this, LeftPanelInputs::INPUT);
  connect(m_inputPanel, &LeftPanelInputs::buttonClicked, this,
          [this](int index) {
            m_currentIndex = index;
            emitNavigateSignal(index);
            m_inputPanel->updateCategoryButton(m_currentIndex);
            m_outputPanel->updateCategoryButton(m_currentIndex);
            m_outputPanel->setCurrentIndex(m_currentIndex - m_currentIndex - 1);
          });
  m_buttonLayout->addWidget(m_inputPanel);
}

void LeftPanel::setupOutputPageButtons() {
  m_outputPanel = new LeftPanelInputs(this, LeftPanelInputs::OUTPUT);
  connect(m_outputPanel, &LeftPanelInputs::buttonClicked, this,
          [this](int index) {
            m_currentIndex = index + 5;
            emitNavigateSignal(m_currentIndex);
            m_outputPanel->updateCategoryButton(m_currentIndex);
            m_inputPanel->updateCategoryButton(m_currentIndex);
            m_inputPanel->setCurrentIndex(m_currentIndex);
          });
  m_buttonLayout->addWidget(m_outputPanel);
}

void LeftPanel::updateButtonState(QFuture<void> future, ButtonAction *runButton,
                                  ButtonAction *runStaticButton) {
  runButton->setEnabled(false);
  runStaticButton->setEnabled(false);
  QTimer::singleShot(200, this, [this, runButton, runStaticButton, future]() {
    QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
    connect(
        watcher, &QFutureWatcher<void>::finished, this,
        [this, watcher, runStaticButton, runButton]() {
          runStaticButton->setEnabled(true);
          runButton->setEnabled(true);
          connect(m_trainSimulation, &TrainSimulationHandler::simulationError,
                  this, [this]() { m_isSimulationError = true; });
          if (!m_isSimulationError) {
            QSet<QString> warnings = m_trainSimulation->getSimulationWarnings();
            showSimMessageBox(warnings, false);
          } else {
            QSet<QString> errors = m_trainSimulation->getSimulationErrors();
            showSimMessageBox(errors, true);
          }
          watcher->deleteLater();
        });
    watcher->setFuture(future);
  });
}

void LeftPanel::showSimMessageBox(const QSet<QString> &warnings, bool isError) {
  QString title = "Simulation Completed";
  QString message;
  MessageBoxWidget::IconType iconType;
  bool isWarning = false;
  if (warnings.isEmpty() && !isError) {
    iconType = MessageBoxWidget::Information;
    message = "Simulation completed!";
  } else if (isError) {
    iconType = MessageBoxWidget::Critical;
    message = "Simulation completed with errors:\n";
    for (const QString &error : warnings) {
      message += "- " + error + "\n";
    }
  } else {
    iconType = MessageBoxWidget::Warning;
    message = "Simulation completed with warnings:\n";
    for (const QString &warning : warnings) {
      message += "- " + warning + "\n";
    }
  }
  MessageBoxWidget messageBox(title, message, iconType);
}

void LeftPanel::setupHeader() {

  QWidget *headerWidget = new QWidget(this);
  QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
  headerLayout->setContentsMargins(12, 12, 12, 12);
  headerLayout->setSpacing(16);
  headerLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  QLabel *iconLabel = new QLabel(this);
  QPixmap pixmap(":/icons/icons/trainSimulationAppLogo.png");
  iconLabel->setPixmap(
      pixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
  iconLabel->setFixedSize(40, 40);
  m_buttonToggle = new ButtonToggle(m_isCollapsed, this);
  headerLayout->addWidget(m_buttonToggle);
  headerLayout->addWidget(iconLabel);
  m_mainLayout->addWidget(headerWidget);
}
