#ifndef MASS_HANDLER_H
#define MASS_HANDLER_H

#include "core/appcontext.h"
#include <QObject>

class MassHandler : public QObject {
  Q_OBJECT
public:
  explicit MassHandler(AppContext &context);
  double countMassEmptyCar();
  double countMassWithLoad();
  double countMassLoadInput();
  double countInertialMass();
  double countInertialMassInput();

private:
  LoadData *loadData;
  MassData *massData;
  TrainData *trainData;
};

#endif // MASS_HANDLER_H
