//moneywindow.cpp
#include "moneywindow.h"
#include "ui_moneywindow.h"
#include "Users.h"
#include "moneychange.h"
#include <QListWidgetItem>
#include <QString>
#include <QDateTime>
#include <qsqlerror.h>
#include <qsqlquery.h>
#include "changebackground.h"
#include "errorwindow.h"
#include "database.h"

MoneyWindow::MoneyWindow(Users &user, QSqlDatabase &db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MoneyWindow)
{
    ui->setupUi(this);
    this->user = &user;
    ui->MoneyLabel->setText(QString::number(user.getMoney()));
    setWindowTitle(user.getName());
    this->db = db;
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
    QString transaction;
    QString dateTimeString = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString operation;
    if(amount > 0){
        operation = " Пополнение: ";
    }
    else{
        operation = " Снятие: ";
    }

    transaction = dateTimeString + operation + QString::number(amount) + " Текущий баланс: " + QString::number(user->getMoney());
    ui->HistoryView->addItem(transaction);
    ui->MoneyLabel->setText(QString::number(user->getMoney()));

    DataBase current;
    if (!current.updateMoneyInDatabase(user->getMoney(),db,user)) {
        ErrorWindow::showWindow("Ошибка обновления money в базе данных");
    }
}



void MoneyWindow::openNewWindow(bool flag,const QString& phrase) {
    MoneyChange *change = new MoneyChange(*user);
    changebackground(change,":/images/2nd background.jpg");
    change->setFlag(flag);
    change->setWindowTitle(phrase);
    connect(change, &MoneyChange::moneyChanged, this, &MoneyWindow::updateDisplay);
    change->setAttribute(Qt::WA_DeleteOnClose);
    change->show();
}





