#include "moneychange.h"
#include "ui_moneychange.h"

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
