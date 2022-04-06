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
      topMargin: - height / 2
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

  Switch {
    id: startStopSimulation

    anchors {
      left: parent.left
      margins: 20
      verticalCenter: parent.verticalCenter
    }

    checked: false

    text: startStopSimulation.checked? "Stop simulation" : "Start simulation"

    indicator: Rectangle {
      width: 60
      height: 30
      radius: 15
      color: startStopSimulation.checked ? theme.greenColor: theme.redColor

      Rectangle {
        x: startStopSimulation.checked ? parent.width - width - 5 : 5
        y: parent.height / 2 - height / 2
        width: 20
        height: 20
        radius: height / 2
        color: theme.foregroundColor

        Behavior on x {
          PropertyAnimation {
            duration: 200
          }
        }
      }

      Behavior on color {
        PropertyAnimation {
          duration: 200
        }
      }
    }

    contentItem: AppText {
      text: startStopSimulation.text
      verticalAlignment: Text.AlignVCenter
      leftPadding: startStopSimulation.indicator.width + startStopSimulation.spacing
    }

    onCheckedChanged: {
      if (startStopSimulation.checked) {
        loggerDataModel.startSimulation()
      } else {
        loggerDataModel.stopSimulation()
      }
    }
  }

  AppButton {
    id: chooseExeFileButton

    anchors {
      left: parent.horizontalCenter
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

    text: externalAppProvider.externalAppPath !== "" ? externalAppProvider.externalAppPath : "No .exe file selected"
  }

  AppButton {
    id: startOrStopExeButton

    anchors {
      right: parent.right
      margins: 20
      verticalCenter: parent.verticalCenter
    }

    text: externalAppProvider.externalAppRunning ? "Stop application" : "Start application"

    enabled: externalAppProvider.externalAppPath !== ""

    opacity: enabled? 1 : 0.2

    background: Rectangle {
      color: externalAppProvider.externalAppRunning ? theme.redColor : theme.greenColor

      Behavior on color {
        PropertyAnimation {
          duration: 200
        }
      }
    }

    onClicked: {
      if (externalAppProvider.externalAppRunning) {
        externalAppProvider.stopExternalApp();
      } else {
        externalAppProvider.runExternalApp();
      }
    }
  }

  FileDialog {
    id: fileDialog

    nameFilters: ["*.exe"]

    onAccepted: {
      let exeFilePath = fileDialog.currentFile.toString().substring(8)
      console.log("You chose program: " + exeFilePath)
      externalAppProvider.externalAppPath = exeFilePath
    }
  }
}
