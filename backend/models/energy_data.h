#ifndef ENERGY_DATA_H
#define ENERGY_DATA_H
#include <vector>

struct EnergyData {
  double stat_vol_line = 0;
  std::vector<double> vol_line;
  std::vector<double> v_vol_line;
  double stat_vol_motor = 0;
  std::vector<double> vol_motor;
  std::vector<double> v_vol_motor;
  double e_motor = 0;
  double e_pow = 0;
  double e_reg = 0;
  double e_aps = 0;
  double e_catenary = 0;
  double curr_catenary = 0;
  double curr_vvvf = 0;
};

#endif // ENERGY_DATA_H
