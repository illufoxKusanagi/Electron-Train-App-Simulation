#ifndef SIMULATION_TRACK_HANDLER_H
#define SIMULATION_TRACK_HANDLER_H

#include "core/appcontext.h"
#include <QObject>

class SimulationTrackHandler : public QObject {
  Q_OBJECT
public:
  explicit SimulationTrackHandler(AppContext &context);
  double calculateBrakingTrack(double speed);
  double calculateBrakingEmergencyTrack();
  double calculateNormalSimulationTrack(double speed);
  double calculateEmergencyNormalSimulationTrack();
  double calculateDelaySimulationTrack(double speed);
  double calculateEmergencyDelaySimulationTrack();
  double calculateSafetySimulationTrack(double speed);
  double calculateEmergencySafetySimulationTrack();
  double calculateOdo(double speed);

private:
  ConstantData *constantData;
  TrainData *trainData;
  MovingData *movingData;
  SimulationDatas *simulationDatas;
};

#endif // SIMULATION_TRACK_HANDLER_H
