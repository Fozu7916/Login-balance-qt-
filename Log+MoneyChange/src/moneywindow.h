#ifndef MONEYWINDOW_H
#define MONEYWINDOW_H

#include <QMainWindow>
#include "users.h"


namespace Ui {
class MoneyWindow;
}

class MoneyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MoneyWindow(QWidget *parent = nullptr);
    ~MoneyWindow();

    //Для считывания баланса
    Users *new_user = new Users("1","1");


private slots:
    void on_AddButton_clicked();

    void on_RemoveButton_clicked();

private:
    Ui::MoneyWindow *ui;
};

#endif // MONEYWINDOW_H
