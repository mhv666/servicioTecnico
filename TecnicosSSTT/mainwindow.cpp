#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    webSockerClient(new WebSocketClient),
    xmlHandler(new XmlHandler)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_btnBuscar_clicked()
{

    //Enviar el xml pertinente al servidor,
    //este devolvera una QlistWidgets donde, primero borraremos la anterior, en caso de que exista, despues,
    //le asignaremos a la que ye tenemos.
    QString estado{"0"};
    if (ui->pendienteDeValidacion->isChecked()) estado     = "1";
    if (ui->preparadoParaLaValidacion->isChecked()) estado = "2";
    if (ui->reparado->isChecked())              estado     = "3";
    if (ui->noReparado->isChecked())            estado     = "4";
    if (ui->EnviadoAlaTienda->isChecked())      estado     = "5";

    QDomDocument xmlToSend = xmlHandler->generateXmlForRma(estado);

    webSockerClient->sendMessage(xmlToSend.toString());


    //Esta sera la consulta a lanzar en el servidor,

    QString Consulta;
    Consulta = "SELECT id_cliente,id_modelo_dispositivo FROM rma WHERE ";

    if (ui->pendienteDeValidacion->isChecked()) {
        Consulta += "id_estado = 1 ";
    }
    if (ui->preparadoParaLaValidacion->isChecked()) {
        Consulta += "id_estado = 2 ";
    }
    if (ui->reparado->isChecked()) {
        Consulta += "id_estado = 3 ";
    }
    if (ui->noReparado->isChecked()) {
        Consulta += "id_estado = 4 ";
    }
    if (ui->EnviadoAlaTienda->isChecked()) {
        Consulta += "id_estado = 5 ";
    }
    Consulta += ";";

}
