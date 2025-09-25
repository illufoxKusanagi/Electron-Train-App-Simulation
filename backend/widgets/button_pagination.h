#ifndef BUTTONPAGINATION_H
#define BUTTONPAGINATION_H

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class ButtonPagination : public QWidget {
  Q_OBJECT

public:
  explicit ButtonPagination(QWidget *parent = nullptr);
  void updateButtons(int currentPage, int totalPages);

signals:
  void pageChanged(int newPage);

private slots:
  void onPrevClicked();
  void onNextClicked();

private:
  QPushButton *prevButton;
  QPushButton *nextButton;
  QLabel *pageLabel;
  int currentPageNum = 0;
  int totalPageCount = 1;
};

#endif