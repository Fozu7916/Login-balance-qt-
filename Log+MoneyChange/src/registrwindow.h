#ifndef REGISTRWINDOW_H
#define REGISTRWINDOW_H

#include <QMainWindow>
#include <qsqldatabase.h>
#include "Users.h"

namespace Ui {
class RegistrWindow;
}

class RegistrWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrWindow(std::vector<Users> *users,QSqlDatabase *db,QWidget *parent = nullptr);
    ~RegistrWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RegistrWindow *ui;
    QSqlDatabase *db;
    std::vector<Users> *users;
};

#endif // REGISTRWINDOW_H
