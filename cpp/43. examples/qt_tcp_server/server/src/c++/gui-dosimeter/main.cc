#include <QCoreApplication>
#include <gui-dosimeter/server/server.h>

int main(int argc, char* argv[]) {
  QCoreApplication app(argc, argv);

  SimpleTcpServer server;
  if (!server.listen(QHostAddress::Any, 12345)) {
    qCritical() << "Failed to start server:" << server.errorString();
    return 1;
  }

  qDebug() << "Server started on port" << server.serverPort();
  return app.exec();
}
