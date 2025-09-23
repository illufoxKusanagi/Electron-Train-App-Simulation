#include "running_data_handler.h"

RunningDataHandler::RunningDataHandler(AppContext *context, QObject *parent)
    : QObject(parent), m_movingData(context->movingData.data()),
      m_resistanceData(context->resistanceData.data()),
      m_trainData(context->trainData.data()) {}

void RunningDataHandler::setStartingResistance(double startRes) {
  if (m_resistanceData) {
    m_resistanceData->startRes = startRes;
  }
}

void RunningDataHandler::setWeakeningPoint1(double v_p1) {
  if (m_movingData) {
    m_movingData->v_p1 = v_p1;
  }
}

void RunningDataHandler::setWeakeningPoint2(double v_p2) {
  if (m_movingData) {
    m_movingData->v_p2 = v_p2;
  }
}

void RunningDataHandler::setWeakeningPoint3(double v_b1) {
  if (m_movingData) {
    m_movingData->v_b1 = v_b1;
  }
}

void RunningDataHandler::setWeakeningPoint4(double v_b2) {
  if (m_movingData) {
    m_movingData->v_b2 = v_b2;
  }
}

void RunningDataHandler::setDifferenceCoastingSpeed(double v_diffCoast) {
  if (m_movingData) {
    m_movingData->v_diffCoast = v_diffCoast;
  }
}

void RunningDataHandler::setEmergencyBrakeDeceleration(double decc_emergency) {
  if (m_movingData) {
    m_movingData->decc_emergency = decc_emergency;
  }
}

void RunningDataHandler::setAccelerationValue(double acceleration) {
  if (m_movingData) {
    m_movingData->acc_start = acceleration;
  }
}

void RunningDataHandler::setDecelerationValue(double decceleration) {
  if (m_movingData) {
    m_movingData->decc_start = decceleration;
  }
}

// void RunningDataHandler::storeFormInputs(
//     const QMap<QString, InputWidget *> &inputWidgets) {
//   if (inputWidgets.contains("Starting Resistance")) {
//     setStartingResistance(inputWidgets["Starting Resistance"]->getValue());
//   }
//   if (inputWidgets.contains("Weakening Point 1 (Powering)")) {
//     setWeakeningPoint1(
//         inputWidgets["Weakening Point 1 (Powering)"]->getValue());
//   }
//   if (inputWidgets.contains("Weakening Point 2 (Powering)")) {
//     setWeakeningPoint2(
//         inputWidgets["Weakening Point 2 (Powering)"]->getValue());
//   }
//   if (inputWidgets.contains("Weakening Point 3 (Braking)")) {
//     setWeakeningPoint3(inputWidgets["Weakening Point 3 (Braking)"]->getValue());
//   }
//   if (inputWidgets.contains("Weakening Point 4 (Braking)")) {
//     setWeakeningPoint4(inputWidgets["Weakening Point 4 (Braking)"]->getValue());
//   }
//   if (inputWidgets.contains("Difference Coasting Speed")) {
//     setDifferenceCoastingSpeed(
//         inputWidgets["Difference Coasting Speed"]->getValue());
//   }
//   if (inputWidgets.contains("Emergency Brake Deceleration")) {
//     setEmergencyBrakeDeceleration(
//         inputWidgets["Emergency Brake Deceleration"]->getValue());
//   }
// }
