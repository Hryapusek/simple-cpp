#pragma once

#include <memory>

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class SimpleTcpClient : public QObject {
  Q_OBJECT

public:
  SimpleTcpClient(const QString& host, quint16 port, QObject* parent = nullptr);

private slots:
  void onConnected();

  void onReadyRead();

  void onError(QTcpSocket::SocketError socketError);

private:
  std::unique_ptr<QTcpSocket> socket;
};
