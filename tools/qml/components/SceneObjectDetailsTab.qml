import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

import "qrc:/qml/components"

import MyCppComponents 1.0

Item {
  property var model
  property var index

  Item {
    id: content
    anchors.fill: parent

    ScrollView {
      anchors.fill: parent
      horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

      ColumnLayout {

        GroupBox {
          title: "Info"
          implicitWidth: content.width

          GridLayout {
            anchors.fill: parent
            columns: 2

            Text{ text: "Identity" }      Text{ id: txt_identity }
            Text{ text: "Name" }          Text{ id: txt_name }
            Text{ text: "Virtual Name" }  Text{ id: txt_vname }
          }
        }

        GroupBox {
          title: "Color"
          implicitWidth: content.width

          ColorPicker{
            id: color_picker
            onColorChanged: model.setProperty(index,SceneProxyModel.SceneObject,"color",color)
          }
        }
      }
    }
  }


  Component.onCompleted: {

    // do your stuff
    txt_identity.text  = model.getProperty(index,SceneProxyModel.SceneObject,"identity")
    txt_name.text      = model.getProperty(index,SceneProxyModel.SceneObject,"name")
    txt_vname.text     = model.getProperty(index,SceneProxyModel.SceneObject,"virtual_name")
    color_picker.color = model.getProperty(index,SceneProxyModel.SceneObject,"color")
  }
}
