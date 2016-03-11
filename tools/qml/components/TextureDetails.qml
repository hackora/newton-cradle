import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQml.Models 2.2
import QtQuick.Layouts 1.1

import "qrc:/qml/components"

import MyCppComponents 1.0

Item {
  id: root
  property var index
  property var model

  Item {
    id: txt
    property string trgt : ""
  }

  ColumnLayout {
    anchors.fill: parent

    DetailsHeader {
      Layout.fillWidth: true
      title: "Texture object"
      index : root.index
      model : root.model
    }

    Item {
      id: tex_item
      Layout.fillWidth: true
      Layout.fillHeight: true

      TextureRenderer {
        id: tex_renderer
        beforeRendering: false
        anchors.fill: parent

        MouseArea {
          focus:true
          anchors.fill: parent
          onClicked: tex_item.state = "info"
        }
      }

      Rectangle {
        id: tex_info
        anchors.fill: parent
        visible:false

        MouseArea {
          focus:true
          anchors.fill: parent
          onClicked: tex_item.state = ""
        }

        ColumnLayout {
          anchors.fill: parent
          Text{ text: "Target: " + txt.trgt }
          Item{ Layout.fillHeight: true}
        }
      }

      states: [
        State {
          name: "info"
          PropertyChanges { target: tex_renderer; visible: false }
          PropertyChanges { target: tex_info;     visible: true }
        }
      ]

    }
  }

  onIndexChanged: {
    tex_renderer.textureId  = root.model.getProperty(root.index,"id")
    txt.trgt                = root.model.getProperty(root.index,"target")
  }
}
