#include "user_manager.h"

#include <QDebug>
UserManager::UserManager(QObject *parent) : QObject(parent) {
  QFile file(":/auth/.auth");
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    while (!in.atEnd()) {
      QString line = in.readLine();
      if (line.startsWith("ADMIN_USERNAME="))
        m_username = line.section('=', 1);
      else if (line.startsWith("ADMIN_PASSWORD_HASH="))
        m_passwordHash = line.section('=', 1);
    }
    file.close();
    m_loaded = !(m_username.isEmpty() || m_passwordHash.isEmpty());
  } else {
    m_loaded = false;
  }
}
