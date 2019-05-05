import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

Item {
    id: root
    width: 650
    height: 500

    Frame {
        background:
            Rectangle {
              color: "grey"
              border.color: "black"
              border.width: 3
              radius: 3
            }
        id: separator
        width: root.height / 100 * 30
        height: root.height
        anchors.right: root.right
        z: 3

        Column {
            spacing: 20
            Repeater {
                model: 2
                Rectangle {
                    //anchors.right: rect2.left
                    //x: rect2.right
                    //y: rect2.top
                    id: rect
                    width: 100
                    height: 100
                    color: "red"
                    border.width: 1
                    Drag.active: ma.drag.active
                    //Drag.hotSpot.x : 100
                    //Drag.hotSpot.y : 100

                    Rectangle {
                        anchors.left: parent.right
                        //x: parent.right
                        //y: parent.top
                        id: rect2
                        width: 100
                        height: 100
                        border.width: 1
                        color: "red"
                        Drag.active: ma.drag.active
                        //Drag.hotSpot.x : 100
                        //Drag.hotSpot.y : 100
                    }

                    MouseArea {
                        id: ma
                        anchors.fill: parent
                        drag.target: parent
                        onReleased: {
                            console.log("Release")
                        }
                    }
                }
            }
        }

    }

    Grid {
        z: 2
        rows: 5
        columns: 5
        Repeater {
            model: 25

            DropArea {
                width: 100
                height: 100

                Rectangle {
                    id: field
                    width: 100
                    height: 100
                    border.width: 1
                    color: "white"
                }

                onEntered: {
                    console.warn("Entered")
                    field.color = "grey"
                }

                onExited: {
                    console.log("Exit")
                    field.color = "white"
                }

                onDropped:{
                    console.log("Drop")
                    rect.destroy()
                }




            }


        }
    }
}


