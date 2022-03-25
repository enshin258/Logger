import QtQuick
import QtQuick.Controls
import Qt.labs.platform
Item {
  id: root

  Rectangle {
    id: background

    anchors.fill: parent

    color: theme.backgroundColor

    Rectangle {
      id: logsRec

      anchors {
        top: parent.top
        left: parent.left
        right: parent.right

        margins: 50
      }

      color: theme.backgroundLightColor

      border {
        width: 2
        color: theme.borderColor
      }

      height: parent.height * 3/4

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
            property string headerText: ""

            signal headerClicked()

            height: parent.height
            color: theme.foregroundColor

            border {
              width: 2
              color: theme.defaultTextColor
            }

            Text {
              anchors.centerIn: parent

              text: headerText

              verticalAlignment: Text.AlignVCenter
              horizontalAlignment: Text.AlignHCenter
            }

            MouseArea {
              anchors.fill: parent
              onClicked:  {
                headerClicked()
              }
            }
          }

          Header {
            id: idHeader

            width: parent.width * 1/16

            headerText: "ID"
          }

          Header {
            id: dateTimeHeader

            width: parent.width * 4/16

            headerText: "DATETIME"
          }

          Header {
            id: priorityHeader

            width: parent.width * 3/16

            headerText: "PRIORITY"
          }

          Header {
            id: contentHeader

            width: parent.width * 8/16

            headerText: "CONTENT"
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
        spacing: 10

        delegate: Rectangle {
          width: logsListView.width
          height: contentText.height

          color: theme.foregroundColor

          Row {
            anchors.fill: parent

            spacing: 0

            Text {
              id: idText

              width: parent.width * 1/16

              text: id

              horizontalAlignment: Text.AlignHCenter
              verticalAlignment: Text.AlignVCenter

              color: priority === "ERROR" ? theme.errorTextColor : theme.defaultTextColor
            }

            Text {
              id: dateTimeText

              width: parent.width * 4/16


              text: dateTime

              horizontalAlignment: Text.AlignHCenter
              verticalAlignment: Text.AlignVCenter

              color: priority === "ERROR" ? theme.errorTextColor : theme.defaultTextColor

            }

            Text {
              id: priorityText

              width: parent.width * 3/16


              text: priority

              horizontalAlignment: Text.AlignHCenter
              verticalAlignment: Text.AlignVCenter

              color: priority === "ERROR" ? theme.errorTextColor : theme.defaultTextColor

            }

            Text {
              id: contentText

              width: parent.width * 8/16

              text: content

              horizontalAlignment: Text.AlignHCenter
              verticalAlignment: Text.AlignVCenter

              wrapMode: Text.WrapAnywhere

              color: priority === "ERROR" ? theme.errorTextColor : theme.defaultTextColor

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
