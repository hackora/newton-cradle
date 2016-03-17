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

    TabView {
      id: tabs
      anchors.fill: parent

      Tab{
        title: "Info"
        id: info_tab

        Item {
          anchors.fill: parent

          GridLayout {
            anchors.fill: parent
            columns: 2

            Text{ text: "Identity:" }      Text{ id: info_identity }
            Text{ text: "Name:" }          Text{ id: info_name }
            Text{ text: "Virtual Name:" }  Text{ id: info_vname }
            Item{ Layout.fillHeight: true }
          }

          Component.onCompleted: {
            info_identity.text = model.getProperty(index,SceneProxyModel.SceneObject,"identity")
            info_name.text     = model.getProperty(index,SceneProxyModel.SceneObject,"name")
            info_vname.text    = model.getProperty(index,SceneProxyModel.SceneObject,"virtual_name")
          }
        }
      }

      Tab {
        title: "Properties"

        ScrollView {
          id: sw

          anchors.fill: parent
          horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

          ColumnLayout {
            ColorPicker{ id: color_picker; title: "Color"; Layout.fillWidth: true }
            MaterialPicker { id: material_picker; title: "Material"; Layout.fillWidth: true }
            Item {Layout.fillHeight: true; implicitWidth: content.width}
          }

          function updateColorOfSceneobject() {
             model.setProperty(index,SceneProxyModel.SceneObject,"color",color)
          }
          function updateMaterialOfSceneobject() {

            var material = model.getProperty(index,SceneProxyModel.SceneObject,"material")
            material.ambient   = material_picker.ambient
            material.diffuse   = material_picker.diffuse
            material.specular  = material_picker.specular
            material.shininess = material_picker.shininess
            model.setProperty(index,SceneProxyModel.SceneObject,"material",material)
          }

          Component.onCompleted: {
            color_picker.color    = model.getProperty(index,SceneProxyModel.SceneObject,"color").qcolor
            var material = model.getProperty(index,SceneProxyModel.SceneObject,"material")
            material_picker.ambient   = material.ambient;
            material_picker.diffuse   = material.diffuse;
            material_picker.specular  = material.specular;
            material_picker.shininess = material.shininess;

            color_picker.colorChanged.connect(updateColorOfSceneobject)
            material_picker.materialChanged.connect(updateMaterialOfSceneobject)
          }
        }

      }

      Tab { title: "Visualizers"
        ColumnLayout {
          anchors.fill: parent
          ComboBox { Layout.fillWidth: true; model: ["Visu1", "Visu2"]}
          Item{ Layout.fillHeight: true }
        }
      }
    }
  }

}
