#ifndef TRAIN_DATA_HANDLER_H
#define TRAIN_DATA_HANDLER_H

#include "core/appcontext.h"
// #include "widgets/input_widget.h"
#include <QObject>

class TrainDataHandler : public QObject {
  Q_OBJECT
public:
  explicit TrainDataHandler(AppContext *context, QObject *parent = nullptr);
  // void storeFormInputs(const QMap<QString, InputWidget *> &inputWidgets);
  // void setTypeValue(const QMap<QString, InputWidget *> &inputWidgets);
  // void setMassValue(const QMap<QString, InputWidget *> &inputWidgets);
  // void setPassengerValue(const QMap<QString, InputWidget *> &inputWidgets);
  void setDegradedTrainMotorValues(double numberM1, double numberM2);
  void setNumberCarValue(double numberCar);
  void setTrainsetLengthValue(double carLength);

private:
  TrainData *m_trainData;
  MassData *m_massData;
  LoadData *m_loadData;
  void setNumberTractionMotorValue(double numberTractionMotor);
  void setNumberAxleValue(double numberAxle);
  void setWheelDiameterValue(double wheelDiameter);
  void setGearRatioValue(double gearRatio);
  void setLoadValue(double load);
  void setPassengerWeightValue(double passengerWeight);
  void setInertialCoefficientTrailerValue(double inertialCoefficientTrailer);
  void setInertialCoefficientMotorValue(double inertialCoefficientMotor);
};

#endif // TRAIN_DATA_HANDLER_H
