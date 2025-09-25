#include "input_widget.h"

InputWidget::InputWidget(QWidget *parent, const InputType &inputType,
                         QStringList options)
    : QWidget(parent), m_inputField(nullptr), m_inputUpload(nullptr),
      m_inputDropdown(nullptr), m_inputInvalid(nullptr),
      m_inputFieldUpload(nullptr) {
  layout = new QVBoxLayout(this);

  m_label = new QLabel(inputType.label, this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(8);
  layout->addWidget(m_label);
  m_label->setStyleSheet(TextStyle::BodyMediumRegular() +
                         "color: " + Colors::Secondary700.name() +
                         ";"
                         "white-space: normal;");
  m_label->setWordWrap(true);
  m_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
  if (inputType.type == "field") {
    buildInputField(inputType);
  } else if (inputType.type == "dropdown") {
    m_inputDropdown = new InputDropdown(this, options);
    connect(m_inputDropdown, &InputDropdown::valueChanged, this, [this]() {
      m_inputValue = m_inputDropdown->getValue();
      emit valueChanged();
    });
    layout->addWidget(m_inputDropdown);
    layout->setAlignment(m_inputDropdown, Qt::AlignLeft);
  } else if (inputType.type == "upload") {
    buildInputUpload(inputType);
  } else if (inputType.type == "field upload") {
    buildInputFieldUpload(inputType);
  } else if (inputType.type == "invalid") {
    m_inputInvalid = new InputInvalid(inputType.type, this);
    layout->addWidget(m_inputInvalid);
    layout->setAlignment(m_inputInvalid, Qt::AlignLeft);
  }

  else {
    m_inputInvalid = new InputInvalid(inputType.type, this);
    layout->addWidget(m_inputInvalid);
    layout->setAlignment(m_inputInvalid, Qt::AlignLeft);
  }
  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  adjustSize();
}

void InputWidget::buildInputField(InputType inputType) {
  m_inputField = new InputField(inputType.unit, this);
  m_inputField->setPlaceholder();
  m_inputField->setReadOnly(inputType.isReadOnly);
  m_inputField->setValue(inputType.value);
  m_inputField->connectTextChanged();

  connect(m_inputField->findChild<QLineEdit *>(), &QLineEdit::textChanged, this,
          [this]() {
            m_inputValue = m_inputField->getValue();
            emit valueChanged();
          });
  layout->addWidget(m_inputField);
  layout->setAlignment(m_inputField, Qt::AlignLeft);
}

QList<double> InputWidget::getCsvValue(const int requiredColumn) {
  if (m_inputUpload) {
    return m_inputUpload->getColumnData(requiredColumn);
  }
  if (m_inputFieldUpload) {
    InputUpload *inputUpload = m_inputFieldUpload->findChild<InputUpload *>();
    if (inputUpload) {
      return inputUpload->getColumnData(requiredColumn);
    }
  }
  return QList<double>();
}

void InputWidget::setValue(double value) {
  if (m_inputField) {
    m_inputValue = value;
    m_inputField->setValue(value);
  } else if (m_inputDropdown) {
    m_inputValue = m_inputDropdown->getValue();
  } else if (m_inputFieldUpload) {
    InputField *inputField = m_inputFieldUpload->findChild<InputField *>();
    m_inputValue = value;
    inputField->setValue(value);
  }
}

double InputWidget::getValue() { return m_inputValue; }

bool InputWidget::isModified() const {
  return m_inputField ? m_inputField->isModified() : false;
}

void InputWidget::setModified(bool modified) {
  if (m_inputField) {
    m_inputField->setModified(modified);
  }
}

void InputWidget::buildInputUpload(InputType inputType) {
  m_inputUpload = new InputUpload(inputType.label, this);
  m_inputUpload->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  connect(m_inputUpload, &InputUpload::fileLoaded, this,
          [this]() { emit valueChanged(); });
  connect(m_inputUpload, &InputUpload::fileLoadError, this,
          [this](const QString &errorMessage) {
            MessageBoxWidget messageBox("CSV Load Error", errorMessage,
                                        MessageBoxWidget::Warning);
          });
  layout->addWidget(m_inputUpload);
  layout->setAlignment(m_inputUpload, Qt::AlignLeft);
}

void InputWidget::buildInputFieldUpload(InputType inputType) {
  m_inputFieldUpload = new QWidget(this);
  QVBoxLayout *fieldLayout = new QVBoxLayout(m_inputFieldUpload);
  m_inputFieldUpload->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  fieldLayout->setContentsMargins(0, 0, 0, 0);
  fieldLayout->setSpacing(4);

  InputField *inputField = new InputField(inputType.unit, m_inputFieldUpload);
  inputField->setPlaceholder();
  inputField->setReadOnly(inputType.isReadOnly);
  inputField->setValue(inputType.value);

  InputUpload *inputUpload =
      new InputUpload(inputType.label, m_inputFieldUpload);
  inputUpload->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  connect(inputField->findChild<QLineEdit *>(), &QLineEdit::textChanged, this,
          [this, inputField]() {
            m_inputValue = inputField->getValue();
            emit valueChanged();
          });
  connect(inputUpload, &InputUpload::fileLoaded, this,
          [this]() { emit valueChanged(); });
  connect(inputUpload, &InputUpload::fileLoadError, this,
          [this](const QString &errorMessage) {
            MessageBoxWidget messageBox("CSV Load Error", errorMessage,
                                        MessageBoxWidget::Warning);
          });
  fieldLayout->addWidget(inputUpload);
  fieldLayout->addWidget(inputField);
  layout->addWidget(m_inputFieldUpload);
  layout->setAlignment(m_inputFieldUpload, Qt::AlignLeft);
}

void InputWidget::setEchoMode(QLineEdit::EchoMode mode) {
  if (m_inputField) {
    m_inputField->setEchoMode(mode);
  }
}

void InputWidget::setPlaceholderText(const QString &placeholder) {
  if (m_inputField) {
    m_inputField->setPlaceholderText(placeholder);
  }
}

void InputWidget::setSize(int width, int height) {
  if (m_inputField) {
    m_inputField->setSize(width, height);
  }
}

QString InputWidget::getTextValue() { return m_inputField->getTextValue(); }