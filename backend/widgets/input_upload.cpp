#include "input_upload.h"

InputUpload::InputUpload(const QString &inputLabel, QWidget *parent)
    : QWidget(parent), m_uploadButton(new QPushButton("Choose csv File", this)),
      m_uploadLabel(new QLabel("No file selected", this)),
      m_requiredColumnCount(0), m_inputLabel(inputLabel) {
  QHBoxLayout *layout = new QHBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  m_uploadButton->setIcon(QIcon(":/icons/icons/upload.svg"));
  m_uploadButton->setIconSize(QSize(16, 16));

  layout->addWidget(m_uploadButton);
  layout->addWidget(m_uploadLabel);

  setStyleSheet("QPushButton{"
                "border: 1px solid " +
                Colors::Secondary400.name() +
                ";"
                "border-radius: 8px;" +
                TextStyle::BodySmallRegular() +
                "color: " + Colors::Secondary400.name() +
                ";"
                "}"
                "QPushButton:pressed {"
                "background-color: " +
                Colors::Secondary50.name() +
                ";"
                "}");
  m_uploadButton->setFixedSize(132, 32);
  setDisabled(false);
  connect(m_uploadButton, &QPushButton::clicked, this,
          [this]() { onUploadButtonClicked(); });
  m_uploadLabel->setStyleSheet(TextStyle::SubttileSmallRegular() +
                               "color: " + Colors::Secondary700.name() + ";");
}
void InputUpload::setRequiredColumnCount(int count) {
  m_requiredColumnCount = count;
}

void InputUpload::setTargetColumns(const QList<int> &columnIndices) {
  m_targetColumns = columnIndices;
}

bool InputUpload::validateColumnCount(const QStringList &values) {
  if (m_requiredColumnCount > 0 && values.size() < m_requiredColumnCount) {
    return false;
  }
  return true;
}

QString InputUpload::getFilePath() const { return m_filePath; }

bool InputUpload::isFileLoaded() const { return !m_filePath.isEmpty(); }

QList<QList<double>> InputUpload::getAllData() const { return m_data; }

void InputUpload::onUploadButtonClicked() {
  QString filePath = QFileDialog::getOpenFileName(
      this, QString("Select " + m_inputLabel + " CSV File"), QDir::homePath(),
      tr("CSV Files (*.csv);;All Files (*)"));

  if (filePath.isEmpty()) {
    MessageBoxWidget messageBox("Error", "No file selected",
                                MessageBoxWidget::Warning);
    return;
  }

  if (readCsvFile(filePath)) {
    m_filePath = filePath;
    QFileInfo fileInfo(filePath);
    m_uploadLabel->setText(fileInfo.fileName());
    m_uploadLabel->setStyleSheet(TextStyle::SubttileSmallRegular() +
                                 "color: " + Colors::Secondary700.name() + ";");
    emit fileLoaded(filePath);
  }
}

bool InputUpload::readCsvFile(const QString &filePath) {
  QFile file(filePath);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    m_uploadLabel->setText("Failed to open file");
    m_uploadLabel->setStyleSheet(TextStyle::SubttileSmallRegular() +
                                 "color: " + Colors::Danger500.name() + ";");
    emit fileLoadError("Could not open file for reading");
    return false;
  }
  m_data.clear();
  QTextStream in(&file);
  int lineNumber = 0;
  while (!in.atEnd()) {
    lineNumber++;
    QString line = in.readLine();
    if (line.trimmed().isEmpty()) {
      continue;
    }
    QStringList values = line.split(",", Qt::KeepEmptyParts);
    if (!validateColumnCount(values)) {
      file.close();
      m_uploadLabel->setText(
          QString("Not enough columns (line %1)").arg(lineNumber));
      m_uploadLabel->setStyleSheet(TextStyle::SubttileSmallRegular() +
                                   "color: " + Colors::Danger500.name() + ";");
      emit fileLoadError(
          QString("Line %1 doesn't have enough columns").arg(lineNumber));
      return false;
    }
    QList<double> rowData;
    for (const QString &value : values) {
      bool isNonNumeric;
      double numValue = value.trimmed().toDouble(&isNonNumeric);
      if (!isNonNumeric) {
        numValue = 0.0;
      }
      rowData.append(numValue);
    }
    m_data.append(rowData);
  }
  file.close();
  if (m_data.isEmpty()) {
    m_uploadLabel->setText("No valid data in file");
    m_uploadLabel->setStyleSheet(TextStyle::SubttileSmallRegular() +
                                 "color: " + Colors::Danger500.name() + ";");
    emit fileLoadError("File contains no valid data");
    return false;
  }
  return true;
}

QList<double> InputUpload::getColumnData(int columnIndex) const {
  QList<double> columnData;
  for (const QList<double> &row : m_data) {
    if (columnIndex < row.size()) {
      columnData.append(row[columnIndex]);
    } else {
      columnData.append(0.0);
    }
  }
  return columnData;
}

bool InputUpload::hasRequiredColumns() const {
  return !m_data.isEmpty() &&
         (m_requiredColumnCount == 0 ||
          (m_data.first().size() >= m_requiredColumnCount));
}
