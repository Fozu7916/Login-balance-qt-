#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include "Users.h"

class DataBase
{
public:
    DataBase(QSqlDatabase &db);
    int getMoneyFromUser(const QString& username);
    QSqlDatabase connectToMySQL();
    std::vector<Users> getUsersFromDatabase();
    bool updateMoneyInDatabase(int newMoney,Users *user);
    void AddUser(std::vector<Users> *users,Users &user,QString password,QString username);
private:
    QSqlDatabase &m_db;
};

#endif // DATABASE_H
