import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.1

Window {
    width: 250
    height: 250
    minimumWidth: 250
    minimumHeight: 250
    maximumWidth: 250
    maximumHeight: 250
    visible: true
    title: qsTr("Greedy Snake")

    GridLayout {
        id : grid
        anchors.fill: parent
        rowSpacing: 0
        columnSpacing: 0

        Repeater {
            id: repeater

            Rectangle {
                color: "grey";
                width: 25;
                height: 25;
                border.color: "black"
            }

            Component.onCompleted: {
                grid.rows = board.rows
                grid.columns = board.cols
                repeater.model = board.rows * board.cols
            }
        }
    }

    GameOverDialog {
        id: gameOverDialog
        anchors.centerIn: parent
    }

    Connections {
        target: board
        function onBoardStateChanged(row, col, color) {
            repeater.itemAt(row * board.rows + col).color = color
        }
    }

    Connections {
        target: board
        function onGameOver() {
            gameOverDialog.visible = true
        }
    }
}
