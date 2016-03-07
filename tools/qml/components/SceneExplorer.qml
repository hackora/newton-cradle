import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Rectangle {
  id: root

  opacity: 0.7
  border.color: "black"
  border.width: 5
  radius: 10

  TreeView {
    anchors.fill: parent
    anchors.margins: 10

    model: scene_model

    TableViewColumn {
      role: 'identity'
      title: "Identity"
    }

    TableViewColumn {
      role: 'name'
      title: "Name"
    }

    TableViewColumn {
      role: 'pointer'
      title: "0x"
    }

    TableViewColumn{
      role: 'visible'
      title: "Visible"
//      delegate: Button {
//        text: visible === true ? "V" : "I"
//      }
    }
  }
}
