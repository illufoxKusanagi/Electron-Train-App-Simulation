#ifndef INPUTTYPE_H
#define INPUTTYPE_H

#include <QString>
#include <optional>

class InputType {
public:
  QString type;
  QString label;
  QString unit;
  double value;
  bool isReadOnly;
  InputType() : type(""), label(""), unit(""), isReadOnly(false) {}
  InputType(const QString &inputType, const QString &inputLabel,
            const QString &inputUnit = "", bool isReadOnly = false,
            double value = 0.0)
      : type(inputType), label(inputLabel), unit(inputUnit),
        isReadOnly(isReadOnly), value(value) {}
};

#endif // INPUTTYPE_H
