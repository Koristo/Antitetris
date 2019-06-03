import QtQuick 2.0
import Figures 1.0

Fig_3 {
    property int coor_x: 0
    property int coor_y: 0
    property int index_fig: 2
    property int index

    x: coor_x
    y: coor_y
    Drag.hotSpot.x: 0
    Drag.hotSpot.y: 0
    Drag.active: ma_3.drag.active
    id: fig3
    width: 150
    height: 150

    MouseArea {
        id: ma_3
        anchors.fill: parent

        onPressed: {
            if (fig3.in_figure(mouseX, mouseY, MyField)) {
                fig3.scale = 2
                drag.target = parent
            }

        }
        onReleased: {
            fig3.scale = 1
            drag.target = null
            fig3.x = coor_x
            fig3.y = coor_y
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
