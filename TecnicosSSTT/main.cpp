#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    //WebSocketClient * wsc = new WebSocketClient();
    w.show();

    return a.exec();
}
