//moneywindow.cpp
#include "moneywindow.h"
#include "ui_moneywindow.h"
#include "moneychange.h"
#include "../model/Users.h"
#include <QListWidgetItem>
#include <QString>
#include <QDateTime>
#include "../changebackground.h"

MoneyWindow::MoneyWindow(AuthController *controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MoneyWindow)
    ,m_controller(controller)
{
    ui->setupUi(this);
    ui->MoneyLabel->setText(QString::number(m_controller->getUser().getMoney()));
    setWindowTitle(m_controller->getUser().getName());
}

MoneyWindow::~MoneyWindow()
{
    delete ui;
}

void MoneyWindow::on_AddButton_clicked() {
    MoneyWindow::openNewWindow(false,"Пополнить");
}

void MoneyWindow::on_RemoveButton_clicked() {
    MoneyWindow::openNewWindow(true,"Снять");
}

void MoneyWindow::updateDisplay(int amount) {
    ui->HistoryView->addItem(m_controller->updateDisplay(amount));
    ui->MoneyLabel->setText(QString::number(m_controller->getUser().getMoney()));
}

void MoneyWindow::openNewWindow(bool isWithdrawal,const QString& phrase) {
    MoneyChange *change = new MoneyChange(m_controller);
    connect(m_controller, &AuthController::moneyChanged, this, &MoneyWindow::updateDisplay);
    changebackground(change,":/images/2nd background.jpg");
    change->setIsWithdrawal(isWithdrawal);
    change->setWindowTitle(phrase);
    change->setAttribute(Qt::WA_DeleteOnClose);
    change->show();
}





