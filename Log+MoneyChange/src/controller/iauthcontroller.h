#ifndef IAUTHCONTROLLER_H
#define IAUTHCONTROLLER_H

#include <QObject>
#include "../model/idatabase.h"
#include "../model/Users.h"

class IAuthController : public QObject
{
public:
    explicit IAuthController(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~IAuthController() {}

    virtual IDataBase& getDatabase() = 0;
    virtual Users& getUser() = 0;

    virtual void login(QString username, QString password) = 0;
    virtual void reg(QString username, QString password, QString password2) = 0;
    virtual QString updateDisplay(int amount) = 0;
    virtual void updateBalance(bool isWithdrawal, int amount) = 0;
    virtual QList<QString> getTransactionHistory() const = 0;


// Виртуальные методы для подключения к сигналам
    virtual void connectToErrorSignal(QObject* receiver, const char* method) = 0;
    virtual void connectToMoneyChangedSignal(QObject* receiver, const char* method) = 0;
    virtual void connectToMoneyWindowRequestedSignal(QObject* receiver, const char* method) = 0;
};

#endif // IAUTHCONTROLLER_H

