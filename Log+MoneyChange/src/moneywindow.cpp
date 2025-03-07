//moneywindow.cpp
#include "moneywindow.h"
#include "ui_moneywindow.h"

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
