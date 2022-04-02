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
}
