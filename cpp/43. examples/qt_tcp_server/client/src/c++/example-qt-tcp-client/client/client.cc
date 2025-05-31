#include <example-qt-tcp-client/client/client.h>
#include <qtcpsocket.h>
#include <QCoreApplication>
#include <QTcpSocket>
#include <QDebug>

SimpleTcpClient::SimpleTcpClient(QString const& host, quint16 port, QObject* parent)
  : QObject(parent)
  , socket(std::make_unique<QTcpSocket>())
{
  connect(socket.get(), &QTcpSocket::connected, this, &SimpleTcpClient::onConnected);
  connect(socket.get(), &QTcpSocket::readyRead, this, &SimpleTcpClient::onReadyRead);
  connect(socket.get(), &QTcpSocket::errorOccurred, this, &SimpleTcpClient::onError);

  qDebug() << "Connecting to server...";
  socket->connectToHost(host, port);
}

void SimpleTcpClient::onConnected()
{
  qDebug() << "Connected to server!";
  socket->write("Hello, server!");
}

void SimpleTcpClient::onReadyRead() { qDebug() << "Server says:" << socket->readAll(); }

void SimpleTcpClient::onError(QTcpSocket::SocketError socketError)
{
  qCritical() << "Socket error:" << socket->errorString();
}
