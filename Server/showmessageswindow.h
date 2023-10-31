#ifndef SHOWMESSAGESWINDOW_H
#define SHOWMESSAGESWINDOW_H

#include <QDialog>
#include "database.h"

namespace Ui {
class showMessagesWindow;
}

class showMessagesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit showMessagesWindow(DatabaseManager* dbManager, QWidget *parent = nullptr);
    ~showMessagesWindow();

private slots:
    void on_closeUsersMessagesButton_clicked();

    void on_showAllMessagesButton_clicked();

private:
    Ui::showMessagesWindow *ui;
    DatabaseManager *databaseManager;
};

#endif // SHOWMESSAGESWINDOW_H
