#ifndef USERS_H
#define USERS_H



#include <QString>

class Users {
public:
    Users(QString first, QString second);
    Users();
    ~Users();

    int money;

    QString getName() const;
    void setName(const QString& name);
    QString getPassword() const;
    void setPassword(const QString& password);

private:
    QString name;
    QString password;
};

#endif // USERS_H
