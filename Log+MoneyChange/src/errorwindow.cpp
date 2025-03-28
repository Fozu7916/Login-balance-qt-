//errorwindow.cpp
#include "errorwindow.h"
#include "ui_errorwindow.h"

ErrorWindow::ErrorWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ErrorWindow)
{
    ui->setupUi(this);
}

ErrorWindow::~ErrorWindow()
{
        delete ui;
}

void ErrorWindow::setErrorMessage(const QString& message){
    ui->MainText->setText(message);
}

void ErrorWindow::on_ConfirmButton_clicked()
{
    this->close();
}

void ErrorWindow::showWindow(const QString& error) {
    static bool isShown = false;
    if (!isShown) {
        ErrorWindow *err = new ErrorWindow();
        err->setErrorMessage(error);
        err->setAttribute(Qt::WA_DeleteOnClose);
        err->show();
        err->raise();
        err->activateWindow();
        isShown = true;
        QObject::connect(err, &ErrorWindow::destroyed, []{ isShown = false; });
    }
}

