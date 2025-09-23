#ifndef TRACTION_MOTOR_HANDLER_H
#define TRACTION_MOTOR_HANDLER_H

#include "core/appcontext.h"
#include <QObject>

class TractionMotorHandler : public QObject {
  Q_OBJECT
public:
  explicit TractionMotorHandler(AppContext &context);
  double calculateTractionForce();
  double calculateTorque();
  double calculateRpm();
  double calculateResistanceForcePerMotor(double f_res);

private:
  TrainData *trainData;
  ResistanceData *resistanceData;
  MovingData *movingData;
  TrainMotorData *trainMotorData;
};

#endif // TRACTION_MOTOR_HANDLER_H
