#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include "Users.h"
#include "idatabase.h"

class DataBase : public IDataBase
{
    Q_OBJECT
public:
    explicit DataBase(QSqlDatabase db, QObject *parent = nullptr) : IDataBase(parent), m_db(db) {};

    int getMoneyFromUser(const QString& username) override;
    QSqlDatabase connectToMySQL() override;
    bool updateMoneyInDatabase(int newMoney, Users *user) override;
    void addUser(QString password, QString username) override;
    Users getUserByUsername(const QString& username) override;
    void updateTransaction(const QString& username, const QString& operation, int amount, int balance, const QString& datetime) override;    
    QList<QString> getTransactionHistory(const QString& username) override;
private:
    QSqlDatabase m_db;
};

#endif // DATABASE_H
