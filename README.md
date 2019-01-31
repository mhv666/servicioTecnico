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
 - QTwebsocket5          -
 - libqt5-qtwebsockets   -
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
Abrir **Yast** --> **Administrador de servicios**
 y activar:
apache2
postgresql
```
A continuacion habilitamos php en apache:
```
a2enmod php7
```
Ahora toca ir a configurar el servicio de postgres: 
Editar estos archivos:

- _postgresql.conf_
- _phppg_hba.conf_

en estos archivos hay que quitar la "#" de las siguientes palabras:
```
listen_addres
port
```
Procederemos a reiniciar el servicio
```
sudo systemctl restart postgresql
```
Ahora hay que iniciar como usuario postgres, para ello utilizamos el siguiente comando:
```
su postgres
```
Acto seguido crearemos un usuario nuevo:
```
createuser -sP [nombre usuario]
```

ahora, hay qué editar este archivo:
_/etc/phpPgmyadmin/config.inc.php_


Hay que modificar 2 lineas
- en _$conf_  en la parte del host escribir entre comillas simples localhost
- en _$conf_  en la parte del port escribir 5432

y para finalizar hay que añadir las siguientes lineas en el .Pro del proyecto en qt.
```
QT += websockets
QT += XML
Config += c++11 

```


----------

## Posibles Fallos
- Fallo en el inicio del servicio de apache
  - _Solucion_

    Ir a:
    ```
    /etc/apache2/conf.d/phpPgAdmin.conf
    ```
    y borrar las lineas de:
    ```
     "<2.4>" y "<ifVersion>"
    ```
- Instalacion de una version anterior de phppgadmin
  -  _Solucion_ 
    
    Proceder con el borrado recursivo de la instalacion anterior:
    ```
    rm -rf phpPgAdmin
    ```
    Procederemos a lainstalacion de la version correcta mediante wget:
    ```
    wget https://github.com/phppgadmin/phppgadmin/releases/download/REL_5-6-0/phpPgAdmin-5.6.0.tar.bz2
    ```
    Una vez descargado, procedemos a la descompresion:
    ```
    tar -xjvf phpPgAdmin-5.6.0.tar.bz2
    ```
    
 