#include "mass_handler.h"

MassHandler::MassHandler(AppContext &context)
    : loadData(context.loadData.data()), massData(context.massData.data()),
      trainData(context.trainData.data()) {}

double MassHandler::countMassEmptyCar() {
  massData->mass_Me = (trainData->n_M1 * massData->mass_M1) +
                      (trainData->n_M2 * massData->mass_M2);
  massData->mass_Te = (trainData->n_Tc * massData->mass_TC) +
                      (trainData->n_T1 * massData->mass_T1) +
                      (trainData->n_T2 * massData->mass_T2) +
                      (trainData->n_T3 * massData->mass_T3) +
                      (trainData->n_M1_disabled * massData->mass_M1) +
                      (trainData->n_M2_disabled * massData->mass_M2);
  return massData->mass_Me + massData->mass_Te;
}

double MassHandler::countMassWithLoad() {
  loadData->mass_P_final = loadData->mass_P / 1000;
  massData->mass_M =
      massData->mass_Me +
      trainData->n_M1 * (loadData->mass_P_final * loadData->n_PM1) +
      trainData->n_M2 * (loadData->mass_P_final * loadData->n_PM2) +
      trainData->n_M1_disabled * (loadData->mass_P_final * loadData->n_PM1) +
      trainData->n_M2_disabled * (loadData->mass_P_final * loadData->n_PM2);
  massData->mass_T =
      massData->mass_Te +
      trainData->n_Tc * (loadData->mass_P_final * loadData->n_PTc) +
      trainData->n_T1 * (loadData->mass_P_final * loadData->n_PT1) +
      trainData->n_T2 * (loadData->mass_P_final * loadData->n_PT2) +
      trainData->n_T3 * (loadData->mass_P_final * loadData->n_PT3);
  return massData->mass_M + massData->mass_T;
}

double MassHandler::countMassLoadInput() {
  massData->mass_totalLoad =
      massData->mass_totalEmpty + trainData->n_car * loadData->load;
  return massData->mass_totalLoad;
}

double MassHandler::countInertialMass() {
  massData->mass_Mi =
      (massData->mass_Me * massData->i_M) +
      (trainData->n_M1 * (loadData->mass_P_final * loadData->n_PM1) +
       trainData->n_M2 * (loadData->mass_P_final * loadData->n_PM2));
  massData->mass_Ti =
      (massData->mass_Te * massData->i_T) +
      (trainData->n_Tc * (loadData->mass_P_final * loadData->n_PTc) +
       trainData->n_T1 * (loadData->mass_P_final * loadData->n_PT1) +
       trainData->n_T2 * (loadData->mass_P_final * loadData->n_PT2) +
       trainData->n_T3 * (loadData->mass_P_final * loadData->n_PT3) +
       trainData->n_M1_disabled * (loadData->mass_P_final * loadData->n_PM1) +
       trainData->n_M2_disabled * (loadData->mass_P_final * loadData->n_PM2));
  return massData->mass_Mi + massData->mass_Ti;
}

double MassHandler::countInertialMassInput() {
  massData->mass_totalInertial = (massData->mass_Me * massData->i_M) +
                                 (massData->mass_Te * massData->i_T) +
                                 (trainData->n_car * loadData->load);
  return massData->mass_totalInertial;
}
