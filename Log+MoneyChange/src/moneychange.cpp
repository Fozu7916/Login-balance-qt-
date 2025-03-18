//moneychange.cpp
#include "moneychange.h"
#include "ui_moneychange.h"
#include "Users.h"
#include <QString>
#include <qregularexpression.h>
#include "errorwindow.h"

MoneyChange::MoneyChange(Users *user,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MoneyChange)
{
    ui->setupUi(this);
    this->user = user;
}

MoneyChange::~MoneyChange()
{
    delete ui;
}

void MoneyChange::on_ConfirmButton_clicked() {
    int amount = ui->lineEdit->text().toInt(&ok);
    bool is_number;
    ui->lineEdit->text().toInt(&is_number);
    if(flag_decrease and is_number)
    {
        MoneyChange::user->money -= amount;
        emit moneyChanged(-amount);
    }
    else if(!flag_decrease and is_number)
    {
        MoneyChange::user->money += amount;
        emit moneyChanged(amount);
    }
    else
    {
        ErrorWindow *err = new ErrorWindow();
        err->setErrorMessage("Введено не числовое значение");
        err->show();
    }
    close();
}

