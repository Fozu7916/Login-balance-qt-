#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <QObject>
#include "../model/idatabase.h"
#include "../model/Users.h"
#include "iauthcontroller.h"

class AuthController : public IAuthController
{
    Q_OBJECT
public:
    AuthController(IDataBase &db, QObject* parent = nullptr);
    IDataBase& getDatabase() override {return m_db;}
    Users& getUser() override {return m_currentUser;}


    void connectToErrorSignal(QObject* receiver, const char* method) override; 
    void connectToMoneyChangedSignal(QObject* receiver, const char* method) override; 
    void connectToMoneyWindowRequestedSignal(QObject* receiver, const char* method) override ;
    

signals:
    void registrationRequested();
    void moneyWindowRequested(Users& user);
    void error(QString text);
    void moneyChanged(int amount);

public slots:
    void login(QString username,QString password) override;
    void reg(QString username, QString password, QString password2) override;
    QString updateDisplay(int amount) override;
    void updateBalance(bool isWithdrawal, int amount) override;
    QList<QString> getTransactionHistory() const override;
private:
    IDataBase& m_db;
    Users m_currentUser;
};

#endif // AUTHCONTROLLER_H

