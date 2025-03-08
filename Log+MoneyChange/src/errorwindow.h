#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

#include <QMainWindow>

namespace Ui {
class ErrorWindow;
}

class ErrorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ErrorWindow(QWidget *parent = nullptr);
    void setErrorMessage(const QString& message);
    ~ErrorWindow();
    bool window_showed;
private slots:
    void on_pushButton_clicked();

private:
    Ui::ErrorWindow *ui;
};

#endif // ERRORWINDOW_H
