#ifndef CSV_VARIABLES_HANDLER_H
#define CSV_VARIABLES_HANDLER_H

#include "core/appcontext.h"
#include <QObject>
#include <QSet>

class CsvVariableHandler : public QObject {
  Q_OBJECT
public:
  explicit CsvVariableHandler(AppContext &context,
                              QSet<QString> *simulationWarnings = nullptr);

  int setSlopeIndex(int slopeIndex, double distanceTravelled);
  int setRadiusIndex(int radiusIndex, double distanceTravelled);
  int setMaxSpeedIndex(int maxSpeedIndex, double distanceTravelled);
  int setEffGearIndex(int effGearIndex, double speed);
  int setEffVvvfIndex(int effVvvfIndex, double speed);
  int setEffMotorIndex(int effMotorIndex, double speed);
  int setLineVoltageIndex(int lineVoltageIndex, double speed);
  int setMotorVoltageIndex(int motorVoltageIndex, double speed);
  double setSlopeData(int slopeIndex, double distanceTravelled);
  double setRadiusData(int radiusIndex, double distanceTravelled);
  double setMaxSpeedData(int maxSpeedIndex, double distanceTravelled);
  double setEffGearData(int effGearIndex, double speed);
  double setEffVvvfData(int effVvvfIndex, double speed);
  double setEffMotorData(int effMotorIndex, double speed);
  double setLineVoltageData(int lineVoltageIndex, double speed);
  double setMotorVoltageData(int motorVoltageIndex, double speed);
  double setDwellTimeData(int dwellTimeIndex);

private:
  StationData *stationData;
  EfficiencyData *efficiencyData;
  EnergyData *energyData;
  QSet<QString> *m_simulationWarnings;
};

#endif // CSV_VARIABLES_HANDLER_H
