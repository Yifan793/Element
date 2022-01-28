QT       += core gui quickwidgets qml

TEMPLATE = subdirs

SUBDIRS += \
    MainWindow \
    BaseWidgets

QML_IMPORT_PATH = $$PWD/builtinRes/baseWidgets

BaseWidgets.file = depends/BaseWidgets/FaceMagicCreatorWidgets.pro

MainWindow.depends += BaseWidgets
