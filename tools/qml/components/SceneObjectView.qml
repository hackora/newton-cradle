import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQml.Models 2.2
import QtQuick.Layouts 1.1

import "qrc:/qml/components"

Rectangle {
  id: root
  property alias model : sceneobject_delegatmodel.model
  property alias rootIndex : sceneobject_delegatmodel.rootIndex


  Rectangle {
    anchors.fill: parent
    anchors.margins: 10

    color: "red"


    ColumnLayout {
      anchors.fill: parent
      anchors.margins: 10

      Repeater {
        id: rep
        model: sceneobject_delegatmodel

        Rectangle {
          Layout.fillWidth: true
          implicitHeight: 30

          color: "green"
        }

        onModelChanged: console.debug("repeater: model changed: " + model + ",  so_dm: " + sceneobject_delegatmodel )
      }

    }
  }

  DelegateModel {
    id: sceneobject_delegatmodel

    onRootIndexChanged: console.debug("rootIndexChanged (items: " + count + "); " + rootIndex + ", repeater count: " + rep.count)
  }



}
