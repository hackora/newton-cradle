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

    Item {
      id: shader_item
      Layout.fillWidth: true
      Layout.fillHeight: true
//      border.color: "black"
//      border.width: 3

      ColumnLayout {
        anchors.fill: parent

        RowLayout {

          Layout.fillWidth: true

          height: 20

          Item { Layout.fillWidth: true}
          Button{ text: "Build"}
          Button{ text: "+"; implicitWidth: height; onClicked: source.font.pointSize = source.font.pointSize+1}
          Button{ text: "-"; implicitWidth: height; onClicked: source.font.pointSize = source.font.pointSize-1}
          Item { width: 5 }

        }

        ScrollView {
          Layout.fillWidth: true
          Layout.fillHeight: true

          TextEdit {
            id: source
  //          readOnly: true
            font.family: "Mono"
            font.pointSize: 9

            textMargin: 10

            GLSLSyntaxHighlighter {
              id: highlighter
            }

          }
        }
      }
    }
  }

  onIndexChanged: {
    source.text = root.model.getProperty(root.index, "source")
    highlighter.setQuickTextDocument(source.textDocument);
  }
}
