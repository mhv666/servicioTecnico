#include <QtSql>
#include <QSqlQuery>
#include <QDebug>
#include "basedatos.h"

BaseDatos::BaseDatos()
{

}
void BaseDatos::connectDatabase()
{
     mdb = QSqlDatabase::addDatabase("QPSQL");
    mdb.setHostName("127.0.0.1");
    mdb.setPort(5432);
    mdb.setDatabaseName("Central");
    mdb.setUserName("usuario");
    mdb.setPassword("1234");


    bool ok = mdb.open();

    //QSqlError error = db.lastError();
    //qDebug()<<"error: "<< error;

    if(ok)
    {
        qDebug()<<"Conexion ok";

    }
}

QVariant BaseDatos::crearRma(QString idCliente,QString idEstado,QString idDispositivo,QString idTecnico,QString idTienda,QString DescripcionProblema)
{
    bool ok = mdb.open();
    if(ok)
    {
        mdb.transaction();
        QSqlQuery query("INSERT INTO rma (id_cliente,id_estado,id_dispositivo,id_tecnico,id_tienda,descripcion_rma) VALUES('"+idCliente+"','"+idEstado+"','"+idDispositivo+"','"+idTecnico+"','"+idTienda+"','"+DescripcionProblema+"') ");
        mdb.commit();
        return query.lastInsertId();

    }
    QVariant null;
    return null;
}
QString BaseDatos::estadoRma(QString idRma)
{
    bool ok = mdb.open();
    if (ok)
    {

     QSqlQuery query("SELECT nombre_estado FROM rma join estado ON(rma.id_estado = estado.id_estado WHERE id_rma="+idRma+");");
     QString estado = query.value(0).toString();
     return estado;
    }
    QString null;
    return null;
}

