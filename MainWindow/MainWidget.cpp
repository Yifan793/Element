#include "MainWidget.h"

#include <QCoreApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <xmlparser/BEXmlParser.h>

MainWidget::MainWidget()
{
    engine()->addImportPath(QCoreApplication::applicationDirPath() + "/../Resources/builtinRes/baseWidgets");
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    setSource(QUrl(getQmlUrl()));
    setMinimumSize(668, 550);
    rootContext()->setContextProperty("", this);
    parserXml();
}

QString MainWidget::getQmlUrl()
{
    return "qrc:/SettingPage.qml";
}

void MainWidget::parserXml()
{
    BEXmlParser xmlParser;
    xmlParser.loadFile(":/xml/particleSystem.xml");
    xmlParser.parser();
    qDebug() << "test xmlObj " << xmlParser.getXmlObj();
}
