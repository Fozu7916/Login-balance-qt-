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

MoneyWindow::MoneyWindow(Users *user,QSqlDatabase db,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MoneyWindow)
{
    ui->setupUi(this);
    this->user = user;
    ui->label_3->setText(QString::number(user->money));
    setWindowTitle(user->getName());
    this->db = db;
}

MoneyWindow::~MoneyWindow()
{
    delete ui;
}



void MoneyWindow::on_AddButton_clicked() {
    MoneyChange *change = new MoneyChange(user);
    changebackground(change,":/images/2nd background.jpg");
    change->flag_decrease = false;
    change->setWindowTitle("Пополнить");
    connect(change, &MoneyChange::moneyChanged, this, &MoneyWindow::updateDisplay);
    change->show();
}



void MoneyWindow::on_RemoveButton_clicked() {
    MoneyChange *change = new MoneyChange(user);
    changebackground(change,":/images/2nd background.jpg");
    change->flag_decrease = true;
    change->setWindowTitle("Cнять");
    connect(change, &MoneyChange::moneyChanged, this, &MoneyWindow::updateDisplay);
    change->show();
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

    transaction = dateTimeString + operation + QString::number(amount) + " Текущий баланс: " + QString::number(user->money);
    ui->HistoryView->addItem(transaction);
    ui->label_3->setText(QString::number(user->money));

    if (!updateMoneyInDatabase(user->money)) {
        qCritical() << "Ошибка обновления money в базе данных";
    }
}

bool MoneyWindow::updateMoneyInDatabase(int newMoney) {
    if (!db.isOpen()) {
        qCritical() << "База данных не открыта в updateMoneyInDatabase!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE users SET money = ? WHERE Name = ?");
    query.addBindValue(newMoney);
    query.addBindValue(user->getName());

    if (!query.exec()) {
        qCritical() << "Ошибка при выполнении запроса UPDATE:" << query.lastError().text();
        return false;
    }

    return true;
}





