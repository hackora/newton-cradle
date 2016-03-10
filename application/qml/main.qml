import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4

import "qrc:/qml/components"

import MyCppComponents 1.0


Item {
  id: root

  ListModel {
    id: contactModel

      ListElement {
          name: "Bill Smith"
          number: "555 3264"
      }
      ListElement {
          name: "John Brown"
          number: "555 8426"
      }
      ListElement {
          name: "Sam Wise"
          number: "555 0473"
      }
  }

  signal toggleHidBindView

  onToggleHidBindView: hid_bind_view.toggle()

  RowLayout {
    anchors.fill: parent

    SceneExplorer {
      id: scene_explorer

      Layout.fillHeight: true
      width: 400

      anchors.margins: 50
      visible:false

    }

    GLMngExplorer {
      id: glmng_explorer

      Layout.fillHeight: true
      width: 400

      anchors.margins: 50
      visible:false
    }

    RCPairRenderer{
      id: renderer

      Layout.fillHeight: true
      Layout.fillWidth: true


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

        onClicked: root.toggleState("hid_bind_view")
      }

      Button {
        id: scene_explorer_button
        text: "X"
        anchors.top: parent.top
        anchors.right: hid_bind_view_button.left
        anchors.margins: 5

        width: height
        opacity: 0.7

        onClicked: root.toggleState("scene_explorer")
      }

      Button {
        text: "Y"
        anchors.top: parent.top
        anchors.right: scene_explorer_button.left
        anchors.margins: 5

        width: height
        opacity: 0.7

        onClicked: root.toggleState("glmng_explorer")
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

      }


  //    TextureViewer {

  //      width:  256
  //      height: 144

  //      anchors.right:  parent.right
  //      anchors.bottom: parent.bottom
  //    }

    }

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
    },
    State{
      name: "glmng_explorer"
      PropertyChanges {
        target: glmng_explorer
        visible: true
      }
    }
  ]

}

