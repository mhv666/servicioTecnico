# servicioTecnico
_Proyecto Para el Grado superior de DAM, creacion de un servicio tecnico y rma con websockets y base de datos PostgresSQL_

----------

## Requisitos Previos
Antes de empezar necesitaremos estos componentes de software
1. Sistema Operativo
 - OpenSuse 15 Leap(En mi caso)

3. Software
 - Qt

2. Paquetes necessarios
 - libqt55ql5-postgresql - Driver necesario para qt pueda conectarse apostgres
 - postgresql            - Cliente SQL
 - postgresql-contrib    - Extensiones de Postgres(utiles si queremos añadir un campo uuid)  
 - postgresql-server     - Servidor SQL
 - phppgadmin            - Pagina de administracion de la Base de datos 
 - Servidor Web y Lamp   - Pattern que incluye todo lo necesario para el servidor web

----------

## Instalacion
Una vez instalado todo el software necesario procederemos:
_Poner en ejecuccuion los servicios postgres y apache_
```
Abrir Yast --> Administrador de servicios
_y activar: _
apache2
postgresql
```
----------

## Posibles Fallos
- Fallo en el inicio del servicio de apache
  _Solucion_
    Ir a:
    ```
    /etc/apache2/conf.d/phpPgAdmin.conf
    ```
    _y borrar las lineas de "<2.4>" y "<ifVersion>"_
     
 