#ifndef REGISTRWINDOW_H
#define REGISTRWINDOW_H

#include <QMainWindow>
#include <qsqldatabase.h>
#include "Users.h"
#include "database.h"

namespace Ui {
class RegistrWindow;
}

class RegistrWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrWindow(DataBase &db, QWidget *parent = nullptr);
    ~RegistrWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RegistrWindow *ui;
    DataBase &db;
    std::vector<Users> *users;
};

#endif // REGISTRWINDOW_H
