#include <QCoreApplication>

#include <QDebug>

#include "universallistener.h"

using namespace stnctl;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int port;
    if (argc == 1) {
        port = 50000;
    }
    else {
        bool ok;
        port = QString(argv[1]).toInt(&ok);
        if (!ok) { port = 50000; }
    }

    qDebug() << "Listening on port " << port;

    UniversalListener server(port);
    server.initConnections();
    server.startListener();


    return a.exec();
}
