#ifndef RESISTANCE_DATA_H
#define RESISTANCE_DATA_H

struct ResistanceData {
  double startRes;
  double slope;
  double radius;
  double r_train = 0;
  double r_slope = 0;
  double r_radius = 0;
  double r_run = 0;
  double f_res = 0;
  double f_resStart = 0;
  double f_resRunning = 0;
  double f_resRunningZero = 0;
  double f_resRunningFive = 0;
  double f_resRunningTen = 0;
  double f_resRunningTwentyFive = 0;
  double f_total = 0;
  double f_start = 0;
  double f_motor = 0;
  double f_brake = 0;
};

#endif // RESISTANCE_DATA_H
