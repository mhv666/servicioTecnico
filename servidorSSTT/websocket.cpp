#include <QtCore/QDebug>
#include "websocket.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include "xmlhandler.h"
#include "app.h"
extern App *aplicacion;
WebSocket::WebSocket(quint16 port):
    m_webSocketServer(new QWebSocketServer(QStringLiteral("Central server"),
                                           QWebSocketServer::NonSecureMode,this))
{
    if (m_webSocketServer->listen(QHostAddress::Any,port))
    {
        qDebug()<<"Server iniciado en :"<< port;
        connect(m_webSocketServer, &QWebSocketServer::newConnection,this,&WebSocket::onNewConnection);
        connect(m_webSocketServer, &QWebSocketServer::closed,this,&WebSocket::closed);
    }//End if


}
WebSocket::~WebSocket()
{
  m_webSocketServer->close();
  qDeleteAll(m_clients.begin(),m_clients.end());
}
void WebSocket::onNewConnection()
{
    QWebSocket *pSocket = m_webSocketServer->nextPendingConnection();
    qDebug()<<"Socket conectado: "<<pSocket;

    connect(pSocket,&QWebSocket::textMessageReceived,this,&WebSocket::proessTextMessage);
    connect(pSocket,&QWebSocket::disconnected,this,&WebSocket::socketDisconnected);

    m_clients << pSocket;
}

void WebSocket::proessTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    aplicacion->xmlh->QstringToXml(message);



    QString ContenidoHeader = aplicacion->xmlh->readContentOfTag(message,"header");
    if (ContenidoHeader =="request_modelos")
    {
        bool isXmlValid = aplicacion->xmlh->validaXML("modelos.xml");
        if (isXmlValid)
        {
            QStringList marcas = aplicacion->bd->consultarMarcas();
            QDomDocument xmlDeRespuesta = aplicacion->xmlh->generateXmlOfMarcas(marcas);
            QDomNodeList dispositivos = xmlDeRespuesta.elementsByTagName("dispositivo");
            for (int i = 0; i < dispositivos.size(); ++i) {
                QStringList modelos = aplicacion->bd->consultarModelos(dispositivos.at(i).firstChild().toElement().text());
                //xmlDeRespuesta.elementsByTagName("dispositivo").at(i).appendChild(xmlDeRespuesta.createElement("modelo"));
                xmlDeRespuesta = aplicacion->xmlh->generateXmlOfModelos(xmlDeRespuesta,modelos,i);
            }
            pClient->sendTextMessage(xmlDeRespuesta.toString());
        }



    }else if(ContenidoHeader=="newRma")
    {
        bool isXmlValid = aplicacion->xmlh->validaXML("newRma.xml");
        if (isXmlValid){
            ///TODO:crear la insercion a la bbdd  y devolver si esta correcto
            QString usuario     = aplicacion->xmlh->readContentOfTag(message,"nombre");
            QString apellido     = aplicacion->xmlh->readContentOfTag(message,"apellido");
            QString numTelefono = aplicacion->xmlh->readContentOfTag(message,"numTelefono");
            QString modelo = aplicacion->xmlh->readContentOfTag(message,"modelo");
            QString idTienda = aplicacion->xmlh->readContentOfTag(message,"idTienda");
            QString descripcion = aplicacion->xmlh->readContentOfTag(message,"aSolucionar");


            QString idUsuario;
            idUsuario = aplicacion->bd->devolverIdUsuario(usuario,apellido,numTelefono);
            qDebug()<< "usuario cargado: " <<idUsuario;
            if (idUsuario.isNull()) {
                idUsuario = aplicacion->bd->crearUsuario(usuario,apellido,numTelefono).toString();
                qDebug()<< "usuario creado: " <<idUsuario;

            }
            QString idModelo = aplicacion->bd->devolverIdModelo(modelo);
            QString idEstado = "1"; //Pendiente de validacion
            QString idTecnico = "1"; //Dormo es el unico tecnico

            QVariant idRma = aplicacion->bd->crearRma(idUsuario,idEstado,idModelo,idTecnico,idTienda,descripcion);

            if (!idRma.isNull()) {
                QDomDocument xml = aplicacion->xmlh->generateXmlReturnRma(idRma.toString());
                pClient->sendTextMessage(xml.toString());
                qDebug()<< "idRma NO ES NULL: " ;
            }else{
                QString null;
                QDomDocument xml = aplicacion->xmlh->generateXmlReturnRma(null);
                pClient->sendTextMessage(xml.toString());
                qDebug()<< "idRma ES NULL: " ;

            }

        }
    }else if(ContenidoHeader=="loginRequest")
    {
         bool isXmlValid = aplicacion->xmlh->validaXML("loginRequest.xml");
        if (isXmlValid){
            QString usuario  = aplicacion->xmlh->readContentOfTag(message,"username");
            QString password = aplicacion->xmlh->readContentOfTag(message,"password");
            QString idTienda = aplicacion->bd->loginCentral(usuario,password);
            if(idTienda.isNull())
            {
                qDebug()<<"usuario no valido";
                QDomDocument xml =aplicacion->xmlh->generateXmlOfLogin(idTienda);
                pClient->sendTextMessage(xml.toString());

                //Usuario no encontrado enviar error
                return;
            }else{

                QDomDocument xml =aplicacion->xmlh->generateXmlOfLogin(idTienda);
                pClient->sendTextMessage(xml.toString());
            }
        }
    }
    qDebug() << "De:" << pClient << "Mensaje recibido:" << message;

}
void WebSocket::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    qDebug() << "Socket desconectado:" << pClient;
    if (pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    } // end if
}

