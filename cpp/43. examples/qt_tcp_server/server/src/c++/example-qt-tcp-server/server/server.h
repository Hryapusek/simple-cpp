#pragma once
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <memory>
#include <QAbstractEventDispatcher>

/*
1. Мы запустили сервер (запросили у системы сокет(1) для прослушивания и принятия входящих подключений)
2. Клиент отправляет серверу запрос на соединение
3. ОС выделила серверу ДРУГОЙ сокет для общения с клиентом (Так как сокет(1) на котором работает сервер уже занят, 
   для взаимодействия с клиентом нужен другой сокет)
4. Handshake
--------- Дальше в зависимости от сервера. Например:
5. Сервер ждет запрос от клиента
6. При получении запроса происходит обработка и отправка ответа клиенту
7. И так пока не будет получен запрос на разрыв соединения

# Сокеты Бернулли
- read
- write
- accept
- listen
- connect
- disconnect
*/

class ClientHandler : public QThread
{
  Q_OBJECT

 public:
  explicit ClientHandler(long long socketDescriptor)
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

    connect(socket.get(), &QTcpSocket::readyRead, this->eventDispatcher(), [this, socket]() { 
      handleReadyRead(socket);
    });

    // connect(socket.get(), &QTcpSocket::readyRead, this->eventDispatcher(), foo);
    // connect(socket.get(), &QTcpSocket::readyRead, this->eventDispatcher(), foo());

    connect(socket.get(), &QTcpSocket::disconnected, this->eventDispatcher(), [this, socket]() { 
      handleDisconnected(socket);
    });

    // socket->disconnectFromHost();

    // this;

    exec();  // Start the event loop for this thread
    /*
    start -> system thread -> run()
    run in different thread
    */
  }
  
  long long m_socketDescriptor;

 signals: // public
  void error(QTcpSocket::SocketError socketError);

  private slots: // slots -> "" -> nothing
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

  // Вызывается при закрытии соединения
  void handleDisconnected(std::shared_ptr<QTcpSocket> socket)
  {
    // Возвращаем системе ресурс
    socket->close();
    // Завершаем работу потока
    // Каждый поток рассчитан на ОДНО соединение потому что мы сами так решили
    // Как только соединение разрывается - поток больше не нужен
    this->quit(); // Exiting thread
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
