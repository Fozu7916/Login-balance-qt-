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

private:
    Ui::MoneyChange *ui;
};

#endif // MONEYCHANGE_H
