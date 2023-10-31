#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

class DatabaseManager //: public QObject
{

    // Q_OBJECT

signals:
         //void infoMessageDB(const QString &message);

public:
    DatabaseManager();
    ~DatabaseManager();

    bool openDatabase(const QString &databaseName);
    void closeDatabase();

    bool createUserTable();
    bool createChatHistoryTable();
    bool addUser(const QString &username, const QString &password);
    bool getUser(const QString &username, QString &password);
    bool addChatMessage(int senderId, int receiverId, const QString &message);
    QSqlQuery getChatHistory(int senderId, int receiverId);
    bool userExists(const QString &username);
    bool createAdminUser();
    QSqlQuery executeQueryResult(const QString &query);

    QVector<QString> showAllUsersMessages();
    bool setBannStatus(const QString &username, bool bannStatus);
    QVector<QString> showUsersNameStatus();

private:
    QSqlDatabase database;
    QSqlQuery executeQueryWithResult(const QString &query);
    bool executeQuery(const QString &query);

};

#endif // DATABASEMANAGER_H
