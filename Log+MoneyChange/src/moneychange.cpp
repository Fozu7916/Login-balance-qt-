//moneychange.cpp
#include "moneychange.h"
#include "ui_moneychange.h"
#include "Users.h"
#include <QString>
#include <qregularexpression.h>
#include "errorwindow.h"

MoneyChange::MoneyChange(Users &user, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MoneyChange)
{
    ui->setupUi(this);
    this->user = &user;
}

MoneyChange::~MoneyChange()
{
    delete ui;
}

void MoneyChange::on_ConfirmButton_clicked() {
    int balance = user->getMoney();
    bool is_number;
    int amount = ui->MoneyEnter->text().toInt(&is_number);
    if( getFlag() and is_number and amount>= 0)
    {
        if (balance - amount < 0) {
         //   ErrorWindow::showWindow("Недостаточно средств");
            return;
        }
        MoneyChange::user->setMoney(balance - amount);
        emit moneyChanged(-1 * amount);
    }
    else if( !getFlag() and is_number and amount>= 0 and amount + balance <= INT_MAX)
    {
        MoneyChange::user->setMoney(balance + amount);
        emit moneyChanged(amount);
    }
    else
    {
       // ErrorWindow::showWindow("Неверное введёное значение");
    }
    close();
}

bool MoneyChange::getFlag(){
    return flag_decrease;
}



void MoneyChange::setFlag(bool boolean){
    flag_decrease = boolean;
}

