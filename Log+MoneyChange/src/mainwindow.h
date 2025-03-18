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
    void on_pushButton_clicked();
    bool login(std::vector<Users> &users);
    bool connectToMySQL();
    std::vector<Users> getUsersFromDatabase(QSqlDatabase &db);
    int getMoneyForUser(const QString& username);
private:
    Ui::MainWindow *ui;
    std::vector<Users> users;
    Users *current_user;
};
#endif // MAINWINDOW_H
