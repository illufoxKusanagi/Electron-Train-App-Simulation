#ifndef TRACK_DATA_HANDLER_H
#define TRACK_DATA_HANDLER_H

using namespace std;

#include "core/appcontext.h"
// #include "widgets/input_widget.h"
#include <QObject>

class TrackDataHandler : public QObject {
  Q_OBJECT
public:
  explicit TrackDataHandler(AppContext *context, QObject *parent = nullptr);
  // void storeFormInputs(const QMap<QString, InputWidget *> &inputWidgets);

private:
  MovingData *m_movingData;
  ResistanceData *m_resistanceData;
  StationData *m_stationData;
  void setStationDistanceValue(double stationDistance);
  void setSlopeValue(double slope);
  void setRadiusValue(double radius);
  void setMaxSpeedValue(double maxSpeed);
  void setStationDistanceList(const vector<double> &stationDistanceList,
                              const vector<double> &stationDistanceTotalList);
  void setSlopeList(const vector<double> &slopeList,
                    const vector<double> &slopeStartCoordinateList,
                    const vector<double> &slopeEndCoordinateList);
  void setRadiusList(const vector<double> &radiusList,
                     const vector<double> &radiusStartCoordinateList,
                     const vector<double> &radiusEndCoordinateList);
  void setMaxSpeedList(const vector<double> &maxSpeedList,
                       const vector<double> &maxSpeedStartCoordinateList,
                       const vector<double> &maxSpeedEndCoordinateList);
  std::vector<double> toStdVector(const QList<double> &list) const;
};

#endif // TRACK_DATA_HANDLER_H
