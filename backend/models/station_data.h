#ifndef STATION_DATA_H
#define STATION_DATA_H

#include <vector>

struct StationData {
  double stat_x_station = 0.0;
  double stat_v_limit = 0.0;
  double stat_slope = 0.0;
  double stat_radius = 0.0;
  double stat_dwellTime = 0.0;
  double stat_slope_1;
  double stat_slope_2;
  double stat_slope_3;
  double x_odo = 0.0;
  int n_station = 2;
  std::vector<double> x_station;
  std::vector<double> tot_x_station;
  std::vector<double> v_limit;
  std::vector<double> x_v_limitStart;
  std::vector<double> x_v_limitEnd;
  std::vector<double> slope;
  std::vector<double> x_slopeStart;
  std::vector<double> x_slopeEnd;
  std::vector<double> radius;
  std::vector<double> x_radiusStart;
  std::vector<double> x_radiusEnd;
  std::vector<double> x_section;
  std::vector<double> dwellTime;
};

#endif // STATION_DATA_H
