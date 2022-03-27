import QtQuick
import "qml"
import "qml/utilities"

Window {
  id: root

  width: 1200
  height: 900

  visible: true
  title: qsTr("Logger")

  Theme {
    id: theme
  }

  MainPage {
    id: mainPage

    anchors.fill: parent
  }
}
