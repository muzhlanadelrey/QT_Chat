#include "mainwindow.h"
#include "database.h"
#include <QtSql>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle("blue");

    QString databaseName = "qt_chat_database.db";

    DatabaseManager databaseManager;

    if (databaseManager.openDatabase(databaseName)) {
        qDebug() << "База данных успешно открыта или создана.";

    } else {
        qDebug() << "Ошибка при открытии или создании базы данных.";
    }

    MainWindow w(&databaseManager);
    w.show();
    return a.exec();
}
