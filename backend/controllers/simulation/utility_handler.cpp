#include "utility_handler.h"
#include <qdebug.h>

UtilityHandler::UtilityHandler(AppContext &context)
    : context(&context), simulationDatas(context.simulationDatas.data()) {}

void UtilityHandler::addSimulationDatas(int i, double time, QString phase) {
  simulationDatas->odos.append(context->stationData->x_odo);
  simulationDatas->tractionEfforts.append(context->resistanceData->f_motor);
  simulationDatas->vvvfPowers.append(context->powerData->p_vvvfIn);
  simulationDatas->catenaryPowers.append(context->powerData->p_catenary);
  simulationDatas->vvvfCurrents.append(context->energyData->curr_vvvf);
  simulationDatas->catenaryCurrents.append(context->energyData->curr_catenary);
  simulationDatas->distance.append(context->movingData->x);
  simulationDatas->timeTotal.append(time);
  simulationDatas->distanceTotal.append(context->movingData->x_total);
  simulationDatas->phase.append(phase);
  simulationDatas->motorForce.append(context->resistanceData->f_motor);
  simulationDatas->motorResistance.append(
      i == 0 ? context->resistanceData->f_resStart
             : context->resistanceData->f_resRunning);
  simulationDatas->totalResistance.append(context->resistanceData->f_total);
  simulationDatas->tractionForcePerMotor.append(context->trainMotorData->tm_f);
  simulationDatas->resistancePerMotor.append(context->trainMotorData->tm_f_res);
  simulationDatas->torque.append(context->trainMotorData->tm_t);
  simulationDatas->rpm.append(context->trainMotorData->tm_rpm);
  simulationDatas->powerWheel.append(context->powerData->p_wheel);
  simulationDatas->powerMotorOut.append(context->powerData->p_motorOut);
  simulationDatas->powerMotorIn.append(context->powerData->p_motorIn);
  simulationDatas->energyConsumptions.append(context->energyData->e_motor);
  simulationDatas->energyPowerings.append(context->energyData->e_pow);
  simulationDatas->energyRegenerations.append(context->energyData->e_reg);
  simulationDatas->energyAps.append(context->energyData->e_aps);
  simulationDatas->energyCatenaries.append(context->energyData->e_catenary);
  simulationDatas->motorResistancesZero.append(
      context->resistanceData->f_resRunningZero);
  simulationDatas->motorResistancesFive.append(
      context->resistanceData->f_resRunningFive);
  simulationDatas->motorResistancesTen.append(
      context->resistanceData->f_resRunningTen);
  simulationDatas->motorResistancesTwentyFive.append(
      context->resistanceData->f_resRunningTwentyFive);
}

void UtilityHandler::resetSimulation() {
  context->resistanceData->f_resStart = 0;
  context->resistanceData->f_resRunning = 0;
  context->resistanceData->f_motor = 0;
  context->resistanceData->f_start = 0;
  context->resistanceData->f_brake = 0;
  context->resistanceData->f_total = 0;
  context->resistanceData->f_total = 0;
  context->trainMotorData->tm_f_res = 0;
  context->trainMotorData->tm_f = 0;
  context->trainMotorData->tm_t = 0;
  context->movingData->acc = context->movingData->acc_start;
  context->movingData->acc_si = context->movingData->acc_start;
  context->movingData->v = 0;
  context->movingData->v_si = 0;
  context->powerData->p_wheel = 0;
  context->powerData->p_motorOut = 0;
  context->powerData->p_motorIn = 0;
  context->powerData->p_vvvfIn = 0;
  context->powerData->p_catenary = 0;
  context->trainMotorData->tm_rpm = 0;
  context->movingData->x = 0;
  context->movingData->time = 0;
  context->movingData->x_total = 0;
  context->movingData->time_total = 0;
  context->energyData->e_aps = 0;
  context->energyData->e_motor = 0;
  context->energyData->e_pow = 0;
  context->energyData->e_reg = 0;
  context->energyData->curr_catenary = 0;
  context->energyData->curr_vvvf = 0;
  context->energyData->e_catenary = 0;
  context->resistanceData->f_resRunningZero = 0;
  context->resistanceData->f_resRunningFive = 0;
  context->resistanceData->f_resRunningTen = 0;
  context->resistanceData->f_resRunningTwentyFive = 0;
  context->resistanceData->f_res = 0;
}

void UtilityHandler::clearSimulationDatas() {
  simulationDatas->trainSpeeds.clear();
  simulationDatas->trainSpeedsSi.clear();
  simulationDatas->accelerations.clear();
  simulationDatas->accelerationsSi.clear();
  simulationDatas->tractionEfforts.clear();
  simulationDatas->vvvfPowers.clear();
  simulationDatas->catenaryPowers.clear();
  simulationDatas->vvvfCurrents.clear();
  simulationDatas->catenaryCurrents.clear();
  simulationDatas->phase.clear();
  simulationDatas->motorForce.clear();
  simulationDatas->motorResistance.clear();
  simulationDatas->totalResistance.clear();
  simulationDatas->tractionForcePerMotor.clear();
  simulationDatas->resistancePerMotor.clear();
  simulationDatas->torque.clear();
  simulationDatas->rpm.clear();
  simulationDatas->powerWheel.clear();
  simulationDatas->powerMotorOut.clear();
  simulationDatas->powerMotorIn.clear();
  simulationDatas->distance.clear();
  simulationDatas->time.clear();
  simulationDatas->distanceTotal.clear();
  simulationDatas->timeTotal.clear();
  simulationDatas->energyConsumptions.clear();
  simulationDatas->energyPowerings.clear();
  simulationDatas->energyRegenerations.clear();
  simulationDatas->energyAps.clear();
  simulationDatas->energyCatenaries.clear();
  simulationDatas->mileages.clear();
  simulationDatas->motorResistancesZero.clear();
  simulationDatas->motorResistancesFive.clear();
  simulationDatas->motorResistancesTen.clear();
  simulationDatas->motorResistancesTwentyFive.clear();
  simulationDatas->slopes.clear();
  simulationDatas->radiuses.clear();
  simulationDatas->speedLimits.clear();
}
