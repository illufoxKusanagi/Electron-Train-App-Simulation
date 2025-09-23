#ifndef RESISTANCE_HANDLER_H
#define RESISTANCE_HANDLER_H

#include "core/appcontext.h"
#include <QObject>

class ResistanceHandler : public QObject {
  Q_OBJECT
public:
  explicit ResistanceHandler(AppContext &context);
  double calculateResTrain(float m, float startRes);
  double calculateResSlope(float m, float slope);
  double calculateResRadius(float m, float radius);
  double calculateStartRes(double slope, double radius);
  double calculateRunningRes(float v, double slope, double radius);
  double calculateTotalRes() {
    return resistanceData->r_train + resistanceData->r_slope +
           resistanceData->r_radius + resistanceData->r_run;
  }

private:
  ResistanceData *resistanceData;
  ConstantData *constantData;
  MassData *massData;
  TrainData *trainData;
};

#endif // RESISTANCE_HANDLER_H
