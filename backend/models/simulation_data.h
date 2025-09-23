#ifndef SIMULATIONDATA_H
#define SIMULATIONDATA_H

#include <QList>
#include <QSharedPointer>
#include <QString>

struct SimulationDatas {
  QList<QString> phase;
  QList<double> trainSpeeds;
  QList<double> trainSpeedsSi;
  QList<double> accelerations;
  QList<double> accelerationsSi;
  QList<double> tractionEfforts;
  QList<double> vvvfPowers;
  QList<double> catenaryPowers;
  QList<double> vvvfCurrents;
  QList<double> catenaryCurrents;
  QList<double> time;
  QList<double> timeTotal;
  QList<double> distance;
  QList<double> distanceTotal;
  QList<double> motorForce;
  QList<double> motorResistance;
  QList<double> totalResistance;
  QList<double> tractionForcePerMotor;
  QList<double> resistancePerMotor;
  QList<double> torque;
  QList<double> rpm;
  QList<double> powerWheel;
  QList<double> powerMotorOut;
  QList<double> powerMotorIn;
  QList<double> powerVvvfIn;
  QList<double> powerCatenary;
  QList<double> currentCatenary;
  QList<double> currentVvvf;
  QList<double> energyConsumptions;
  QList<double> energyPowerings;
  QList<double> energyRegenerations;
  QList<double> energyAps;
  QList<double> maxCurrTime;
  QList<double> maxPowTime;
  QList<double> energyCatenaries;
  QList<double> mileages;
  QList<double> slopes;
  QList<double> radiuses;
  QList<double> speedLimits;

  QList<double> motorResistancesZero;
  QList<double> motorResistancesFive;
  QList<double> motorResistancesTen;
  QList<double> motorResistancesTwentyFive;

  QList<double> brakingDistances;
  QList<double> odos;
};

#endif // SIMULATIONDATA_H
