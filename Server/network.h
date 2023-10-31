#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Network : public QObject
{
    Q_OBJECT

public:
    explicit Network(QObject *parent = nullptr);
    ~Network();

signals:
    void clientConnected(QTcpSocket *clientSocket);
    void infoMessage(const QString &message);

public slots:
    void startServer();
    void closeServer();

private slots:
    void newClientConnection();

private:
    QTcpServer *server;
};

#endif // NETWORK_H
