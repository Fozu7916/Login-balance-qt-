#include "database.h"
#include <QSqlDatabase>
#include <QString>
#include <qsqlquery.h>
#include "Users.h"
#include "errorwindow.h"

DataBase::DataBase() {}


bool DataBase::connectToMySQL(QSqlDatabase &db) {
    db = QSqlDatabase::addDatabase("QMYSQL");

    //тут данные из конфига
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("users");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        ErrorWindow::showWindow("Ошибка подключения к таблице");
        return false;
    }
    return true;
}


std::vector<Users> DataBase::getUsersFromDatabase(QSqlDatabase &db) {
    std::vector<Users> users_from_db;
    QSqlQuery query(db);

    if (!query.exec("SELECT Name, Hash_Password, Money FROM users")) {
        ErrorWindow::showWindow("Ошибка: таблица пуста");

    }

    while (query.next()) {
        Users user;
        user.setName(query.value(0).toString());
        user.setPassword(query.value(1).toString());
        user.setMoney(query.value(2).toInt());
        users_from_db.push_back(user);
    }

    return users_from_db;
}

int DataBase::getMoneyFromUser(QSqlDatabase &db, const QString& username) {
    QSqlQuery query(db);
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
        ErrorWindow::showWindow("Ошибка запроса getMoneyForUser");
        return -1;
    }
}

bool DataBase::updateMoneyInDatabase(int newMoney, QSqlDatabase &db, Users *user) {
    if (!db.isOpen()) {
        ErrorWindow::showWindow("Ошибка подключенияБаза данных не открыта в updateMoneyInDatabase!");
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE users SET money = ? WHERE Name = ?");
    query.addBindValue(newMoney);
    query.addBindValue(user->getName());

    if (!query.exec()) {
        ErrorWindow::showWindow("Ошибка обновления баланса");
        return false;
    }

    return true;
}
