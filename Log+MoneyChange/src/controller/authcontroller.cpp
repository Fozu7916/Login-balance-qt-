#include "authcontroller.h"
#include "../model/database.h"
#include "../model/Users.h"
#include <qdatetime.h>
#include "../hashutils.h"

AuthController::AuthController(DataBase &db, QObject *parent)
    : QObject(parent), m_db(db) {}

void AuthController::login(QString username, QString password) {

    Users user = m_db.getUserByUsername(username);
    if (user.getName().isEmpty()) {
        emit error("Пользователь не найден");
        return;
    }

    if (HashUtils::verifyPassword(password, user.getPassword())) {
        m_currentUser = user;
        emit moneyWindowRequested(m_currentUser);
    } else {
        emit error("Неверный пароль");
    }
}


void AuthController::reg(QString username, QString password, QString password2) {
    if (password != password2) {
        emit error("Пароли не совпадают");
        return;
    }

    Users existingUser = m_db.getUserByUsername(username);
    if (!existingUser.getName().isEmpty()) {
        emit error("Пользователь с таким именем уже существует!");
        return;
    }

    QString hashedPassword = HashUtils::hashPassword(password);
    m_db.addUser(hashedPassword, username);
    
    emit registrationRequested();
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


void AuthController::updateBalance(bool isWithdrawal,int amount){
    int balance = m_currentUser.getMoney();
    if( isWithdrawal and QString::number(amount).toInt() == amount)
    {
        if (balance - amount < 0) {
            emit error("Недостаточно средств");
            return;
        }
        m_currentUser.setMoney(balance - amount);
        emit moneyChanged(-1 * amount);
    }
    else if( !isWithdrawal and  QString::number(amount).toInt() == amount and amount + balance <= INT_MAX)
    {
        m_currentUser.setMoney(balance + amount);
        emit moneyChanged(amount);
    }
    else
    {
       emit error("Неверное введёное значение");
    }
}

