#ifndef REGISTRWINDOW_H
#define REGISTRWINDOW_H

#include <QMainWindow>
#include <qsqldatabase.h>
#include "authcontroller.h"

namespace Ui {
class RegistrWindow;
}

class RegistrWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrWindow(AuthController* controller, QWidget *parent = nullptr);
    ~RegistrWindow();

private slots:
    void on_pushButton_clicked();
    void showError(QString text);

private:
    Ui::RegistrWindow *ui;
    AuthController* m_controller;
};

#endif // REGISTRWINDOW_H
