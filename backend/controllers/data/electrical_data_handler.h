#ifndef ELECTRICAL_DATA_HANDLER_H
#define ELECTRICAL_DATA_HANDLER_H

#include "core/appcontext.h"
// #include "widgets/input_widget.h"
#include <QObject>
#include <vector>

class ElectricalDataHandler : public QObject {
  Q_OBJECT
public:
  explicit ElectricalDataHandler(AppContext *context,
                                 QObject *parent = nullptr);
  // void storeFormInputs(const QMap<QString, InputWidget *> &inputWidgets);

private:
  EfficiencyData *m_efficiencyData;
  EnergyData *m_energyData;
  PowerData *m_powerData;
  void setGearboxEfficiency(double stat, const std::vector<double> &eff,
                            const std::vector<double> &v_eff);
  void setVvvfEfficiency(double stat, const std::vector<double> &eff,
                         const std::vector<double> &v_eff);
  void setTractionMotorEfficiency(double stat, const std::vector<double> &eff,
                                  const std::vector<double> &v_eff);
  void setLineVoltage(double stat, const std::vector<double> &vol,
                      const std::vector<double> &v_vol);
  void setMotorVoltage(double stat, const std::vector<double> &vol,
                       const std::vector<double> &v_vol);
  void setAuxiliaryPower(double p_aps);
  std::vector<double> toStdVector(const QList<double> &list) const;
};

#endif // ELECTRICAL_DATA_HANDLER_H
