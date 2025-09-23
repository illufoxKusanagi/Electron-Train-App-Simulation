#include "current_handler.h"

CurrentHandler::CurrentHandler(AppContext &context)
    : powerData(context.powerData.data()),
      energyData(context.energyData.data()) {}

double CurrentHandler::calculateVvvfCurrent(double vol_line) {
  energyData->curr_vvvf = 1000 * (powerData->p_vvvfIn / vol_line);
  return energyData->curr_vvvf;
}

double CurrentHandler::calculateCatenaryCurrent(double vol_line) {
  energyData->curr_catenary = 1000 * (powerData->p_catenary / vol_line);
  return energyData->curr_catenary;
}