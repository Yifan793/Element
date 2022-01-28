#ifndef BEXMLPARSER_H
#define BEXMLPARSER_H

#include <QJsonObject>
#include <QXmlStreamReader>

class BEXmlParser
{
public:
    BEXmlParser();
    bool loadFile(const QString& filePath);
    bool parse();
    QJsonObject getXmlObj() { return m_xmlObj; }

protected:
    void readPage();
    void readMeta(QJsonArray& dataArr);
    void readScript(QJsonArray& dataArr);
    void readCollapse(QJsonArray& dataArr);
    void readColumn(QJsonArray& dataArr);

    void readItem(QJsonArray& dataArr);
    void readCheckBox(QJsonArray& dataArr);
    void readOneNumberInput(QJsonArray& dataArr);
    void readTwoNumberInput(QJsonArray& dataArr);
    void readThreeNumberInput(QJsonArray& dataArr);
    void readCombobox(QJsonArray& dataArr);
    void readOption(QJsonArray& dataArr);

private:
    QJsonObject m_xmlObj;
    QXmlStreamReader m_xmlReader;
};

#endif // BEXMLPARSER_H
