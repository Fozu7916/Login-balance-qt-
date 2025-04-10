//registrwindow.cpp
#include "registrwindow.h"
#include "errorwindow.h"
#include "ui_registrwindow.h"
#include <qsqlerror.h>
#include <qsqlquery.h>
#include "../controller/iauthcontroller.h"

RegistrWindow::RegistrWindow(IAuthController* controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegistrWindow)
    ,m_controller(controller)
{
    ui->setupUi(this);
    m_controller->connectToErrorSignal(m_controller, SLOT(error(QString)));
}

RegistrWindow::~RegistrWindow()
{
    delete ui;
}

void RegistrWindow::on_pushButton_clicked()
{
    m_controller->reg(ui->NameEdit->text(), ui->PasEdit->text(), ui->PasEdit_2->text());
    this->close();
}

void RegistrWindow::showError(QString text){
    ErrorWindow *err = new ErrorWindow();
    err->showWindow(text);
}
