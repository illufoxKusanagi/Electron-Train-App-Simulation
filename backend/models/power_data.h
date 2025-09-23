#ifndef POWER_DATA_H
#define POWER_DATA_H

struct PowerData {
  double p_wheel = 0;
  double p_motorOut = 0;
  double p_motorIn = 0;
  double p_vvvfIn = 0;
  double p_catenary = 0;
  double p_aps = 0;
  double stat_p_aps = 0;
};

#endif // POWER_DATA_H
