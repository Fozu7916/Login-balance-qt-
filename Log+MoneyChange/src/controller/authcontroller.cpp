#include "authcontroller.h"
#include "../model/Users.h"
#include "../model/idatabase.h"
#include "../hashutils.h"
#include <qdatetime.h>

AuthController::AuthController(IDataBase &db, QObject* parent)
    : IAuthController(parent)
    , m_db(db)
{}


void AuthController::connectToErrorSignal(QObject* receiver, const char* method) {
    connect(this, SIGNAL(error(QString)), receiver, method);
}
 
void AuthController::connectToMoneyChangedSignal(QObject* receiver, const char* slot) {
    connect(this, SIGNAL(moneyChanged(int)), receiver, slot);
}

void AuthController::connectToMoneyWindowRequestedSignal(QObject* receiver, const char* method) {
    connect(this, SIGNAL(moneyWindowRequested(Users&)), receiver, method);
}
    

void AuthController::login(QString username, QString password) {

    Users user = m_db.getUserByUsername(username);
    if (user.getName().isEmpty()) {
        emit error("Неверный логин или пароль");
        return;
    }

    if (HashUtils::verifyPassword(password, user.getPassword())) {
        m_currentUser = user;
        emit moneyWindowRequested(m_currentUser);
    } 
    else {
    return;
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
    
    m_db.updateTransaction(m_currentUser.getName(),operation,amount,m_currentUser.getMoney(),dateTimeString);
    return transaction;
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
        if (!m_db.updateMoneyInDatabase(m_currentUser.getMoney(), &m_currentUser)) {
            m_currentUser.setMoney(balance); // откатываем изменения если не удалось сохранить
            return;
        }
        emit moneyChanged(-1 * amount);
    }
    else if( !isWithdrawal and  QString::number(amount).toInt() == amount and amount + balance <= INT_MAX)
    {
        m_currentUser.setMoney(balance + amount);
        if (!m_db.updateMoneyInDatabase(m_currentUser.getMoney(), &m_currentUser)) {
            m_currentUser.setMoney(balance); // откатываем изменения если не удалось сохранить
            return;
        }
        emit moneyChanged(amount);
    }
    else
    {
       emit error("Неверное введёное значение(либо введены не цифры, либо итоговый баланс превыщает значение int)");
    }
}

QList<QString> AuthController::getTransactionHistory() const {
    return m_db.getTransactionHistory(m_currentUser.getName());
}
