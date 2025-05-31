#pragma once
#include <QTcpServer>

class SimpleTcpServer : public QTcpServer {
  Q_OBJECT

public:
  SimpleTcpServer(QObject* parent = nullptr);
  ~SimpleTcpServer() override;

protected:
  void incomingConnection(qintptr socketDescriptor) override;

private:
  void handleReadyRead(QTcpSocket* clientSocket);

  void handleDisconnected(QTcpSocket* clientSocket);
};
