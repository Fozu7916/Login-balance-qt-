//mainwindow.cpp
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "moneywindow.h"
#include "Users.h"
#include "errorwindow.h"
#include "registrwindow.h"
#include "changebackground.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <vector>
#include "database.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    changebackground(this,":/images/background.png");
    ui->PasEdit->setEchoMode(QLineEdit::Password);
    if(current.connectToMySQL(db)) {
        users = current.getUsersFromDatabase(db);
    }
    else
    {
       ErrorWindow::showWindow("Нету пользователей");
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ConfirmButton_clicked()
{
    bool user_finded = login(users);
    if(user_finded)
    {
        this->hide();
        MoneyWindow *NewWindow = new MoneyWindow(*MainWindow::current_user,db);
        changebackground(NewWindow,":/images/2nd background.jpg");
        NewWindow->setAttribute(Qt::WA_DeleteOnClose);
        NewWindow->show();
    }
    else
    {
        ErrorWindow::showWindow("Неверный логин или пароль");
    }
}

bool MainWindow::login(std::vector<Users> &users) {
    QString trueUsername = ui->NameEdit->text();
    QString truePassword = ui->PasEdit->text();

    for (auto& user : users) {
        if (trueUsername == user.getName() && truePassword == user.getPassword()) {
            user.setMoney(current.getMoneyFromUser(db,trueUsername));
            current_user = &user;
            return true;
        }
    }
    return false;
}

void MainWindow::on_RegistrButton_clicked()
{
    static bool isShown = false;
    if (!isShown) {
        RegistrWindow *RegWindow = new RegistrWindow(&this->users,&this->db);
        changebackground(RegWindow,":/images/background.png");
        RegWindow->setAttribute(Qt::WA_DeleteOnClose);
        RegWindow->show();
        isShown = true;
        QObject::connect(RegWindow, &RegistrWindow::destroyed, []{ isShown = false; });
    }

}

