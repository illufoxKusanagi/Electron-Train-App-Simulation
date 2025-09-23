#include "electrical_data_handler.h"

ElectricalDataHandler::ElectricalDataHandler(AppContext *context,
                                             QObject *parent)
    : QObject(parent), m_efficiencyData(context->efficiencyData.data()),
      m_energyData(context->energyData.data()),
      m_powerData(context->powerData.data()) {}

void ElectricalDataHandler::setGearboxEfficiency(
    double stat, const std::vector<double> &eff,
    const std::vector<double> &v_eff) {
  if (m_efficiencyData) {
    m_efficiencyData->stat_eff_gear = stat;
    m_efficiencyData->eff_gear = eff;
    m_efficiencyData->v_eff_gear = v_eff;
  }
}

void ElectricalDataHandler::setVvvfEfficiency(
    double stat, const std::vector<double> &eff,
    const std::vector<double> &v_eff) {
  if (m_efficiencyData) {
    m_efficiencyData->stat_eff_vvvf = stat;
    m_efficiencyData->eff_vvvf = eff;
    m_efficiencyData->v_eff_vvvf = v_eff;
  }
}

void ElectricalDataHandler::setTractionMotorEfficiency(
    double stat, const std::vector<double> &eff,
    const std::vector<double> &v_eff) {
  if (m_efficiencyData) {
    m_efficiencyData->stat_eff_motor = stat;
    m_efficiencyData->eff_motor = eff;
    m_efficiencyData->v_eff_motor = v_eff;
  }
}

void ElectricalDataHandler::setLineVoltage(double stat,
                                           const std::vector<double> &vol,
                                           const std::vector<double> &v_vol) {
  if (m_energyData) {
    m_energyData->stat_vol_line = stat;
    m_energyData->vol_line = vol;
    m_energyData->v_vol_line = v_vol;
  }
}

void ElectricalDataHandler::setMotorVoltage(double stat,
                                            const std::vector<double> &vol,
                                            const std::vector<double> &v_vol) {
  if (m_energyData) {
    m_energyData->stat_vol_motor = stat;
    m_energyData->vol_motor = vol;
    m_energyData->v_vol_motor = v_vol;
  }
}

void ElectricalDataHandler::setAuxiliaryPower(double p_aps) {
  if (m_powerData) {
    m_powerData->p_aps = p_aps;
  }
}

// void ElectricalDataHandler::storeFormInputs(
//     const QMap<QString, InputWidget *> &inputWidgets) {
//   if (inputWidgets.contains("Auxiliary Power")) {
//     setAuxiliaryPower(inputWidgets["Auxiliary Power"]->getValue());
//   }
//   if (inputWidgets.contains("Efficiency of Gearbox")) {
//     InputWidget *widget = inputWidgets["Efficiency of Gearbox"];
//     setGearboxEfficiency(widget->getValue(),
//                          toStdVector(widget->getCsvValue(1)),
//                          toStdVector(widget->getCsvValue(0)));
//   }
//   if (inputWidgets.contains("Efficiency of VVVF")) {
//     InputWidget *widget = inputWidgets["Efficiency of VVVF"];
//     setVvvfEfficiency(widget->getValue(), toStdVector(widget->getCsvValue(1)),
//                       toStdVector(widget->getCsvValue(0)));
//   }
//   if (inputWidgets.contains("The Efficiency of Traction Motor")) {
//     InputWidget *widget = inputWidgets["The Efficiency of Traction Motor"];
//     setTractionMotorEfficiency(widget->getValue(),
//                                toStdVector(widget->getCsvValue(1)),
//                                toStdVector(widget->getCsvValue(0)));
//   }
//   if (inputWidgets.contains("Line Voltage")) {
//     InputWidget *widget = inputWidgets["Line Voltage"];
//     setLineVoltage(widget->getValue(), toStdVector(widget->getCsvValue(1)),
//                    toStdVector(widget->getCsvValue(0)));
//   }
//   if (inputWidgets.contains("Motor Voltage")) {
//     InputWidget *widget = inputWidgets["Motor Voltage"];
//     setMotorVoltage(widget->getValue(), toStdVector(widget->getCsvValue(1)),
//                     toStdVector(widget->getCsvValue(0)));
//   }
// }

std::vector<double>
ElectricalDataHandler::toStdVector(const QList<double> &list) const {
  std::vector<double> vec;
  vec.reserve(list.size());
  for (double val : list) {
    vec.push_back(val);
  }
  return vec;
}
