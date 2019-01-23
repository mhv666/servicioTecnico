#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
class QwebSocketServer;
class QWebSocket;

class WebSocket :public QObject
{
    Q_OBJECT

public:
    WebSocket();
    void Listen(quint16 port);
    ~WebSocket();

signals:
    void closed();
private slots:
    void onNewConnection();
    void proessTextMessage(QString message);
    void socketDisconnected();

private:
    QwebSocketServer *m_webSocketServer;
    QList<QWebSocket *>m_clients;
};

#endif // WEBSOCKET_H
