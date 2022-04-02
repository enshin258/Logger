import QtQuick
import QtQuick.Controls
import Qt.labs.platform
import logger.extra 1.0
import "../elements"

Rectangle {
  id: root

  color: theme.backgroundColor

  Rectangle {
    id: descriptionRec

    anchors {
      top: parent.top
      left: parent.left
      right: parent.right
      margins: 20
      topMargin:  - height / 2
    }

    width: 250
    height: 20

    radius: 15

    color: theme.foregroundColor
    border.color: theme.backgroundLightColor

    AppText {
      id: desciptionText
      anchors.centerIn: parent
      text: "Executable"
      font.bold: true
    }
  }

  AppButton {
    id: chooseExeFileButton

    anchors {
      left: parent.left
      margins: 20
      verticalCenter: parent.verticalCenter
    }

    text: "Choose .exe file"

    onClicked: {
      fileDialog.open()
    }
  }

  AppText {
    id: exeText

    anchors {
      left: chooseExeFileButton.right
      right: startOrStopExeButton.left
      margins: 20
      verticalCenter: parent.verticalCenter
    }

    elide: Text.ElideRight

    font.pixelSize: 12

    text: externalAppsController.externalAppPath !== "" ? externalAppsController.externalAppPath : "No .exe file selected"
  }

  AppButton {
    id: startOrStopExeButton

    anchors {
      right: parent.right
      margins: 20
      verticalCenter: parent.verticalCenter
    }

    text: externalAppsController.externalAppRunning ? "Stop application" : "Start application"

    enabled: externalAppsController.externalAppPath !== ""

    opacity: enabled? 1 : 0.2

    onClicked: {
      if (externalAppsController.externalAppRunning) {
        externalAppsController.stopExternalApp();
      } else {
        externalAppsController.runExternalApp();
      }
    }
  }

  FileDialog {
    id: fileDialog

    nameFilters: ["*.exe"]

    onAccepted: {
      let exeFilePath = fileDialog.currentFile.toString().substring(8)
      console.log("You chose program: " + exeFilePath)
      externalAppsController.externalAppPath = exeFilePath
    }
  }
}
