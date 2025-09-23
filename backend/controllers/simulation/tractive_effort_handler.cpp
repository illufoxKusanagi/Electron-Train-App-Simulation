#include "tractive_effort_handler.h"

TractiveEffortHandler::TractiveEffortHandler(AppContext &context)
    : massData(context.massData.data()),
      resistanceData(context.resistanceData.data()),
      trainData(context.trainData.data()),
      movingData(context.movingData.data()),
      trainMotorData(context.trainMotorData.data()),
      loadData(context.loadData.data()),
      constantData(context.constantData.data()) {}

double TractiveEffortHandler::calculateStartForce(float acc) {
  return massData->mass_totalInertial * acc + resistanceData->f_resStart;
}

double TractiveEffortHandler::calculateTotalForce(float v) {
  resistanceData->f_total =
      resistanceData->f_motor -
      (v <= 0 ? resistanceData->f_resStart : resistanceData->f_resRunning);
  return resistanceData->f_total;
}

double TractiveEffortHandler::calculateTotalBrakeForce() {
  resistanceData->f_total = resistanceData->f_motor;
  return resistanceData->f_total;
}

void TractiveEffortHandler::calculatePoweringForce(float acc, float v) {
  resistanceData->f_start = calculateStartForce(movingData->acc_start);
  if (v <= movingData->v_p1) {
    resistanceData->f_motor = resistanceData->f_start;
  } else if (v > movingData->v_p1 && v <= movingData->v_p2) {
    resistanceData->f_motor = (resistanceData->f_start * movingData->v_p1) / v;
  } else if (v > movingData->v_p2) {
    resistanceData->f_motor =
        (resistanceData->f_start * movingData->v_p1 * movingData->v_p2) /
        (v * v);
  }
}

void TractiveEffortHandler::calculateBrakingForce() {
  resistanceData->f_brake =
      massData->mass_totalInertial * movingData->decc_start;
  if (movingData->v < movingData->v_b1) {
    resistanceData->f_motor = -resistanceData->f_brake;
  } else if (movingData->v > movingData->v_b1 &&
             movingData->v <= movingData->v_b2) {
    resistanceData->f_motor =
        -((resistanceData->f_brake * movingData->v_b1) / movingData->v);
  } else if (movingData->v > movingData->v_b2) {
    resistanceData->f_motor =
        -((resistanceData->f_brake * movingData->v_b1 * movingData->v_b2) /
          (movingData->v * movingData->v));
  }
}

double TractiveEffortHandler::calculateAdhesion() {
  trainMotorData->tm_adh =
      (trainMotorData->tm_f * constantData->cF) /
      (((massData->mass_M2 + (loadData->mass_P_final * loadData->n_PM2)) *
        1000) /
       trainData->n_axle);
  return trainMotorData->tm_adh;
}
