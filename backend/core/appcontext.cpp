#include "appcontext.h"
#include <qdebug.h>

AppContext::AppContext(QObject *parent) : QObject(parent) {
  trainData = QSharedPointer<TrainData>::create();
  massData = QSharedPointer<MassData>::create();
  loadData = QSharedPointer<LoadData>::create();
  resistanceData = QSharedPointer<ResistanceData>::create();
  movingData = QSharedPointer<MovingData>::create();
  trainMotorData = QSharedPointer<TrainMotorData>::create();
  efficiencyData = QSharedPointer<EfficiencyData>::create();
  powerData = QSharedPointer<PowerData>::create();
  energyData = QSharedPointer<EnergyData>::create();
  stationData = QSharedPointer<StationData>::create();
  constantData = QSharedPointer<ConstantData>::create();
  simulationDatas = QSharedPointer<SimulationDatas>::create();
  userManager = new UserManager(this);
  authManager = new AuthManager(userManager, this);
}
