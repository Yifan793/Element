QT       += core gui quickwidgets qml

TEMPLATE = subdirs

SUBDIRS += \
    MainWindow \
    BaseWidgets

BaseWidgets.file = depends/BaseWidgets/FaceMagicCreatorWidgets.pro

MainWindow.depends += BaseWidgets
