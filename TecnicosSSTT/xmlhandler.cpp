#include "xmlhandler.h"
#include <QDomDocument>
#include <QDomDocumentType>

XmlHandler::XmlHandler()
{

}

QDomDocument XmlHandler::generateXmlForRma(QString id_estado)
{
     QDomDocument doc;
     QDomElement root = doc.createElement("document");
     QDomElement header = doc.createElement("header");
     QDomElement tipo = doc.createElement("tipo");
     QDomElement payload = doc.createElement("payload");
     QDomElement estado = doc.createElement("estado");

     estado.appendChild(doc.createTextNode(id_estado));
     tipo.appendChild(doc.createTextNode("return_rma"));
     root.appendChild(header);
     header.appendChild(tipo);
     payload.appendChild(estado);
     root.appendChild(payload);
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
