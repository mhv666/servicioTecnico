#include "websocket.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QDebug>
WebSocket::WebSocket()
{

}
WebSocket::~WebSocket()
{
  m_webSocketServer->close();
  qDeleteAll(m_clients.begin(),m_clients.end());
}
void WebSocket::Listen(quint16 port):
m_webSocketServer(new QwebSocketServer(QStringLiteral("Central server"),
                                       QWebSocketServer::NonSecureMode,this)){
    if (m_webSocketServer->listen(QHostAddress::Any,port))
    {
        qDebug()<<"Server iniciado en :"<< port;
        connect(m_webSocketServer, &QwebSocketServer::newConnection,this,&WebSocket::onNewConnection);
        connect(m_webSocketServer, &QwebSocketServer::closed,this,&WebSocket::closed);
    }//End if


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
    QWebSocket *pClient = qobject_cast<QwebSocket *>(sender());
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
