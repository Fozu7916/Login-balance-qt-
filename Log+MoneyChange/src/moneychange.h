#ifndef MONEYCHANGE_H
#define MONEYCHANGE_H

#include <QMainWindow>

namespace Ui {
class MoneyChange;
}

class MoneyChange : public QMainWindow
{
    Q_OBJECT

public:
    explicit MoneyChange(QWidget *parent = nullptr);
    ~MoneyChange();
    bool flag_decrease;



private slots:
    void on_ConfirmButton_clicked();

private:
    Ui::MoneyChange *ui;
};

#endif // MONEYCHANGE_H
