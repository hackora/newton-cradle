import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQml.Models 2.2
import QtQuick.Layouts 1.1

import "qrc:/qml/components"

import MyCppComponents 1.0

Rectangle {
  id: root

  SplitView {
    id: splitview
    anchors.fill: parent
    orientation: Qt.Vertical

    GLMngView {
      id: glmng_view
      selectionMode: SelectionMode.NoSelection

      Layout.fillHeight: true
      Layout.fillWidth: true

      model: glmng_model

      onCurrentIndexChanged: {
        details.displayIndexData(currentIndex)
      }
    }


    Rectangle {
      id: details
      height: width
      Layout.minimumHeight: width
      Layout.fillWidth: true

      function displayIndexData(index) {

        var obj_type = glmng_model.getGLObjectType(index)
        var enum_tex = GMOpenGLProxyModel.Texture;
        var obj_type_eq_enum_tex = obj_type === enum_tex;

        switch(obj_type) {
          case GMOpenGLProxyModel.Shader:
            details.state = "shader"
            shader_details.index = index
            break
          case GMOpenGLProxyModel.Texture:
            details.state = "texture"
            texture_details.index = index
            break
          default:
            details.state = ""
        }
      }

      ShaderDetails {
        id: shader_details
        anchors.fill: parent
        model: glmng_model
        visible: false
      }

      TextureDetails {
        id: texture_details
        anchors.fill: parent
        model: glmng_model
        visible: false
      }

      states: [
        State{
          name: "shader"
          PropertyChanges { target: shader_details;          visible: true }
        },
        State{
          name: "texture"
          PropertyChanges { target: texture_details;          visible: true }
        }
      ]

    }
  }

}
