import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import QtQuick.Layouts 1.1

Rectangle {

  TabView {
    anchors.fill: parent

    Tab {
      title: "RCPairs"

      ColumnLayout {
        anchors.fill: parent

        ComboBox {
          id: rcpairs
          Layout.fillWidth: true

          Component.onCompleted: {

            model = gmlibwrapper.getRCPairNamesList();
            clear_color.color = gmlibwrapper.getRCPairProperty(currentText,"clear_color")
          }

          onCurrentIndexChanged: {

            if(currentIndex === undefined ) return;
            if(!currentText.length) return;

            clear_color.color = gmlibwrapper.getRCPairProperty(currentText,"clear_color")
          }
        }

        ColorPicker{
          id: clear_color;
          title: "Clear color"
          Layout.fillWidth: true
          onColorChanged: gmlibwrapper.setRCPairProperty(rcpairs.currentText,"clear_color",color)
        }

        Item { Layout.fillHeight: true }
      }
    }

  }
}
