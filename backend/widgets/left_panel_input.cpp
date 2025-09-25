#include "left_panel_input.h"

LeftPanelInputs::LeftPanelInputs(QWidget *parent, PanelType type)
    : QWidget(parent), mainLayout(new QVBoxLayout(this)), m_type(type),
      m_buttonTypes(type == INPUT ? INPUT_BUTTON_TYPES : OUTPUT_BUTTON_TYPES),
      m_buttonNames(type == INPUT ? INPUT_BUTTON_NAMES : OUTPUT_BUTTON_NAMES) {
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->setSpacing(4);
  mainLayout->setAlignment(Qt::AlignCenter);
  m_categoryButton =
      new ButtonSidebar(this, "category", type == INPUT ? "Inputs" : "Outputs");
  m_categoryButton->setEnabled(m_currentIndex);
  QFrame *topSeparator = new QFrame();
  topSeparator->setFrameShape(QFrame::HLine);
  topSeparator->setFrameShadow(QFrame::Sunken);
  topSeparator->setFixedHeight(1);

  QFrame *bottomSeparator = new QFrame();
  bottomSeparator->setFrameShape(QFrame::HLine);
  bottomSeparator->setFrameShadow(QFrame::Sunken);
  bottomSeparator->setFixedHeight(1);

  mainLayout->addWidget(topSeparator);
  mainLayout->addWidget(m_categoryButton);
  setupButtons();
  mainLayout->addWidget(bottomSeparator);
  connect(m_categoryButton, &QPushButton::clicked, this,
          &::LeftPanelInputs::toggleButtons);
}

void LeftPanelInputs::setupButtons() {
  local_buttonContainer = new QWidget(this);
  local_buttonLayout = new QVBoxLayout(local_buttonContainer);
  local_buttonLayout->setContentsMargins(16, 0, 0, 0);
  for (int i = 0; i < m_buttonNames.size(); i++) {
    ButtonSidebar *button =
        new ButtonSidebar(this, m_buttonTypes[i], m_buttonNames[i]);
    button->setIconSize(40, 40);
    connect(button, &QPushButton::clicked, this, [this, i]() {
      m_currentIndex = i;
      updateButtonStates();
      emit buttonClicked(i);
    });
    m_sidebarButtons.append(button);
    local_buttonLayout->addWidget(button);
  }
  local_buttonContainer->setLayout(local_buttonLayout);
  mainLayout->addWidget(local_buttonContainer);
  updateButtonStates();
}

void LeftPanelInputs::updateCategoryButton(int index) {
  m_currentIndex = index;
  m_categoryButton->setEnabled(m_type == INPUT ? m_currentIndex <= 4
                                               : m_currentIndex > 4);
}

void LeftPanelInputs::setCurrentIndex(int index) {
  m_currentIndex = index;
  updateButtonStates();
}

void LeftPanelInputs::toggleButtons() {
  m_isShown = !m_isShown;
  m_categoryButton->updateIcon(m_isShown);
  local_buttonContainer->setVisible(m_isShown);
}

void LeftPanelInputs::updateButtonStates() {
  updateCategoryButton(m_currentIndex);
  for (int i = 0; i < m_sidebarButtons.size(); i++) {
    if (m_sidebarButtons[i]) {
      m_sidebarButtons[i]->setEnabled(i == m_currentIndex);
    }
  }
}

void LeftPanelInputs::onPageChanged(int pageIndex) {
  m_currentIndex = pageIndex;
  updateButtonStates();
}

void LeftPanelInputs::toggleCollapse(bool isCollapsed) {
  mainLayout->setAlignment(isCollapsed ? Qt::AlignCenter : Qt::AlignLeft);
  local_buttonLayout->setContentsMargins(isCollapsed ? 0 : 16, 0, 0, 0);
  for (auto *button : m_sidebarButtons) {
    if (button) {
      button->setLabelVisible(!isCollapsed);
    }
  }
}
const QStringList LeftPanelInputs::INPUT_BUTTON_NAMES = {
    "Constant Values", "Train Parameter", "Running Parameter",
    "Track Parameter", "Electrical Parameter"};

const QStringList LeftPanelInputs::INPUT_BUTTON_TYPES = {
    "constant", "train", "running", "track", "electrical"};

const QStringList LeftPanelInputs::OUTPUT_BUTTON_NAMES = {
    "Train Speed", "Traction Effort", "Train Power", "Train Track",
    "Train Consumption"};

const QStringList LeftPanelInputs::OUTPUT_BUTTON_TYPES = {
    "speed", "traction", "power", "track", "energy"};
