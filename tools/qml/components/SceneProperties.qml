import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import QtQuick.Layouts 1.1

Item {

  ColumnLayout {
    anchors.fill: parent

    GridLayout {
      Layout.fillWidth: true
      columns: 2

      Text{ text: "Running: "     }     Text{ text: "Does it look like I care..." }
    }

    Item{
      Layout.fillHeight: true
    }

  }

  Component.onCompleted: {

  }
}
