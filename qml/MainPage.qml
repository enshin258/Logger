import QtQuick
import QtQuick.Controls
import Qt.labs.platform
import "panels"

Item {
  id: root

  Rectangle {
    id: background

    anchors.fill: parent

    color: theme.backgroundColor

    LogsPanel {
      id: logsPanel

      anchors {
        top: parent.top
        left: parent.left
        right: parent.right

        margins: 20
      }

      height: parent.height * 3/4
    }

    Button {
      id: chooseExeFileButton
      anchors {
        bottom: parent.bottom
        bottomMargin: 50
        right: parent.horizontalCenter
      }

      width: 100
      height: 100

      text: "choose .exe file"

      onClicked: {
        fileDialog.open()
      }
    }

    Button {
      id: startExeButton
      anchors {
        bottom: parent.bottom
        bottomMargin: 50
        left: parent.horizontalCenter
      }

      width: 100
      height: 100

      text: "start exe!"

      enabled: externalAppsController.externalAppPath !== ""

      opacity: enabled? 1 : 0.2

      onClicked: {
        externalAppsController.runExternalApp();
      }
    }

    FileDialog {
      id: fileDialog

      onAccepted: {
        console.log("You chose: " + fileDialog.currentFile)
        externalAppsController.externalAppPath = fileDialog.currentFile
      }
      onRejected: {
        console.log("Canceled")
      }
    }
  }

}
