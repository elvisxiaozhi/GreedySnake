import QtQuick.Window 2.2
import QtQuick.Controls 2.12

Popup {
    id: gameOverDialog
    width: 100
    height: 70
    visible: false

    MouseArea {
      anchors.fill: parent
      drag.target: Overlay.overlay
    }

    Text {
        text: "Game Over"
        anchors.centerIn: parent
    }
}
