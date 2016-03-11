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
  }

  ColumnLayout {
    anchors.fill: parent

    DetailsHeader {
      Layout.fillWidth: true
      title: "Shader object"
      index : root.index
      model : root.model
    }

    Rectangle {
      id: shader_item
      Layout.fillWidth: true
      Layout.fillHeight: true
      border.color: "black"
      border.width: 3

      TextEdit {
        id: source
        anchors.fill: parent
        readOnly: true
        font.family: "Mono"
      }
    }
  }

  onIndexChanged: {
    source.text = root.model.getProperty(root.index, "source")
  }
}
