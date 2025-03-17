//main.cpp
#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QSqlDatabase>
#include <QPluginLoader>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
