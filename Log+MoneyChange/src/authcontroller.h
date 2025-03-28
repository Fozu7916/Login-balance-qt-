#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <qmainwindow.h>
#include <QObject>
#include <QWidget>
#include "database.h"
#include "Users.h"

class AuthController : public QObject
{
    Q_OBJECT
public:
    AuthController(DataBase &db, QObject* parent = nullptr);
    DataBase& m_db;
    Users m_currentUser;


signals:
    void registrationRequested();
    void moneyWindowRequested(Users* user);

public slots:
    bool Login(QString username,QString password);
    void createRegistrationWindow();
    void createMoneyWindow();


private:
};

#endif // AUTHCONTROLLER_H

