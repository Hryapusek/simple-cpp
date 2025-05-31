#pragma once
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <memory>
#include <QAbstractEventDispatcher>

class ClientHandler : public QThread
{
  Q_OBJECT

 public:
  explicit ClientHandler(qintptr socketDescriptor)
    : m_socketDescriptor(socketDescriptor)
  {}

 protected:
  void run() override
  {
    auto socket = std::make_shared<QTcpSocket>();
    if (!socket->setSocketDescriptor(m_socketDescriptor)) {
      emit error(socket->error());
      return;
    }

    connect(socket.get(), &QTcpSocket::readyRead, eventDispatcher(), [this, socket]() { 
      handleReadyRead(socket);
    });

    connect(socket.get(), &QTcpSocket::disconnected, eventDispatcher(), [this, socket]() { 
      handleDisconnected(socket);
    });

    exec();  // Start the event loop for this thread
  }
  
  qintptr m_socketDescriptor;

 signals:
  void error(QTcpSocket::SocketError socketError);

  private slots:
  void handleReadyRead(std::shared_ptr<QTcpSocket> socket)
  {
    QByteArray data = socket->readAll();
    // Process the data here
    for(int i = 0; i < 3; ++i) {
      socket->write("Response from server: " + data);
      socket->flush();    // Ensure the data is sent immediately
      QThread::sleep(1);    // Wait for 1 second before sending the next message
    }
  }

  void handleDisconnected(std::shared_ptr<QTcpSocket> socket)
  {
    socket->close();
    quit();
  }
};

class SimpleTcpServer : public QTcpServer
{
  Q_OBJECT

 public:
  explicit SimpleTcpServer(QObject* parent = nullptr);
  ~SimpleTcpServer() override;

 protected:
  void incomingConnection(qintptr socketDescriptor) override;
};
