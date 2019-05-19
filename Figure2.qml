import QtQuick 2.0
import Figure_2 1.0

Fig_2 {
    property var coor_x: 0
    property var coor_y: 0
    property int index
    property bool alive: true

    onAliveChanged: fig2.destroy

    x: coor_x
    y: coor_y
    Drag.hotSpot.x: 50
    Drag.hotSpot.y: 0
    Drag.active: ma_2.drag.active
    id: fig2
    width: 150
    height: 150

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
            fig2.x = coor_x
            fig2.y = coor_y
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
