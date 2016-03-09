import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQml.Models 2.2
import QtQuick.Layouts 1.1

import "qrc:/qml/components"

Rectangle {
  id: root

  opacity: 0.7
  border.color: "black"
  border.width: 5
  radius: 10

  RowLayout {
    anchors.fill: parent
    anchors.margins: 10

    SceneView {
      id: scene_view
      selectionMode: SelectionMode.NoSelection

      Layout.fillHeight: true

      Layout.fillWidth: true
//      implicitWidth: Math.min( parent.width / 3, 300 )



      model: scene_model

//      onClicked: {
//        console.debug("current index changed: " +index)
//        object_view.currentIndex = index.parent
//      }

    }

//    SceneObjectView {
//      id: sceneobject_view
//      Layout.fillHeight: true
//      Layout.fillWidth: true

//      model: scene_model
//      rootIndex: scene_view.currentIndex

//    }

//    ColumnLayout {
//      Layout.fillWidth: true
//      Layout.fillHeight: true

//      Repeater {
//        id: rep
//        model: DelegateModel {
//          model: scene_model
//          rootIndex: scene_view.currentIndex

//          Rectangle{

//            Layout.fillWidth: true
//            implicitHeight: 30

//            color: "yellow"



//          }

//          onRootIndexChanged: console.debug("rootIndexChanged (items: " + count + "); " + rootIndex + ", repeater count: " + rep.count)
////          onRootIndexChanged: console.debug( "Root index: " + rootIndex + " has a count of:" + count )
//        }
//      }

//      Item { Layout.fillHeight: true }
//    }
  }

}
