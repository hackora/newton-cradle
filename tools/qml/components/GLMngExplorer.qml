import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQml.Models 2.2
import QtQuick.Layouts 1.1

import "qrc:/qml/components"

import MyCppComponents 1.0

Rectangle {
  id: root

  opacity: 0.7
  border.color: "black"
  border.width: 5
  radius: 10

  SplitView {
    id: splitview
    anchors.fill: parent
    orientation: Qt.Vertical

    GLMngView {
      id: glmng_view
      selectionMode: SelectionMode.NoSelection

      Layout.fillHeight: true
      Layout.fillWidth: true

      model: glmng_model

      onCurrentIndexChanged: {
        details.displayIndexData(currentIndex)
      }
    }


    Rectangle {
      id: details

      height: width
      Layout.minimumHeight: width
      Layout.fillWidth: true

      TextureRenderer {
        id: tex_renderer
        opacity: 1.0

        anchors.fill: parent

      }


      function displayIndexData(index) {

        var obj_type = glmng_model.getGLObjectType(index)
        console.debug("qmi type: " + obj_type );

        if(obj_type !== 5) return;

        var tex_id = glmng_model.getProperty(index,"texture_id");
        tex_renderer.setTextureId(tex_id)

      }

//      ListView {
//        anchors.fill: parent
//          id: view
////          width: 300
////          height: 400

//          model: DelegateModel {
//              model:glmng_model

//              delegate: Rectangle {
//                  width: 200; height: 25
//                  Text { text: display_name}

//                  MouseArea {
//                      anchors.fill: parent
//                      onClicked: {
//                          if (model.hasModelChildren)
//                              view.model.rootIndex = view.model.modelIndex(index)
//                      }
//                  }
//              }
//          }
//      }

//      ListView {
//        id: globj_view
//        anchors.fill: parent
//        model: DelegateModel {
//          model: glmng_model
//          delegate: Rectangle {
//            width: globj_view.width
//            height: globj_view.height
//              Text{ text: display_name}
//          }


////          onRootIndexChanged: console.debug("Root index changed: " + rootIndex + " - " + count)
//        }

//        clip: true
//        onCurrentIndexChanged: { contentY = currentItem.y }

//      }

    }
  }

}
