#ifndef LEFT_PANEL_H
#define LEFT_PANEL_H

#include "button_toggle.h"
#include "controllers/simulation/train_simulation_handler.h"
#include "left_panel_input.h"
#include "message_box_widget.h"
#include "widgets/button_action.h"
#include <QFuture>
#include <QFutureWatcher>
#include <QPushButton>
#include <QScrollArea>
#include <QSet>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QtConcurrent/QtConcurrent>

class LeftPanel : public QWidget {
  Q_OBJECT

public:
  explicit LeftPanel(QWidget *parent = nullptr,
                     TrainSimulationHandler *trainSimulation = nullptr);
public slots:
  void emitNavigateSignal(int pageIndex);

signals:
  void navigateToPage(int pageIndex);

private:
  bool m_isCollapsed = false;
  bool m_isSimulationError = false;
  int m_currentIndex = -1;
  QVBoxLayout *m_mainLayout;
  ButtonToggle *m_buttonToggle;
  QVBoxLayout *m_buttonLayout;
  LeftPanelInputs *m_inputPanel;
  LeftPanelInputs *m_outputPanel;
  TrainSimulationHandler *m_trainSimulation;
  QVBoxLayout *m_runVButtonLayout;
  QHBoxLayout *m_runHButtonLayout;

  int getCurrentIndex() const { return m_currentIndex; }
  void setCurrentIndex(int index) { m_currentIndex = index; }
  void createRunButton();
  void setupHeader();
  void setupInputPageButtons();
  void setupOutputPageButtons();
  void updateButtonState(QFuture<void> future, ButtonAction *runButton,
                         ButtonAction *staticRunButton);
  void showSimMessageBox(const QSet<QString> &warnings, bool isError = false);
};

#endif // LEFT_PANEL_H
