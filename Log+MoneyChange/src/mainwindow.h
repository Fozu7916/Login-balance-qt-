#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "Users.h"

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
    QSqlDatabase db;


private slots:
    bool login(std::vector<Users> &users);
    bool connectToMySQL();
    std::vector<Users> getUsersFromDatabase(QSqlDatabase &db);
    int getMoneyForUser(const QString& username);
    void on_ConfirmButton_clicked();

    void on_RegistrButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<Users> users;
    Users *current_user;
};
#endif // MAINWINDOW_H
