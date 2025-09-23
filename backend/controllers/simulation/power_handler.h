#ifndef POWER_HANDLER_H
#define POWER_HANDLER_H

#include "core/appcontext.h"
#include <QObject>

class PowerHandler : public QObject {
  Q_OBJECT
public:
  explicit PowerHandler(AppContext &context);
  double calculatePowerWheel();
  double calculateOutputTractionMotor(double eff_gear);
  double calculateInputTractionMotor(double eff_motor);
  double calculatePowerInputOfVvvf(double eff_vvvf);
  double calculatePowerOfCatenary();

private:
  PowerData *powerData;
  ResistanceData *resistanceData;
  MovingData *movingData;
  EfficiencyData *efficiencyData;
  EnergyData *energyData;
  ConstantData *constantData;
};

#endif // POWER_HANDLER_H
