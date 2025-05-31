#include <QCoreApplication>
#include <example-qt-tcp-client/client/client.h>


int main(int argc, char* argv[]) {
  QCoreApplication app(argc, argv);

  QString host = "127.0.0.1"; // Replace with the server's IP address if needed
  quint16 port = 12345;       // Replace with the server's port if needed

  SimpleTcpClient client(host, port);

  return app.exec();
}
