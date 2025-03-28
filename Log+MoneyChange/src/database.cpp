#include "database.h"
#include <QSqlDatabase>
#include <QString>
#include <qsqlerror.h>
#include <qsqlquery.h>
#include "Users.h"
#include "errorwindow.h"
#include "config.h"

DataBase::DataBase(QSqlDatabase db)
    :m_db(db)
{
}

QSqlDatabase DataBase::connectToMySQL()
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");

    m_db.setHostName(Config::DB_HOST);
    m_db.setPort(Config::DB_PORT);
    m_db.setDatabaseName(Config::DB_NAME);
    m_db.setUserName(Config::DB_USER);
    m_db.setPassword(Config::DB_PASSWORD);

    if (!m_db.open()) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка подключения к базе данных");
    }
    return m_db;
}

std::vector<Users> DataBase::getUsersFromDatabase() {
    std::vector<Users> usersFromDb;
    QSqlQuery query(m_db);

    if (!query.exec("SELECT Name, Hash_Password, Money FROM users")) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка: таблица пуста");
    }

    while (query.next()) {
        Users user;
        user.setName(query.value(0).toString());
        user.setPassword(query.value(1).toString());
        user.setMoney(query.value(2).toInt());
        usersFromDb.push_back(user);
    }

    return usersFromDb;
}

int DataBase::getMoneyFromUser(const QString& username) {
    QSqlQuery query(m_db);
    query.prepare("SELECT Money FROM users WHERE Name = ?");
    query.addBindValue(username);
    if (query.exec()) {
        if (query.next()) {
            bool ok;
            return query.value(0).toInt(&ok);
        }
        else {
            return -1;
        }
    }
    else {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка запроса getMoneyFromUser");
        return -1;
    }
}

bool DataBase::updateMoneyInDatabase(int newMoney, Users *user) {
    if (!m_db.isOpen()) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка: база данных не открыта в updateMoneyInDatabase");
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare("UPDATE users SET money = ? WHERE Name = ?");
    query.addBindValue(newMoney);
    query.addBindValue(user->getName());

    if (!query.exec()) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка обновления баланса");
        return false;
    }

    return true;
}

void DataBase::addUser(QString password, QString username) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO users (Name, Hash_Password, Money) VALUES (?, ?, 0)");
    query.addBindValue(username);
    query.addBindValue(password); 

    if (!query.exec()) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка создания пользователя: " + query.lastError().text());
        return;
    }
}




