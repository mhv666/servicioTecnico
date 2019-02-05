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




    if (aplicacion->xmlh->readContentOfTag(message,"header")=="request_modelos")
    {
        if (aplicacion->xmlh->validaXML("modelos.xml"))
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



    }else if(aplicacion->xmlh->readContentOfTag(message,"header")=="newRma")
    {
        if (aplicacion->xmlh->validaXML("newRma.xml")){


        }
    }else if(aplicacion->xmlh->readContentOfTag(message,"header")=="loginRequest")
    {
        if (aplicacion->xmlh->validaXML("loginRequest.xml")){
            QString usuario  = aplicacion->xmlh->readContentOfTag(message,"username");
            QString password = aplicacion->xmlh->readContentOfTag(message,"password");
            bool isAuthorizedUser = aplicacion->bd->loginCentral(usuario,password);
            if(!isAuthorizedUser)
            {
                return;
            }else{
                ///TODO: enviar mensaje de login satisfactorio
                pClient->sendTextMessage();
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

