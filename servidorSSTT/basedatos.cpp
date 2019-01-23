#include <QtSql>
#include <QSqlQuery>
#include <QDebug>
#include "basedatos.h"

void BaseDatos::connectDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setPort(5432);
    db.setDatabaseName("Central");
    db.setUserName("usuario");
    db.setPassword("1234");

    bool ok = db.open();

    //QSqlError error = db.lastError();
    //qDebug()<<"error: "<< error;

    if(ok)
    {
        qDebug()<<"Conexion ok";

    }
}
BaseDatos::BaseDatos()
{

}
