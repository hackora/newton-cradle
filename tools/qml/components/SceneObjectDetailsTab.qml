import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

import "qrc:/qml/components"

import MyCppComponents 1.0

Item {
  property var model
  property var index

  ColumnLayout {

    GridLayout {
      Layout.fillWidth: true
      columns: 2

      Text{ text: "Identity" }      Text{ id: txt_identity }
      Text{ text: "Name" }          Text{ id: txt_name }
      Text{ text: "Virtual Name" }  Text{ id: txt_vname }
      Text{ text: "Color" }         ColorPicker{ id: color_picker; onColorChanged: model.setProperty(index,SceneProxyModel.SceneObject,"color",color) }
    }
  }



  Component.onCompleted: {

    console.debug("SceneObjectDetailsTab")
    console.debug("  model: " + model)
    console.debug("  index: " + index)
    // do your stuff
    txt_identity.text  = model.getProperty(index,SceneProxyModel.SceneObject,"identity")
    txt_name.text      = model.getProperty(index,SceneProxyModel.SceneObject,"name")
    txt_vname.text     = model.getProperty(index,SceneProxyModel.SceneObject,"virtual_name")
    color_picker.color = model.getProperty(index,SceneProxyModel.SceneObject,"color")
  }
}
