#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QQuickWidget>

class MainWidget : public QQuickWidget
{
    Q_OBJECT
public:
    MainWidget();
    QString getQmlUrl();

protected:
    void parserXml();
};

#endif // MAINWIDGET_H
