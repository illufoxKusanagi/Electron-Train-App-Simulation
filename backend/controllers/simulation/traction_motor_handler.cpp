#include "traction_motor_handler.h"

TractionMotorHandler::TractionMotorHandler(AppContext &context)
    : trainData(context.trainData.data()),
      resistanceData(context.resistanceData.data()),
      movingData(context.movingData.data()),
      trainMotorData(context.trainMotorData.data()) {}

double TractionMotorHandler::calculateTractionForce() {
  trainMotorData->tm_f = resistanceData->f_motor / trainData->n_tm;
  return trainMotorData->tm_f;
}

double TractionMotorHandler::calculateRpm() {
  trainMotorData->tm_rpm = (movingData->v * 1000 / 60 * trainData->gearRatio) /
                           ((M_PI * trainData->wheel) / 1000);
  return trainMotorData->tm_rpm;
}

double TractionMotorHandler::calculateTorque() {
  trainMotorData->tm_t = (resistanceData->f_motor * (trainData->wheel / 2000)) /
                         trainData->gearRatio;
  return trainMotorData->tm_t;
}

double TractionMotorHandler::calculateResistanceForcePerMotor(double f_res) {
  trainMotorData->tm_f_res = f_res / trainData->n_tm;
  return trainMotorData->tm_f_res;
}