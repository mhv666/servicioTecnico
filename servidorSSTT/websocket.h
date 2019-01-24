#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"

class QWebSocketServer;
class QWebSocket;

class WebSocket : public QObject
{
    Q_OBJECT

public:
    explicit WebSocket(quint16 port);
    ~WebSocket();

signals:
    void closed();

private slots:
    void onNewConnection();
    void proessTextMessage(QString message);
    void socketDisconnected();

private:
    QWebSocketServer *m_webSocketServer;
    QList<QWebSocket *>m_clients;
};

#endif // WEBSOCKET_H
