#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "authcontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(AuthController* controller,QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void createRegistrationWindow();
    void createMoneyWindow();
    void on_ConfirmButton_clicked();
    void showError(QString text);

private:
    AuthController* m_controller;
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
