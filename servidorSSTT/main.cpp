#include <QCoreApplication>
#include "basedatos.h"
#include "websocket.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BaseDatos *bd;
    WebSocket *ws;
    bd->connectDatabase();
    ws->Listen(3344);
    return a.exec();
}
