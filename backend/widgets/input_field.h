#ifndef INPUTFIELD_H
#define INPUTFIELD_H

#include "styles/colors.h"
#include "styles/text_style.h"
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <optional>

class InputField : public QWidget {
  Q_OBJECT

signals:
  void valueChanged(double value);

public:
  explicit InputField(const QString &unitText = "", QWidget *parent = nullptr);
  void setValue(double value);
  void setPlaceholder();
  void setReadOnly(bool isReadOnly);
  void connectTextChanged();
  double getValue();
  QString getTextValue();
  bool isModified() const;
  void setModified(bool modified);
  void setEchoMode(QLineEdit::EchoMode mode);
  void setPlaceholderText(const QString &placeholder);
  void setSize(int width, int height);

private:
  QLineEdit *m_input;
  QLabel *m_unitLabel;
  static const QString s_styleSheet;
};

#endif
