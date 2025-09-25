#include "chart_widget.h"

ChartWidget::ChartWidget(QWidget *parent, QString chartTitle,
                         QString seriesName,
                         TrainSimulationHandler *trainSimulation,
                         AppContext *context)
    : QWidget(parent), mainLayout(new QVBoxLayout(this)),
      m_chartLayout(nullptr), m_chartWidget(nullptr),
      m_trainSimulation(trainSimulation), m_chartTitle(chartTitle),
      m_simulationType(SaveButtonHandler::None), context(context) {
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->setSpacing(16);
  addSeries(seriesName, QColor(0, 114, 206));
  connect(m_trainSimulation, &TrainSimulationHandler::simulationCompleted, this,
          &ChartWidget::onSimulationCompleted);
  connect(m_trainSimulation, &TrainSimulationHandler::staticSimulationCompleted,
          this, &ChartWidget::onStaticSimulationCompleted);
  m_outputTableHandler =
      new OutputTableHandler(trainSimulation, mainLayout, chartTitle, context);
  chartTitle.contains("Track") ? m_outputTableHandler->setupTable()
                               : buildDummyLine(seriesName);
  m_saveButtonHandler =
      new SaveButtonHandler(m_trainSimulation, chartTitle, &m_simulationType);
  m_staticSimulationChartHandler = new StaticSimulationChartHandler(
      m_trainSimulation, m_chart, chartTitle, &m_simulationType, context);
  m_dynamicSimulationChartHandler = new DynamicSimulationChartHandler(
      m_trainSimulation, m_chart, chartTitle, &m_simulationType);
}

void ChartWidget::addSeries(const QString &name, const QColor &color) {
  if (!m_seriesToDisplay.contains(name)) {
    m_seriesToDisplay.append(name);
    m_seriesColors[name] = color;
  }
}

void ChartWidget::onSimulationCompleted() {
  m_simulationType = SaveButtonHandler::Dynamic;
  if (m_chartTitle.contains("Dynamic") || m_chartTitle.contains("Distance")) {
    m_dynamicSimulationChartHandler->updateChart();
  }
}

void ChartWidget::onStaticSimulationCompleted() {
  m_simulationType = SaveButtonHandler::Static;
  if (m_chartTitle.contains("Static")) {
    m_chartTitle.contains("Track")
        ? m_outputTableHandler->updateTable()
        : m_staticSimulationChartHandler->updateStaticChart();
  }
}
void ChartWidget::buildDummyLine(QString seriesName) {
  QLineSeries *series = new QLineSeries();
  series->setName(seriesName);
  series->append(0.0, 0.0);
  series->append(1.1, 2.1);
  series->append(1.9, 3.3);
  series->append(2.1, 2.1);
  series->append(2.9, 4.9);
  series->append(3.4, 3.0);
  series->append(4.1, 3.3);
  setupChart(series, m_chartTitle);
}

void ChartWidget::setupChart(QLineSeries *series, QString title) {
  m_chartWidget = new QWidget();
  m_chart = new QChart();
  m_chart->addSeries(series);
  m_chart->setTitle(title);
  m_chart->createDefaultAxes();

  QFont titleFont;
  titleFont.setPixelSize(20);
  titleFont.setWeight(QFont::DemiBold);
  m_chart->setTitleFont(titleFont);
  m_chart->setTitleBrush(QBrush(Colors::StandardBlack));

  QChartView *chartView = new QChartView(m_chart);
  chartView->setRenderHint(QPainter::Antialiasing);
  chartView->setFixedSize(860, 450);
  m_chartLayout = new QVBoxLayout(m_chartWidget);
  m_chartLayout->setContentsMargins(0, 0, 0, 0);
  m_chartLayout->setSpacing(16);
  m_chartLayout->addWidget(chartView, 0, Qt::AlignCenter);
  chartView->setStyleSheet("border: 1px solid " + Colors::Grey100.name() +
                           ";"
                           "border-radius: 12px;");
  m_chart->legend()->setVisible(true);
  m_chart->legend()->setAlignment(Qt::AlignBottom);
  m_chart->legend()->setFont(QFont("Roboto", 10));
  m_chart->setPlotAreaBackgroundVisible(true);
  m_chart->setPlotAreaBackgroundBrush(QBrush(Colors::Secondary50));
  createChartButtons(chartView);
  mainLayout->addWidget(m_chartWidget);
}

void ChartWidget::createChartButtons(QChartView *chartView) {
  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->setAlignment(Qt::AlignRight);
  buttonLayout->setSpacing(16);
  ButtonAction *saveButton = new ButtonAction(this, "Save Chart");
  ButtonAction *saveCurrentData = new ButtonAction(this, "Save this data");
  ButtonAction *saveAllData = new ButtonAction(this, "Save all data");
  connect(saveButton, &QPushButton::clicked, this, [this, chartView]() {
    m_saveButtonHandler->onSaveButtonClicked(chartView);
  });
  connect(saveCurrentData, &QPushButton::clicked, this,
          [this]() { m_saveButtonHandler->onSaveCurrentDataClicked(); });
  connect(saveAllData, &QPushButton::clicked, this,
          [this]() { m_saveButtonHandler->onSaveAllDataClicked(); });

  saveButton->setEnabled(true);
  saveCurrentData->setEnabled(true);
  saveAllData->setEnabled(true);

  saveButton->setFixedSize(150, 48);
  saveCurrentData->setFixedSize(150, 48);
  saveAllData->setFixedSize(150, 48);

  buttonLayout->addWidget(saveButton);
  buttonLayout->addWidget(saveCurrentData);
  buttonLayout->addWidget(saveAllData);

  m_chartLayout->addLayout(buttonLayout);
}
