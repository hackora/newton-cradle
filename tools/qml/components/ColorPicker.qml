import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

RowLayout {
  id: root

  Item {
    id: priv

    function updateColor() {

      root.color.r = r_slider.value
      root.color.g = g_slider.value
      root.color.b = b_slider.value
      root.color.a = a_slider.value

      updatePreviews()
    }

    function updateSliders() {

      r_slider.value = root.color.r
      g_slider.value = root.color.g
      b_slider.value = root.color.b
      a_slider.value = root.color.a
    }

    function updatePreviews() {

      r_preview.color.r = root.color.r
      g_preview.color.g = root.color.g
      b_preview.color.b = root.color.b
      a_preview.color.a = root.color.a
    }

    function init() {

      updateSliders()
      updatePreviews()

    }
  }

  property color color : "#FFFF0000"  // ARGB
  property alias previewVisible : preview.visible
  property bool  alphaVisible: true

  signal setColor( color c )

  onSetColor: {

    root.color = c
    priv.updatePreviews()
  }



  GridLayout {
    id: gl
    columns: 3
    flow: GridLayout.LeftToRight

    Text{ id: r_text; text: "R" }
    Slider { id: r_slider; minimumValue: 0; maximumValue: 1; stepSize: 0.01; value: 1 }
    Rectangle { id: r_preview; width: height*2; height: r_text.height; border { width: 1; color: "black" } radius: 2; color: "#F00" }


    Text{ id: g_text; text: "G" }
    Slider { id: g_slider; minimumValue: 0; maximumValue: 1; stepSize: 0.01; value: 1 }
    Rectangle { id: g_preview; width: height*2; height: g_text.height; border { width: 1; color: "black" } radius: 2; color: "#0F0"  }


    Text{ id: b_text; text: "B" }
    Slider { id: b_slider; minimumValue: 0; maximumValue: 1; stepSize: 0.01; value: 1 }
    Rectangle { id: b_preview; width: height*2; height: b_text.height; border { width: 1; color: "black" } radius: 2; color: "#00F"  }


    Text{ id: a_text; visible: alphaVisible; text: "A" }
    Slider { id: a_slider; visible: alphaVisible; minimumValue: 0; maximumValue: 1; stepSize: 0.01; value: 1 }
    Rectangle { id: a_preview; visible: alphaVisible; width: height*2; height: a_text.height; border { width: 1; color: "black" } radius: 2; color: "#FFF"  }
  }

  Rectangle {
    id: preview
    width: height
    height: gl.height
    color: root.color

    border { width: 1; color: "black" } radius: 2
  }

  Component.onCompleted: {

    priv.init()

    r_slider.onValueChanged.connect(priv.updateColor)
    g_slider.onValueChanged.connect(priv.updateColor)
    b_slider.onValueChanged.connect(priv.updateColor)
    a_slider.onValueChanged.connect(priv.updateColor)
  }
}
