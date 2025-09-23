#ifndef CURRENT_HANDLER_H
#define CURRENT_HANDLER_H

#include "core/appcontext.h"

class CurrentHandler {
public:
  explicit CurrentHandler(AppContext &context);
  double calculateVvvfCurrent(double vol_line);
  double calculateCatenaryCurrent(double vol_line);

private:
  EnergyData *energyData;
  PowerData *powerData;
};

#endif // CURRENT_HANDLER_H
