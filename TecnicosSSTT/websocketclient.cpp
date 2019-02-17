#include <QDebug>
#include <QTimer>
#include "websocketclient.h"

QT_USE_NAMESPACE

WebSocketClient::WebSocketClient()
{
    QTimer::singleShot(0,this,SLOT(go()));
    m_url = QUrl(QStringLiteral("ws://localhost:3344"));
}

void WebSocketClient::go()
{
    m_webSocket = new QWebSocket();
    connect(m_webSocket, SIGNAL(connected()),this,SLOT(connected()));
    connect(m_webSocket, SIGNAL(disconnected()),this,SLOT(disconnected()));
    m_webSocket->open(m_url);
}

void WebSocketClient::connected()
{
    m_connected = true;
    qDebug() << "WebSocket connected";
    qDebug() << m_connected;
}

void WebSocketClient::disconnected()
{
    m_connected = false;
    qDebug() << "WebSocket disconnected";
}

void WebSocketClient::sendMessage(QString message)
{
    if (m_connected){
        qDebug() << "Message enviado:" << message;
        m_webSocket->sendTextMessage(message);

    }
}




