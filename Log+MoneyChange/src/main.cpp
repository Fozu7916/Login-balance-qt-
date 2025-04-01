//main.cpp
#include "view/mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QSqlDatabase>
#include <QPluginLoader>
#include "model/database.h"
#include "controller/authcontroller.h"


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
