/**
 * @param {*} parent       组件的父
 * @param {Component} comp 在Components.qml中定义，调用createObject创建实例
 */
const createComponentObjFunc = {
    "page": createPageObject,
    "collapse": createCollapseObject,
    "column": createColumnObject,
    "checkbox": createCheckboxObject,
    "one_number_input": createOneNumberInputObject,
    "two_number_input": createTwoNumberInputObject,
    "three_number_input": createThreeNumberInputObject,
    "combobox": createComboboxObject,
    "option": createOptionObject,
    "slider_negative": createOneNumberInputObject,
    "texture_combobox": createTextureComboboxObject,
    "one_colorPicker": createObjectWithTitleDefault,
    "two_colorPicker": createTwoColorPickerObject,
    "sliderInput1": createObjectWithTitleDefault,
    "sliderInput2": createObjectWithTitleDefault,
    "sliderInput3": createObjectWithTitleDefault,
    "sliderInput4": createObjectWithTitleDefault,
    "sliderInput5": createObjectWithTitleDefault,
    "dropFile": createDropFileObject,
    "image": createObjectDefault
}

var rootPage = undefined

function loadJsFile(root, parent, path) {
    let qmlString = `import '${path}' as JsFunc; import QtQuick 2.15; Item {id: __jsHelper; property var __jsFunc: JsFunc;}`
    let jsHelperObj = Qt.createQmlObject(qmlString, parent, "errorMsg")
    if (jsHelperObj === null) {
        console.error("Error creating jsHelperObj")
    }
    rootPage = root
    return jsHelperObj
}

const defaultKey = ["children", "type"]

function getPropertiesObj(obj) {
    var propObj = {}
    Object.keys(obj).forEach(function (key) {
        if (defaultKey.indexOf(key) !== -1) {
            return
        }

        if (key.startsWith(":")) {
            propObj[key.slice(1)] = rootPage.elements.__jsHelper.__jsFunc[obj[key]]
        } else if(key.startsWith("on-"))
        {
            propObj[key.slice(3)] = rootPage.elements.__jsHelper.__jsFunc[obj[key]]
        } else {
            let objValue = obj[key]
            //所有的数据类型都是string，需要转换
            objValue = (objValue === "true" ? true : objValue)
            objValue = (objValue === "false" ? false : objValue)
            propObj[key] = objValue
        }
    })
    return propObj
}

/**
 * @brief 大多数空组件默认创建方式
 */
function createObjectDefault(parent, comp, obj) {
    let propObj = Object.assign(getPropertiesObj(obj))
    var compObj = comp.createObject(parent, propObj)
    if (compObj === null) {
        console.error("Error creating compObj Default")
    }
    return compObj
}

/**
 * @brief 大多数带有文字说明的组件默认创建方式
 * @param {string} strText 属性名称
 */
function createObjectWithTitleDefault(parent, comp, obj) {
    let propObj = Object.assign(getPropertiesObj(obj), {
                                    "strText": qsTr(obj.titleText)
                                })
    var compObj = comp.createObject(parent, propObj)
    if (compObj === null) {
        console.error("Error creating compObj DefaultWithTitle")
    }
    return compObj
}


/**
 * @brief page组件，实际为一个column，竖向顺序排列
 */
function createPageObject(parent, comp, obj) {
    var page = comp.createObject(parent)
    if (page === null) {
        console.error("Error creating page")
    }
    return page
}


/**
 * @brief 可折叠组件，一般作为group的title
 * @param {string} titleText 折叠组名称
 */
function createCollapseObject(parent, comp, obj) {
    let propObj = Object.assign(getPropertiesObj(obj), {
                                    "titleText": qsTr(obj.title)
                                })
    var collapse = comp.createObject(parent, propObj)
    if (collapse === null) {
        console.error("Error creating collpase")
    }
    return collapse
}


/**
 * @brief layout，Column，竖向顺序排列
 */
function createColumnObject(parent, comp, obj) {
    var column = comp.createObject(parent, getPropertiesObj(obj))
    if (column === null) {
        console.error("Error creating column")
    }
    if (parent.hasOwnProperty("accordionContent")) {
        parent.accordionContent = column //todo 特殊代码
    }
    return column
}


/**
 * @brief 选择框
 * @param {string} titleText 属性名称
 */
function createCheckboxObject(parent, comp, obj) {
    let propObj = Object.assign(getPropertiesObj(obj), {
                                    "strTitle": qsTr(obj.titleText)
                                })
    var checkbox = comp.createObject(parent, propObj)
    if (checkbox === null) {
        console.error("Error creating checkbox")
    }
    return checkbox
}


/**
 * @brief 一个数字输入框
 * @param {string} titleText 属性名称
 */
function createOneNumberInputObject(parent, comp, obj) {
    let propObj = Object.assign(getPropertiesObj(obj), {
                                    "strTitle": qsTr(obj.titleText)
                                })
    var oneNumberInput = comp.createObject(parent, propObj)
    if (oneNumberInput === null) {
        console.error("Error creating oneNumberInput")
    }
    return oneNumberInput
}


/**
 * @brief 横向两个数字输入框
 * @param {string} titleText 属性名称
 */
function createTwoNumberInputObject(parent, comp, obj) {
    let propObj = Object.assign(getPropertiesObj(obj), {
                                    "strTitle": qsTr(obj.titleText)
                                })
    var twoNumberInput = comp.createObject(parent, propObj)
    if (twoNumberInput === null) {
        console.error("Error creating twoNumberInput")
    }
    return twoNumberInput
}


/**
 * @brief 横向三个数字输入框
 * @param {string} titleText 属性名称
 */
function createThreeNumberInputObject(parent, comp, obj) {
    let propObj = Object.assign(getPropertiesObj(obj), {
                                    "strTitle": qsTr(obj.titleText)
                                })
    var threeNumberInput = comp.createObject(parent, propObj)
    if (threeNumberInput === null) {
        console.error("Error creating threeNumberInput")
    }
    return threeNumberInput
}


/**
 * @brief 下拉框
 * @param {string} title 属性名称
 */
function createComboboxObject(parent, comp, obj) {
    let propObj = Object.assign(getPropertiesObj(obj), {
                                    "strTitle": qsTr(obj.title)
                                })
    var combobox = comp.createObject(parent, propObj)
    if (combobox === null) {
        console.error("Error creating combobox")
    }
    return combobox
}

function createOptionObject(parent, comp, obj) {
    parent.model.append({
                           "show": obj.titleText,
                           "value": obj.prop
                        })
}

/**
 * @brief 文件拖拽框
 * @param {string} detailText 未拖拽文件时显示的内容
 */
function createDropFileObject(parent, comp, obj) {
    let propObj = Object.assign(getPropertiesObj(obj), {
                                    "detailText": qsTr(obj.detailText)
                                })
    var dropFile = comp.createObject(parent, propObj)
    if (dropFile === null) {
        console.error("Error creating dropFile")
    }
    return dropFile
}

//==================3d组件=====================


/**
 * @brief 贴图选择框
 */
function createTextureComboboxObject(parent, comp, obj) {
    let propObj = Object.assign(getPropertiesObj(obj), {
                                    "strTitle": qsTr(obj.titleText)
                                })
    var textureCombobox = comp.createObject(parent, propObj)
    if (textureCombobox === null) {
        console.error("Error creating textureCombobox")
    }
    return textureCombobox
}


/**
 * @brief 纯色/渐变颜色选择器
 */
function createTwoColorPickerObject(parent, comp, obj) {
    let propObj = Object.assign(getPropertiesObj(obj), {
                                    "strTitle": qsTr(obj.titleText)
                                })
    var twoColorPicker = comp.createObject(parent, propObj)
    if (twoColorPicker === null) {
        console.error("Error creating twoColorPicker")
    }
    return twoColorPicker
}
