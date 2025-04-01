#ifndef MONEYWINDOW_H
#define MONEYWINDOW_H

#include <QMainWindow>
#include "../controller/iauthcontroller.h"

namespace Ui {
class MoneyWindow;
}

class MoneyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MoneyWindow(IAuthController* controller,QWidget *parent = nullptr);
    ~MoneyWindow();

    void updateDisplay(int amount);
    void loadTransactionHistory();
    void openNewWindow(bool isWithdrawal,const QString& phrase);

private slots:
    void on_AddButton_clicked();
    void on_RemoveButton_clicked();

private:
    Ui::MoneyWindow *ui;
    IAuthController* m_controller;
};

#endif // MONEYWINDOW_H
