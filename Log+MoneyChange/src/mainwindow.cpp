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




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    changebackground(this,":/images/background.png");
    ui->PasEdit->setEchoMode(QLineEdit::Password);
    if(connectToMySQL()) {
        users = getUsersFromDatabase(db);
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
        MoneyWindow *NewWindow = new MoneyWindow(MainWindow::current_user,db);
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
            user.setMoney(getMoneyForUser(trueUsername));
            current_user = &user;
            return true;
        }
    }
    return false;
}


bool MainWindow::connectToMySQL() {
    MainWindow::db = QSqlDatabase::addDatabase("QMYSQL");

    //тут меняем данные под нашу конкретную бд
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("users");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        ErrorWindow::showWindow("Ошибка подключения к таблице");
        return false;
    }
    return true;
}


std::vector<Users> MainWindow::getUsersFromDatabase(QSqlDatabase &db) {
    std::vector<Users> users_from_db;
    QSqlQuery query(db);



    if (!query.exec("SELECT Name, Hash_Password, Money FROM users")) {
        ErrorWindow::showWindow("Ошибка: таблица пуста");

    }

    while (query.next()) {
        Users user;
        user.setName(query.value(0).toString());
        user.setPassword(query.value(1).toString());
        user.setMoney(query.value(2).toInt());
        users_from_db.push_back(user);
    }

    return users_from_db;
}



int MainWindow::getMoneyForUser(const QString& username) {
    QSqlQuery query(db);
    query.prepare("SELECT Money FROM users WHERE Name = ?");
    query.addBindValue(username);
    if (query.exec()) {
        if (query.next()) {
            bool ok;
            return query.value(0).toInt(&ok);
        }
        else {
            return -1;
        }

    }
    else {
        ErrorWindow::showWindow("Ошибка запроса getMoneyForUser");
        return -1;
    }
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

