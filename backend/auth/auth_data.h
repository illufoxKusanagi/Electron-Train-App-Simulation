#ifndef AUTH_DATA_H
#define AUTH_DATA_H

#include <QString>

class UserData {
public:
  UserData() = default;
  UserData::UserData(const QString &username, const QString &passwordHash)
      : m_username(username), m_passwordHash(passwordHash) {}
  QString UserData::getUsername() const { return m_username; }
  QString UserData::getPasswordHash() const { return m_passwordHash; }

private:
  QString m_username;
  QString m_passwordHash;
};
#endif // AUTH_DATA_H
