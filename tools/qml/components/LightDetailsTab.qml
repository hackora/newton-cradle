import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

import "qrc:/qml/components"

import MyCppComponents 1.0

Item {
  id: root

  property var model
  property var index

  ColumnLayout {
    anchors.fill: parent
    CheckBox{
      text: "Enabled"; Layout.fillWidth: true

      Component.onCompleted:  {
        checked = model.getProperty(index,SceneProxyModel.Light,"enabled");
        checkedChanged.connect(updateEnabled)
      }

      function updateEnabled() { model.setProperty(index,SceneProxyModel.Light,"enabled",checked) }
    }
    Rectangle {
      Layout.fillWidth: true
      height:1
      color: "black"
    }
    ColorPicker{
      title: "Ambient"; Layout.fillWidth: true

      Component.onCompleted: {
        color = model.getProperty(index,SceneProxyModel.Light,"ambient").qcolor
        colorChanged.connect(updateAmbient)
      }

      function updateAmbient() { model.setProperty(index,SceneProxyModel.Light,"ambient",color) }
    }
    ColorPicker{
      title: "Diffuse"; Layout.fillWidth: true

      Component.onCompleted: {
        color = model.getProperty(index,SceneProxyModel.Light,"diffuse").qcolor
        colorChanged.connect(updateDiffuse)
      }

      function updateDiffuse() { model.setProperty(index,SceneProxyModel.Light,"diffuse",color) }
    }
    ColorPicker{
      title: "Specular"; Layout.fillWidth: true

      Component.onCompleted: {
        color = model.getProperty(index,SceneProxyModel.Light,"specular").qcolor
        colorChanged.connect(updateSpecular)
      }

      function updateSpecular() { model.setProperty(index,SceneProxyModel.Light,"specular",color) }
    }
    Item{Layout.fillHeight: true}
  }

}
