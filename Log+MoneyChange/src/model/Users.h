#ifndef USERS_H
#define USERS_H



#include <QString>

class Users {
public:
    Users(QString first, QString second);
    Users();
    ~Users();



    QString getName() const;
    QString getPassword() const;
    int getMoney();

    void setPassword(const QString& password);
    void setName(const QString& name);
    void setMoney(int money_here);

private:
    QString name;
    QString password;
    int money;
};

#endif // USERS_H
