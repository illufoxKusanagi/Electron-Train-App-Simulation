
#include "input_field.h"

InputField::InputField(const QString &unitText, QWidget *parent)
    : QWidget(parent), m_input(new QLineEdit(this)),
      m_unitLabel(new QLabel(unitText, this)) {
  QHBoxLayout *layout = new QHBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);

  layout->addWidget(m_input);
  layout->addWidget(m_unitLabel);

  m_input->setStyleSheet(s_styleSheet);
  m_input->setBaseSize(128, 32);
  m_input->setMinimumHeight(32);
  m_unitLabel->setStyleSheet(TextStyle::BodySmallRegular() +
                             "color: " + Colors::Secondary700.name() + ";");
}

void InputField::setValue(double value) {
  if (value != 0)
    m_input->setText(QString::number(value));
  else
    m_input->clear();
  m_input->setModified(false);
}

double InputField::getValue() { return m_input->text().toDouble(); }

void InputField::setPlaceholder() {
  m_input->setPlaceholderText("enter value...");
}

void InputField::setReadOnly(bool isReadOnly) {
  m_input->setStyleSheet(
      isReadOnly ? s_styleSheet +
                       ("background-color: " + Colors::Primary50.name() + ";")
                 : s_styleSheet);
  m_input->setReadOnly(isReadOnly);
}

void InputField::connectTextChanged() {
  connect(m_input, &QLineEdit::textChanged, [this](const QString &text) {
    double value = text.toDouble();
    emit valueChanged(value);
  });
}

void InputField::setEchoMode(QLineEdit::EchoMode mode) {
  m_input->setEchoMode(mode);
}

void InputField::setPlaceholderText(const QString &placeholder) {
  m_input->setPlaceholderText(placeholder);
}

void InputField::setSize(int width, int height) {
  m_input->setFixedSize(width, height);
}

bool InputField::isModified() const { return m_input->isModified(); }

void InputField::setModified(bool modified) { m_input->setModified(modified); }

QString InputField::getTextValue() { return m_input->text(); }

const QString InputField::s_styleSheet =
    "padding: 4px 12px; border: 1px solid " + Colors::Secondary400.name() +
    "; border-radius: 8px;" + TextStyle::BodySmallRegular() +
    "color: " + Colors::Secondary400.name() + ";";