#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

class WebSocketClient : public QObject
{

    Q_OBJECT

public:
    explicit WebSocketClient();

    void sendMessage(QString message);

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void go();
    void connected();
    void disconnected();


private:
    QWebSocket * m_webSocket;
    QUrl  m_url;
    bool m_connected;


};

#endif // WEBSOCKETCLIENT_H
