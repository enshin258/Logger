import QtQuick
import logger.extra 1.0
import "../elements"

Rectangle {
  id: root

  color: theme.backgroundColor

  border {
    width: 2
    color: theme.borderColor
  }

  Rectangle {
    id: topBar

    anchors {
      top: parent.top
      left: parent.left
      right: parent.right
      margins: 5
    }

    height: 30

    color: theme.foregroundColor

    Row {
      id: sortingRow

      anchors {
        fill: parent
      }

      spacing: 0

      component Header: Rectangle {
        id: header
        property string headerText: ""
        property var headerRole

        height: parent.height
        color: headerRole === loggerDataModel.sortRole ? (loggerDataModel.sortOrder === Qt.AscendingOrder? theme.greenColor : theme.redColor) : theme.foregroundColor

        border {
          width: 2
          color: theme.backgroundLightColor
        }

        AppText {
          anchors.fill: parent

          text: headerText
        }

        MouseArea {
          anchors.fill: parent
          onClicked: {
            console.log("Header clicked")
            loggerDataModel.sortOrder = loggerDataModel.sortOrder === Qt.AscendingOrder? Qt.DescendingOrder: Qt.AscendingOrder
            loggerDataModel.sortRole = header.headerRole;
          }
        }
      }

      Header {
        id: idHeader

        width: parent.width * 1/16

        headerText: "ID"
        headerRole: LoggerDataModel.IdRole
      }

      Header {
        id: dateTimeHeader

        width: parent.width * 4/16

        headerText: "DATETIME"
        headerRole: LoggerDataModel.DateTimeRole
      }

      Header {
        id: priorityHeader

        width: parent.width * 3/16

        headerText: "PRIORITY"
        headerRole: LoggerDataModel.PriorityRole
      }

      Header {
        id: contentHeader

        width: parent.width * 8/16

        headerText: "CONTENT"
        headerRole: LoggerDataModel.ContentRole
      }
    }
  }

  ListView {
    id: logsListView

    anchors {
      top: topBar.bottom
      topMargin: 20
      left: parent.left
      right: parent.right
      bottom: parent.bottom
      margins: 5
    }

    clip: true

    model: loggerDataModel

    delegate: Rectangle {
      width: logsListView.width
      height: contentText.height

      color: "transparent"

      Row {
        anchors.fill: parent

        spacing: 0

        component LogText: AppText {
          id: logText

          font.pixelSize: 12

          color: switch(priority) {
                 case "DEBUG":
                   theme.debugTextColor
                   break
                 case "INFO":
                   theme.infoTextColor
                   break
                 case "WARNING":
                   theme.warningTextColor
                   break
                 case "ERROR":
                   theme.errorTextColor
                   break
                 }
        }

        LogText {
          id: idText

          width: parent.width * 1/16

          text: id
        }

        LogText {
          id: dateTimeText

          width: parent.width * 4/16

          text: dateTime
        }

        LogText {
          id: priorityText

          width: parent.width * 3/16

          text: priority
        }

        LogText {
          id: contentText

          width: parent.width * 8/16

          text: content.trim()

          horizontalAlignment: Text.AlignLeft
          wrapMode: Text.WrapAnywhere
        }
      }
    }

    Connections {
      target: loggerDataModel

      function onRowsInserted() {
        logsListView.positionViewAtEnd()
      }
    }
  }
}
