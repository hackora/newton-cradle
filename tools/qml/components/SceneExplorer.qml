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
      title: "Name"
      role: "name"
    }

    TableViewColumn {
      title: "Identity"
      role: "identity"
    }

    TableViewColumn {
      title: "0x"
      role: "pointer"
    }

  }
}
