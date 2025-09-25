#ifndef CHART_WIDGET_H
#define CHART_WIDGET_H

#include "controllers/output/dynamic_simulation_chart_handler.h"
#include "controllers/output/output_table_handler.h"
#include "controllers/output/save_button_handler.h"
#include "controllers/output/static_simulation_chart_handler.h"
#include "controllers/simulation/tractive_effort_handler.h"
#include "controllers/simulation/train_simulation_handler.h"
#include "core/appcontext.h"
#include "styles/colors.h"
#include "styles/text_style.h"
#include "widgets/button_action.h"
#include "widgets/button_pagination.h"
#include "widgets/message_box_widget.h"
#include <QAbstractSeries>
#include <QFileDialog>
#include <QFont>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QTableView>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QValueAxis>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

class ChartWidget : public QWidget {
  Q_OBJECT
public:
  explicit ChartWidget(QWidget *parent = nullptr, QString chartTitle = "",
                       QString seriesName = "",
                       TrainSimulationHandler *trainSimulation = nullptr,
                       AppContext *context = nullptr);
  void addSeries(const QString &name, const QColor &color);
  void updateChart();
  void updateStaticChart();

private slots:
  void onSimulationCompleted();
  void onStaticSimulationCompleted();

private:
  QVBoxLayout *mainLayout;
  QWidget *m_chartWidget;
  QVBoxLayout *m_chartLayout;
  TrainSimulationHandler *m_trainSimulation;
  QString m_chartTitle;
  QChart *m_chart;
  QList<QString> m_seriesToDisplay;
  QMap<QString, QColor> m_seriesColors;
  QTableWidget *m_table;
  SaveButtonHandler::SimulationType m_simulationType;
  TractiveEffortHandler *m_tractiveEffortHandler;
  SaveButtonHandler *m_saveButtonHandler;
  StaticSimulationChartHandler *m_staticSimulationChartHandler;
  DynamicSimulationChartHandler *m_dynamicSimulationChartHandler;
  OutputTableHandler *m_outputTableHandler;
  AppContext *context;

  void buildDummyLine(QString seriesName);
  void setupChart(QLineSeries *series, QString title);
  void createChartButtons(QChartView *chartView);
};

#endif // CHART_WIDGET_H
