#pragma once
#include <QTcpServer>
#include <memory>

class SimpleTcpServer : public QTcpServer {
  Q_OBJECT

public:
  explicit SimpleTcpServer(QObject* parent = nullptr);
  ~SimpleTcpServer() override;

protected:
  void incomingConnection(qintptr socketDescriptor) override;

private:
  void handleReadyRead(std::shared_ptr<QTcpSocket> clientSocket);

  void handleDisconnected(std::shared_ptr<QTcpSocket> clientSocket);
};
