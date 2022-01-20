import QtQuick 2.0
import FMCQmlPlugin 1.0 as Plugin

Rectangle {
    color: "black"

    Plugin.ComAccordionBox {
        id: test
        titleText: qsTr("灯光设置")
    }
}
