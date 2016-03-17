import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

Item {
  id: root
  implicitHeight: cl.implicitHeight
  implicitWidth:  cl.implicitWidth
//  implicitHeight: dl.visible ? cl.implicitHeight + dl.implicitHeight : cl.implicitHeight
//  implicitWidth:  dl.visible ? Math.max(cl.implicitWidth,dl.implicitWidth) : cl.implicitWidth

  property alias ambient   : ambient_color_picker.color
  property alias diffuse   : diffuse_color_picker.color
  property alias specular  : specular_color_picker.color
  property alias shininess : shininess_slider.value
  property string title : ""
  readonly property int left_pad : 5

  signal materialChanged

  ColumnLayout {
    id: cl
    anchors.fill: parent

    Item {
      Layout.preferredWidth:  height
      Layout.preferredHeight: height
      Layout.minimumWidth:    rl.implicitWidth
      Layout.minimumHeight:   rl.implicitHeight
      Layout.fillWidth: true

      height: 20

      RowLayout {
        id: rl
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
      id: dl
      visible: false

      Layout.fillWidth: true
      flow: GridLayout.LeftToRight
      columns: 4

      Item{ width: left_pad } ColorPicker {id: ambient_color_picker;  title: "Ambient";  Layout.fillWidth: true; Layout.columnSpan: 3 }
      Item{ width: left_pad } ColorPicker {id: diffuse_color_picker;  title: "Diffuse";  Layout.fillWidth: true; Layout.columnSpan: 3 }
      Item{ width: left_pad } ColorPicker {id: specular_color_picker; title: "Specular"; Layout.fillWidth: true; Layout.columnSpan: 3 }
      Item{ width: left_pad } Text{text:"Shininess"; font.bold: true} Item{Layout.fillWidth: true} Slider{id: shininess_slider; width: 20}
    }
  }




  states: [
    State {
      name: "details"
      PropertyChanges { target: simple_preview; visible: false }
      PropertyChanges { target: dl; visible: true }
    }
  ]

  onAmbientChanged:   materialChanged()
  onDiffuseChanged:   materialChanged()
  onSpecularChanged:  materialChanged()
  onShininessChanged: materialChanged()
}
