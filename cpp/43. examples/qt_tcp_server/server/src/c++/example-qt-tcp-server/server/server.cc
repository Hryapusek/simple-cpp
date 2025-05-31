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
  auto clientThread = new ClientHandler(socketDescriptor); // QThread
  // delete clientThread; // c++ delete
  // clientThread->deleteLater(); // Qt deleteLater
  connect(clientThread, &ClientHandler::finished, clientThread, &QObject::deleteLater);
  clientThread->start();
}
