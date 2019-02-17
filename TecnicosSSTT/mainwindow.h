#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "websocketclient.h"
#include "xmlhandler.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
    void on_btnBuscar_clicked();

private:
    WebSocketClient *webSockerClient;
    XmlHandler *xmlHandler;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
