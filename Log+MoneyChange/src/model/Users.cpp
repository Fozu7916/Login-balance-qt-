// users.cpp
#include "users.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QList>
#include <qsqlerror.h>

Users::Users(QString first, QString second)
{
    name = first;
    password = second;
    money = 0;
}

Users::Users() : name(""), password(""), money(0) {}

Users::~Users() {}

int Users::getMoney(){
    return money;
}

QString Users::getName() const {
    return name;
}


QString Users::getPassword() const {
    return password;
}



void Users::setMoney(int money_here) {
    if(money_here >=0 and money_here <= INT_MAX){
        this->money = money_here;
    }
}

void Users::setName(const QString& name) {
    this->name = name;
}

void Users::setPassword(const QString& password) {
    this->password = password;
}



