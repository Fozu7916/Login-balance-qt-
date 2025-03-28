#include "database.h"
#include <QSqlDatabase>
#include <QString>
#include <qsqlerror.h>
#include <qsqlquery.h>
#include "Users.h"

DataBase::DataBase(QSqlDatabase &db)
    :m_db(db)
{

}


QSqlDatabase DataBase::connectToMySQL()
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");

    //тут данные из конфига
    m_db.setHostName("localhost");
    m_db.setPort(3306);
    m_db.setDatabaseName("users");
    m_db.setUserName("root");
    m_db.setPassword("root");

    if (!m_db.open()) {
       // ErrorWindow::showWindow("Ошибка подключения к таблице");
    }
    return m_db;
}


std::vector<Users> DataBase::getUsersFromDatabase() {
    std::vector<Users> users_from_db;
    QSqlQuery query(m_db);

    if (!query.exec("SELECT Name, Hash_Password, Money FROM users")) {
        //ErrorWindow::showWindow("Ошибка: таблица пуста");

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
      //  ErrorWindow::showWindow("Ошибка запроса getMoneyForUser");
        return -1;
    }
}

bool DataBase::updateMoneyInDatabase(int newMoney,Users *user) {
    if (!m_db.isOpen()) {
       // ErrorWindow::showWindow("Ошибка подключенияБаза данных не открыта в updateMoneyInDatabase!");
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare("UPDATE users SET money = ? WHERE Name = ?");
    query.addBindValue(newMoney);
    query.addBindValue(user->getName());

    if (!query.exec()) {
       /// ErrorWindow::showWindow("Ошибка обновления баланса");
        return false;
    }

    return true;
}


void DataBase::AddUser(std::vector<Users> *users,Users &user,QString password,QString username){
    bool userExists = false;
    for(const auto& user : *users) {
        if(user.getName() == username) {
            userExists = true;
            break;
        }
    }

    if(userExists) {
       // ErrorWindow::showWindow("Пользователь с таким именем уже существует!");
        return;
    }

    if (!m_db.isOpen()) {
      //  ErrorWindow::showWindow("Ошибка подключения к базе данных!");
        return;
    }

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO users (Name, Hash_Password, Money) VALUES (?, ?, 0)");
    query.addBindValue(username);

    query.addBindValue(password); 

    if (!query.exec()) {
       // ErrorWindow::showWindow("Ошибка создания пользователя: " + query.lastError().text());
        return;
    }


}




