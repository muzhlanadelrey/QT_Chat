#include "database.h"
#include <QDebug>

DatabaseManager::DatabaseManager()
{

}

DatabaseManager::~DatabaseManager()
{
    closeDatabase();
}

bool DatabaseManager::openDatabase(const QString &databaseName)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(databaseName);

    if (!database.open()) {
        QSqlError error = database.lastError();
        qDebug() << "Ошибка при открытии базы данных: " << error.text();
        return false;
    }

    if (!database.tables().contains("users")) {
        if (!createUserTable()) {
            qDebug() << "Ошибка создания таблицы users";
            return false;
        }
    }

    if (!database.tables().contains("chat_history")) {
        if (!createChatHistoryTable()) {
            qDebug() << "Ошибка создания таблицы chat_history";
            return false;
        }
    }

    if (!createAdminUser()) {
        qDebug() << "Ошибка создания пользователя admin";
        return false;
    }

    return true;
}

void DatabaseManager::closeDatabase()
{
    database.close();
}

bool DatabaseManager::executeQuery(const QString &query)
{
    QSqlQuery sqlQuery(database);

    if (!sqlQuery.exec(query)) {
        QSqlError error = sqlQuery.lastError();
        qDebug() << "Ошибка выполнения SQL-запроса: " << error.text();
        return false;
    }

    return true;
}

QSqlQuery DatabaseManager::executeQueryWithResult(const QString &query)
{
    QSqlQuery sqlQuery(database);
    sqlQuery.exec(query);

    return sqlQuery;
}

bool DatabaseManager::createUserTable()
{
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS users ("
                               "id INTEGER PRIMARY KEY, "
                               "username TEXT UNIQUE NOT NULL, "
                               "password TEXT NOT NULL, "
                               "isbanned INTEGER DEFAULT 0)";

    return executeQuery(createTableQuery);
}

bool DatabaseManager::createChatHistoryTable()
{
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS chat_history ("
                               "id INTEGER PRIMARY KEY, "
                               "sender_id INTEGER NOT NULL, "
                               "receiver_id INTEGER NOT NULL, "
                               "message TEXT NOT NULL, "
                               "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP)";

    return executeQuery(createTableQuery);
}

bool DatabaseManager::addUser(const QString &username, const QString &password)
{
    QString insertQuery = QString("INSERT INTO users (username, password) VALUES ('%1', '%2')")
                              .arg(username)
                              .arg(password);

    return executeQuery(insertQuery);
}

bool DatabaseManager::getUser(const QString &username, QString &password)
{
    QString selectQuery = QString("SELECT password FROM users WHERE username = '%1'")
                              .arg(username);

    QSqlQuery query = executeQueryWithResult(selectQuery);
    if (query.next()) {
        password = query.value(0).toString();
        return true;
    }
    return false;
}

bool DatabaseManager::addChatMessage(int senderId, int receiverId, const QString &message)
{
    QString insertQuery = QString("INSERT INTO chat_history (sender_id, receiver_id, message) VALUES (%1, %2, '%3')")
                              .arg(senderId)
                              .arg(receiverId)
                              .arg(message);

    return executeQuery(insertQuery);
}

QSqlQuery DatabaseManager::getChatHistory(int senderId, int receiverId)
{
    QString selectQuery = QString("SELECT message, timestamp FROM chat_history WHERE (sender_id = %1 AND receiver_id = %2) OR (sender_id = %2 AND receiver_id = %1) ORDER BY timestamp")
                              .arg(senderId)
                              .arg(receiverId);

    return executeQueryWithResult(selectQuery);
}

bool DatabaseManager::userExists(const QString &username)
{
    QString selectQuery = QString("SELECT id FROM users WHERE username = '%1'")
                              .arg(username);

    QSqlQuery query = executeQueryWithResult(selectQuery);
    return query.next();
}

bool DatabaseManager::createAdminUser()
{
    if (userExists("admin")) {
        qDebug() << "Пользователь 'admin' уже существует.";
        //emit infoMessageDB("Пользователь 'admin' уже существует.");
        return true;
    }

    QString username = "admin";
    QString password = "admin";
    if (addUser(username, password)) {
        qDebug() << "Пользователь 'admin' создан успешно.";
        //emit infoMessageDB("Пользователь 'admin' создан успешно.");
        return true;
    } else {
        qDebug() << "Ошибка создания пользователя 'admin'.";
        //emit infoMessageDB("Ошибка создания пользователя 'admin'.");
        return false;
    }
}

QSqlQuery DatabaseManager::executeQueryResult(const QString &query)
{
    QSqlQuery sqlQuery(database);

    if (!sqlQuery.exec(query)) {
        QSqlError error = sqlQuery.lastError();
        qDebug() << "Ошибка выполнения SQL-запроса: " << error.text();
    }

    return sqlQuery;
}

QVector<QString> DatabaseManager::showAllUsersMessages()
{
    QVector<QString> messages;

    QString query = "SELECT message FROM chat_history";
    QSqlQuery result = executeQueryWithResult(query);

    while (result.next()) {
        QString message = result.value(0).toString();
        messages.append(message);
    }

    return messages;
}

bool DatabaseManager::setBannStatus(const QString &username, bool bannStatus)
{
    QString query = QString("UPDATE users SET isbanned = %1 WHERE username = '%2'")
                        .arg(bannStatus ? 1 : 0)
                        .arg(username);

    return executeQuery(query);
}
QVector<QString> DatabaseManager::showUsersNameStatus() {
    QVector<QString> userNames;

    QString query = "SELECT username, isbanned FROM users";
    QSqlQuery result = executeQueryWithResult(query);

    while (result.next()) {
        QString username = result.value(0).toString();
        bool isBanned = result.value(1).toBool();

        QString userStatus = username + " (" + (isBanned ? "Заблокирован" : "Активен") + ")";
        userNames.append(userStatus);
    }

    return userNames;
}
