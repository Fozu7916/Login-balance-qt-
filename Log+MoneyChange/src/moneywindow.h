#ifndef MONEYWINDOW_H
#define MONEYWINDOW_H

#include <QMainWindow>
#include "Users.h"

namespace Ui {
class MoneyWindow;
}

class MoneyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MoneyWindow(Users *user,QWidget *parent = nullptr);
    ~MoneyWindow();
    void updateDisplay();



private slots:
    void on_AddButton_clicked();
    void on_RemoveButton_clicked();

private:
    Ui::MoneyWindow *ui;
    Users *user;
};

#endif // MONEYWINDOW_H
