import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQml.Models 2.2
import QtQuick.Layouts 1.1

Item {
  id: root
  property var index
  property var model
  property string title

  height: root_layout.implicitHeight

  Item {
    id: txt
    property string id : ""
    property string name : ""
    property string count : ""
    property string persistent : "Persistent"
    property string non_persistent : "C++ object bound"
    property bool   is_persistent : false
  }


  ColumnLayout {
    id: root_layout
    anchors.fill: parent
    Text{
      text: root.title
      Layout.fillWidth: true
      height: 30
    }

    Text{ text: "Id:   " + txt.id + (txt.name.length ? (" (" + txt.name + ")") : "" ) }
    Text{ text: "Instances: " + txt.count }
    Text{ text: txt.is_persistent ? txt.persistent : txt.non_persistent }
  }


  onIndexChanged: {

    if(root.index===undefined) return;

    txt.id            = root.model.getProperty(root.index,"id")
    txt.name          = root.model.getProperty(root.index,"name")
    txt.count         = root.model.getProperty(root.index,"count")
    txt.is_persistent = root.model.getProperty(root.index,"persistent")
  }
}
