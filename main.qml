import QtQuick 2.12
import QtQuick.Window 2.1
import QtQuick.Controls 2.0
import Figure_1 1.0

Item {
    id: root
    width: 850
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
        width: root.width / 100 * 40
        height: root.height
        anchors.right: root.right
        z: 3

        Fig_1 {

            Drag.hotSpot.x: 0
            Drag.hotSpot.y: 0
            Drag.active: ma.drag.active
            id: fig1
            width: 300
            height: 300

            MouseArea {
                id: ma
                anchors.fill: parent

                onPressed: {
                    if (fig1.in_figure(mouseX, mouseY, MyField)) {
                        drag.target = fig1
                    }

                }
                onReleased: {
                    drag.target = null
                    fig1.x = 0
                    fig1.y = 0
                }
            }

            Behavior on x {
                NumberAnimation {duration:500}
            }

            Behavior on y {
                NumberAnimation {duration:500}
            }
        }

    }


    GridView {
        width: 500
        height: 500
        model: MyField
        delegate:
            DropArea {
                width: 100
                height: 100
                Rectangle {
                    anchors.fill: parent
                    id: field
                    width: 100
                    height: 100
                    color: ColorData
                    border.width: 1
                    x: field_x
                    y: field_y


//                    states: [
//                        State {
//                            name: "clear"
//                            PropertyChanges {
//                                target: field
//                                color: "white"
//                            }
//                        },
//                        State {
//                            name: "contestation"
//                            PropertyChanges {
//                                target: field
//                                color: "grey"
//                            }
//                        },
//                        State {
//                            name: "busy"
//                            PropertyChanges {
//                                target: field
//                                color: "red"
//                            }
//                        }

//                    ]
                }

                onEntered: {
                    console.warn("Entered")
                    //field.state = "contestation"
                    if (fig1.check_field(MyField, index)) {
                        fig1.fill_field(MyField, index, "grey")
                        //fig1.destroy()
                    }
                }

                onExited: {
                    console.log("Exit")
                    //field.state = "clear"
                }

            }
    }
}


