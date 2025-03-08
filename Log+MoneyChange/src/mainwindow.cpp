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
    //connect_on_db();
    Users NewUser("","");
    users.push_back(NewUser);
    Users NewUser2("Fozu","qszxaw12");
    users.push_back(NewUser2);
    Users NewUser3("qq","ww");
    users.push_back(NewUser3);


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
        this->hide();
        MoneyWindow *NewWindow = new MoneyWindow(MainWindow::current_user);
        NewWindow->show();
    }
    else
    {
        ErrorWindow *Error = new ErrorWindow();
        Error->show();
        Error->raise();
    }
}


bool MainWindow::login(std::vector<Users> &users)
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
            MainWindow::current_user = &users[i];
            break;
        }
    }
    return user_finded;
}






