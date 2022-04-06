import QtQuick
import QtQuick.Controls
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
      text: "Network"
      font.bold: true
    }
  }

  TextField {
    id: addresTextField

    anchors {
      left: parent.left
      margins: 20
      verticalCenter: parent.verticalCenter
    }

    height: 30
    width: 100

    text: networkController.hostAddress
    placeholderText: "Server address.."
    placeholderTextColor: theme.defaultTextColor
    color: theme.defaultTextColor

    font.pixelSize: 16

    background: Rectangle {
      color: theme.foregroundColor
      border.color: addresTextField.focus ? theme.greenColor : theme.backgroundLightColor
    }

    onTextChanged: {
      networkController.hostAddress = addresTextField.text
    }
  }

  TextField {
    id: portTextField

    anchors {
      left: addresTextField.right
      margins: 20
      verticalCenter: parent.verticalCenter
    }

    height: 30
    width: 100

    text: networkController.hostPort
    placeholderText: "Server port.."
    placeholderTextColor: theme.defaultTextColor
    color: theme.defaultTextColor

    font.pixelSize: 16

    background: Rectangle {
      color: theme.foregroundColor
      border.color: portTextField.focus ? theme.greenColor : theme.backgroundLightColor
    }

    onTextChanged: {
      var portInt = parseInt(portTextField.text)
      networkController.hostPort = parseInt(portInt)
    }
  }

  AppButton {
    id: testWriteToSocket

    anchors {
      right: parent.right
      margins: 20
      verticalCenter: parent.verticalCenter
    }

    background: Rectangle {
      color: networkController.isConnected ? theme.redColor : theme.greenColor

      Behavior on color {
        PropertyAnimation {
          duration: 200
        }
      }
    }

    text: networkController.isConnected ? "Disconnect from host" : "Connect to host"

    onClicked: {
      if (networkController.isConnected) {
        networkController.disconnectFromHost()
      } else {
        if(!networkController.connectToHost()) {
          infoPopup.infoText = "Failed to connect to host!"
          infoPopup.open()
        }
      }
    }
  }
}
