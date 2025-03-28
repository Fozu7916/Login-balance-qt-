#ifndef MONEYCHANGE_H
#define MONEYCHANGE_H

#include <QMainWindow>
#include "Users.h"
#include "authcontroller.h"

namespace Ui {
class MoneyChange;
}

class MoneyChange : public QMainWindow
{
    Q_OBJECT
signals:


public:
    explicit MoneyChange(AuthController* controller,QWidget *parent = nullptr);
    ~MoneyChange();
    bool getFlag();
    void setFlag(bool boolean);
    void showError(QString text);



private slots:
    void on_ConfirmButton_clicked();

private:
    Ui::MoneyChange *ui;
    Users *user;
    AuthController* m_controller;
    bool flag;
};

#endif // MONEYCHANGE_H
