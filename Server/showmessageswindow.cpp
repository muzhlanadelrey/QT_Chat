#include "showmessageswindow.h"
#include "ui_showmessageswindow.h"

showMessagesWindow::showMessagesWindow(DatabaseManager* dbManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showMessagesWindow),
    databaseManager(dbManager)
{
    ui->setupUi(this);
}

showMessagesWindow::~showMessagesWindow()
{
    delete ui;
}

void showMessagesWindow::on_closeUsersMessagesButton_clicked()
{
    close();
}


void showMessagesWindow::on_showAllMessagesButton_clicked()
{
    DatabaseManager databaseManager;

    QVector<QString> messages = databaseManager.showAllUsersMessages();

    if (messages.isEmpty()) {
        ui->usersMessagesBrowser->setText("Сообщений нет");
    } else {
        QString allMessages;
        for (const QString& message : messages) {
            allMessages += message + "\n";
        }
        ui->usersMessagesBrowser->setText(allMessages);
    }
}
