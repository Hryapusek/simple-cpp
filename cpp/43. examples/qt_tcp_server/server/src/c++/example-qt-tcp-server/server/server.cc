#include <example-qt-tcp-server/server/server.h>

#include <QCoreApplication>
#include <QTcpSocket>
#include <QDebug>

SimpleTcpServer::SimpleTcpServer(QObject* parent)
  : QTcpServer(parent)
{}

SimpleTcpServer::~SimpleTcpServer() { qDebug() << "Server is shutting down."; }

void SimpleTcpServer::incomingConnection(qintptr socketDescriptor)
{
  auto clientSocket = std::make_shared<QTcpSocket>(this);
  if(clientSocket->setSocketDescriptor(socketDescriptor)) {
    qDebug() << "New client connected from:" << clientSocket->peerAddress().toString();
    connect(
      clientSocket.get(),
      &QTcpSocket::readyRead,
      this,
      [this, clientSocket]() { handleReadyRead(clientSocket.get()); }
    );
    connect(
      clientSocket.get(),
      &QTcpSocket::disconnected,
      this,
      [this, clientSocket]() { handleDisconnected(clientSocket.get()); }
    );
  }
}

void SimpleTcpServer::handleReadyRead(QTcpSocket* clientSocket)
{
  QByteArray data = clientSocket->readAll();
  qDebug() << "Received:" << data;
  clientSocket->write("Echo: " + data);  // Echo back the received data
}

void SimpleTcpServer::handleDisconnected(QTcpSocket* clientSocket)
{
  qDebug() << "Client disconnected:" << clientSocket->peerAddress().toString();
}
