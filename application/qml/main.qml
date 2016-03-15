import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4

import "qrc:/qml/components"

import MyCppComponents 1.0


Item {
  id: root

  signal toggleHidBindView


  SplitView {
    anchors.fill: parent

    Rectangle {
      id: tool_bar

      width: 300
      Layout.fillHeight: true
      Layout.minimumWidth: 200


      TabView {
        anchors.fill: parent

        Tab {
          title: "App"

          Component.onCompleted: {
            setSource("qrc:/qml/components/ApplicationProperties.qml" )
          }
        }

        Tab {
          title: "Scene"

          Component.onCompleted: {
            setSource("qrc:/qml/components/SceneProperties.qml" )
          }
        }

        Tab {
          title: "Explorer"

          Component.onCompleted: setSource( "qrc:/qml/components/SceneExplorer.qml" )
        }

        Tab {
          title: "OpenGL"
          Component.onCompleted: setSource( "qrc:/qml/components/GLMngExplorer.qml" )
        }

        Component.onCompleted: currentIndex = 2
      }
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
        id: tools_button
        text: "T"
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 5

        width: height
        opacity: 0.7

        onClicked: tool_bar.visible = !tool_bar.visible
      }

      Button {
        id: hid_bind_view_button
        text: "?"
        anchors.top: tools_button.bottom
        anchors.right: parent.right
        anchors.margins: 5

        width: height
        opacity: 0.7

        onClicked: hid_bind_view.visible = !hid_bind_view.visible
      }


      HidBindingView {
        id: hid_bind_view
        anchors.fill: parent
        anchors.margins: 50
        visible:false

        signal toggleVisible

        onToggleVisible: visible = !visible
      }
    }

  }

  Component.onCompleted: {
    root.toggleHidBindView.connect( hid_bind_view.toggleVisible )
  }

}

