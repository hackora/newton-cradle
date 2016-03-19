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
    ColorPicker{
      title: "Ambient"; Layout.fillWidth: true

      Component.onCompleted: {
        color = model.getProperty(index,SceneProxyModel.PointLight,"ambient").qcolor
        colorChanged.connect(updateAmbient)
      }

      function updateAmbient() { model.setProperty(index,SceneProxyModel.PointLight,"ambient",color) }
    }
    ColorPicker{
      title: "Diffuse"; Layout.fillWidth: true

      Component.onCompleted: {
        color = model.getProperty(index,SceneProxyModel.PointLight,"diffuse").qcolor
        colorChanged.connect(updateDiffuse)
      }

      function updateDiffuse() { model.setProperty(index,SceneProxyModel.PointLight,"diffuse",color) }
    }
    ColorPicker{
      title: "Specular"; Layout.fillWidth: true

      Component.onCompleted: {
        color = model.getProperty(index,SceneProxyModel.PointLight,"specular").qcolor
        colorChanged.connect(updateSpecular)
      }

      function updateSpecular() { model.setProperty(index,SceneProxyModel.PointLight,"specular",color) }
    }
    Item{Layout.fillHeight: true}
  }

}
