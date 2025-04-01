#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "../controller/iauthcontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(IAuthController* controller, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_RegistrButton_clicked();
    void createMoneyWindow();
    void on_ConfirmButton_clicked();
    void showError(QString text);

private:
    IAuthController* m_controller;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
