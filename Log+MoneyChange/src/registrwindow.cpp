//registrwindow.cpp
#include "registrwindow.h"
#include "errorwindow.h"
#include "ui_registrwindow.h"
#include <qsqlerror.h>
#include <qsqlquery.h>

RegistrWindow::RegistrWindow(AuthController* controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegistrWindow)
    ,m_controller(controller)
{
    ui->setupUi(this);
    connect(m_controller,&AuthController::error,this,&RegistrWindow::showError);
}

RegistrWindow::~RegistrWindow()
{
    delete ui;
}

void RegistrWindow::on_pushButton_clicked()
{
    m_controller->reg(ui->NameEdit->text(),ui->PasEdit->text(),ui->PasEdit_2->text());
}

void RegistrWindow::showError(QString text){
    ErrorWindow *err = new ErrorWindow();
    err->showWindow(text);
}
