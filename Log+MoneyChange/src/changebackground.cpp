#include "changebackground.h"
#include "view/errorwindow.h"
#include <QPixmap>
#include <QPalette>
#include <QBrush>
#include <QSize>
#include <Qt>

void changebackground(QMainWindow *here,QString backgroundpath){
    QPixmap bkgnd(backgroundpath);
    if(bkgnd.isNull())
    {
        ErrorWindow *err = new ErrorWindow();
        err->showWindow("Не удалось загрузить фон");
    }
    QPixmap scaledBkgnd = bkgnd.scaled(here->size(), Qt::KeepAspectRatioByExpanding);
    QPalette pal;
    pal.setBrush(QPalette::Window, scaledBkgnd);
    here->setPalette(pal);
}
