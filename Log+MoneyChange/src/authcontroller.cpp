#include "authcontroller.h"
#include "database.h"
#include "Users.h"

AuthController::AuthController(DataBase &db, QObject *parent)
    : QObject(parent), m_db(db) {}


void AuthController::createMoneyWindow(){
    emit moneyWindowRequested(&m_currentUser);
}

void AuthController::createRegistrationWindow(){
    emit registrationRequested();
}


bool AuthController::Login(QString username, QString password)
{
    std::vector<Users> users = m_db.getUsersFromDatabase();
    for(auto& user : users) {
        if(username == user.getName() && password == user.getPassword())
        {
            double money = m_db.getMoneyFromUser(username);
            user.setMoney(money);
            m_currentUser = user;
            return true;
        }
    }

    return false;
}
