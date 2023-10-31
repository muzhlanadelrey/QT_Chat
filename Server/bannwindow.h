#ifndef BANNWINDOW_H
#define BANNWINDOW_H

#include <QDialog>
#include "database.h"

namespace Ui {
class BannWindow;
}

class BannWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BannWindow(DatabaseManager* dbManager, QWidget *parent = nullptr);
    ~BannWindow();

private slots:
    void on_bannCurrentUserButton_clicked();
    void on_unbannCurrentUserButton_clicked();
    void on_closeBunnWindowButton_clicked();
    void on_showUsersInfoButton_clicked();

    void on_usersBrowser_anchorClicked(const QUrl &link);

    void showUserStatusDialog(bool newStatus);
private:
    Ui::BannWindow *ui;
    DatabaseManager *databaseManager;
    QVector<QString> userInformation;
    QString selectedUserName;
};

#endif // BANNWINDOW_H
