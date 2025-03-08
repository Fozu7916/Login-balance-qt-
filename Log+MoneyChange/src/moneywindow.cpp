//moneywindow.cpp
#include "moneywindow.h"
#include "ui_moneywindow.h"
#include "moneychange.h"

MoneyWindow::MoneyWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MoneyWindow)
{
    ui->setupUi(this);
    ui->label_3->setText(QString::number(new_user->money));
}

MoneyWindow::~MoneyWindow()
{
    delete ui;
}

void MoneyWindow::on_AddButton_clicked()
{
    MoneyChange *m2 = new MoneyChange();
}


void MoneyWindow::on_RemoveButton_clicked()
{

}

