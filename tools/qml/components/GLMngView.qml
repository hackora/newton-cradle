import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

TreeView {
  id: tree_view

  anchors.margins: 10
//  backgroundVisible: false

  TableViewColumn {
    role: 'display_name'
    title: "Name"

    resizable: false
    movable: false

    width: tree_view.viewport.width - visible_column.width
  }

  TableViewColumn{
    id: visible_column
    role: 'icon'
    title: "Icon"
    resizable: false
    movable: false
    width: 65
  }
}
