#include "authcontroller.h"
#include "database.h"
#include "Users.h"
#include "database.h"
#include <qdatetime.h>
#include "hashutils.h"

AuthController::AuthController(DataBase &db, QObject *parent)
    : QObject(parent), m_db(db) {}


void AuthController::login(QString username, QString password){
    std::vector<Users> users = m_db.getUsersFromDatabase();
    QString hashedPassword = HashUtils::hashPassword(password);
    
    for(auto& user : users) {
        if(username == user.getName() && hashedPassword == user.getPassword())
        {
            double money = m_db.getMoneyFromUser(username);
            user.setMoney(money);
            m_currentUser = user;
            emit moneyWindowRequested(m_currentUser);
            return;
        }
    }
    emit error("Неверный логин или пароль");
    return;
}

void AuthController::reg(QString username, QString password, QString password2){
    if(password != password2) {
        emit error("Пароли не совпадают");
        return;
    }

    bool userExists = false;
    std::vector<Users> users = m_db.getUsersFromDatabase();
    for(const auto& user : users) {
        if(user.getName() == username) {
            userExists = true;
            break;
        }
    }

    if(userExists) {
        emit error("Пользователь с таким именем уже существует!");
        return;
    }

    QString hashedPassword = HashUtils::hashPassword(password);
    m_db.addUser(hashedPassword, username);
}


QString AuthController::updateDisplay(int amount) {
    QString transaction;
    QString dateTimeString = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString operation;
    if(amount > 0){
        operation = " Пополнение: ";
    }
    else{
        operation = " Снятие: ";
    }
    transaction = dateTimeString + operation + QString::number(amount) + " Текущий баланс: " + QString::number(m_currentUser.getMoney());
    if (!m_db.updateMoneyInDatabase(m_currentUser.getMoney(),&m_currentUser)) {
        return "ERROR!";
    }
    else{
        return transaction;
    }
}


void AuthController::updateBalance(bool flag,int amount){
    int balance = m_currentUser.getMoney();
    if( flag and QString::number(amount).toInt() == amount)
    {
        if (balance - amount < 0) {
            emit error("Недостаточно средств");
            return;
        }
        m_currentUser.setMoney(balance - amount);
        emit moneyChanged(-1 * amount);
    }
    else if( !flag and  QString::number(amount).toInt() == amount and amount + balance <= INT_MAX)
    {
        m_currentUser.setMoney(balance + amount);
        emit moneyChanged(amount);
    }
    else
    {
       emit error("Неверное введёное значение");
    }
}

