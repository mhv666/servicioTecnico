#ifndef APP_H
#define APP_H
#include "basedatos.h"
#include "websocket.h"
#include "xmlhandler.h"

class App
{
public:
    App();
    BaseDatos  *bd = new BaseDatos();
    WebSocket  *ws = new WebSocket(3344);
};

#endif // APP_H
