#ifndef XMLHANDLER_H
#define XMLHANDLER_H
#include <QDomDocument>

class XmlHandler
{
public:
    XmlHandler();
    bool validaXML(const char *xml);
    QString read( QString xml,QString nombreTag);
};

#endif // XMLHANDLER_H
