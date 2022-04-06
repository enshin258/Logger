import QtQuick
import QtQuick.Controls
import Qt.labs.platform
import "panels"
import "elements"

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

    Popup {
      id: infoPopup

      property string infoText: ""

      width: 300
      height: 150

      dim: true

      anchors.centerIn: parent

      background: Rectangle {
        color: theme.backgroundColor
        border {
          width: 3
          color: theme.backgroundLightColor
        }

        radius: 30
      }

      contentItem: Item {
        AppText {
          id: message

          anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
            margins: 20
          }

          text: infoPopup.infoText
        }

        AppButton {
          id: closeButton

          anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
            margins: 20
          }

          text: "Close"

          background: Rectangle {
            color: theme.foregroundColor
          }

          width: 100
          height: 30

          onClicked: {
            infoPopup.close()
          }
        }
      }
    }
  }
}
