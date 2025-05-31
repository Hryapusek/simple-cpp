#include <QCoreApplication>
#include <example-qt-tcp-server/server/server.h>

int main(int argc, char* argv[]) {
  QCoreApplication app(argc, argv);

  // Server -> server.listen(QHostAddress::Any, 12345)
  // Client -> QTcpSocket::connectToHost("192.168.1.27", 12345)

  // Server -> 192.168.0.3
  // Client -> 192.168.0.9
  // Client -> QTcpSocket::connectToHost("192.168.0.3", 12345)
  SimpleTcpServer* server = new SimpleTcpServer(&app);
  if (not server->listen(QHostAddress::Any, 12345)) {
    qCritical() << "Failed to start server:" << server->errorString();
    return 1;
  }

  qDebug() << "Server started on port" << server->serverPort();
  return app.exec();
}
