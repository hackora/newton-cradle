import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import QtQuick.Layouts 1.1

Rectangle {
  id: root
  property string active_rcpair : ""

  TabView {
    anchors.fill: parent

    Tab {
      title: "Active RCPair"

      ColumnLayout {
        anchors.fill: parent

        ColorPicker{
          id: clear_color;
          title: "Clear color"
          Layout.fillWidth: true
          onColorChanged: gmlibwrapper.setRCPairProperty(root.active_rcpair,"clear_color",color)

          signal fetchActiveRcPairProperties()

          onFetchActiveRcPairProperties: {

            if(!root.active_rcpair.length) return;
            clear_color.color = gmlibwrapper.getRCPairProperty(root.active_rcpair,"clear_color")
          }

          Component.onCompleted: {
            if(root.active_rcpair.length) clear_color.color = gmlibwrapper.getRCPairProperty(root.active_rcpair,"clear_color")

            root.active_rcpairChanged.connect(fetchActiveRcPairProperties)
          }
        }

        Item { Layout.fillHeight: true }
      }
    }
  }
}
