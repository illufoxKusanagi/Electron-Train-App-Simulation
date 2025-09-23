#include "auth_manager.h"
#include <qdebug.h>

AuthManager::AuthManager(UserManager *userManager, QObject *parent)
    : QObject(parent), m_userManager(userManager) {}

bool AuthManager::login(const QString &username, const QString &password) {
  if (!m_userManager || !m_userManager->isLoaded()) {
    return false;
  }

  QString inputHash = hashPassword(password);
  if (username == m_userManager->username() &&
      inputHash == m_userManager->passwordHash()) {
    m_authenticated = true;
    return true;
  }
  m_authenticated = false;
  return false;
}

bool AuthManager::isAuthenticated() const { return m_authenticated; }

QString AuthManager::hashPassword(const QString &password) {
  QByteArray hash =
      QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
  return QString(hash.toHex());
}

bool AuthManager::processLogin() {
  bool isLoggedIn = false;
  bool okUsername, okPassword;
  // QString username = QInputDialog::getText(
  //     nullptr, "Login", "Username:", QLineEdit::Normal, QString(), &okUsername);
  // if (!okUsername) {
  //   return 0;
  // }

  // QString password =
  //     QInputDialog::getText(nullptr, "Login", "Password:", QLineEdit::Password,
  //                           QString(), &okPassword);
  // if (!okPassword) {
  //   return 0;
  // }

  // if (login(username, password)) {
  //   isLoggedIn = true;
  //   QMessageBox::information(nullptr, "Login Successful",
  //                            "Welcome to the Train Simulation App!");
  // } else {
  //   QMessageBox::critical(nullptr, "Login Failed",
  //                         "Invalid username or password. Please try again.");
  // }
  return isLoggedIn;
}
