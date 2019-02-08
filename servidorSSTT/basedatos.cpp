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
    QVariant id;
    if(ok)
    {
        mdb.transaction();
        QSqlQuery query("INSERT INTO rma (id_cliente,id_estado,id_dispositivo,id_tecnico,id_tienda,descripcion_rma) VALUES('"+idCliente+"','"+idEstado+"','"+idDispositivo+"','"+idTecnico+"','"+idTienda+"','"+DescripcionProblema+"') ");
        mdb.commit();
        id =query.lastInsertId();
        return id ;

    }

    return id;
}
QString BaseDatos::estadoRma(QString idRma)
{
    bool ok = mdb.open();
    QString estado ;
    if (ok)
    {

     QSqlQuery query("SELECT nombre_estado FROM rma join estado ON(rma.id_estado = estado.id_estado WHERE id_rma="+idRma+");");
     estado = query.value(0).toString();
     return estado;
    }

    return estado;
}
QStringList BaseDatos::consultarMarcas()
{
    bool ok = mdb.open();

    QStringList marcas;
    if (ok)
    {

     QSqlQuery query("SELECT nombre_marca_dispositivo FROM marca_dispositivo;");

     while (query.next())
     {

        marcas.append(query.value(0).toString());
     }


     return marcas;
    }

    return marcas;
}

QStringList BaseDatos::consultarModelos(QString marca)
{
    bool ok = mdb.open();
    QStringList modelos;
    if (ok)
    {


    ///*************************************************************///
    ///TODO: acabar de hacer la query, esta incompleta, falta hacer join
    ///
    ///SELECT nombre_modelo_dispositivo FROM modelo_dispositivo JOIN marca_dispositivo ON modelo_dispositivo.id_marca_dispositivo = marca_dispositivo.id_marca_dispositivo WHERE marca_dispositivo.nombre_marca_dispositivo = "Samsung" ;
    ///
    ///*************************************************************///
     QSqlQuery query("SELECT nombre_modelo_dispositivo FROM modelo_dispositivo JOIN marca_dispositivo ON modelo_dispositivo.id_marca_dispositivo = marca_dispositivo.id_marca_dispositivo WHERE marca_dispositivo.nombre_marca_dispositivo = '"+marca+"';");

     while (query.next()) {
        modelos.append(query.value(0).toString());
     }

     return modelos;
    }

    return modelos;
}
QString BaseDatos::loginCentral(QString usuario, QString password){

    QString resultado;
    bool ok = mdb.open();
    if (ok)
    {
         QSqlQuery query("SELECT id_tienda FROM tienda WHERE usuario ='"+ usuario +"'  AND password='"+ password +"';");
         while (query.next())
         {
             resultado = query.value(0).toString();
            return resultado;
         }
    }
    return resultado;
}


