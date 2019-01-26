#include <QtCore/QDebug>
#include "websocket.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include "xmlhandler.h"

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
    XmlHandler xmlh;
    if (xmlh.validaXML(message.toStdString().c_str())) {
       xmlh.QstringToXml(message);
    }else{
    qDebug()<< "Error al validar el xml";
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
