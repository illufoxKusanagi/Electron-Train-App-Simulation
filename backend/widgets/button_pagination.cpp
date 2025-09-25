#include "button_pagination.h"
#include "styles/colors.h"
#include "styles/text_style.h"

ButtonPagination::ButtonPagination(QWidget *parent) : QWidget(parent) {
  QHBoxLayout *layout = new QHBoxLayout(this);
  layout->setSpacing(16);
  layout->setContentsMargins(0, 0, 0, 0);

  prevButton = new QPushButton("<", this);
  nextButton = new QPushButton(">", this);
  pageLabel = new QLabel("1/3", this);

  QString buttonStyle = "QPushButton {"
                        "    background-color: " +
                        Colors::Primary600.name() +
                        ";"
                        "    border-radius: 8px;"
                        "    min-width: 40px;"
                        "    min-height: 40px;"
                        "    color: white;"
                        "    " +
                        TextStyle::BodyMediumBold() +
                        "}"
                        "QPushButton:hover {"
                        "    background-color: " +
                        Colors::Primary500.name() +
                        ";"
                        "}"
                        "QPushButton:pressed {"
                        "    background-color: " +
                        Colors::Primary700.name() +
                        ";"
                        "}"
                        "QPushButton:disabled {"
                        "    background-color: " +
                        Colors::Grey300.name() +
                        ";"
                        "}";
  prevButton->setStyleSheet(buttonStyle);
  nextButton->setStyleSheet(buttonStyle);
  pageLabel->setStyleSheet(TextStyle::BodyMediumRegular());
  layout->addWidget(prevButton);
  layout->addWidget(pageLabel);
  layout->addWidget(nextButton);

  connect(prevButton, &QPushButton::clicked, this,
          &ButtonPagination::onPrevClicked);
  connect(nextButton, &QPushButton::clicked, this,
          &ButtonPagination::onNextClicked);
  updateButtons(0, 1);
}

void ButtonPagination::updateButtons(int currentPage, int totalPages) {
  currentPageNum = currentPage;
  totalPageCount = totalPages;

  pageLabel->setText(
      QString("%1/%2").arg(currentPageNum + 1).arg(totalPageCount));
  prevButton->setEnabled(currentPageNum > 0);
  nextButton->setEnabled(currentPageNum < totalPageCount - 1);
}

void ButtonPagination::onPrevClicked() {
  if (currentPageNum > 0) {
    currentPageNum--;
    updateButtons(currentPageNum, totalPageCount);
    emit pageChanged(currentPageNum);
  }
}

void ButtonPagination::onNextClicked() {
  if (currentPageNum < totalPageCount - 1) {
    currentPageNum++;
    updateButtons(currentPageNum, totalPageCount);
    emit pageChanged(currentPageNum);
  }
}
