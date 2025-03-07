// users.cpp
#include "users.h"

Users::Users(QString first, QString second)
{
    name = first;
    password = second;
}

Users::~Users() {}

int Users::money = 0.0;//обязательная иницианализаиця

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
