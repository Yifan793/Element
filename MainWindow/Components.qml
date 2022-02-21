import QtQuick 2.15
import QtQuick.Layouts 1.15
import FMCQmlPlugin 1.0 as Plugin

Item {
    id: components

    property var leftMargin : 12

    property var allComponent: {
        "page": page,
        "collapse": collapse,
        "column": column,
        "checkbox": checkbox,
        "one_number_input": oneNumberInput,
        "two_number_input": twoNumberInput,
        "three_number_input": threeNumberInput,
        "combobox": combobox,
        "option": undefined,
        "slider_negative": textureCombobox,
        "texture_combobox": textureCombobox,
        "one_colorPicker": oneColorPicker,
        "two_colorPicker": twoColorPicker,
        "sliderInput1": sliderInput1,
        "sliderInput2": sliderInput2,
        "sliderInput3": sliderInput3,
        "sliderInput4": sliderInput4,
        "sliderInput5": sliderInput5,
        "dropFile": dropFile,
        "image": image
    }

    Component {
        id: page
        Column {
            width: parent.width
            topPadding: 8
            spacing: 8
        }
    }

    Component {
        id: collapse
        Plugin.ComAccordionBox {
            width: parent.width - 16
            anchors.left: parent.left
            anchors.leftMargin: 8
        }
    }

    Component {
        id: column
        Column {
            spacing: 8
            bottomPadding: 8
        }
    }

    Component {
        id: checkbox
        Plugin.ComMetaUiCheckBoxComponent {
            anchors.left: parent.left
            anchors.leftMargin: leftMargin
        }
    }

    Component {
        id: oneNumberInput
        Plugin.ComMetaUiOneNumberInputComponent {
            anchors.left: parent.left
            anchors.leftMargin: leftMargin
        }
    }

    Component {
        id: twoNumberInput
        Plugin.ComMetaUiTwoNumberInput1Component {
            anchors.left: parent.left
            anchors.leftMargin: leftMargin
            anchors.right: parent.right
            anchors.rightMargin: leftMargin
        }
    }

    Component {
        id: threeNumberInput
        Plugin.ComMetaUiThreeNumberInput1Component {
            anchors.left: parent.left
            anchors.leftMargin: leftMargin
        }
    }

    Component {
        id: combobox
        Plugin.ComMetaUiComboBoxComponent {
            anchors.left: parent.left
            anchors.leftMargin: leftMargin
        }
    }

    Component {
        id: textureCombobox
        Plugin.ComMetaUiComboBoxComponent {
            anchors.left: parent.left
            anchors.leftMargin: leftMargin
        }
    }

    Component {
        id: oneColorPicker
        Plugin.ComMetaUiColorSelectComponent{
            anchors.left: parent.left
            anchors.leftMargin: leftMargin
        }
    }

    Component {
        id: twoColorPicker
        Plugin.ComMetaUiComboBoxComponent {
            anchors.left: parent.left
            anchors.leftMargin: leftMargin
        }
    }

    Component {
        id: sliderInput1
        Plugin.ComSliderInputText_Style1 {
            anchors.left: parent.left
            anchors.leftMargin: leftMargin
        }
    }

    Component {
        id: sliderInput2
        Plugin.ComSliderInputText_Style2 {
            anchors.left: parent.left
            anchors.leftMargin: leftMargin
        }
    }

    Component {
        id: sliderInput3
        Plugin.ComSliderInputText_Style3 {
            anchors.left: parent.left
            anchors.leftMargin: leftMargin
        }
    }

    Component {
        id: sliderInput4
        Plugin.ComSliderInputText_Style4 {
            anchors.left: parent.left
            anchors.leftMargin: leftMargin
        }
    }

    Component {
        id: sliderInput5
        Plugin.ComSliderInputText_Style5 {
            anchors.left: parent.left
            anchors.leftMargin: leftMargin
        }
    }

    Component {
        id: dropFile
        Plugin.ComDropFileArea {
            anchors.left: parent.left
            anchors.leftMargin: leftMargin
        }
    }

    Component {
        id: image
        Plugin.ComImage {
            anchors.left: parent.left
            anchors.leftMargin: leftMargin
        }
    }

}
