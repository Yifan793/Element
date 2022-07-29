QT       += core gui quickwidgets qml xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#qml控件库提示
QML_IMPORT_PATH = $$PWD/builtinRes/baseWidgets

SOURCES += \
    MainWidget.cpp \
    main.cpp \
    xmlparser/BEXmlDomParser.cpp \
    xmlparser/BEXmlParser.cpp

HEADERS += \
    MainWidget.h \
    xmlparser/BEXmlDomParser.h \
    xmlparser/BEXmlParser.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc \
    xml.qrc \
    xmlPlugin.qrc

src_dir = $$PWD/../builtinRes
dst_dir = $$OUT_PWD/$${TARGET}.app/Contents/Resources/
QMAKE_POST_LINK += $$system(mkdir -p $$dst_dir)
QMAKE_POST_LINK += $$system(ln -sf $$src_dir $$dst_dir)
