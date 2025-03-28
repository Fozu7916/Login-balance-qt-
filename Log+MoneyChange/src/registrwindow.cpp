#include "registrwindow.h"
#include "ui_registrwindow.h"
#include <qsqlerror.h>
#include <qsqlquery.h>
#include "database.h"

RegistrWindow::RegistrWindow(DataBase &db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegistrWindow)
    , db(db)
{
    ui->setupUi(this);
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
    Users user(username,password);


    if(ui->PasEdit->text() != ui->PasEdit_2->text()) {
     //   ErrorWindow::showWindow("Пароли не совпадают!");
        return;
    }

    db.AddUser(this->users,user,password,username);

    Users newUser(username, password);
    newUser.setMoney(0);
    RegistrWindow::users->push_back(newUser);

    this->close();
}

