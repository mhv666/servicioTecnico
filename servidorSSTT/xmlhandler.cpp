#include "xmlhandler.h"
#include <iostream>
#include <QDebug>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <QDomDocument>
#include <QDomDocumentType>



XmlHandler::XmlHandler()
{

}
bool XmlHandler::validaXML(const char *xml)
{
    bool result = false;

    /// Crea el contexto del analizador.
    xmlParserCtxtPtr ctxt = xmlNewParserCtxt();
    if (ctxt == NULL)
    {
        std::cout << "Error al crear el contexto del analizador." << std::endl;
        return false;
    } // end if

    /// Analiza el archivo activando la opción de validación DTD.
    xmlDocPtr doc = xmlCtxtReadFile(ctxt, xml, NULL, XML_PARSE_DTDVALID);
    if (doc == NULL)
    {
        std::cout << "Error al analizar el archivo." << std::endl;
        return false;
    } // end if

    /// Comprueba la validez del XML.
    if (ctxt->valid == 0)
    {
        std::cout << "El archivo XML no es valido." << std::endl;
    } else {
        std::cout << "El archivo XML es valido." << std::endl;
        result = true;
    } // end if

    /// Libera memoria.
    xmlFreeDoc(doc);
    xmlFreeParserCtxt(ctxt);

    return result;
}
bool XmlHandler::validarDomInsert(QString xml){
    QDomDocument doc;
    QDomDocumentType docdtd();


    doc.setContent(xml);
    QDomElement root = doc.documentElement();
    QString rootTag = root.tagName();
    qDebug()<<"The ROOT tag is"<<rootTag;
    QDomElement header =root.firstChild().toElement();
    QDomElement payload =header.nextSibling().toElement();
    qDebug()<<"The header tag is"<<header.tagName();
    qDebug()<<"The payload tag is"<<payload.tagName();
    QDomElement type = header.firstChild().toElement();
    qDebug()<<"The type tag is"<<type.tagName();
    QDomElement user = payload.firstChild().toElement();
    QDomElement telefono = user.nextSibling().toElement();
    QDomElement tienda = user.nextSibling().nextSibling().toElement();
    qDebug()<<"The type user is"<<user.tagName();
    qDebug()<<"The type telefono is"<<telefono.tagName();
    qDebug()<<"The type tienda  is"<<tienda.tagName();
    QDomElement nombre = user.firstChild().toElement();
    QDomElement apellido = nombre.nextSibling().toElement();
    QDomElement numTlf = nombre.nextSibling().nextSibling().toElement();
    qDebug()<<"The type nombre is"<<nombre.tagName();
    qDebug()<<"The type apellido is"<<apellido.tagName();
    qDebug()<<"The type numTlf is"<<numTlf.tagName();
    QDomElement marca = telefono.firstChild().toElement();
    QDomElement modelo = marca.nextSibling().toElement();
    qDebug()<<"The type marca is"<<marca.tagName();
    qDebug()<<"The type modelo is"<<modelo.tagName();
    QDomElement idTienda = tienda.firstChild().toElement();
    qDebug()<<"The type id is"<<idTienda.tagName();


}
bool XmlHandler::QstringToXml(QString message){
xmlDocPtr doc;
if (read(message,"tipo") == "request")
{
       doc = xmlReadMemory(message.toStdString().c_str(),strlen(message.toStdString().c_str()),"modelos.xml",NULL,0);
       if (doc ==NULL)
       {
           qDebug()<<"error alconvertir a modelos.xml";

           return false;
       }
       /**
        * @brief xmlSaveFormatFile
        * Guarda el doc en el equipo
        * @nuevaOrden.xml nombre del documento//Ruta
        * @doc el documento en si
        * @1 el formato -> 0=nonformatted, 1=indented formatting, 2= nonindented values.
        */
        xmlSaveFormatFile("modelos.xml",doc,1);
        xmlFreeDoc(doc);
       return true;
    }else if(read(message,"tipo") == "insert")
    {
        doc = xmlReadMemory(message.toStdString().c_str(),strlen(message.toStdString().c_str()),"nuevaOrden.xml",NULL,0);
        if (doc ==NULL)
        {
            qDebug()<<"error alconvertir a nuevaOrden.xml";
            return false;
        }
        xmlSaveFormatFile("nuevaOrden.xml",doc,1);
        xmlFreeDoc(doc);
        return true;
    }

}

QString XmlHandler::read( QString xml ,QString nombreTag){

QDomDocument doc;
doc.setContent(xml);
QDomNodeList list = doc.elementsByTagName(nombreTag);
QString model= list.at(0).toElement().text();
return model;
}
