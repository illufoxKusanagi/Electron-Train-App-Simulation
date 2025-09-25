#include "login_dialog_widget.h"

LoginDialogWidget::LoginDialogWidget(QObject *parent) {
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setContentsMargins(32, 32, 32, 32);
  layout->setSpacing(20);
  layout->setAlignment(Qt::AlignCenter);

  QLabel *titleLabel = new QLabel("Train Simulation Login", this);
  titleLabel->setAlignment(Qt::AlignCenter);
  titleLabel->setStyleSheet("QLabel{" + TextStyle::BodyBigBold() +
                            "colors: " + Colors::StandardBlack.name() +
                            ";"
                            "}");
  layout->addWidget(titleLabel);

  QVBoxLayout *inputLayout = new QVBoxLayout(this);
  inputLayout->setContentsMargins(0, 0, 0, 0);
  inputLayout->setSpacing(8);
  inputLayout->setAlignment(Qt::AlignCenter);
  m_usernameInput = new InputWidget(this, InputType("field", "Username"));
  m_passwordInput = new InputWidget(this, InputType("field", "Password"));
  m_passwordInput->setEchoMode(QLineEdit::Password);
  m_usernameInput->setPlaceholderText("Enter username...");
  m_passwordInput->setPlaceholderText("Enter password...");
  m_usernameInput->setSize(256, 32);
  m_passwordInput->setSize(256, 32);

  inputLayout->addWidget(m_usernameInput);
  inputLayout->addWidget(m_passwordInput);

  m_loginButton = new ButtonAction(this, "Login", "no");
  m_loginButton->setEnabled(true);
  m_loginButton->setSize(256, 44);
  layout->addLayout(inputLayout);
  layout->addWidget(m_loginButton);
  connect(m_loginButton, &QPushButton::clicked, this,
          &LoginDialogWidget::onLoginButtonClicked);
  setFixedSize(350, 300);
  setWindowTitle("Login");
  setModal(true);
  setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void LoginDialogWidget::onLoginButtonClicked() {
  QString username = m_usernameInput->getTextValue();
  QString password = m_passwordInput->getTextValue();
  emit loginAttempt(username, password);
}
