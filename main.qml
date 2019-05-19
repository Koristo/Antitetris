import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import Figure_1 1.0
import Figure_2 1.0
import QtQuick.Dialogs 1.1

Window {
    visible: true
    property int figures: 3
    property var my_obj
    id: root
    width: 665
    height: 500

    MessageDialog {
        id: msg
        text: "End of the game"
        informativeText: "No more turns left. Press Ok to exit the game."
        onAccepted: {
              Qt.quit()
          }
      }

    Frame {
        width: root.width / 100 * 25
        height: root.height
        anchors.right: parent.right
        background:
            Rectangle {
                color: "grey"
                border.color: "black"
                border.width: 3
                radius: 3
                Component.onCompleted: {
                    for (var fig_num = 0; fig_num < figures; fig_num++){
                        switch(Math.floor(Math.random() * 3)) {
                        case 0:
                            var component = Qt.createComponent("Figure1.qml")
                            my_obj = component.createObject(separator.contentItem, {y: fig_num * 150 + fig_num * 10, z:4})
                            my_obj.coor_y = fig_num * 150 + fig_num * 10
                            my_obj.index = fig_num
                            break
                        case 1:
                            component = Qt.createComponent("Figure2.qml")
                            my_obj = component.createObject(separator.contentItem, {y: fig_num * 150 + fig_num * 10, z:3})
                            my_obj.coor_y = fig_num * 150 + fig_num * 10
                            my_obj.index = fig_num
                            break
                        case 2:
                            component = Qt.createComponent("Figure3.qml")
                            my_obj = component.createObject(separator.contentItem, {y: fig_num * 150 + fig_num * 10, z:3})
                            my_obj.coor_y = fig_num * 150 + fig_num * 10
                            my_obj.index = fig_num
                            break
                        }
                        MyField.add_list_figure(my_obj.get_form())
                    }
                }
            }
        id: separator
        z: 2


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
                        if (drag.source.check_field(MyField, index)) {
                            drag.source.fill_field(MyField, index, "grey")
                        }
                    }

                    onExited: {
                        if (drag.source.check_field(MyField, index))
                            drag.source.fill_field(MyField, index, "white")
                    }
                    onDropped: {
                        if(drag.source.check_field(MyField, index)) {
                            drag.source.fill_field(MyField, index, "red")
                            var new_index = drag.source.index
                            drag.source.destroy()

                            switch(Math.floor(Math.random() * 3)) {
                            case 0:
                                var component = Qt.createComponent("Figure1.qml")
                                my_obj = component.createObject(separator.contentItem, {y: new_index * 150 + new_index * 10, z:3})
                                my_obj.coor_y = new_index * 150 + new_index * 10
                                my_obj.index = new_index
                                my_obj.edit_figure_in_list(MyField, new_index)
                                if(!MyField.check_turns()) {
                                    console.log("No turns!")
                                    msg.visible = true
                                }
                                break

                            case 1:
                                component = Qt.createComponent("Figure2.qml")
                                my_obj = component.createObject(separator.contentItem, {y: new_index * 150 + new_index * 10, z:3})
                                my_obj.coor_y = new_index * 150 + new_index * 10
                                my_obj.index = new_index
                                my_obj.edit_figure_in_list(MyField, new_index)
                                if(!MyField.check_turns()) {
                                    console.log("No turns!")
                                    msg.visible = true
                                }
                                break

                            case 2:

                                component = Qt.createComponent("Figure3.qml")
                                my_obj = component.createObject(separator.contentItem, {y: new_index * 150 + new_index * 10, z:3})
                                my_obj.coor_y = new_index * 150 + new_index * 10
                                my_obj.index = new_index
                                my_obj.edit_figure_in_list(MyField, new_index)
                                if(!MyField.check_turns()) {
                                    console.log("No turns!")
                                    msg.visible = true
                                }
                                break
                            }
                        }

                    }

                }

            }
    }
}
