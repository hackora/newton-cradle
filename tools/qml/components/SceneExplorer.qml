import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQml.Models 2.2
import QtQuick.Layouts 1.1

import "qrc:/qml/components"

import MyCppComponents 1.0

Rectangle {
  id: root

  Component {
    id: template

    Rectangle {

      color: "blue"

      Text{ text: "N/A"; anchors.centerIn: parent; color: "red"; font.bold: true }
    }
  }

  SplitView {

    anchors.fill: parent

    SceneView {
      id: scene_view
      selectionMode: SelectionMode.NoSelection

      Layout.fillHeight: true
      Layout.fillWidth: true

      model: scene_model

      onCurrentIndexChanged: details.displayIndexData(currentIndex)
    }

    TabView {
      id: details


      height: width
      Layout.minimumHeight: width
      Layout.fillWidth: true

      property var model : scene_model

      function displayIndexData(index) {

//        console.debug( "-----------------------------------------------------")
//        console.debug( "Display Index Data" )
//        console.debug( "Model: " + model )
//        console.debug( "DisplayIndexData: " + index )

        var i;
        var prev_tab_index = currentIndex

        // Remove all tabs down to the scene tab
        for( i = count-1; i >= 1; --i ) {
          removeTab(i)
        }

        // Add one tab for each <known> module
        var modules = model.getPropertyModules(index);
//        console.debug("Modules: " + modules )
        for( i = 0; i < modules.length; ++i ) {
//          console.debug("  : " + modules[i])

          var module = modules[i]

          // GMlib modules
          if(module === SceneProxyModel.SceneObject)      setupSceneObjectTab(addTab("SO"),index)
          else if(module === SceneProxyModel.Camera)      addTab("C",         template)
          else if(module === SceneProxyModel.PSurf )      addTab("PSurf",     template)
          else if(module === SceneProxyModel.PERBSSurf )  addTab("PERBSSurf", template)
          else if(module === SceneProxyModel.PTorus )     addTab("PTorus",    template)

          // My custom modules
          else if(module === MySceneProxyModel.TestTorus) addTab("TestTorus", template)

          // I have no Idea modules
          else                                            addTab("X",         template)

        }

        if( prev_tab_index < count ) currentIndex = prev_tab_index
        else                         currentIndex = 1



      }


      Tab {
        title: "Scene"

        ColumnLayout {

          GridLayout {
            Layout.fillWidth: true
            columns: 2

            Text{ text: "Running: "     }     Text{ text: "Does it look like I care..." }
          }

          Item{
            Layout.fillHeight: true
          }
        }
      }
    }

  }

  function setupSceneObjectTab(tab,index) {

    tab.setSource("qrc:/qml/components/SceneObjectDetailsTab.qml", {"model" : scene_model, "index": index} )
  }
}




















