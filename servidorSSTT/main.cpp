#include <QCoreApplication>
#include "basedatos.h"
#include "websocket.h"
#include "xmlhandler.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BaseDatos  *bd = new BaseDatos();
    WebSocket  *ws = new WebSocket(3344);
    XmlHandler *xmlh = new XmlHandler();
    QObject::connect(ws,&WebSocket::closed,&a,&QCoreApplication::quit);
    bd->connectDatabase();
    QString xml= QString("<?xml version=\"1.0\" encoding=\"utf-8\"?>")
               + QString("<modelo>hola mundo </modelo>");

    QString res=  xmlh->read(xml,"modelo");
    qDebug()<< res;
    return a.exec();
}
