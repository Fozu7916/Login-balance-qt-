#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <qmainwindow.h>
#include <QObject>
#include <QWidget>
#include "database.h"
#include "Users.h"
#include <QString>

class AuthController : public QObject
{
    Q_OBJECT
public:
    AuthController(DataBase &db, QObject* parent = nullptr);
    DataBase& getDatabase()  {return m_db;}
    Users& getUser() {return m_currentUser;}


signals:
    void registrationRequested();
    void moneyWindowRequested(Users& user);
    void error(QString text);
    void moneyChanged(int amount);

public slots:
    void login(QString username,QString password);
    void reg(QString username, QString password, QString password2);
    QString updateDisplay(int amount);
    void updateBalance(bool flag,int amount);

private:
    DataBase& m_db;
    Users m_currentUser;
};

#endif // AUTHCONTROLLER_H

