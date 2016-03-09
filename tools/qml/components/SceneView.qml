import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

TreeView {
  id: tree_view

  anchors.margins: 10
//  backgroundVisible: false

  TableViewColumn {
    role: 'so_identity'
    title: "Identity"

    resizable: false
    movable: false

    width: tree_view.viewport.width - (selected_column.width + visible_column.width)
  }

  TableViewColumn{
    id: selected_column
    role: 'so_selected'
    title: "Selected"

    resizable: false
    movable: false

    width: 50
  }

  TableViewColumn{
    id: visible_column
    role: 'so_visible'
    title: "Visible"
    resizable: false
    movable: false

    width: 50

    delegate: Button {
      id: visible_button
      iconSource: styleData.value === true ? "qrc:/tools/gfx/visible" : "qrc:/tools/gfx/invisible"
      style: ButtonStyle {
        background: Item{}
//                background: Rectangle {
//                    border.width: control.activeFocus ? 2 : 1
//                    border.color: "red"
//                    radius: 0
//                    gradient: Gradient {
//                        GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
//                        GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
//                    }
//                }
          }
    }
  }
}
