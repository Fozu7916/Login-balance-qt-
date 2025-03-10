#ifndef MONEYCHANGE_H
#define MONEYCHANGE_H

#include <QMainWindow>
#include "Users.h"

namespace Ui {
class MoneyChange;
}

class MoneyChange : public QMainWindow
{
    Q_OBJECT
signals:
    void moneyChanged(int amount);

public:
    explicit MoneyChange(Users *user,QWidget *parent = nullptr);
    ~MoneyChange();
    bool flag_decrease;



private slots:
    void on_ConfirmButton_clicked();

private:
    Ui::MoneyChange *ui;
    Users *user;
};

#endif // MONEYCHANGE_H
