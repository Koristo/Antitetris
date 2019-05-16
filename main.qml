import QtQuick 2.12
import QtQuick.Window 2.1
import QtQuick.Controls 2.0
import Figure_1 1.0
import Figure_2 1.0

Item {
    id: root
    width: 665
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
        width: root.width / 100 * 25
        height: root.height
        anchors.right: root.right
        z: 3

        Fig_1 {
            x: 0
            y: 0
            Drag.hotSpot.x: 0
            Drag.hotSpot.y: 0
            Drag.active: ma_1.drag.active
            id: fig1
            width: 225
            height: 225

            MouseArea {
                id: ma_1
                anchors.fill: parent

                onPressed: {
                    if (fig1.in_figure(mouseX, mouseY, MyField)) {
                        drag.target = parent
                    }

                }
                onReleased: {
                    drag.target = null
                    fig1.x = 0
                    fig1.y = 0
                    parent.Drag.drop()
                }
            }

            Behavior on x {
                NumberAnimation {duration:500}
            }

            Behavior on y {
                NumberAnimation {duration:500}
            }
        }

        Fig_2 {
            x: 0
            y: 150
            Drag.hotSpot.x: 50
            Drag.hotSpot.y: 0
            Drag.active: ma_2.drag.active
            id: fig2
            width: 225
            height: 225

            MouseArea {
                id: ma_2
                anchors.fill: parent

                onPressed: {
                    if (fig2.in_figure(mouseX, mouseY, MyField)) {
                        drag.target = parent
                    }

                }
                onReleased: {
                    drag.target = null
                    fig2.x = 0
                    fig2.y = 225
                    parent.Drag.drop()
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
            Rectangle {
                    id: field
                    width: 100
                    height: 100
                    color: ColorData
                    border.width: 1
                    x: field_x
                    y: field_y

                    DropArea {
                        anchors.fill: parent
                        id: da
                        width: 100
                        height: 100

                        onEntered: {
                            console.warn("Entered")
                            if (drag.source.check_field(MyField, index)) {
                                drag.source.fill_field(MyField, index, "grey")
                            }
                        }

                        onExited: {
                            console.log("Exit")
                            if (drag.source.check_field(MyField, index))
                                drag.source.fill_field(MyField, index, "white")
                        }
                        onDropped: {
                            console.log("dropped")

                            if(drag.source.check_field(MyField, index)) {
                                drag.source.fill_field(MyField, index, "red")
                                //drag.source.destroy()
                            }

                        }

                    }

            }
    }
}
