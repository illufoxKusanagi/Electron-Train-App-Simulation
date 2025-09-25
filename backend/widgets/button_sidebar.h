#ifndef BUTTONSIDEBAR_H
#define BUTTONSIDEBAR_H

#include "button_sidebar_widget.h"
#include "resources/icon_paths.h"
#include "styles/colors.h"
#include "styles/text_style.h"
#include <QBoxLayout>
#include <QPushButton>

class ButtonSidebar : public QPushButton {
  Q_OBJECT

public:
  explicit ButtonSidebar(QWidget *parent = nullptr,
                         const QString &iconType = "",
                         const QString &buttonLabel = "");
  void setLabelVisible(bool visible);
  void setIconVisible(bool visible);
  void setEnabled(bool isEnabled);
  void updateIcon(bool isHidden);
  void setIconSize(int width, int height);

protected:
  QString m_iconType;

private:
  static const QString s_styleHover;
  static const QString s_stylePressed;
  static const QString s_styleBase;

  QPushButton *buttonSidebar;
  ButtonSidebarWidget *m_contentWidget;
  QHBoxLayout *m_layout;
  bool isLabelVisible;
};

#endif // BUTTONSIDEBAR_H
