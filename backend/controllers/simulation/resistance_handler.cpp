#include "resistance_handler.h"

ResistanceHandler::ResistanceHandler(AppContext &context)
    : resistanceData(context.resistanceData.data()),
      constantData(context.constantData.data()),
      massData(context.massData.data()), trainData(context.trainData.data()) {}

double ResistanceHandler::calculateResTrain(float m, float startRes) {
  resistanceData->r_train = (m * startRes) / 1000;
  return resistanceData->r_train;
}

double ResistanceHandler::calculateResSlope(float m, float slope) {
  resistanceData->r_slope = (m * constantData->g * slope) / 1000;
  return resistanceData->r_slope;
}

double ResistanceHandler::calculateResRadius(float m, float radius) {
  resistanceData->r_radius = (m * constantData->g * (6.0 / radius)) / 1000;
  return resistanceData->r_radius;
}

double ResistanceHandler::calculateStartRes(double slope, double radius) {
  resistanceData->r_train =
      calculateResTrain(massData->mass_totalLoad, resistanceData->startRes);
  resistanceData->r_slope =
      calculateResSlope(massData->mass_totalInertial, slope);
  resistanceData->r_radius =
      calculateResRadius(massData->mass_totalInertial, radius);
  return resistanceData->r_train + resistanceData->r_slope +
         resistanceData->r_radius;
}

double ResistanceHandler::calculateRunningRes(float v, double slope,
                                              double radius) {
  resistanceData->r_slope =
      calculateResSlope(massData->mass_totalInertial, slope);
  resistanceData->r_radius =
      calculateResRadius(massData->mass_totalInertial, radius);
  resistanceData->r_run =
      (1.0 / 1000.0) *
      (((1.65 + (0.0247 * v)) * (massData->mass_M * constantData->g)) +
       ((0.78 + (0.0028 * v)) * (massData->mass_T * constantData->g)) +
       (constantData->g * (0.028 + 0.0078 * (trainData->n_car - 1)) * (v * v)));
  return resistanceData->r_run + resistanceData->r_slope +
         resistanceData->r_radius;
}
