#include "changebackground.h"
#include <QPixmap>
#include <QPalette>
#include <QBrush>
#include <QSize>
#include <Qt>
#include "errorwindow.h"

void changebackground(QMainWindow *here,QString backgroundpath){
    QPixmap bkgnd(backgroundpath);
    if(bkgnd.isNull())
    {
        ErrorWindow::showWindow("Не удалось загрузить фон!");
    }
    QPixmap scaledBkgnd = bkgnd.scaled(here->size(), Qt::KeepAspectRatioByExpanding);
    QPalette pal;
    pal.setBrush(QPalette::Window, scaledBkgnd);
    here->setPalette(pal);
}
