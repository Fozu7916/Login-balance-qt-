//moneychange.cpp
#include "moneychange.h"
#include "../controller/authcontroller.h"
#include "errorwindow.h"
#include "./ui_moneychange.h"
#include <QString>
#include <qregularexpression.h>

MoneyChange::MoneyChange(AuthController *controller,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MoneyChange)
    , m_controller(controller)
{
    ui->setupUi(this);
    connect(m_controller,&AuthController::error,this,&MoneyChange::showError);
}

MoneyChange::~MoneyChange()
{
    delete ui;
}

void MoneyChange::on_ConfirmButton_clicked() {
    m_controller->updateBalance(this->getIsWithdrawal(),ui->MoneyEnter->text().toInt());
    close();
}

bool MoneyChange::getIsWithdrawal(){
    return isWithdrawal;
}

void MoneyChange::setIsWithdrawal(bool isWithdrawal){
    this->isWithdrawal = isWithdrawal;
}

void MoneyChange::showError(QString text){
    ErrorWindow *err = new ErrorWindow();
    err->showWindow(text);
}
