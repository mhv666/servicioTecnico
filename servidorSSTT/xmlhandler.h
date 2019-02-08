#ifndef XMLHANDLER_H
#define XMLHANDLER_H
#include <QDomDocument>

class XmlHandler
{
public:
    XmlHandler();
    bool validaXML(const char *xml);
    bool procesarXml(QString xml);
    bool validarDomInsert(QString xml);
    bool QstringToXml(QString message);
    QString readContentOfTag( QString xml,QString nombreTag);
    QDomDocument generateXmlOfMarcas(QStringList marcas);
    QDomDocument generateXmlOfModelos(QDomDocument doc,QStringList modelos,int marca);
    QDomDocument generateXmlOfLogin(QString id);


};

#endif // XMLHANDLER_H
