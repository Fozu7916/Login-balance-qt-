#ifndef MONEYWINDOW_H
#define MONEYWINDOW_H

#include <QMainWindow>
#include "Users.h"
#include "database.h"
#include <QSqlDatabase>

namespace Ui {
class MoneyWindow;
}

class MoneyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MoneyWindow(Users &user, DataBase &db, QWidget *parent = nullptr);
    ~MoneyWindow();
    void updateDisplay(int amount);
    bool updateMoneyInDatabase(int newMoney);
    void openNewWindow(bool flag,const QString& phrase);



private slots:
    void on_AddButton_clicked();
    void on_RemoveButton_clicked();

private:
    Ui::MoneyWindow *ui;
    Users *user;
    DataBase &db;
};

#endif // MONEYWINDOW_H
