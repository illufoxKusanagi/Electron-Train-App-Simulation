#ifndef MOVING_DATA_H
#define MOVING_DATA_H

struct MovingData {
  double acc = 0;
  double acc_si = 0;
  double decc = 0;
  double decc_si = 0;
  double acc_start;
  double decc_start;
  double decc_emergency;
  double v = 0;
  double v_si = 0;
  double v_limit;
  double v_p1;
  double v_p2;
  double v_b1;
  double v_b2;
  double v_diffCoast;
  double time = 0;
  double x = 0;
  double time_total = 0;
  double x_total = 0;
  double x_station = 100;
};

#endif // MOVING_DATA_H
