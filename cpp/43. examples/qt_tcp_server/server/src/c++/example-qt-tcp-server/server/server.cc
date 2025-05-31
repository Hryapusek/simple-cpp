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
  auto clientSocket = std::make_shared<QTcpSocket>();
  if (not clientSocket->setSocketDescriptor(socketDescriptor))
  {
    qWarning() << "Failed to set socket descriptor for client:" << socketDescriptor;
    return;
  }
  qDebug() << "New client connected from:" << clientSocket->peerAddress().toString();
  connect(
    clientSocket.get(), // QTcpSocket* - инициатор события
    &QTcpSocket::readyRead, // Какое событие
    [this, clientSocket]() { handleReadyRead(clientSocket); } // Действие при событии
  );
  connect(
    clientSocket.get(),
    &QTcpSocket::disconnected,
    [this, clientSocket]() { handleDisconnected(clientSocket); }
  );
}

void SimpleTcpServer::handleReadyRead(std::shared_ptr<QTcpSocket> clientSocket)
{
  QByteArray data = clientSocket->readAll();
  qDebug() << "Received:" << data;
  qint64 bytesWritten = clientSocket->write("Echo: " + data);  // Echo back the received data
  if (bytesWritten == -1)
  {
    qWarning() << "Failed to write data to client:" << clientSocket->peerAddress().toString();
  }
  else
  {
    qDebug() << "Successfully wrote" << bytesWritten << "bytes to client.";
  }
}

void SimpleTcpServer::handleDisconnected(std::shared_ptr<QTcpSocket> clientSocket)
{
  qDebug() << "Client disconnected:" << clientSocket->peerAddress().toString();
}
