#ifndef LOGIN_DIALOG_WIDGET_H
#define LOGIN_DIALOG_WIDGET_H

#include "button_action.h"
#include "input_widget.h"
#include "message_box_widget.h"
#include "styles/colors.h"
#include "styles/text_style.h"
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QVBoxLayout>

class LoginDialogWidget : public QDialog {
  Q_OBJECT

signals:
  void loginAttempt(const QString &username, const QString &password);

private slots:
  void onLoginButtonClicked();

public:
  explicit LoginDialogWidget(QObject *parent = nullptr);

private:
  InputWidget *m_usernameInput;
  InputWidget *m_passwordInput;
  ButtonAction *m_loginButton;
  ButtonAction *m_cancelButton;
};

#endif // LOGIN_DIALOG_WIDGET_H