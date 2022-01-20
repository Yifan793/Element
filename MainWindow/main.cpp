#include "MainWidget.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.resize(668, 550);
    w.show();
    return a.exec();
}
