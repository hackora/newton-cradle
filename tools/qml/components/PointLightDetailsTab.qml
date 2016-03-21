import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

import "qrc:/qml/components"

import MyCppComponents 1.0

Item {
  id: root

  property var model
  property var index

  ColumnLayout {
    Item{Layout.fillHeight: true}
  }

}
