#include "train_data_handler.h"

TrainDataHandler::TrainDataHandler(AppContext *context, QObject *parent)
    : QObject(parent), m_loadData(context->loadData.data()),
      m_massData(context->massData.data()),
      m_trainData(context->trainData.data()) {}

void TrainDataHandler::setNumberTractionMotorValue(double numberTractionMotor) {
  if (m_trainData) {
    m_trainData->n_tm = numberTractionMotor;
  }
}

void TrainDataHandler::setNumberAxleValue(double numberAxle) {
  if (m_trainData) {
    m_trainData->n_axle = numberAxle;
  }
}

void TrainDataHandler::setWheelDiameterValue(double wheelDiameter) {
  if (m_trainData) {
    m_trainData->wheel = wheelDiameter;
  }
}

void TrainDataHandler::setGearRatioValue(double gearRatio) {
  if (m_trainData) {
    m_trainData->gearRatio = gearRatio;
  }
}

void TrainDataHandler::setLoadValue(double load) {
  if (m_loadData) {
    m_loadData->load = load;
  }
}

void TrainDataHandler::setPassengerWeightValue(double passengerWeight) {
  if (m_loadData) {
    m_loadData->mass_P = passengerWeight;
  }
}

void TrainDataHandler::setInertialCoefficientTrailerValue(
    double inertialCoefficientTrailer) {
  if (m_massData) {
    m_massData->i_T = inertialCoefficientTrailer;
  }
}

void TrainDataHandler::setInertialCoefficientMotorValue(
    double inertialCoefficientMotor) {
  if (m_massData) {
    m_massData->i_M = inertialCoefficientMotor;
  }
}

// void TrainDataHandler::setTypeValue(
//     const QMap<QString, InputWidget *> &inputWidgets) {
//   if (inputWidgets.contains("Tc")) {
//     m_trainData->n_Tc = inputWidgets["Tc"]->getValue();
//   }
//   if (inputWidgets.contains("M1")) {
//     m_trainData->n_M1 = inputWidgets["M1"]->getValue();
//   }
//   if (inputWidgets.contains("M2")) {
//     m_trainData->n_M2 = inputWidgets["M2"]->getValue();
//   }
//   if (inputWidgets.contains("T1")) {
//     m_trainData->n_T1 = inputWidgets["T1"]->getValue();
//   }
//   if (inputWidgets.contains("T2")) {
//     m_trainData->n_T2 = inputWidgets["T2"]->getValue();
//   }
//   if (inputWidgets.contains("T3")) {
//     m_trainData->n_T3 = inputWidgets["T3"]->getValue();
//   }
// }

// void TrainDataHandler::setMassValue(
//     const QMap<QString, InputWidget *> &inputWidgets) {
//   if (inputWidgets.contains("Tc")) {
//     m_massData->mass_TC = inputWidgets["Tc"]->getValue();
//   }
//   if (inputWidgets.contains("M1")) {
//     m_massData->mass_M1 = inputWidgets["M1"]->getValue();
//   }
//   if (inputWidgets.contains("M2")) {
//     m_massData->mass_M2 = inputWidgets["M2"]->getValue();
//   }
//   if (inputWidgets.contains("T1")) {
//     m_massData->mass_T1 = inputWidgets["T1"]->getValue();
//   }
//   if (inputWidgets.contains("T2")) {
//     m_massData->mass_T2 = inputWidgets["T2"]->getValue();
//   }
//   if (inputWidgets.contains("T3")) {
//     m_massData->mass_T3 = inputWidgets["T3"]->getValue();
//   }
// }

// void TrainDataHandler::setPassengerValue(
//     const QMap<QString, InputWidget *> &inputWidgets) {
//   if (inputWidgets.contains("Tc")) {
//     m_loadData->n_PTc = inputWidgets["Tc"]->getValue();
//   }
//   if (inputWidgets.contains("M1")) {
//     m_loadData->n_PM1 = inputWidgets["M1"]->getValue();
//   }
//   if (inputWidgets.contains("M2")) {
//     m_loadData->n_PM2 = inputWidgets["M2"]->getValue();
//   }
//   if (inputWidgets.contains("T1")) {
//     m_loadData->n_PT1 = inputWidgets["T1"]->getValue();
//   }
//   if (inputWidgets.contains("T2")) {
//     m_loadData->n_PT2 = inputWidgets["T2"]->getValue();
//   }
//   if (inputWidgets.contains("T3")) {
//     m_loadData->n_PT3 = inputWidgets["T3"]->getValue();
//   }
// }

void TrainDataHandler::setNumberCarValue(double numberCar) {
  if (m_trainData) {
    m_trainData->n_car = numberCar;
  }
}

void TrainDataHandler::setTrainsetLengthValue(double carLength) {
  if (m_trainData) {
    m_trainData->trainsetLength = carLength * m_trainData->n_car;
  }
}

void TrainDataHandler::setDegradedTrainMotorValues(double numberM1,
                                                   double numberM2) {
  if (m_trainData) {
    m_trainData->n_M1_disabled = numberM1;
    m_trainData->n_M2_disabled = numberM2;
  }
}

// void TrainDataHandler::storeFormInputs(
//     const QMap<QString, InputWidget *> &inputWidgets) {
//   if (inputWidgets.contains("Number of Traction Motor")) {
//     setNumberTractionMotorValue(
//         inputWidgets["Number of Traction Motor"]->getValue());
//   }
//   if (inputWidgets.contains("Number of Axle")) {
//     setNumberAxleValue(inputWidgets["Number of Axle"]->getValue());
//   }
//   if (inputWidgets.contains("Wheel Diameter (mm)")) {
//     setWheelDiameterValue(inputWidgets["Wheel Diameter (mm)"]->getValue());
//   }
//   if (inputWidgets.contains("Gear Ratio")) {
//     setGearRatioValue(inputWidgets["Gear Ratio"]->getValue());
//   }
//   if (inputWidgets.contains("Load per Car(ton)")) {
//     setLoadValue(inputWidgets["Load per Car(ton)"]->getValue());
//   }
//   if (inputWidgets.contains("Passenger Weight (kg)")) {
//     setPassengerWeightValue(inputWidgets["Passenger Weight (kg)"]->getValue());
//   }
//   if (inputWidgets.contains("Inertial Coefficient Trailer")) {
//     setInertialCoefficientTrailerValue(
//         inputWidgets["Inertial Coefficient Trailer"]->getValue());
//   }
//   if (inputWidgets.contains("Inertial Coefficient Motor")) {
//     setInertialCoefficientMotorValue(
//         inputWidgets["Inertial Coefficient Motor"]->getValue());
//   }
// }