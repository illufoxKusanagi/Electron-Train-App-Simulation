#ifndef RUNNING_DATA_HANDLER_H
#define RUNNING_DATA_HANDLER_H

#include "core/appcontext.h"
// #include "widgets/input_widget.h"
#include <QMap>
#include <QObject>

class RunningDataHandler : public QObject {
  Q_OBJECT
public:
  explicit RunningDataHandler(AppContext *context, QObject *parent = nullptr);
  // void storeFormInputs(const QMap<QString, InputWidget *> &inputWidgets);
  void setAccelerationValue(double acceleration);
  void setDecelerationValue(double decceleration);

private:
  MovingData *m_movingData;
  TrainData *m_trainData;
  ResistanceData *m_resistanceData;
  void setStartingResistance(double startRes);
  void setWeakeningPoint1(double v_p1);
  void setWeakeningPoint2(double v_p2);
  void setWeakeningPoint3(double v_b1);
  void setWeakeningPoint4(double v_b2);
  void setDifferenceCoastingSpeed(double v_diffCoast);
  void setEmergencyBrakeDeceleration(double decc_emergency);
  std::vector<double> toStdVector(const QList<double> &list) const;
};

#endif // RUNNING_DATA_HANDLER_H
