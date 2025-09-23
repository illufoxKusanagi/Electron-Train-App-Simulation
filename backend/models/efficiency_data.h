#ifndef EFFICIENCY_DATA_H
#define EFFICIENCY_DATA_H
#include <vector>

struct EfficiencyData {
  double stat_eff_gear;
  double stat_eff_motor;
  double stat_eff_vvvf;
  std::vector<double> eff_gear;
  std::vector<double> eff_motor;
  std::vector<double> eff_vvvf;
  std::vector<double> v_eff_gear;
  std::vector<double> v_eff_motor;
  std::vector<double> v_eff_vvvf;
};

#endif // EFFICIENCY_DATA_H
