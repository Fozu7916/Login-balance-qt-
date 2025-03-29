#ifndef MONEYWINDOW_H
#define MONEYWINDOW_H

#include <QMainWindow>
#include "../controller/authcontroller.h"
#include <QSqlDatabase>

namespace Ui {
class MoneyWindow;
}

class MoneyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MoneyWindow(AuthController* controller,QWidget *parent = nullptr);
    ~MoneyWindow();
    void updateDisplay(int amount);
    bool updateMoneyInDatabase(int newMoney);
    void openNewWindow(bool flag,const QString& phrase);



private slots:
    void on_AddButton_clicked();
    void on_RemoveButton_clicked();

private:
    Ui::MoneyWindow *ui;
    AuthController* m_controller;
};

#endif // MONEYWINDOW_H
