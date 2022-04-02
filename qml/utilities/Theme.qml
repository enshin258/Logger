import QtQuick

QtObject {
  id: root

  readonly property color backgroundColor: "#2e2f30"
  readonly property color backgroundLightColor: "#404142"
  readonly property color foregroundColor: "#535455"
  readonly property color borderColor: "#323334"

  readonly property color greenColor: "#92bd6c"
  readonly property color redColor: "#e17f7f"

  readonly property color defaultTextColor: "white"

  readonly property color debugTextColor: defaultTextColor
  readonly property color infoTextColor: "yellow"
  readonly property color warningTextColor: "orange"
  readonly property color errorTextColor: "red"
}
