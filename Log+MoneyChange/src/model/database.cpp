#include "database.h"
#include <QSqlDatabase>
#include <QString>
#include <qsqlerror.h>
#include <qsqlquery.h>
#include "Users.h"
#include "../view/errorwindow.h"
#include "../config.h"
#include <QSqlError>

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
        err->showWindow("Ошибка подключения к базе данных: " + m_db.lastError().text());
    }
    return m_db;
}

std::vector<Users> DataBase::getUsersFromDatabase() {
    std::vector<Users> usersFromDb;
    QSqlQuery query(m_db);

    // Используем подготовленный запрос с пустым условием
    query.prepare("SELECT Name, Hash_Password, Money FROM users WHERE 1=1");

    if (!query.exec()) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка получения пользователей: " + query.lastError().text());
        return usersFromDb;
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
    if (username.isEmpty()) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка: имя пользователя не может быть пустым");
        return -1;
    }

    QSqlQuery query(m_db);
    query.prepare("SELECT Money FROM users WHERE Name = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка запроса getMoneyFromUser: " + query.lastError().text());
        return -1;
    }

    if (query.next()) {
        bool ok;
        int money = query.value(0).toInt(&ok);
        if (!ok) {
            ErrorWindow *err = new ErrorWindow();
            err->showWindow("Ошибка: некорректное значение денег в базе данных");
            return -1;
        }
        return money;
    }
    
    return -1;
}

bool DataBase::updateMoneyInDatabase(int newMoney, Users *user) {
    if (!m_db.isOpen()) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка: база данных не открыта в updateMoneyInDatabase");
        return false;
    }

    if (!user || user->getName().isEmpty()) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка: некорректные данные пользователя");
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare("UPDATE users SET Money = :money WHERE Name = :username");
    query.bindValue(":money", newMoney);
    query.bindValue(":username", user->getName());

    if (!query.exec()) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка обновления баланса: " + query.lastError().text());
        return false;
    }

    if (query.numRowsAffected() == 0) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка: пользователь не найден");
        return false;
    }

    return true;
}

void DataBase::addUser(QString password, QString username) {
    if (username.isEmpty() || password.isEmpty()) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка: имя пользователя и пароль не могут быть пустыми");
        return;
    }

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO users (Name, Hash_Password, Money) VALUES (:username, :password, 0)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка создания пользователя: " + query.lastError().text());
        return;
    }
}




