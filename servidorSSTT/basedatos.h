#ifndef BASEDATOS_H
#define BASEDATOS_H
#include <QSqlQuery>


class BaseDatos
{
public:
    BaseDatos();
    void connectDatabase();
    QString estadoRma(QString idRma);
    QVariant crearRma(QString idCliente,QString idEstado,QString idDispositivo,QString idTecnico,QString idTienda,QString DescripcionProblema);
    QStringList consultarMarcas();
private:
    QSqlDatabase mdb;
};

#endif // BASEDATOS_H
