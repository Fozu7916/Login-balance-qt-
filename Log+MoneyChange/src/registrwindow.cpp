#include "registrwindow.h"
#include "ui_registrwindow.h"
#include <qsqlerror.h>
#include <qsqlquery.h>
#include "errorwindow.h"

RegistrWindow::RegistrWindow(std::vector<Users> *users,QSqlDatabase *db,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegistrWindow)
{
    ui->setupUi(this);
    this->db = db;
    this->users = users;
}

RegistrWindow::~RegistrWindow()
{
    delete ui;
}

void RegistrWindow::on_pushButton_clicked()
{
    QString username = ui->NameEdit->text();
    QString password = ui->PasEdit->text();
    QString password2 = ui->PasEdit_2->text();


    if(ui->PasEdit->text() != ui->PasEdit_2->text()) {
        ErrorWindow::showWindow("Пароли не совпадают!");
        return;
    }


    bool userExists = false;
    for(const auto& user : *RegistrWindow::users) {
        if(user.getName() == username) {
            userExists = true;
            break;
        }
    }

    if(userExists) {
        ErrorWindow::showWindow("Пользователь с таким именем уже существует!");
        return;
    }

    if (!db->isOpen()) {
        ErrorWindow::showWindow("Ошибка подключения к базе данных!");
        return;
    }

    QSqlQuery query(*this->db);
    query.prepare("INSERT INTO users (Name, Hash_Password, Money) VALUES (?, ?, 0)");
    query.addBindValue(username);

    query.addBindValue(password); //тут делаем хеширование

    if (!query.exec()) {
        ErrorWindow::showWindow("Ошибка создания пользователя: " + query.lastError().text());
        return;
    }


    Users newUser(username, password);
    newUser.setMoney(0);
    RegistrWindow::users->push_back(newUser);

    this->close();
}

