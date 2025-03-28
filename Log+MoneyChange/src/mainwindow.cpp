//mainwindow.cpp
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include "authcontroller.h"
#include "errorwindow.h"
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

    connect(ui->RegistrButton, &QPushButton::clicked,this, &MainWindow::createRegistrationWindow);
    connect(m_controller,&AuthController::error,this,&MainWindow::showError);
    connect(m_controller, &AuthController::moneyWindowRequested,this, &MainWindow::createMoneyWindow);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ConfirmButton_clicked(){
    m_controller->login(ui->NameEdit->text(),ui->PasEdit->text());
}

void MainWindow::createRegistrationWindow()
{
    RegistrWindow *regWindow = new RegistrWindow(m_controller);
    regWindow->setAttribute(Qt::WA_DeleteOnClose);
    regWindow->show();
}

void MainWindow::createMoneyWindow()
{
    MoneyWindow *window = new MoneyWindow(m_controller);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
    this->close();
}

void MainWindow::showError(QString text){
    ErrorWindow *err = new ErrorWindow();
    err->showWindow(text);
}

