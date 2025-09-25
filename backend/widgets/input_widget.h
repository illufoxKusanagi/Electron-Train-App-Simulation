#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include "input_dropdown.h"
#include "input_field.h"
#include "input_invalid.h"
#include "input_upload.h"
#include "resources/input_type.h"
#include "styles/colors.h"
#include "styles/text_style.h"
#include <QBoxLayout>
#include <QLabel>

struct InputSize {
  int width;
  int height;
};

class InputWidget : public QWidget {
  Q_OBJECT
public:
  explicit InputWidget(QWidget *parent = nullptr,
                       const InputType &inputType = InputType(),
                       QStringList options = {});
  void setValue(double value);
  void setSize(int width, int height);
  double getValue();
  QString getTextValue();
  bool isModified() const;
  void setModified(bool modified);
  QList<double> getCsvValue(const int requiredColumn);
  void setEchoMode(QLineEdit::EchoMode mode);
  void setPlaceholderText(const QString &placeholder);

signals:
  void valueChanged();

private:
  QLabel *m_label;
  InputField *m_inputField;
  InputDropdown *m_inputDropdown;
  InputUpload *m_inputUpload;
  InputInvalid *m_inputInvalid;
  QWidget *m_inputFieldUpload;
  QVBoxLayout *layout;
  double m_inputValue;
  void buildInputField(InputType inputType);
  void buildInputUpload(InputType inputType);
  void buildInputFieldUpload(InputType inputType);
};

#endif // INPUTWIDGET_H
