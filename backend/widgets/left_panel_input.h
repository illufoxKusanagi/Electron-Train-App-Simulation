#ifndef LEFT_PANEL_INPUTS_H
#define LEFT_PANEL_INPUTS_H

#include "button_sidebar.h"
#include <QVBoxLayout>
#include <QWidget>

class LeftPanelInputs : public QWidget {
  Q_OBJECT
public:
  enum PanelType { INPUT, OUTPUT };
  explicit LeftPanelInputs(QWidget *parent = nullptr, PanelType type = INPUT);
  void toggleCollapse(bool isCollapsed);

public slots:
  void onPageChanged(int pageIndex);
  void updateCategoryButton(int index);
  void setCurrentIndex(int index);

signals:
  void buttonClicked(int index);

private:
  static const QStringList INPUT_BUTTON_NAMES;
  static const QStringList INPUT_BUTTON_TYPES;
  static const QStringList OUTPUT_BUTTON_NAMES;
  static const QStringList OUTPUT_BUTTON_TYPES;

  int m_currentIndex = -1;
  bool m_isShown = true;
  const QStringList m_buttonNames;
  const QStringList m_buttonTypes;
  QVBoxLayout *local_buttonLayout;
  QWidget *local_buttonContainer;
  QVBoxLayout *mainLayout;
  ButtonSidebar *m_categoryButton;
  QList<ButtonSidebar *> m_sidebarButtons;
  PanelType m_type;
  void setupButtons();
  void updateButtonStates();
  void toggleButtons();
};

#endif // LEFT_PANEL_INPUTS_H
