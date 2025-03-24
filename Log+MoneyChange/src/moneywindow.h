#ifndef MONEYWINDOW_H
#define MONEYWINDOW_H

#include <QMainWindow>
#include "Users.h"
#include <QSqlDatabase>

namespace Ui {
class MoneyWindow;
}

class MoneyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MoneyWindow(Users *user,QSqlDatabase db,QWidget *parent = nullptr);
    ~MoneyWindow();
    void updateDisplay(int amount);
    QSqlDatabase db;
    bool updateMoneyInDatabase(int newMoney);
    void openNewWindow(bool flag,const QString& phrase);



private slots:
    void on_AddButton_clicked();
    void on_RemoveButton_clicked();

private:
    Ui::MoneyWindow *ui;
    Users *user;
};

#endif // MONEYWINDOW_H
