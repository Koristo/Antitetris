import QtQuick 2.12
import QtQuick.Window 2.1
import QtQuick.Controls 2.0
import Figure_1 1.0

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

        Fig_1 {
            id: fig1
            width: 300
            height: 200
//            transform: Scale {
//                yScale: 1
//                xScale: 1
//                origin.x: 100
//                origin.y: 100
//            }
            MouseArea {
                id: ma
                anchors.fill: parent

                //Drag.hotSpot.x: 100
                //Drag.hotSpot.y: 100
                Drag.active : ma.drag.active
                onPressed: {
                    if (fig1.in_figure(mouseX, mouseY)) {
                        drag.target = fig1

                    }

                }
                onReleased: {
                    drag.target = null
                    Drag.active = null
                    fig1.x = 0
                    fig1.y = 0
                }
            }
        }


//        Column {
//            spacing: 20
//            Repeater {
//                model: 2
//                Rectangle {
//                    //anchors.right: rect2.left
//                    //x: rect2.right
//                    //y: rect2.top
//                    id: rect
//                    width: 100
//                    height: 100
//                    color: "red"
//                    border.width: 1
//                    Drag.active: ma.drag.active
//                    Drag.hotSpot.x : 0
//                    Drag.hotSpot.y : 0

//                    Rectangle {
//                        anchors.left: parent.right
//                        //x: parent.right
//                        //y: parent.top
//                        id: rect2
//                        width: 100
//                        height: 100
//                        border.width: 1
//                        color: "red"
//                        Drag.active: ma.drag.active
//                        //Drag.hotSpot.x : 100
//                        //Drag.hotSpot.y : 100
//                    }

//                    MouseArea {
//                        id: ma
//                        anchors.fill: parent
//                        drag.target: parent
//                        onReleased: {
//                            console.log("Release")
//                        }
//                    }
//                }
//            }
//        }

    }

//    Grid {
//        z: 2
//        rows: 5
//        columns: 5
//        Repeater {
//            model: 25

//            DropArea {
//                width: 100
//                height: 100

//                Rectangle {
//                    id: field
//                    width: 100
//                    height: 100
//                    border.width: 1
//                    color: "white"
//                }

//                onEntered: {
//                    console.warn("Entered")
//                    field.color = "grey"
//                }

//                onExited: {
//                    console.log("Exit")
//                    field.color = "white"
//                }

//                onDropped:{
//                    console.log("Drop")
//                    rect.destroy()
//                }




//            }


//        }
//    }

    Repeater {
        model: MyField
        //spacing: 1
        anchors.fill: parent
        delegate:
            DropArea {
                anchors.fill: parent
                Rectangle {
                    id: field
                    width: 100
                    height: 100
                    color: color
                    border.width: 1
                    x: field_x
                    y: field_y
                }

                onEntered: {
                    console.warn("Entered")
                    field.color = "grey"
                }

                onExited: {
                    console.log("Exit")
                    field.color = "white"
                }

            }
    }
}


