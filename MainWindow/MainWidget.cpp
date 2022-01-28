#include "MainWidget.h"

#include "xmlparser/BEXmlDomParser.h"
#include "xmlparser/BEXmlParser.h"

#include <QCoreApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <sys/time.h>

MainWidget::MainWidget()
{
    engine()->addImportPath(QCoreApplication::applicationDirPath() + "/../Resources/builtinRes/baseWidgets");
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    rootContext()->setContextProperty("mainWidget", this);
    setSource(QUrl(getQmlUrl()));
    setMinimumSize(352, 1200);
    setFixedWidth(352);
    m_xmlObj = parseDomXml();
    //    qDebug() << "test m_xmlObj " << m_xmlObj;

    //    {
    //        struct timeval tpstart, tpend;
    //        float timeuse;
    //        gettimeofday(&tpstart, NULL);
    //        parseXml();
    //        gettimeofday(&tpend, NULL);
    //        timeuse = (1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec) / 1000000.0;
    //        qDebug() << "time is : " << timeuse << "s";
    //    }
    //    {
    //        struct timeval tpstart, tpend;
    //        float timeuse;
    //        gettimeofday(&tpstart, NULL);
    //        parseDomXml();
    //        gettimeofday(&tpend, NULL);
    //        timeuse = (1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec) / 1000000.0;
    //        qDebug() << "time is : " << timeuse << "s";
    //    }
}

QJsonObject MainWidget::getSettingObj()
{
    QJsonObject settingObj = parseDomXml();
    //    qDebug() << "test SettingObj " << settingObj;
    return settingObj;
}

QString MainWidget::getQmlUrl()
{
    return "qrc:/SettingPage.qml";
}

QJsonObject MainWidget::parseXml()
{
    BEXmlParser xmlParser;
    xmlParser.loadFile(":/xml/particleSystem.xml");
    xmlParser.parse();
    //    qDebug() << "test xmlObj " << __FUNCTION__ << " " << xmlParser.getXmlObj();
    return xmlParser.getXmlObj();
}

QJsonObject MainWidget::parseDomXml()
{
    BEXmlDomParser xmlParser;
    xmlParser.loadFile(":/xml/particleSystem.xml");
    xmlParser.parse();
    //    qDebug() << "test xmlObj 2 " << __FUNCTION__ << " " << xmlParser.getXmlObj();
    return xmlParser.getXmlObj();
}
