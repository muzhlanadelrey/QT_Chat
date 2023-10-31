#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include "network.h"
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DatabaseManager* databaseManager, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startServerButton_clicked();
    void on_stopServerButton_clicked();
    void on_showMessagesButton_clicked();
    void on_bannUserButton_clicked();
    void on_exitButton_clicked();
    void displayMessage(const QString &message);

private:
    Ui::MainWindow *ui;
    Network *network;
    QTextBrowser *debugWindowBrowser;
    DatabaseManager* databaseManager;
};
#endif // MAINWINDOW_H
