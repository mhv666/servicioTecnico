#ifndef XMLHANDLER_H
#define XMLHANDLER_H
#include <QDomDocument>

class XmlHandler
{
public:
    XmlHandler();
    QDomDocument generateXmlForRma(QString id_estado);
    QString readContentOfTag( QString xml ,QString nombreTag);

};
#endif // XMLHANDLER_H
