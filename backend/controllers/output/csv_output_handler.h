#ifndef CSV_OUTPUT_HANDLER_H
#define CSV_OUTPUT_HANDLER_H

#include "controllers/simulation/utility_handler.h"
// #include "widgets/message_box_widget.h"
// #include <QFileDialog>
#include <QObject>
#include <fstream>
#include <iostream>

class CsvOutputHandler : public QObject {
public:
  explicit CsvOutputHandler(SimulationDatas &simulationDatas);
  void printSimulationDatas();
  bool saveTrainSpeedData();
  bool saveTractionEffortData();
  bool saveTrainPowerData();
  bool saveTrainTrackData();
  bool saveEnergyConsumptionData();
  bool saveEnergyPoweringData();
  bool saveEnergyRegenData();
  bool saveEnergyApsData();

  double findMaxSpeed();
  double findMaxVvvfPower();
  double findMaxCatenaryPower();
  double findMaxVvvfCurrent();
  double findMaxCatenaryCurrent();
  double findMaxTractionEffort();
  double findDistanceTravelled();
  double findMaxEnergyConsumption();
  double findMaxEnergyRegen();
  double findMaxEnergyPowering();
  double findMaxEnergyAps();
  double findMaxCurrTime();
  double findMaxPowTime();
  double getAdhesion();

  int getAllDataNumber();
  int getTrainSpeedDataNumber();
  int getTractionEffortDataNumber();
  int getTrainPowerDataNumber();
  int getTrainTrackDataNumber();

private:
  SimulationDatas *simulationDatas;
  UtilityHandler *utilityHandler;
  QString m_csvHeader;
};

#endif // CSV_OUTPUT_HANDLER_H
