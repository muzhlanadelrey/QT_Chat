#include "network.h"

Network::Network(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &Network::newClientConnection);
}

Network::~Network()
{
    if (server) {
        server->close();
        delete server;
    }
}

void Network::startServer()
{
    if (server->listen(QHostAddress::Any, 7777)) {
        qDebug() << "Server is listening on port 7777";
        emit infoMessage("Server is listening on port 7777");
    } else {
        qDebug() << "Server failed to start!";
        emit infoMessage("Server failed to start!");
    }
}

void Network::closeServer()
{
    if (server) {
        server->close();
        if (server->isListening())
        {
            qDebug() << "Сервер закрыт.";
            emit infoMessage("Сервер закрыт.");
        }
        else
        {
            qDebug() << "Ошибка при закрытии сервера: " << server->errorString();
            emit infoMessage("Ошибка при закрытии сервера");
        }
        delete server;
        server = nullptr;
    }
}

void Network::newClientConnection()
{
    while (server->hasPendingConnections()) {
        QTcpSocket *clientSocket = server->nextPendingConnection();
        connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
        emit clientConnected(clientSocket);
    }
}
