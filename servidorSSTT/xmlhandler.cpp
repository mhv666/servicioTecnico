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
if (readContentOfTag(message,"tipo") == "modelos_request")
{
       doc = xmlReadMemory(message.toStdString().c_str(),strlen(message.toStdString().c_str()),"modelos.xml",NULL,0);
       if (doc ==NULL)
       {
           qDebug()<<"error  linea 93 xmlhandler.cpp";

           return false;
       }
       /**
        * @brief xmlSaveFormatFile
        * Guarda el doc en el equipo
        * @nuevaOrden.xml nombre del documento//Ruta
        * @doc el documento en si
        * @1 el formato -> 0=nonformatted, 1=indented formatting, 2= nonindented values.
        */
        xmlSaveFormatFile("modelos_request.xml",doc,1);
        xmlFreeDoc(doc);
       return true;
    }else if(readContentOfTag(message,"tipo") == "newRma")
    {
        doc = xmlReadMemory(message.toStdString().c_str(),strlen(message.toStdString().c_str()),"newRma.xml",NULL,0);
        if (doc ==NULL)
        {
            qDebug()<<"error alconvertir a newRma.xml";
            return false;
        }
        xmlSaveFormatFile("newRma.xml",doc,1);
        xmlFreeDoc(doc);
        return true;
    }else if(readContentOfTag(message,"tipo") == "loginRequest"){
        doc = xmlReadMemory(message.toStdString().c_str(),strlen(message.toStdString().c_str()),"loginRequest.xml",NULL,0);
        if (doc ==NULL)
        {
            qDebug()<<"error alconvertir a loginRequest.xml";
            return false;
        }
        xmlSaveFormatFile("loginRequest.xml",doc,1);
        xmlFreeDoc(doc);
        return true;
    }

}
QDomDocument XmlHandler::generateXmlOfMarcas(QStringList marcas)
{
QDomDocument doc;
QDomElement root = doc.createElement("document");
QDomElement header = doc.createElement("header");
QDomElement payload = doc.createElement("payload");
QDomElement tipo = doc.createElement("tipo");
tipo.appendChild(doc.createTextNode("modelos_result"));
QDomElement dispositivos = doc.createElement("dispositivos");

for (int i = 0; i < marcas.size(); ++i) {
    QDomElement dispositivo = doc.createElement("dispositivo");
    QDomElement marca = doc.createElement("marca");

    marca.appendChild(doc.createTextNode(marcas.at(i)));
    dispositivos.appendChild(dispositivo);
    dispositivo.appendChild(marca);

}


root.appendChild(header);
root.appendChild(payload);
payload.appendChild(dispositivos);
header.appendChild(tipo);
doc.appendChild(root);

return doc;
}
QDomDocument XmlHandler::generateXmlOfModelos(QDomDocument doc,QStringList modelos,int marca)
{




        for (int i = 0; i < modelos.size(); ++i)
        {

            QDomElement modelo = doc.createElement("modelo");
            modelo.appendChild(doc.createTextNode(modelos.at(i)));
            doc.elementsByTagName("dispositivo").at(marca).appendChild(modelo);
        }



    return doc;
}
QDomDocument XmlHandler::generateXmlOfLogin(QString id)
{
    QDomDocument doc;
    QDomElement root = doc.createElement("login");
    QDomElement header = doc.createElement("header");
    QDomElement payload = doc.createElement("payload");
    QDomElement tipo = doc.createElement("tipo");
    tipo.appendChild(doc.createTextNode("login_result"));
    QDomElement isValid = doc.createElement("isValid");

    QDomElement idTienda =doc.createElement("idTienda");

    if (!id.isNull()) {
       isValid.appendChild(doc.createTextNode("true"));
       idTienda.appendChild(doc.createTextNode(id));
        qDebug()<<"isValid is true";
    }else{
        isValid.appendChild(doc.createTextNode("false"));
        qDebug()<<"isValid is false";
    }
    root.appendChild(header);
    header.appendChild(tipo);
    root.appendChild(payload);
    payload.appendChild(isValid);
    payload.appendChild(idTienda);
    doc.appendChild(root);
    return doc;

}
QDomDocument XmlHandler::generateXmlReturnRma(QString idRma)
{
 QDomDocument doc;
 QDomElement root = doc.createElement("document");
 QDomElement header = doc.createElement("header");
 QDomElement payload = doc.createElement("payload");
 QDomElement tipo = doc.createElement("tipo");
 tipo.appendChild(doc.createTextNode("rma_result"));
 QDomElement rmaResult = doc.createElement("rmaResult");
 if (!idRma.isNull()) {
    rmaResult.appendChild(doc.createTextNode("El id del RMA es :"+idRma));


 }else{
     rmaResult.appendChild(doc.createTextNode("Error:No ha sido posible insertar la nueva orden"));

 }
 root.appendChild(header);
 header.appendChild(tipo);
 root.appendChild(payload);
 payload.appendChild(rmaResult);
 doc.appendChild(root);
 return doc;
}

QString XmlHandler::readContentOfTag( QString xml ,QString nombreTag)
{

QDomDocument doc;
doc.setContent(xml);
QDomNodeList list = doc.elementsByTagName(nombreTag);
QString model= list.at(0).toElement().text();
return model;
}
