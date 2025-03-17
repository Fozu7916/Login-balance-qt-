//mainwindow.cpp
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "moneywindow.h"
#include "Users.h"
#include "errorwindow.h"
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
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    connectToMySQL();
    users = getUsersFromDatabase(db);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    bool user_finded = login(users);
    if(user_finded)
    {
        this->hide();
        MoneyWindow *NewWindow = new MoneyWindow(MainWindow::current_user);
        changebackground(NewWindow,":/images/2nd background.jpg");
        NewWindow->show();
    }
    else
    {
        ErrorWindow *Error = new ErrorWindow();
        Error->show();
        Error->raise();
    }
}


bool MainWindow::login(std::vector<Users> &users){
    bool user_finded = false;
    for(int i = 0;i<users.size();i++)
    {
        QString enteredUsername = users[i].getName();
        QString enteredPassword = users[i].getPassword();
        if(ui->lineEdit->text() == enteredUsername and ui->lineEdit_3->text() == enteredPassword )
        {
            users[i].money = getMoneyForUser(enteredUsername); // тут считывать значение с дб
            user_finded = true;
            MainWindow::current_user = &users[i];
            break;
        }
    }
    return user_finded;
}


bool MainWindow::connectToMySQL() {
    MainWindow::db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("users");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        qCritical() << "Ошибка подключения:" << db.lastError().text();
        return false;
    }
    qDebug() << "Подключение успешно!";
    return true;
}


std::vector<Users> MainWindow::getUsersFromDatabase(QSqlDatabase &db) {
    std::vector<Users> users_from_db;
    if (!db.isOpen()) {
        qDebug() << "Ошибка: База данных не открыта.";
        return users_from_db;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT Name, Password, money FROM users")) {
        qDebug() << "Ошибка запроса:" << query.lastError().text();
        return users_from_db;
    }

    while (query.next()) {
        Users user;
        user.setName(query.value(0).toString());
        user.setPassword(query.value(1).toString());
        user.money = query.value(2).toInt();
        users_from_db.push_back(user);
    }

    return users_from_db;
}



int MainWindow::getMoneyForUser(const QString& username) {
    QSqlQuery query(db);
    query.prepare("SELECT money FROM users WHERE Name = ?");
    query.addBindValue(username);
    if (query.exec()) {
        if (query.next()) {
            bool ok;
            return query.value(0).toInt(&ok);
        } else {
            qWarning() << "Пользователь не найден";
            return -1;
        }

    } else {
        qCritical() << "Ошибка запроса getMoneyForUser:" << query.lastError().text();
        return -1;
    }
}
