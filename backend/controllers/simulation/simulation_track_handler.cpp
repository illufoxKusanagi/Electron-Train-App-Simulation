#include "simulation_track_handler.h"

SimulationTrackHandler::SimulationTrackHandler(AppContext &context)
    : constantData(context.constantData.data()),
      trainData(context.trainData.data()),
      movingData(context.movingData.data()),
      simulationDatas(context.simulationDatas.data()) {}

double SimulationTrackHandler::calculateBrakingTrack(double speed) {
  double m_speed = speed / constantData->cV;
  double brakingTrack = (pow(m_speed, 2) / (2 * movingData->decc_start));
  return brakingTrack;
}

double SimulationTrackHandler::calculateBrakingEmergencyTrack() {
  double speed = simulationDatas->trainSpeedsSi.last();
  double brakingTrack = (speed * constantData->t_reaction) +
                        (pow(speed, 2) / (2 * movingData->decc_emergency));
  return brakingTrack;
}

double SimulationTrackHandler::calculateNormalSimulationTrack(double speed) {
  double poweringDistance = simulationDatas->distanceTotal.last();
  double trainLength = trainData->trainsetLength;
  double brakingDistance = calculateBrakingTrack(speed);
  return poweringDistance + trainLength + brakingDistance;
}

double SimulationTrackHandler::calculateEmergencyNormalSimulationTrack() {
  double poweringDistance = simulationDatas->distanceTotal.last();
  double trainLength = trainData->trainsetLength;
  double brakingDistance = calculateBrakingEmergencyTrack();
  return poweringDistance + trainLength + brakingDistance;
}

double SimulationTrackHandler::calculateDelaySimulationTrack(double speed) {
  double poweringDistance = simulationDatas->distanceTotal.last();
  double trainLength = trainData->trainsetLength;
  double brakingDistance = calculateBrakingTrack(speed);
  return poweringDistance + brakingDistance + trainLength +
         (simulationDatas->trainSpeedsSi.last() * constantData->t_delay) +
         (0.5 * simulationDatas->accelerationsSi.last() *
          pow(constantData->t_delay, 2));
}

double SimulationTrackHandler::calculateEmergencyDelaySimulationTrack() {
  double poweringDistance = simulationDatas->distanceTotal.last();
  double trainLength = trainData->trainsetLength;
  double brakingDistance = calculateBrakingEmergencyTrack();
  return poweringDistance + brakingDistance + trainLength +
         (simulationDatas->trainSpeedsSi.last() * constantData->t_delay) +
         (0.5 * simulationDatas->accelerationsSi.last() *
          pow(constantData->t_delay, 2));
}

double SimulationTrackHandler::calculateSafetySimulationTrack(double speed) {
  return 1.2 * calculateDelaySimulationTrack(speed);
}

double SimulationTrackHandler::calculateEmergencySafetySimulationTrack() {
  return 1.2 * calculateEmergencyDelaySimulationTrack();
}

double SimulationTrackHandler::calculateOdo(double speed) {
  double distance =
      simulationDatas->odos.isEmpty() ? 0 : simulationDatas->odos.last();
  double brakingDistance = calculateBrakingTrack(speed);
  double calculatedDistance = simulationDatas->distance.isEmpty()
                                  ? 0
                                  : simulationDatas->distance.last();
  return distance + brakingDistance + calculatedDistance;
}
