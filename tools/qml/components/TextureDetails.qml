import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQml.Models 2.2
import QtQuick.Layouts 1.1

import "qrc:/qml/components"

import MyCppComponents 1.0

Item {
  id: root
  property var index
  property var model

  Item {
    id: txt
    property string trgt : ""
    property int    tex_width : 0
    property int    tex_height : 0
  }

  ColumnLayout {
    anchors.fill: parent

    DetailsHeader {
      Layout.fillWidth: true
      title: "Texture object"
      index : root.index
      model : root.model
    }
    RowLayout {
      Layout.fillWidth: true
      Text { text: "Color magnification" }
      Item{ Layout.fillWidth: true }
      ComboBox {
        width: 72
        model: [1,10,100,1000];
        onCurrentTextChanged: tex_renderer.setColorMagnification(currentText)
      }
    }

    Item {
      id: tex_item
      Layout.fillWidth: true
      Layout.fillHeight: true

      MouseArea {
        focus:true
        anchors.fill: parent
        onClicked: tex_item.state = tex_item.state === "" ? "info" : ""
        z: 1
      }

      Rectangle {
        id: tex_renderer_frame
        anchors.centerIn: parent
        width: Math.min(parent.width,parent.height)
        height: width
        border.width: 2
        border.color: "black"
        radius: 4
        color: "transparent"

        TextureRenderer {
          id: tex_renderer
          beforeRendering: false
          anchors.fill: parent
          anchors.margins: parent.border.width

        }
      }

      Rectangle {
        id: tex_info
        anchors.fill: parent
        visible:false

        ColumnLayout {
          anchors.fill: parent
          Text{ text: "Target: " + txt.trgt }
          Text{ text: "Width:  " + txt.tex_width }
          Text{ text: "Height: " + txt.tex_height }
          Item{ Layout.fillHeight: true}
        }
      }

      states: [
        State {
          name: "info"
          PropertyChanges { target: tex_renderer; visible: false }
          PropertyChanges { target: tex_info;     visible: true }
        }
      ]

      onWidthChanged: root.updateTexRendererSize()
      onHeightChanged: root.updateTexRendererSize()
    }
  }

  onIndexChanged: {
    tex_renderer.textureId  = root.model.getProperty(root.index,"id")
    txt.trgt                = root.model.getProperty(root.index,"target")

    updateTexRendererSize()
  }

  function updateTexRendererSize() {

    var texture_width  = root.model.getProperty(index,"width")
    var texture_height = root.model.getProperty(index,"height")

    if(texture_width === undefined || texture_height === undefined) return

    txt.tex_width           = texture_width
    txt.tex_height          = texture_height

    // Get size of texture
    if(txt.tex_width === 0 || txt.tex_height === 0) return

    var aspect_tex  = txt.tex_width / txt.tex_height
    var aspect_item = tex_item.width / tex_item.height

    var tr_width, tr_height
    if( aspect_tex > aspect_item) {
      tr_width = tex_item.width
      tr_height = tr_width / aspect_tex
    }
    else {
      tr_height = tex_item.height
      tr_width  = tr_height * aspect_tex
    }

    tex_renderer_frame.width = tr_width
    tex_renderer_frame.height = tr_height
  }
}


































