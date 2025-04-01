//moneywindow.cpp
#include "moneywindow.h"
#include "ui_moneywindow.h"
#include "moneychange.h"
#include "../model/Users.h"
#include <QListWidgetItem>
#include <QString>
#include <QDateTime>
#include "../changebackground.h"

MoneyWindow::MoneyWindow(IAuthController *controller, QWidget *parent)   
    : QMainWindow(parent)
    , ui(new Ui::MoneyWindow)
    ,m_controller(controller)
{
    ui->setupUi(this);
    ui->MoneyLabel->setText(QString::number(m_controller->getUser().getMoney()));
    setWindowTitle(m_controller->getUser().getName());
    changebackground(this, ":/images/2nd background.jpg");

    m_controller->connectToMoneyChangedSignal(this, SLOT(updateDisplay(int)));
    loadTransactionHistory();
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

void MoneyWindow::loadTransactionHistory() {
    ui->HistoryView->clear();
    QList<QString> history = m_controller->getTransactionHistory();
    // Добавляем транзакции в обратном порядке (самые новые сверху)
    for (const QString& transaction : history) {
        ui->HistoryView->addItem(transaction);
    }
}

void MoneyWindow::updateDisplay(int amount) {
    QString transaction = m_controller->updateDisplay(amount);
    if (transaction != "ERROR!") {
        ui->MoneyLabel->setText(QString::number(m_controller->getUser().getMoney()));
        loadTransactionHistory();
    }
}

void MoneyWindow::openNewWindow(bool isWithdrawal,const QString& phrase) {
    MoneyChange *change = new MoneyChange(m_controller);
    changebackground(change,":/images/2nd background.jpg");
    change->setIsWithdrawal(isWithdrawal);
    change->setWindowTitle(phrase);
    change->setAttribute(Qt::WA_DeleteOnClose);
    change->show();
}


