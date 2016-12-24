#include "QDebug"
#include "QSqlError"
#include "mainwindow.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("data.sqlite");
    if(!database.open()) {
        qDebug() << database.lastError().text();
        return 1;
    }

    w.init(&database);
    w.show();

    return a.exec();
}
