import QtQuick 2.0
import Figure_1 1.0

Fig_1 {
    property var coor_x: 0
    property var coor_y: 0
    property int index
    property bool alive: true

    onAliveChanged: fig1.destroy

    x: coor_x
    y: coor_y
    Drag.hotSpot.x: 0
    Drag.hotSpot.y: 0
    Drag.active: ma_1.drag.active
    id: fig1
    width: 150
    height: 150

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
            fig1.x = coor_x
            fig1.y = coor_y
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
