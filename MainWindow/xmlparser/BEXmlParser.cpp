#include "BEXmlParser.h"

#include <QDebug>
#include <QFile>
#include <QGlobalStatic>
#include <QJsonArray>
#include <QXmlStreamReader>

static const QString c_page = "page";
static const QString c_meta = "meta";
static const QString c_script = "script";
static const QString c_collapse = "collapse";
static const QString c_column = "column";

static const QString c_item = "item";
static const QString c_checkbox = "checkbox";
static const QString c_one_number_input = "one_number_input";
static const QString c_two_number_input = "two_number_input";
static const QString c_three_number_input = "three_number_input";
static const QString c_combobox = "combobox";
static const QString c_option = "option";
static const QString c_texture_combobox = "texture_combobox";
static const QString c_two_colorPicker = "two_colorPicker";
static const QString c_slider_negative = "slider_negative";
static const QStringList c_itemList = { c_item, c_checkbox, c_one_number_input, c_two_number_input, c_three_number_input,
                                        c_combobox, c_texture_combobox, c_two_colorPicker, c_slider_negative };

BEXmlParser::BEXmlParser()
{
}

bool BEXmlParser::loadFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "[xml error]: cannot read filePath " << filePath << " errorString: " << file.errorString();
        return false;
    }
    m_xmlObj = QJsonObject();
    m_xmlReader.clear();
    m_xmlReader.addData(file.readAll());
    file.close();
    if (m_xmlReader.hasError())
    {
        qDebug() << QString::fromLocal8Bit("[xml error]:%1  line:%2  column:%3  characterOffset:%4").arg(m_xmlReader.errorString()).arg(m_xmlReader.lineNumber()).arg(m_xmlReader.columnNumber()).arg(m_xmlReader.characterOffset());
        return false;
    }
    return true;
}

bool BEXmlParser::parse()
{
    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name() == c_page)
        {
            readPage();
        }
        else
        {
            m_xmlReader.raiseError(QObject::tr("[xml error]: must start with page"));
        }
    }
    else
    {
        m_xmlReader.raiseError(QObject::tr("[xml error]: start error"));
    }
    if (m_xmlReader.hasError())
    {
        qDebug() << QString::fromLocal8Bit("[xml error]:%1  line:%2  column:%3  characterOffset:%4").arg(m_xmlReader.errorString()).arg(m_xmlReader.lineNumber()).arg(m_xmlReader.columnNumber()).arg(m_xmlReader.characterOffset());
    }

    m_xmlReader.clear();
    return !m_xmlReader.error();
}

void BEXmlParser::readPage()
{
    Q_ASSERT(m_xmlReader.isStartElement() && m_xmlReader.name() == c_page);
    QJsonObject Obj = QJsonObject{
        { "type", c_page }
    };
    QJsonArray childrenDataArr;
    while (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name() == c_meta)
        {
            readMeta(childrenDataArr);
        }
        if (m_xmlReader.name() == c_collapse)
        {
            readCollapse(childrenDataArr);
        }
        else
        {
            m_xmlReader.skipCurrentElement();
        }
    }
    if (!childrenDataArr.isEmpty())
    {
        Obj["children"] = childrenDataArr;
    }
    m_xmlObj = Obj;
}

void BEXmlParser::readMeta(QJsonArray& dataArr)
{
    Q_ASSERT(m_xmlReader.isStartElement() && m_xmlReader.name() == c_meta);
    QJsonObject obj = QJsonObject{
        { "type", c_meta }
    };
    QJsonArray childrenDataArr;
    while (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name() == c_script)
        {
            readScript(childrenDataArr);
        }
        else
        {
            m_xmlReader.skipCurrentElement();
        }
    }
    if (!childrenDataArr.isEmpty())
    {
        obj["children"] = childrenDataArr;
    }
    dataArr.append(obj);
}

void BEXmlParser::readScript(QJsonArray& dataArr)
{
    Q_ASSERT(m_xmlReader.isStartElement() && m_xmlReader.name() == c_script);
    QJsonObject obj = {
        { "type", c_script },
        { "src", m_xmlReader.attributes().value("src").toString() } //做个循环遍历即可？
    };
    dataArr.append(obj);
}

void BEXmlParser::readCollapse(QJsonArray& dataArr)
{
    Q_ASSERT(m_xmlReader.isStartElement() && m_xmlReader.name() == c_collapse);
    QJsonObject obj = QJsonObject{
        { "type", m_xmlReader.name().toString() },
        //        { "titleText", m_xmlReader.readElementText() }
    };
    auto attrs = m_xmlReader.attributes();
    for (auto it = attrs.begin(); it != attrs.end(); it++)
    {
        obj[it->name().toString()] = it->value().toString();
    }
    QJsonArray childrenDataArr;
    while (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name() == c_column)
        {
            readColumn(childrenDataArr);
        }
        else
        {
            m_xmlReader.skipCurrentElement();
        }
    }
    if (!childrenDataArr.isEmpty())
    {
        obj["children"] = childrenDataArr;
    }
    dataArr.append(obj);
}

void BEXmlParser::readColumn(QJsonArray& dataArr)
{
    Q_ASSERT(m_xmlReader.isStartElement() && m_xmlReader.name() == c_column);
    QJsonObject obj = QJsonObject{
        { "type", c_column }
    };
    auto attrs = m_xmlReader.attributes();
    for (auto it = attrs.begin(); it != attrs.end(); it++)
    {
        obj[it->name().toString()] = it->value().toString();
    }
    QJsonArray childrenDataArr;
    while (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name() == c_item)
        {
            readItem(childrenDataArr);
        }
        else if (m_xmlReader.name() == c_checkbox)
        {
            readCheckBox(childrenDataArr);
        }
        else if (m_xmlReader.name() == c_one_number_input)
        {
            readOneNumberInput(childrenDataArr);
        }
        else if (m_xmlReader.name() == c_two_number_input)
        {
            readTwoNumberInput(childrenDataArr);
        }
        else if (m_xmlReader.name() == c_three_number_input)
        {
            readThreeNumberInput(childrenDataArr);
        }
        else if (m_xmlReader.name() == c_combobox)
        {
            readCombobox(childrenDataArr);
        }
        else
        {
            m_xmlReader.skipCurrentElement();
        }
    }
    if (!childrenDataArr.isEmpty())
    {
        obj["children"] = childrenDataArr;
    }
    dataArr.append(obj);
}

void BEXmlParser::readItem(QJsonArray& dataArr)
{
    Q_ASSERT(m_xmlReader.isStartElement() && c_itemList.contains(m_xmlReader.name()));
    QJsonObject obj = QJsonObject{
        { "type", m_xmlReader.name().toString() },
        //        { "titleText", m_xmlReader.readElementText() }
    };
    auto attrs = m_xmlReader.attributes();
    for (auto it = attrs.begin(); it != attrs.end(); it++)
    {
        obj[it->name().toString()] = it->value().toString();
    }
    QJsonArray childrenDataArr;
    while (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name() == c_checkbox)
        {
            readCheckBox(childrenDataArr);
        }
        else if (m_xmlReader.name() == c_one_number_input)
        {
            readOneNumberInput(childrenDataArr);
        }
        else if (m_xmlReader.name() == c_two_number_input)
        {
            readTwoNumberInput(childrenDataArr);
        }
        else if (m_xmlReader.name() == c_three_number_input)
        {
            readThreeNumberInput(childrenDataArr);
        }
        else if (m_xmlReader.name() == c_combobox)
        {
            readCombobox(childrenDataArr);
        }
        else
        {
            m_xmlReader.skipCurrentElement();
        }
    }
    if (!childrenDataArr.isEmpty())
    {
        obj["children"] = childrenDataArr;
    }
    dataArr.append(obj);
}

void BEXmlParser::readCheckBox(QJsonArray& dataArr)
{
    Q_ASSERT(m_xmlReader.isStartElement() && m_xmlReader.name() == c_checkbox);
    QJsonObject obj = QJsonObject{
        { "type", c_checkbox },
        { "titleText", m_xmlReader.readElementText() }
    };
    auto attrs = m_xmlReader.attributes();
    for (auto it = attrs.begin(); it != attrs.end(); it++)
    {
        obj[it->name().toString()] = it->value().toString();
    }
    dataArr.append(obj);
}

void BEXmlParser::readOneNumberInput(QJsonArray& dataArr)
{
    Q_ASSERT(m_xmlReader.isStartElement() && m_xmlReader.name() == c_one_number_input);
    QJsonObject obj = QJsonObject{
        { "type", c_one_number_input },
        { "titleText", m_xmlReader.readElementText() }
    };
    auto attrs = m_xmlReader.attributes();
    for (auto it = attrs.begin(); it != attrs.end(); it++)
    {
        obj[it->name().toString()] = it->value().toString();
    }
    dataArr.append(obj);
}

void BEXmlParser::readTwoNumberInput(QJsonArray& dataArr)
{
    Q_ASSERT(m_xmlReader.isStartElement() && m_xmlReader.name() == c_two_number_input);
    QJsonObject obj = QJsonObject{
        { "type", c_two_number_input },
        { "titleText", m_xmlReader.readElementText() }
    };
    auto attrs = m_xmlReader.attributes();
    for (auto it = attrs.begin(); it != attrs.end(); it++)
    {
        obj[it->name().toString()] = it->value().toString();
    }
    dataArr.append(obj);
}

void BEXmlParser::readThreeNumberInput(QJsonArray& dataArr)
{
    Q_ASSERT(m_xmlReader.isStartElement() && m_xmlReader.name() == c_three_number_input);
    QJsonObject obj = QJsonObject{
        { "type", c_three_number_input },
        { "titleText", m_xmlReader.readElementText() }
    };
    auto attrs = m_xmlReader.attributes();
    for (auto it = attrs.begin(); it != attrs.end(); it++)
    {
        obj[it->name().toString()] = it->value().toString();
    }
    dataArr.append(obj);
}

void BEXmlParser::readCombobox(QJsonArray& dataArr)
{
    Q_ASSERT(m_xmlReader.isStartElement() && m_xmlReader.name() == c_combobox);
    QJsonObject obj = QJsonObject{
        { "type", c_combobox }
    };
    auto attrs = m_xmlReader.attributes();
    for (auto it = attrs.begin(); it != attrs.end(); it++)
    {
        obj[it->name().toString()] = it->value().toString();
    }
    QJsonArray childrenDataArr;
    while (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name() == c_option)
        {
            readOption(childrenDataArr);
        }
        else
        {
            m_xmlReader.skipCurrentElement();
        }
    }
    obj["children"] = childrenDataArr;
    dataArr.append(obj);
}

void BEXmlParser::readOption(QJsonArray& dataArr)
{
    Q_ASSERT(m_xmlReader.isStartElement() && m_xmlReader.name() == c_option);
    QJsonObject obj = QJsonObject{
        { "titleText", m_xmlReader.readElementText() }
    };
    auto attrs = m_xmlReader.attributes();
    for (auto it = attrs.begin(); it != attrs.end(); it++)
    {
        obj[it->name().toString()] = it->value().toString();
    }
    dataArr.append(obj);
}
