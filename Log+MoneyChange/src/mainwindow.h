#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "Users.h"
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    bool login(std::vector<Users> &users);
    void on_ConfirmButton_clicked();
    void on_RegistrButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<Users> users;
    Users *current_user;
    QSqlDatabase db;
    DataBase current;

};
#endif // MAINWINDOW_H
