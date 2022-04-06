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
      text: "File"
      font.bold: true
    }
  }

  TextField {
    id: textFileNameText

    anchors {
      left: parent.left
      margins: 20
      verticalCenter: parent.verticalCenter
    }

    height: 30
    width: 300

    text: fileController.fileName
    placeholderText: "Enter text file name.."
    placeholderTextColor: theme.defaultTextColor
    color: theme.defaultTextColor

    font.pixelSize: 16

    background: Rectangle {
      color: theme.foregroundColor
      border.color: textFileNameText.focus ? theme.greenColor : theme.backgroundLightColor
    }

    onTextChanged: {
      fileController.fileName = textFileNameText.text
    }
  }

  AppButton {
    id: createTextFile

    anchors {
      left: textFileNameText.right
      margins: 20
      verticalCenter: parent.verticalCenter
    }

    enabled: fileController.fileName !== ""

    opacity: enabled? 1 : 0.2

    text: "Create text file"

    onClicked: {
      fileController.openFileToSave();
      infoPopup.infoText = "Text file created"
      infoPopup.open()
    }
  }

  TextField {
    id: databaseFileNameText

    anchors {
      right: createDatabaseFile.left
      margins: 20
      verticalCenter: parent.verticalCenter
    }

    height: 30
    width: 300

    text: databaseController.databaseFileName
    placeholderText: "Enter database file name.."
    placeholderTextColor: theme.defaultTextColor
    color: theme.defaultTextColor

    font.pixelSize: 16

    background: Rectangle {
      color: theme.foregroundColor
      border.color: databaseFileNameText.focus ? theme.greenColor : theme.backgroundLightColor
    }

    onTextChanged: {
      databaseController.databaseFileName = databaseFileNameText.text
    }
  }

  AppButton {
    id: createDatabaseFile

    anchors {
      right: parent.right
      margins: 20
      verticalCenter: parent.verticalCenter
    }

    enabled: databaseController.databaseFileName !== ""

    opacity: enabled? 1 : 0.2

    text: "Create Database file"

    onClicked: {
      databaseController.initDatabase()
      infoPopup.infoText = "Database created"
      infoPopup.open()
    }
  }
}
