#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QJsonObject>
#include <QQuickWidget>

class MainWidget : public QQuickWidget
{
    Q_OBJECT
public:
    MainWidget();
    QString getQmlUrl();
    Q_INVOKABLE QJsonObject getSettingObj();

protected:
    QJsonObject parseXml();
    QJsonObject parseDomXml();
    QJsonObject m_xmlObj;
};

#endif // MAINWIDGET_H
