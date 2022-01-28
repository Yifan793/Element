import QtQuick 2.5
import FMCQmlPlugin 1.0 as Plugin
import "./"
import "./createComponent.js" as ComponentCreator
import "./createTree.js" as TreeCreator

Rectangle {
    id: root
    color: "#1F2021"
    width: 352
    property var elements: ({})
    property var tree: TreeCreator.tree

    Component.onCompleted: {
        let settingObj = mainWidget.getSettingObj()
        tree.add(root, "Root", tree.traverseBF)
        loadComponent(root, settingObj)
//        tree.forEach(node => {
//                         console.log("node: ", node.data, " prop ", node.data.prop)
//                     }, tree._root)
    }

    Components {
        id: components
    }

    function loadComponent(parent, obj) {
        if (obj.type === "script") {
            ComponentCreator.loadJsFile("qrc:/xml/" + obj.src)
            return
        }
        let comp = components.allComponent[obj.type]
        let func = ComponentCreator.createComponentObjFunc[obj.type]
        let compObj = func(parent, comp, obj)
        if (obj.tag) {
            elements[obj.tag] = compObj
        }
        tree.add(compObj, parent, tree.traverseBF)
        if (obj.children !== undefined) {
            for (var i = 0, length = obj.children.length; i < length; i++) {
                let childObj = obj.children[i]
                loadComponent(compObj, childObj)
            }
        }
    }
}
