//moneywindow.cpp
#include "moneywindow.h"
#include "ui_moneywindow.h"
#include "Users.h"
#include "moneychange.h"

MoneyWindow::MoneyWindow(Users *user,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MoneyWindow)
{
    ui->setupUi(this);
    this->user = user;
    ui->label_3->setText(QString::number(user->money));
    setWindowTitle(user->getName());
}

MoneyWindow::~MoneyWindow()
{
    delete ui;
}

void MoneyWindow::on_AddButton_clicked()
{
    MoneyChange *change = new MoneyChange(user);
    change->flag_decrease = false;
    change->setWindowTitle("Пополнить");
    connect(change, &MoneyChange::moneyChanged, this, &MoneyWindow::updateDisplay);
    change->show();
}



void MoneyWindow::on_RemoveButton_clicked()
{
    MoneyChange *change = new MoneyChange(user);
    change->flag_decrease = true;
    change->setWindowTitle("Cнять");
    connect(change, &MoneyChange::moneyChanged, this, &MoneyWindow::updateDisplay);
    change->show();
}

void MoneyWindow::updateDisplay() {
    ui->label_3->setText(QString::number(user->money));

}





