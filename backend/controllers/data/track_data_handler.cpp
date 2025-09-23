#include "track_data_handler.h"

TrackDataHandler::TrackDataHandler(AppContext *context, QObject *parent)
    : QObject(parent), m_movingData(context->movingData.data()),
      m_resistanceData(context->resistanceData.data()),
      m_stationData(context->stationData.data()) {}

void TrackDataHandler::setMaxSpeedValue(double maxSpeed) {
  if (m_stationData) {
    m_stationData->stat_v_limit = maxSpeed;
  }
}

void TrackDataHandler::setStationDistanceValue(double stationDistance) {
  if (m_stationData) {
    m_stationData->stat_x_station = stationDistance;
  }
}

void TrackDataHandler::setSlopeValue(double slope) {
  if (m_stationData) {
    m_stationData->stat_slope = slope;
  }
}

void TrackDataHandler::setRadiusValue(double radius) {
  if (m_stationData) {
    m_stationData->stat_radius = radius;
  }
}

void TrackDataHandler::setStationDistanceList(
    const vector<double> &stationDistanceList,
    const vector<double> &stationDistanceTotalList) {
  if (m_stationData) {
    m_stationData->x_station = stationDistanceList;
    m_stationData->tot_x_station = stationDistanceTotalList;
  }
}

void TrackDataHandler::setSlopeList(
    const vector<double> &slopeList,
    const vector<double> &slopeStartCoordinateList,
    const vector<double> &slopeEndCoordinateList) {
  if (m_stationData) {
    m_stationData->slope = slopeList;
    m_stationData->x_slopeStart = slopeStartCoordinateList;
    m_stationData->x_slopeEnd = slopeEndCoordinateList;
  }
}

void TrackDataHandler::setRadiusList(
    const vector<double> &radiusList,
    const vector<double> &radiusStartCoordinateList,
    const vector<double> &radiusEndCoordinateList) {
  if (m_stationData) {
    m_stationData->radius = radiusList;
    m_stationData->x_radiusStart = radiusStartCoordinateList;
    m_stationData->x_radiusEnd = radiusEndCoordinateList;
  }
}

void TrackDataHandler::setMaxSpeedList(
    const vector<double> &maxSpeedList,
    const vector<double> &maxSpeedStartCoordinateList,
    const vector<double> &maxSpeedEndCoordinateList) {
  if (m_stationData) {
    m_stationData->v_limit = maxSpeedList;
    m_stationData->x_v_limitStart = maxSpeedStartCoordinateList;
    m_stationData->x_v_limitEnd = maxSpeedEndCoordinateList;
  }
}

// void TrackDataHandler::storeFormInputs(
//     const QMap<QString, InputWidget *> &inputWidgets) {
//   const QString speedLimitKey = "Speed Limit";
//   const QString stationDistanceKey = "Station Distance";
//   const QString slopeKey = "Slope per Section";
//   const QString radiusKey = "Radius per Section";
//   const QString dwellTimeKey = "Dwell Time";
//   const QString slope1Key = "1st Slope";
//   const QString slope2Key = "2nd Slope";
//   const QString slope3Key = "3rd Slope";

//   if (inputWidgets.contains(speedLimitKey)) {
//     setMaxSpeedValue(inputWidgets[speedLimitKey]->getValue());
//     setMaxSpeedList(toStdVector(inputWidgets[speedLimitKey]->getCsvValue(2)),
//                     toStdVector(inputWidgets[speedLimitKey]->getCsvValue(0)),
//                     toStdVector(inputWidgets[speedLimitKey]->getCsvValue(1)));
//   }
//   if (inputWidgets.contains(stationDistanceKey)) {
//     setStationDistanceValue(inputWidgets[stationDistanceKey]->getValue());
//     setStationDistanceList(
//         toStdVector(inputWidgets[stationDistanceKey]->getCsvValue(2)),
//         toStdVector(inputWidgets[stationDistanceKey]->getCsvValue(1)));
//   }
//   if (inputWidgets.contains(slopeKey)) {
//     setSlopeValue(inputWidgets[slopeKey]->getValue());
//     setSlopeList(toStdVector(inputWidgets[slopeKey]->getCsvValue(2)),
//                  toStdVector(inputWidgets[slopeKey]->getCsvValue(0)),
//                  toStdVector(inputWidgets[slopeKey]->getCsvValue(1)));
//   }
//   if (inputWidgets.contains(radiusKey)) {
//     setRadiusValue(inputWidgets[radiusKey]->getValue());
//     setRadiusList(toStdVector(inputWidgets[radiusKey]->getCsvValue(2)),
//                   toStdVector(inputWidgets[radiusKey]->getCsvValue(0)),
//                   toStdVector(inputWidgets[radiusKey]->getCsvValue(1)));
//   }
//   if (inputWidgets.contains("Number of Station")) {
//     m_stationData->n_station = inputWidgets["Number of Station"]->getValue();
//   }
//   if (inputWidgets.contains(dwellTimeKey)) {
//     m_stationData->dwellTime =
//         toStdVector(inputWidgets[dwellTimeKey]->getCsvValue(0));
//   }
//   if (inputWidgets.contains(slope1Key)) {
//     m_stationData->stat_slope_1 = inputWidgets[slope1Key]->getValue();
//   }
//   if (inputWidgets.contains(slope2Key)) {
//     m_stationData->stat_slope_2 = inputWidgets[slope2Key]->getValue();
//   }
//   if (inputWidgets.contains(slope3Key)) {
//     m_stationData->stat_slope_3 = inputWidgets[slope3Key]->getValue();
//   }
// }

std::vector<double>
TrackDataHandler::toStdVector(const QList<double> &list) const {
  std::vector<double> vec;
  vec.reserve(list.size());
  for (double val : list) {
    vec.push_back(val);
  }
  return vec;
}