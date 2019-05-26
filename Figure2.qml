import QtQuick 2.0
import Figures 1.0

Fig_2 {
    property var coor_x: 0
    property var coor_y: 0
    property int index

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
                fig2.scale = 2
                drag.target = parent
            }

        }
        onReleased: {
            fig2.scale = 1
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

    Behavior on scale {
        NumberAnimation {
            duration: 500
        }
    }
}
