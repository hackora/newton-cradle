import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

Item {
  id: root
  implicitHeight: cl.implicitHeight
  implicitWidth:  cl.implicitWidth
//  implicitHeight: dl.visible ? cl.implicitHeight + dl.implicitHeight : cl.implicitHeight
//  implicitWidth:  dl.visible ? Math.max(cl.implicitWidth,dl.implicitWidth) : cl.implicitWidth

  property color color : "#FFFF0000"  // ARGB
  property alias previewVisible : preview.visible
  property bool  alphaVisible: true
  property string title : ""
  readonly property int left_pad : 5

  onColorChanged: priv.updateControls()

  Item {
    id: priv

    function updateInternalRedComponent()   { root.color.r = r_slider.value }
    function updateInternalGreenComponent() { root.color.g = g_slider.value }
    function updateInternalBlueComponent()  { root.color.b = b_slider.value }
    function updateInternalAlphaComponent() { root.color.a = a_slider.value }

    function updateControls() {
      if(r_slider.value !== root.color.r) r_slider.value = root.color.r
      if(g_slider.value !== root.color.g) g_slider.value = root.color.g
      if(b_slider.value !== root.color.b) b_slider.value = root.color.b
      if(a_slider.value !== root.color.a) a_slider.value = root.color.a
    }
  }

  Component.onCompleted: {
    r_slider.valueChanged.connect(priv.updateInternalRedComponent)
    g_slider.valueChanged.connect(priv.updateInternalGreenComponent)
    b_slider.valueChanged.connect(priv.updateInternalBlueComponent)
    a_slider.valueChanged.connect(priv.updateInternalAlphaComponent)
  }



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
        Rectangle { id: simple_preview;  width: 60; height: title_text.height; border { width: 1; color: "black" } radius: 2; color: root.color;}
      }

      MouseArea {
        anchors.fill: parent
        onClicked: root.state = root.state === "" ? "details" : ""
      }
    }

    RowLayout {
      id: dl
      visible: false
      Layout.fillWidth: true

      GridLayout{
        id: gl
        columns: 4
        flow: GridLayout.LeftToRight
        Layout.fillWidth: true
        Layout.fillHeight: true

        Item{ width: left_pad }
        Text{ id: r_text; text: "R" }
        Slider { id: r_slider; minimumValue: 0; maximumValue: 1; stepSize: 0.01; value: 1; Layout.fillWidth: true}
        Rectangle { id: r_preview; width: height*2; height: r_text.height; border { width: 1; color: "black" } radius: 2; color: Qt.rgba(root.color.r,0,0,1)}

        Item{ width: left_pad }
        Text{ id: g_text; text: "G" }
        Slider { id: g_slider; minimumValue: 0; maximumValue: 1; stepSize: 0.01; value: 1; Layout.fillWidth: true}
        Rectangle { id: g_preview; width: height*2; height: g_text.height; border { width: 1; color: "black" } radius: 2; color: Qt.rgba(0,root.color.g,0,1)  }

        Item{ width: left_pad }
        Text{ id: b_text; text: "B" }
        Slider { id: b_slider; minimumValue: 0; maximumValue: 1; stepSize: 0.01; value: 1; Layout.fillWidth: true}
        Rectangle { id: b_preview; width: height*2; height: b_text.height; border { width: 1; color: "black" } radius: 2; color: Qt.rgba(0,0,root.color.b,1)  }

        Item{ width: left_pad }
        Text{ id: a_text; visible: alphaVisible; text: "A" }
        Slider { id: a_slider; visible: alphaVisible; minimumValue: 0; maximumValue: 1; stepSize: 0.01; value: 1; Layout.fillWidth: true}
        Rectangle { id: a_preview; visible: alphaVisible; width: height*2; height: a_text.height; border { width: 1; color: "black" } radius: 2; color: Qt.rgba(1,1,1,root.color.a)  }
      }

      Rectangle {
        id: preview
        implicitHeight: gl.height
        implicitWidth: implicitHeight
        color: root.color

        border { width: 1; color: "black" } radius: 2
      }
    }
  }



  states: [
    State {
      name: "details"
      PropertyChanges { target: simple_preview; visible: false }
      PropertyChanges { target: dl; visible: true }
    }
  ]
}
