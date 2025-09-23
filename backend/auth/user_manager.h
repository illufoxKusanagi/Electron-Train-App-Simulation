#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QString>
#include <QTextStream>


class UserManager : public QObject {
  Q_OBJECT
public:
  UserManager(QObject *parent = nullptr);
  QString username() const { return m_username; }
  QString passwordHash() const { return m_passwordHash; }
  bool isLoaded() const { return m_loaded; }

private:
  QString m_username;
  QString m_passwordHash;
  bool m_loaded = false;
};

#endif // USER_MANAGER_H
