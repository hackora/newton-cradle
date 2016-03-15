import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

import "qrc:/qml/components"

import MyCppComponents 1.0

Item {
  id: root

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

            Text{ text: "Identity:" }      Text{ id: info_identity }
            Text{ text: "Name:" }          Text{ id: info_name }
            Text{ text: "Virtual Name:" }  Text{ id: info_vname }
            Text{ text: "Lighted:" }       CheckBox{ id: info_lighted }
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

        GroupBox {
          title: "Material"
          implicitWidth: content.width

          ColumnLayout {
            anchors.fill: parent

            GroupBox { title: "Ambient";    ColorPicker{ id: mat_amb; onColorChanged: root.updateMaterialOfSceneObject() } }
            GroupBox { title: "Diffuse";    ColorPicker{ id: mat_dif; onColorChanged: root.updateMaterialOfSceneObject() } }
            GroupBox { title: "Specular";   ColorPicker{ id: mat_spc; onColorChanged: root.updateMaterialOfSceneObject() } }
            GroupBox { title: "Shininess";  Slider{ id: mat_shininess; minimumValue: 0; maximumValue: 128; stepSize: 0.1; onValueChanged: root.updateMaterialOfSceneObject() } }
          }


        }
      }
    }
  }


  function updateMaterialOfSceneObject() {

    var material = model.getProperty(index,SceneProxyModel.SceneObject,"material")
    material.diffuse   = mat_dif.color
    material.ambient   = mat_amb.color
    material.specular  = mat_spc.color
    material.shininess = mat_shininess.value
    model.setProperty(index,SceneProxyModel.SceneObject,"material",material)

  }


  Component.onCompleted: {

    // do your stuff
    info_identity.text    = model.getProperty(index,SceneProxyModel.SceneObject,"identity")
    info_name.text        = model.getProperty(index,SceneProxyModel.SceneObject,"name")
    info_vname.text       = model.getProperty(index,SceneProxyModel.SceneObject,"virtual_name")
    info_lighted.checked  = model.getProperty(index,SceneProxyModel.SceneObject,"lighted")

    color_picker.color    = model.getProperty(index,SceneProxyModel.SceneObject,"color").qcolor

    var material = model.getProperty(index,SceneProxyModel.SceneObject,"material")
    mat_dif.color = material.diffuse;
    mat_amb.color = material.ambient;
    mat_spc.color = material.specular;
    mat_shininess.value = material.shininess;

  }
}
