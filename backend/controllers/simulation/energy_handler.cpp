#include "energy_handler.h"

EnergyHandler::EnergyHandler(AppContext &context)
    : simulationDatas(context.simulationDatas.data()),
      powerData(context.powerData.data()) {}

double EnergyHandler::calculateEnergyConsumption(int i) {
  if (simulationDatas->time.isEmpty())
    return 0;
  return powerData->p_motorOut / 3600 * simulationDatas->time[i];
}

double EnergyHandler::calculateEnergyOfPowering(int i) {
  if (simulationDatas->time.isEmpty())
    return 0;
  return powerData->p_catenary / 3600 * simulationDatas->time[i];
}

double EnergyHandler::calculateEnergyRegeneration(int i) {
  if (simulationDatas->time.isEmpty())
    return 0;
  return powerData->p_catenary / 3600 * simulationDatas->time[i];
}

double EnergyHandler::calculateEnergyOfAps(int i) {
  if (simulationDatas->time.isEmpty())
    return 0;
  return powerData->p_aps / 3600 * simulationDatas->time[i];
}
