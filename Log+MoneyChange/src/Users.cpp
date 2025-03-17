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
}

Users::Users() {}

Users::~Users() {}


QString Users::getName() const {
    return name;
}

void Users::setName(const QString& name) {
    this->name = name;
}

QString Users::getPassword() const {
    return password;
}

void Users::setPassword(const QString& password) {
    this->password = password;
}


