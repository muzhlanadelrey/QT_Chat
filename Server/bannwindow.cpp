#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QListWidget>
#include "bannwindow.h"
#include "ui_bannwindow.h"

BannWindow::BannWindow(DatabaseManager* dbManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BannWindow),
    databaseManager(dbManager)
{
    ui->setupUi(this);
}

BannWindow::~BannWindow()
{
    delete ui;
}


void BannWindow::showUserStatusDialog(bool newStatus)
{
    QDialog userStatusDialog(this);
    userStatusDialog.setModal(true);

    auto layout = new QVBoxLayout();
    userStatusDialog.setLayout(layout);

    auto userListWgt = new QListWidget(&userStatusDialog);
    layout->addWidget(userListWgt);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &userStatusDialog);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &userStatusDialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &userStatusDialog, &QDialog::reject);

    auto userInformation = databaseManager->showUsersNameStatus();
    for (const QString& info : userInformation) {
        userListWgt->addItem(info);
    }

    userListWgt->setCurrentRow(0);

    auto result = userStatusDialog.exec();

    if (result == QDialog::Accepted && userListWgt->currentItem()) {

        QString selectedUserAndStatus = userListWgt->currentItem()->text();

        QStringList parts = selectedUserAndStatus.split(" ");
        if (parts.size() == 2) {
            QString selectedUserName = parts[0];
            databaseManager->setBannStatus(selectedUserName, newStatus);
        }
    }
}

void BannWindow::on_bannCurrentUserButton_clicked()
{
    showUserStatusDialog(true);
}

void BannWindow::on_unbannCurrentUserButton_clicked()
{
    showUserStatusDialog(false);
}


void BannWindow::on_closeBunnWindowButton_clicked()
{
    close();
}


void BannWindow::on_showUsersInfoButton_clicked()
{
    userInformation = databaseManager->showUsersNameStatus();

    QString userInformationText;
    for (const QString& info : userInformation) {
        userInformationText += info + "\n";
    }

    ui->usersBrowser->setText(userInformationText);
}

void BannWindow::on_usersBrowser_anchorClicked(const QUrl &link)
{
    selectedUserName = link.toString();
}
