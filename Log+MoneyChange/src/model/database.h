#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include "Users.h"
#include <vector>

class DataBase
{
public:
    DataBase(QSqlDatabase db);
    int getMoneyFromUser(const QString& username);
    QSqlDatabase connectToMySQL();
    bool updateMoneyInDatabase(int newMoney, Users *user);
    void addUser(QString password, QString username);
    Users getUserByUsername(const QString& username);

private:
    QSqlDatabase m_db;
};

#endif // DATABASE_H
