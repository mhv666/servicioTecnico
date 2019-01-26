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
    QString xml= QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?> <rma> <header>   <tipo>insert</tipo> </header>  <payload> <user>   <nombre>marti</nombre>      <apellido>Garcia</apellido> <numTelefono>666555444</numTelefono>                </user> <telefono> <marca>Samsung</marca>   <modelo>S9</modelo>    </telefono>          <tienda>   <id></id>  </tienda> </payload>   </rma>");
    qDebug()<<xmlh->QstringToXml(xml);
   // xmlh->validarDomInsert(xml);
    //QString res=  xmlh->read(xml,"modelo");
    //qDebug()<< res;
    return a.exec();
}
