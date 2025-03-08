//errorwindow.cpp
#include "errorwindow.h"
#include "ui_errorwindow.h"

ErrorWindow::ErrorWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ErrorWindow)
{
    ui->setupUi(this);
    window_showed = true;
}

ErrorWindow::~ErrorWindow()
{
        delete ui;
        window_showed = false;
}


void ErrorWindow::on_pushButton_clicked()
{
    this->close();
}


void ErrorWindow::setErrorMessage(const QString& message)
{
    ui->label->setText(message);
}
