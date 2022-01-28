#include "BEXmlDomParser.h"

#include <QFile>
#include <QJsonArray>

BEXmlDomParser::BEXmlDomParser()
{
}

bool BEXmlDomParser::loadFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "[xml error]: cannot read filePath " << filePath << " errorString: " << file.errorString();
        return false;
    }
    m_xmlObj = QJsonObject();
    QString errorStr;
    int errorLine;
    int errorColumn;
    if (!m_domDoc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
    {
        return false;
    }
    return true;
}

bool BEXmlDomParser::parse()
{
    QDomElement root = m_domDoc.documentElement();
    parseXmlElement(root, m_xmlObj);
    return true;
}

void BEXmlDomParser::parseXmlElement(const QDomElement& element, QJsonObject& dataObj)
{
    dataObj["type"] = element.nodeName();
    dataObj["titleText"] = element.text();
    QJsonObject atrrsObj;
    QJsonArray children;
    QDomNamedNodeMap attrs = element.attributes();
    int count = attrs.count();
    for (int i = 0; i < count; i++)
    {
        auto&& attr = attrs.item(i).toAttr();
        dataObj[attr.name()] = attr.value();
    }
    for (auto child = element.firstChild(); !child.isNull(); child = child.nextSibling())
    {
        if (child.nodeType() == QDomNode::NodeType::ElementNode)
        {
            QJsonObject childObj;
            parseXmlElement(child.toElement(), childObj);
            children.append(childObj);
        }
    }
    if (!children.isEmpty())
    {
        dataObj["children"] = children;
    }
}
