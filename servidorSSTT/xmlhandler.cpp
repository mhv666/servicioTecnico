#include "xmlhandler.h"
#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <QDomDocument>



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
QString XmlHandler::read( QString xml ,QString nombreTag){

QDomDocument doc;
doc.setContent(xml);
QDomNodeList list = doc.elementsByTagName(nombreTag);
QString model= list.at(0).toElement().text();
return model;
}
