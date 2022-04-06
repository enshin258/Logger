#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString serverAddress = "127.0.0.1";
    int serverPort = 4242;

    QTcpServer *server = new QTcpServer();

    QAbstractSocket::connect(server, &QTcpServer::newConnection, [server]() {
        qDebug() << "New connection established!!";

        QTcpSocket *socket = server->nextPendingConnection();

        QAbstractSocket::connect(socket, &QTcpSocket::readyRead, [socket]() {
            qDebug() << "SERVER RECIEVED: " << socket->readLine();
        });

        socket->write("Welcome new connection!");
        socket->flush();
    });

    qDebug() << "Starting server...";

    if (server->listen(QHostAddress(serverAddress),serverPort)) {
        qDebug() << "Server started";
    } else {
        qDebug() << "Failed to start server";
    }

    return a.exec();
}
