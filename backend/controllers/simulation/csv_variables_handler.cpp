#include "csv_variables_handler.h"

CsvVariableHandler::CsvVariableHandler(AppContext &context,
                                       QSet<QString> *simulationWarnings)
    : stationData(context.stationData.data()),
      efficiencyData(context.efficiencyData.data()),
      energyData(context.energyData.data()),
      m_simulationWarnings(simulationWarnings) {}

int CsvVariableHandler::setSlopeIndex(int slopeIndex,
                                      double distanceTravelled) {
  if (!stationData->slope.empty()) {
    if (distanceTravelled >= stationData->x_slopeEnd[slopeIndex]) {
      slopeIndex++;
    }
    return slopeIndex;
  } else if (slopeIndex >= stationData->slope.size()) {
    return slopeIndex - 1;
  }
  return 0;
}

int CsvVariableHandler::setRadiusIndex(int radiusIndex,
                                       double distanceTravelled) {
  if (!stationData->radius.empty()) {
    if (distanceTravelled >= stationData->x_radiusEnd[radiusIndex]) {
      radiusIndex++;
    }
    return radiusIndex;
  } else if (radiusIndex >= stationData->radius.size()) {
    return radiusIndex - 1;
  }
  return 0;
}

int CsvVariableHandler::setMaxSpeedIndex(int maxSpeedIndex,
                                         double distanceTravelled) {
  if (!stationData->v_limit.empty()) {
    if (distanceTravelled >= stationData->x_v_limitEnd[maxSpeedIndex]) {
      maxSpeedIndex++;
    }
    return maxSpeedIndex;
  } else if (maxSpeedIndex >= stationData->v_limit.size()) {
    return maxSpeedIndex - 1;
  }
  return 0;
}

int CsvVariableHandler::setEffGearIndex(int effGearIndex, double speed) {
  if (!efficiencyData->eff_gear.empty()) {
    if (speed >= efficiencyData->v_eff_gear[effGearIndex]) {
      effGearIndex++;
    } else if (speed < efficiencyData->v_eff_gear[effGearIndex] &&
               effGearIndex > 0) {
      return effGearIndex - 1;
    }
    return effGearIndex;
  }
  return 0;
}

int CsvVariableHandler::setEffVvvfIndex(int effVvvfIndex, double speed) {
  if (!efficiencyData->eff_vvvf.empty()) {
    if (speed >= efficiencyData->v_eff_vvvf[effVvvfIndex]) {
      effVvvfIndex++;
    } else if (speed < efficiencyData->v_eff_vvvf[effVvvfIndex] &&
               effVvvfIndex > 0) {
      return effVvvfIndex - 1;
    }
    return effVvvfIndex;
  }
  return 0;
}

int CsvVariableHandler::setEffMotorIndex(int effMotorIndex, double speed) {
  if (!efficiencyData->eff_motor.empty()) {
    if (speed >= efficiencyData->v_eff_motor[effMotorIndex]) {
      effMotorIndex++;
    } else if (speed < efficiencyData->v_eff_motor[effMotorIndex] &&
               effMotorIndex > 0) {
      return effMotorIndex - 1;
    }
    return effMotorIndex;
  }
  return 0;
}

int CsvVariableHandler::setLineVoltageIndex(int lineVoltageIndex,
                                            double speed) {
  if (!energyData->vol_line.empty()) {
    if (speed >= energyData->v_vol_line[lineVoltageIndex]) {
      lineVoltageIndex++;
    } else if (speed < energyData->v_vol_line[lineVoltageIndex] &&
               lineVoltageIndex > 0) {
      return lineVoltageIndex - 1;
    }
    return lineVoltageIndex;
  }
  return 0;
}

int CsvVariableHandler::setMotorVoltageIndex(int motorVoltageIndex,
                                             double speed) {
  if (!energyData->vol_motor.empty()) {
    if (speed >= energyData->v_vol_motor[motorVoltageIndex]) {
      motorVoltageIndex++;
    } else if (speed < energyData->v_vol_motor[motorVoltageIndex] &&
               motorVoltageIndex > 0) {
      return motorVoltageIndex - 1;
    }
    return motorVoltageIndex;
  }
  return 0;
}

double CsvVariableHandler::setSlopeData(int slopeIndex,
                                        double distanceTravelled) {
  if (!stationData->slope.empty() && slopeIndex < stationData->slope.size()) {
    if (distanceTravelled >= stationData->x_slopeEnd[slopeIndex]) {
      return stationData->slope[slopeIndex++];
    } else {
      return stationData->slope[slopeIndex];
    }
  } else if (stationData->slope.empty()) {
    m_simulationWarnings->insert("Slope csv data is empty.");
  } else {
    m_simulationWarnings->insert(
        "Attempted to access slope data beyond range.");
  }
  return stationData->stat_slope;
}

double CsvVariableHandler::setRadiusData(int radiusIndex,
                                         double distanceTravelled) {
  if (!stationData->radius.empty() &&
      radiusIndex < stationData->radius.size()) {
    if (distanceTravelled >= stationData->x_radiusEnd[radiusIndex]) {
      return stationData->radius[radiusIndex++];
    } else {
      return stationData->radius[radiusIndex];
    }
  } else if (stationData->radius.empty()) {
    m_simulationWarnings->insert("Radius csv data is empty.");
  } else {
    m_simulationWarnings->insert(
        "Attempted to access radius data beyond range.");
  }
  return stationData->stat_radius;
}

double CsvVariableHandler::setMaxSpeedData(int maxSpeedIndex,
                                           double distanceTravelled) {
  if (!stationData->v_limit.empty() &&
      maxSpeedIndex < stationData->v_limit.size()) {
    if (distanceTravelled >= stationData->x_v_limitEnd[maxSpeedIndex]) {
      return stationData->v_limit[maxSpeedIndex++];
    } else {
      return stationData->v_limit[maxSpeedIndex];
    }
  } else if (stationData->v_limit.empty()) {
    m_simulationWarnings->insert("Speed limit csv data is empty.");
  } else {
    m_simulationWarnings->insert(
        "Attempted to access max speed data beyond range.");
  }
  return stationData->stat_v_limit;
}

double CsvVariableHandler::setEffVvvfData(int effVvvfIndex, double speed) {
  if (effVvvfIndex < efficiencyData->eff_vvvf.size()) {
    if (speed >= efficiencyData->v_eff_vvvf[effVvvfIndex]) {
      return efficiencyData->eff_vvvf[effVvvfIndex++];
    } else if (speed < efficiencyData->v_eff_vvvf[effVvvfIndex] &&
               effVvvfIndex > 0) {
      return efficiencyData->eff_vvvf[effVvvfIndex - 1];
    } else {
      return efficiencyData->eff_vvvf[effVvvfIndex];
    }
  } else if (efficiencyData->eff_vvvf.empty()) {
    m_simulationWarnings->insert("VVVF efficiency csv data is empty.");
  } else {
    m_simulationWarnings->insert(
        "Attempted to access VVVF efficiency data beyond range.");
  }
  return efficiencyData->stat_eff_vvvf;
}

double CsvVariableHandler::setEffGearData(int effGearIndex, double speed) {
  if (!efficiencyData->eff_gear.empty() &&
      effGearIndex < efficiencyData->eff_gear.size()) {
    if (speed >= efficiencyData->v_eff_gear[effGearIndex]) {
      return efficiencyData->eff_gear[effGearIndex++];
    } else if (speed < efficiencyData->v_eff_gear[effGearIndex] &&
               effGearIndex > 0) {
      return efficiencyData->eff_gear[effGearIndex - 1];
    } else {
      return efficiencyData->eff_gear[effGearIndex];
    }
  } else if (efficiencyData->eff_gear.empty()) {
    m_simulationWarnings->insert("Gear efficiency csv data is empty.");
  } else {
    m_simulationWarnings->insert(
        "Attempted to access gear efficiency data beyond range.");
  }
  return efficiencyData->stat_eff_gear;
}

double CsvVariableHandler::setEffMotorData(int effMotorIndex, double speed) {
  if (!efficiencyData->eff_motor.empty() &&
      effMotorIndex < efficiencyData->eff_motor.size()) {
    if (speed >= efficiencyData->v_eff_motor[effMotorIndex]) {
      return efficiencyData->eff_motor[effMotorIndex++];
    } else if (speed < efficiencyData->v_eff_motor[effMotorIndex] &&
               effMotorIndex > 0) {
      return efficiencyData->eff_motor[effMotorIndex - 1];
    } else {
      return efficiencyData->eff_motor[effMotorIndex];
    }
  } else if (efficiencyData->eff_motor.empty()) {
    m_simulationWarnings->insert("Motor efficiency csv data is empty.");
  } else {
    m_simulationWarnings->insert(
        "Attempted to access motor efficiency data beyond range.");
  }
  return efficiencyData->stat_eff_motor;
}

double CsvVariableHandler::setLineVoltageData(int lineVoltageIndex,
                                              double speed) {
  if (!energyData->vol_line.empty() &&
      lineVoltageIndex < energyData->vol_line.size()) {
    if (speed >= energyData->v_vol_line[lineVoltageIndex]) {
      return energyData->vol_line[lineVoltageIndex++];
    } else if (speed < energyData->v_vol_line[lineVoltageIndex] &&
               lineVoltageIndex > 0) {
      return energyData->vol_line[lineVoltageIndex - 1];
    } else {
      return energyData->vol_line[lineVoltageIndex];
    }
  } else if (energyData->vol_line.empty()) {
    m_simulationWarnings->insert("Line voltage csv data is empty.");
  } else {
    m_simulationWarnings->insert(
        "Attempted to access line voltage data beyond range.");
  }
  return energyData->stat_vol_line;
}

double CsvVariableHandler::setMotorVoltageData(int motorVoltageIndex,
                                               double speed) {
  if (!energyData->vol_motor.empty() &&
      motorVoltageIndex < energyData->vol_motor.size()) {
    if (speed >= energyData->v_vol_motor[motorVoltageIndex]) {
      return energyData->vol_motor[motorVoltageIndex++];
    } else if (speed < energyData->v_vol_motor[motorVoltageIndex] &&
               motorVoltageIndex > 0) {
      return energyData->vol_motor[motorVoltageIndex - 1];
    } else {
      return energyData->vol_motor[motorVoltageIndex];
    }
  } else if (energyData->vol_motor.empty()) {
    m_simulationWarnings->insert("Motor voltage csv data is empty.");
  } else {
    m_simulationWarnings->insert(
        "Attempted to access motor voltage data beyond range.");
  }
  return energyData->stat_vol_motor;
}

double CsvVariableHandler::setDwellTimeData(int dwellTimeIndex) {
  if (!stationData->dwellTime.empty() &&
      dwellTimeIndex < stationData->dwellTime.size()) {
    return stationData->dwellTime[dwellTimeIndex];
  } else if (stationData->dwellTime.empty()) {
    m_simulationWarnings->insert("Dwell time csv data is empty.");
  } else {
    m_simulationWarnings->insert(
        "Attempted to access dwell time data beyond range.");
  }
  return stationData->stat_dwellTime;
}