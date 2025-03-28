//mainwindow.cpp
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include "authcontroller.h"
#include "moneywindow.h"
#include "registrwindow.h"
#include "changebackground.h"


MainWindow::MainWindow(AuthController* controller,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_controller(controller)
{
    ui->setupUi(this);
    changebackground(this,":/images/background.png");
    ui->PasEdit->setEchoMode(QLineEdit::Password);
    setupConnetions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ConfirmButton_clicked()
{
    if(login(ui->NameEdit->text(),ui->PasEdit->text())){
        m_controller->createMoneyWindow();
    }
    else{
       //
    }
}

bool MainWindow::login(QString username,QString password) {
    return m_controller->Login(username,password);
}

void MainWindow::on_RegistrButton_clicked()
{
    m_controller->createRegistrationWindow();
}

void MainWindow::setupConnetions(){
    connect(m_controller, &AuthController::moneyWindowRequested,this, &MainWindow::createMoneyWindow);
    connect(m_controller, &AuthController::registrationRequested,this, &MainWindow::createRegistrationWindow);
}


void MainWindow::createRegistrationWindow()
{
    RegistrWindow *regWindow = new RegistrWindow(m_controller->m_db);
    regWindow->setAttribute(Qt::WA_DeleteOnClose);
    regWindow->show();
}

void MainWindow::createMoneyWindow()
{
    MoneyWindow *window = new MoneyWindow(m_controller->m_currentUser,m_controller->m_db);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
}

