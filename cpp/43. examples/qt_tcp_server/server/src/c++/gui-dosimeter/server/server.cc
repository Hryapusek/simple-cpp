#include <gui-dosimeter/server/server.h>

#include <QCoreApplication>
#include <QTcpSocket>
#include <QDebug>

SimpleTcpServer::SimpleTcpServer(QObject* parent)
  : QTcpServer(parent)
{}

SimpleTcpServer::~SimpleTcpServer() { qDebug() << "Server is shutting down."; }

void SimpleTcpServer::incomingConnection(qintptr socketDescriptor)
{
  auto clientSocket = std::make_unique<QTcpSocket>(this);
  if(clientSocket->setSocketDescriptor(socketDescriptor)) {
    qDebug() << "New client connected from:" << clientSocket->peerAddress().toString();
    connect(
      clientSocket.get(),
      &QTcpSocket::readyRead,
      this,
      [this, clientSocket = clientSocket.get()]() { handleReadyRead(clientSocket); }
    );
    connect(
      clientSocket.get(),
      &QTcpSocket::disconnected,
      this,
      [this, clientSocket = clientSocket.release()]() { handleDisconnected(clientSocket); }
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
  clientSocket->deleteLater();
}
