#include <QSqlError>
#include <QSqlDatabase>
#include <QString>
#include <qdatetime.h>
#include <qsqlerror.h>
#include <qsqlquery.h>
#include "Users.h"
#include "database.h"
#include "../view/errorwindow.h"
#include "../config.h"

DataBase::DataBase(QSqlDatabase db)
    :m_db(db)
{
}

QSqlDatabase DataBase::connectToMySQL()
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("localhost");
    m_db.setDatabaseName("users");
    m_db.setUserName("root");
    m_db.setPassword("root");

    if (!m_db.open()) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка подключения к базе данных: " + m_db.lastError().text());
        return m_db;
    }

    QSqlQuery query(m_db);
    


    // Создаем индексы для оптимизации запросов
    query.exec("CREATE INDEX IF NOT EXISTS idx_history_username ON history(username)");
    query.exec("CREATE INDEX IF NOT EXISTS idx_history_data ON history(data)");
    query.exec("CREATE INDEX IF NOT EXISTS idx_history_operation ON history(operation)");

    return m_db;
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

Users DataBase::getUserByUsername(const QString& username) {
    Users user;
    QSqlQuery query(m_db);
    query.prepare("SELECT Name, Hash_Password, Money FROM users WHERE Name = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка запроса getUserByUsername: " + query.lastError().text());
        return user;
    }

    if (query.next()) {
        user.setName(query.value(0).toString());
        user.setPassword(query.value(1).toString());
        user.setMoney(query.value(2).toInt());
    }

    return user;
}

void DataBase::updateTransaction(const QString& username, const QString& operation, int amount, int balance, const QString& datetime) {
    static QSqlQuery query(m_db);
    static bool prepared = false;
    
    if (!prepared) {
        query.prepare("INSERT INTO history (username, operation, amount, balance, data) "
                     "VALUES (:username, :operation, :amount, :balance, :data)");
        prepared = true;
    }
    
    query.bindValue(":username", username);
    query.bindValue(":operation", operation);
    query.bindValue(":amount", amount);
    query.bindValue(":balance", balance);
    query.bindValue(":data", datetime);

    if (!query.exec()) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка сохранения транзакции: " + query.lastError().text());
    }
}


QList<QString> DataBase::getTransactionHistory(const QString& username) {
    QList<QString> history;
    QSqlQuery query(m_db);
    
    // Получаем 10 последних транзакций, отсортированных по дате в обратном порядке
    query.prepare("SELECT data, operation, amount, balance FROM history "
                 "WHERE username = :username "
                 "ORDER BY data DESC "
                 "LIMIT 10");
    query.bindValue(":username", username);
    
    if (!query.exec()) {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Ошибка получения истории транзакций: " + query.lastError().text());
        return history;
    }
    
    while (query.next()) {
        QString dateTime = query.value(0).toString();
        QString operation = query.value(1).toString();
        int amount = query.value(2).toInt();
        int balance = query.value(3).toInt();
        
        QString transaction = dateTime + operation + QString::number(amount) + " Текущий баланс: " + QString::number(balance);
        history.append(transaction);
    }
    
    return history;
}