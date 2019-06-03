import QtQuick 2.0
import Figures 1.0

Fig_1 {

    property int coor_x: 0
    property int coor_y: 0
    property int index_fig: 0
    property int index

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
                fig1.scale = 2
                drag.target = parent
            }

        }
        onReleased: {
            fig1.scale = 1
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

    Behavior on scale {
        NumberAnimation {
            duration: 500
        }
    }
}
