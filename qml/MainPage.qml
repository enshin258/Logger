import QtQuick
import QtQuick.Controls
import Qt.labs.platform
import "panels"

Item {
  id: root

  Rectangle {
    id: background

    anchors.fill: parent

    color: theme.backgroundLightColor

    LogsPanel {
      id: logsPanel

      anchors {
        top: parent.top
        left: parent.left
        right: parent.right
        bottom: panelsItem.top
        margins: 20
      }
    }

    Column {
      id: panelsItem

      anchors {
        left: parent.left
        right: parent.right
        bottom: parent.bottom
        margins: 20
      }

      height: 400
      spacing: 20

      SearchingAndFilteringPanel {
        id: searchingAndFilteringPanel

        width: parent.width
        height: 80
      }

      ExecutablePanel {
        id: executablePanel

        width: parent.width
        height: 80
      }

      FilePanel {
        id: filePanel

        width: parent.width
        height: 80
      }

      NetworkPanel {
        id: networkPanel

        width: parent.width
        height: 80
      }
    }
  }
}
