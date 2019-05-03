import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

Item {
    id: root
    width: 640
    height: 500

    Frame {
        background: Rectangle {
                  color: "grey"
                  border.color: "black"
                  border.width: 3
                  radius: 3
              }
        id: separator
        width: root.height / 100 * 30
        height: root.height
        anchors.right: root.right
    }

    Row {
        Repeater {
            model: 5
            Column {
                Repeater {
                    model: 5
                    Rectangle {
                        width: 100
                        height: 100
                        border.width: 1
                        color: "white"
                    }
                }
            }

        }
    }
}


