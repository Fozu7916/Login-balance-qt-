#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Users.h"
#include "errorwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    bool login(std::vector<Users> users);


private:
    Ui::MainWindow *ui;
    std::vector<Users> users;
    ErrorWindow *Error = new ErrorWindow();
};
#endif // MAINWINDOW_H
