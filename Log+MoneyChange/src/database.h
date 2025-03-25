#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include "Users.h"

class DataBase
{
public:
    DataBase();
    int getMoneyFromUser(QSqlDatabase &db,const QString& username);
    bool connectToMySQL(QSqlDatabase &db);
    std::vector<Users> getUsersFromDatabase(QSqlDatabase &db);
    bool updateMoneyInDatabase(int newMoney, QSqlDatabase &db, Users *user);
};

#endif // DATABASE_H
