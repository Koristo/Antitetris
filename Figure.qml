import QtQuick 2.0
import Figure 1.0

Figure {
    id: fig
    property int coor_x: 0
    property int coor_y
    property int index

    Drag.active: ma.drag.active
    z: 1

    MouseArea {
        id: ma
        anchors.fill: parent

        onPressed: {

            if (fig.in_figure(mouseX, mouseY, MyField)) {
                fig.z = 2
                fig.scale = 1.5
                drag.target = parent
            }

        }
        onReleased: {
            fig.z = 1
            fig.scale = 1
            drag.target = null
            fig.x = coor_x
            fig.y = coor_y
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
