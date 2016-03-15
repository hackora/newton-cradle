import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

import "qrc:/qml/components"

import MyCppComponents 1.0

Item {
  property var model
  property var index

  ScrollView {
    anchors.fill: parent

    ColumnLayout {

      GroupBox {
        Layout.fillWidth: true
        title: "Info"

        GridLayout {
          anchors.fill: parent
          columns: 2

          Text{ text: "Identity" }      Text{ id: txt_identity }
          Text{ text: "Name" }          Text{ id: txt_name }
          Text{ text: "Virtual Name" }  Text{ id: txt_vname }
        }
      }

      GroupBox {
        Layout.fillWidth: true
        title: "Color"

        ColorPicker{
          id: color_picker
          onColorChanged: model.setProperty(index,SceneProxyModel.SceneObject,"color",color)
        }
      }

      GroupBox {
        Layout.fillWidth: true
        title: "Color"

        ColorPicker{
          id: color_picker2
          onColorChanged: model.setProperty(index,SceneProxyModel.SceneObject,"color",color)
        }
      }

      GroupBox {
        Layout.fillWidth: true
        title: "Color"

        ColorPicker{
          id: color_picker3
          onColorChanged: model.setProperty(index,SceneProxyModel.SceneObject,"color",color)
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
