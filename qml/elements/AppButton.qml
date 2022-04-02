import QtQuick
import QtQuick.Controls

AbstractButton {
 id: root

 width: 160
 height: 30

 contentItem: AppText {
     text: root.text
     horizontalAlignment: Text.AlignHCenter
     verticalAlignment: Text.AlignVCenter
     elide: Text.ElideRight
 }

 background: Rectangle {
     color: theme.foregroundColor
 }
}
