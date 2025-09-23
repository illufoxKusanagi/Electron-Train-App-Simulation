#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "auth/auth_manager.h"
#include "auth/user_manager.h"
#include "models/constant_data.h"
#include "models/efficiency_data.h"
#include "models/energy_data.h"
#include "models/load_data.h"
#include "models/mass_data.h"
#include "models/moving_data.h"
#include "models/power_data.h"
#include "models/resistance_data.h"
#include "models/simulation_data.h"
#include "models/station_data.h"
#include "models/train_data.h"
#include "models/train_motor_data.h"
#include <QFile>
#include <QIODevice>
#include <QSharedPointer>

class AppContext : public QObject {
  Q_OBJECT
public:
  AppContext(QObject *parent = nullptr);
  QSharedPointer<ConstantData> constantData;
  QSharedPointer<LoadData> loadData;
  QSharedPointer<MassData> massData;
  QSharedPointer<MovingData> movingData;
  QSharedPointer<ResistanceData> resistanceData;
  QSharedPointer<TrainData> trainData;
  QSharedPointer<TrainMotorData> trainMotorData;
  QSharedPointer<PowerData> powerData;
  QSharedPointer<EnergyData> energyData;
  QSharedPointer<EfficiencyData> efficiencyData;
  QSharedPointer<StationData> stationData;
  QSharedPointer<SimulationDatas> simulationDatas;
  UserManager *userManager;
  AuthManager *authManager;
};

#endif // APPCONTEXT_H
