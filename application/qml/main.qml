import QtQuick 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

import "qrc:/qml/components"

import MyCppComponents 1.0

Item {
  id: root

  signal toggleHidBindView

  onToggleHidBindView: hid_bind_view.toggle()

  RCPairRenderer{
    id: renderer

    anchors.fill: parent

    name: rc_pair_cb.currentText

    ComboBox {
      id: rc_pair_cb
      anchors.top: parent.top
      anchors.left: parent.left
      anchors.margins: 5

      width: 128

      opacity: 0.7

      model: rc_name_model
      textRole: "display"
    }

    Button {
      id: hid_bind_view_button
      text: "?"
      anchors.top: parent.top
      anchors.right: parent.right
      anchors.margins: 5

      width: height
      opacity: 0.7

      onClicked: views.toggleState("hid_bind_view")
    }

    Button {
      text: "X"
      anchors.top: parent.top
      anchors.right: hid_bind_view_button.left
      anchors.margins: 5

      width: height
      opacity: 0.7

      onClicked: views.toggleState("scene_explorer")
    }

    Item {
      id: views
      anchors.fill: parent

      HidBindingView {
        id: hid_bind_view
        anchors.fill: parent
        anchors.margins: 50
        visible:false
      }

      SceneExplorer {
        id: scene_explorer
        anchors.fill: parent
        anchors.margins: 50
        visible:false

        states: [
        ]
      }

      function toggleState(state_to_toggle) {

        if(state === state_to_toggle) state = ""
        else state = state_to_toggle

      }

      states: [
        State{
          name: "hid_bind_view"
          PropertyChanges {
            target: hid_bind_view
            visible: true
          }
        },
        State{
          name: "scene_explorer"
          PropertyChanges {
            target: scene_explorer
            visible: true
          }
        }
      ]
    }


//    TextureViewer {

//      width:  256
//      height: 144

//      anchors.right:  parent.right
//      anchors.bottom: parent.bottom
//    }

  }

}

