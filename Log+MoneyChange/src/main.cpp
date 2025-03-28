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
    QSqlDatabase database;
    DataBase db(database);
    database = db.connectToMySQL();
    AuthController ath(db);
    MainWindow w(&ath);
    w.show();
    return a.exec();
}
