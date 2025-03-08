#include "moneychange.h"
#include "ui_moneychange.h"
#include "Users.h"
#include <QString>

MoneyChange::MoneyChange(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MoneyChange)
{
    ui->setupUi(this);
}

MoneyChange::~MoneyChange()
{
    delete ui;
}

void MoneyChange::on_ConfirmButton_clicked()
{
    Users here("1","1");
    if(flag_decrease)
    {
        here.money -=  ui->lineEdit->text().toInt();
        this->hide();
    }
    else if(!flag_decrease)
    {
        here.money +=  ui->lineEdit->text().toInt();
        this->hide();
    }
}

