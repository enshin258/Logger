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
      text: "Searching and Filtering"
      font.bold: true
    }
  }

  AppButton {
    id: clearButton

    anchors {
      left: parent.left
      margins: 20
      verticalCenter: parent.verticalCenter
    }

    text: "Clear logs"

    onClicked: {
      loggerDataModel.clearLogs()
    }
  }

  TextField {
    id: searchField

    anchors {
      left: clearButton.right
      right: typeFiltersRow.left
      margins: 20
      verticalCenter: parent.verticalCenter
    }

    height: 30

    placeholderText: "Search for content..."
    placeholderTextColor: theme.defaultTextColor
    color: theme.defaultTextColor

    font.pixelSize: 16

    background: Rectangle {
      color: theme.foregroundColor
      border.color: searchField.focus ? theme.greenColor : theme.backgroundLightColor
    }

    onTextChanged: {
      loggerDataModel.contentFilter = searchField.text
    }
  }

  Row {
    id: typeFiltersRow

    component FilterCheckBox: RadioButton {
      id: filterCheckBox

      checked: true
      autoExclusive : false

      indicator: Rectangle {
        width: 30
        height: 30
        color: theme.backgroundLightColor
        border.color: theme.foregroundColor

        Rectangle {
          anchors.centerIn: parent
          width: 20
          height: 20
          radius: height / 2
          color: theme.greenColor
          visible: filterCheckBox.checked
        }
      }

      contentItem: AppText {
        text: filterCheckBox.text
        leftPadding: filterCheckBox.indicator.width + filterCheckBox.spacing
        verticalAlignment: Text.AlignVCenter
      }
    }

    anchors {
      right: parent.right
      margins: 5
      verticalCenter: parent.verticalCenter
    }

    width: 500
    height: 30
    spacing: 15

    FilterCheckBox {
      id: debugFilter

      text: "Debug"

      onCheckedChanged: {
        loggerDataModel.debugFilter = checked
      }
    }

    FilterCheckBox {
      id: infoFilter

      text: "Info"

      onCheckedChanged: {
        loggerDataModel.infoFilter = checked
      }
    }

    FilterCheckBox {
      id: warningFilter

      text: "Warning"

      onCheckedChanged: {
        loggerDataModel.warningFilter = checked
      }
    }

    FilterCheckBox {
      id: errorFilter

      text: "Error"

      onCheckedChanged: {
        loggerDataModel.errorFilter = checked
      }
    }
  }
}
