#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QString>
#include "Users.h"

class IDataBase : public QObject
{
public:
    explicit IDataBase(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IDataBase() {}
    
    virtual int getMoneyFromUser(const QString& username) = 0;
    virtual QSqlDatabase connectToMySQL() = 0;
    virtual bool updateMoneyInDatabase(int newMoney, Users *user) = 0;
    virtual void addUser(QString password, QString username) = 0;
    virtual Users getUserByUsername(const QString& username) = 0;
    virtual void updateTransaction(const QString& username, const QString& operation, int amount, int balance, const QString& datetime) = 0;
    virtual QList<QString> getTransactionHistory(const QString& username) = 0;
};

#endif // IDATABASE_H
