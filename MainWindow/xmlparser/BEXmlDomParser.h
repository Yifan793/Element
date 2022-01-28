#ifndef BEXMLDOMPARSER_H
#define BEXMLDOMPARSER_H

#include <QDomDocument>
#include <QJsonObject>
#include <QString>

class BEXmlDomParser
{
public:
    BEXmlDomParser();
    bool loadFile(const QString& filePath);
    bool parse();
    QJsonObject getXmlObj() { return m_xmlObj; }

protected:
    void parseXmlElement(const QDomElement& element, QJsonObject& dataObj);

protected:
    QJsonObject m_xmlObj;
    QDomDocument m_domDoc;
};

#endif // BEXMLDOMPARSER_H
