import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQml.Models 2.2
import QtQuick.Layouts 1.1

import "qrc:/qml/components"

import MyCppComponents 1.0

Rectangle {
  id: root

  Item {
    id: internal

    readonly property var model : scene_model
  }

  Component {
    id: template

    Rectangle {

      color: "blue"

      Text{ text: "N/A"; anchors.centerIn: parent; color: "red"; font.bold: true }
    }
  }

  SplitView {
    anchors.fill: parent

    orientation: Qt.Vertical

    SceneView {
      id: scene_view
      selectionMode: SelectionMode.NoSelection

      Layout.fillHeight: true
      Layout.fillWidth: true

      model: internal.model

      onCurrentIndexChanged: {
        details.displayIndexData(currentIndex)
        model.selectSceneObject(currentIndex)
      }
    }

    TabView {
      id: details


      height: width
      Layout.minimumHeight: width
      Layout.fillWidth: true

      function displayIndexData(index) {

//        console.debug( "-----------------------------------------------------")
//        console.debug( "Display Index Data" )
//        console.debug( "Model: " + model )
//        console.debug( "DisplayIndexData: " + index )

        var i;
        var prev_tab_index = currentIndex

        // Remove all tabs down to the scene tab
        for( i = count-1; i >= 0; --i ) {
          removeTab(i)
        }

        // Add one tab for each <known> module
        var modules = internal.model.getPropertyModules(index);
//        console.debug("Modules: " + modules )
        for( i = 0; i < modules.length; ++i ) {
//          console.debug("  : " + modules[i])

          var module = modules[i]

          // GMlib modules
          if(module === SceneProxyModel.SceneObject)      setupSceneObjectTab(addTab("SO"),index)
          else if(module === SceneProxyModel.Camera)      addTab("C",         template)
          else if(module === SceneProxyModel.Light)       setupLightTab(      addTab("Light"),index)
          else if(module === SceneProxyModel.PointLight)  setupPointLightTab( addTab("PointLight"),index)
          else if(module === SceneProxyModel.PSurf )      addTab("PSurf",     template)
          else if(module === SceneProxyModel.PERBSSurf )  addTab("PERBSSurf", template)
          else if(module === SceneProxyModel.PTorus )     addTab("PTorus",    template)

          // My custom modules
          else if(module === MySceneProxyModel.TestTorus) addTab("TestTorus", template)

          // I have no Idea modules
          else                                            addTab("X",         template)

        }

        if( prev_tab_index < count ) currentIndex = prev_tab_index
        else                         currentIndex = 0



      }


//          Tab {
//            title: "Scene"

//            Component.onCompleted: {
//              setSource("qrc:/qml/components/SceneDetailsTab.qml", {"model" : scene_model} )
//            }

//          }
    }

  }

  function setupSceneObjectTab(tab,index) {

    tab.setSource("qrc:/qml/components/SceneObjectDetailsTab.qml", {"model" : internal.model, "index": index} )
  }

  function setupLightTab(tab,index) {

    tab.setSource("qrc:/qml/components/LightDetailsTab.qml", {"model" : internal.model, "index": index} )
  }

  function setupPointLightTab(tab,index) {

    tab.setSource("qrc:/qml/components/PointLightDetailsTab.qml", {"model" : internal.model, "index": index} )
  }
}




















