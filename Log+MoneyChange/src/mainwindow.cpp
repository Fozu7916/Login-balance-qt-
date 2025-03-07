//mainwindow.cpp
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "moneywindow.h"
#include "Users.h"
#include "errorwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/images/background.png");
    QPixmap scaledBkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QPalette pal;
    pal.setBrush(QPalette::Window, scaledBkgnd);
    this->setPalette(pal);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);

    //сделать коннект с дб vestor<Users> users - массив всех пользователей из дб
    Users NewUser("Fozu","qszxaw12");
    users.push_back(NewUser);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    bool user_finded = login(users);
    if(user_finded)
    {
        this->close();
        MoneyWindow *NewWindow = new MoneyWindow();
        NewWindow->show();
    }
    else
    {
        Error->show();
        Error->raise();
    }
}


bool MainWindow::login(std::vector<Users> users)
{
    bool user_finded = false;
    for(int i = 0;i<users.size();i++)
    {
        QString enteredUsername = users[i].getName();
        QString enteredPassword = users[i].getPassword();
        if(ui->lineEdit->text() == enteredUsername and ui->lineEdit_3->text() == enteredPassword )
        {
            users[i].money = 10000; // тут считывать значение с дб
            user_finded = true;
            break;
        }
    }
    return user_finded;
}







