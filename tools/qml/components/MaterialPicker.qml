import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

Item {
  id: root
  implicitHeight: rect.implicitHeight
  implicitWidth: rect.implicitWidth

  property alias ambient   : ambient_color_picker.color
  property alias diffuse   : diffuse_color_picker.color
  property color specular  : specular_color_picker.color
  property real  shininess : shininess_slider.value
//  property alias previewVisible : preview.visible
//  property bool  alphaVisible: true
  property string title : ""
  readonly property int left_pad : 10


  Rectangle {
    id: rect
    anchors.fill: parent
    implicitWidth: cl.implicitWidth
    implicitHeight: cl.implicitHeight

    ColumnLayout {
      id: cl
      anchors.fill: parent

      Item {
        Layout.fillWidth: true
        height: 20

        RowLayout {
          anchors.fill: parent
          Text { id: title_text; anchors.fill: parent; text: root.title; font.bold: true }
          Item{ Layout.fillWidth: true }
          Rectangle { id: simple_preview;  width: 60; height: title_text.height; border { width: 1; color: "black" } radius: 2; color: root.diffuse;}
        }

        MouseArea {
          anchors.fill: parent
          onClicked: root.state = root.state === "" ? "details" : ""
        }
      }

      GridLayout {
        id: rl
        visible: false


        Layout.fillWidth: true
        flow: GridLayout.LeftToRight
        columns: 4


        Item{ width: left_pad } ColorPicker {id: ambient_color_picker;  title: "Ambient";  Layout.fillWidth: true; Layout.columnSpan: 3 }
        Item{ width: left_pad } ColorPicker {id: diffuse_color_picker;  title: "Diffuse";  Layout.fillWidth: true; Layout.columnSpan: 3 }
        Item{ width: left_pad } ColorPicker {id: specular_color_picker; title: "Specular"; Layout.fillWidth: true; Layout.columnSpan: 3 }
        Item{ width: left_pad } Text{text:"Shininess"; font.bold: true} Item{Layout.fillWidth: true} Slider{id: shininess_slider; width: 20}
      }

//      ColumnLayout {
//        id: rl
//        visible: false
//        Layout.fillWidth: true

//        ColorPicker {id: ambient_color_picker;  title: "Ambient";  Layout.fillWidth: true }
//        ColorPicker {id: diffuse_color_picker;  title: "Diffuse";  Layout.fillWidth: true }
//        ColorPicker {id: specular_color_picker; title: "Specular"; Layout.fillWidth: true }
//        RowLayout{ Text{text:"Shininess"; font.bold: true} Item{Layout.fillWidth: true} Slider{id: shininess_slider; width: 20} }
//      }
    }
  }




  states: [
    State {
      name: "details"
      PropertyChanges { target: simple_preview; visible: false }
      PropertyChanges { target: rl; visible: true }
    }
  ]

}