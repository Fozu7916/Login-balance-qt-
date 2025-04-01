#ifndef MONEYCHANGE_H
#define MONEYCHANGE_H

#include <QMainWindow>
#include "../model/Users.h"
#include "../controller/iauthcontroller.h"

namespace Ui {
class MoneyChange;
}

class MoneyChange : public QMainWindow
{
    Q_OBJECT
signals:


public:
    explicit MoneyChange(IAuthController* controller,QWidget *parent = nullptr);
    ~MoneyChange();
    bool getIsWithdrawal();
    void setIsWithdrawal(bool isWithdrawal);



private slots:
    void on_ConfirmButton_clicked();
    void showError(QString text);

private:
    Ui::MoneyChange *ui;
    Users *user;
    IAuthController* m_controller;
    bool isWithdrawal;
};

#endif // MONEYCHANGE_H
