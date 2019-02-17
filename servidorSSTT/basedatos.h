#ifndef BASEDATOS_H
#define BASEDATOS_H
#include <QSqlQuery>
#include <QSqlTableModel>

class BaseDatos
{
public:
    BaseDatos();
    void connectDatabase();
    QString loginCentral(QString usuario, QString password);
    QString estadoRma(QString idRma);
    QVariant crearRma(QString idCliente,QString idEstado,QString idDispositivo,QString idTecnico,QString idTienda,QString DescripcionProblema);
    QSqlTableModel consultarRma(QString estado);
    QStringList consultarMarcas();
    QStringList consultarModelos(QString marca);
    QString devolverIdUsuario(QString usuario, QString apellido,QString numeroTelefono);
    QVariant crearUsuario(QString usuario, QString apellido,QString numeroTelefono);
    QString devolverIdModelo(QString nombreModelo);

private:
    QSqlDatabase mdb;
};

#endif // BASEDATOS_H
