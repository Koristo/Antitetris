import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.1

ApplicationWindow {
    id: root
    visible: true
    property int count_figures: 3
    property var my_obj
    width: 665
    height: 500


    menuBar: MenuBar {
              Menu {
                  title: "Game"
                  MenuItem {
                      text: "Cancel the turn"
                      onTriggered: {
                          var figure_list = fig_field.contentItem.children
                          for(var fig_num = 0; fig_num< figure_list.length; fig_num++)
                              figure_list[fig_num].destroy()
                          var figures = MyField.get_info_figure()
                          for(var i = 0; i < figures.length; i+=2) {
                              var fig_index = figures[i]
                              var fig_type = figures[i+1]
                              switch(fig_type) {
                                case 0:
                                    var component = Qt.createComponent("Figure1.qml")
                                    my_obj = component.createObject(fig_field.contentItem, {y: fig_index * 150 + fig_index * 10, z:4})
                                    my_obj.coor_y = fig_index * 150 + fig_index * 10
                                    my_obj.index = fig_index
                                    break
                                case 1:
                                    component = Qt.createComponent("Figure2.qml")
                                    my_obj = component.createObject(fig_field.contentItem, {y: fig_index * 150 + fig_index * 10, z:3})
                                    my_obj.coor_y = fig_index * 150 + fig_index * 10
                                    my_obj.index = fig_index
                                    break
                                case 2:
                                    component = Qt.createComponent("Figure3.qml")
                                    my_obj = component.createObject(fig_field.contentItem, {y: fig_index * 150 + fig_index * 10, z:3})
                                    my_obj.coor_y = fig_index * 150 + fig_index * 10
                                    my_obj.index = fig_index
                                    break
                                }
                                MyField.edit_list_figure(my_obj.get_form(), fig_index)

                          }
                          MyField.cancel_turn()
                      }
                  }

                  MenuItem {
                      text: "Save game..."
                      onTriggered: MyField.save_game()
                  }
                  MenuItem {
                      text: "Load game..."
                      onTriggered: MyField.load_game()
                  }
              }
    }

    MessageDialog {
        id: msg
        text: "End of the game"
        informativeText: "No more turns left. Press Ok to exit the game."
        onAccepted: {
              Qt.quit()
          }
      }

    Frame {
        id: fig_field
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
                    for (var fig_num = 0; fig_num < count_figures; fig_num++){
                        var fig_type = Math.floor(Math.random() * 3)
                        switch(fig_type) {
                        case 0:
                            var component = Qt.createComponent("Figure1.qml")
                            my_obj = component.createObject(fig_field.contentItem, {y: fig_num * 150 + fig_num * 10, z:4})
                            my_obj.coor_y = fig_num * 150 + fig_num * 10
                            my_obj.index = fig_num
                            break
                        case 1:
                            component = Qt.createComponent("Figure2.qml")
                            my_obj = component.createObject(fig_field.contentItem, {y: fig_num * 150 + fig_num * 10, z:3})
                            my_obj.coor_y = fig_num * 150 + fig_num * 10
                            my_obj.index = fig_num
                            break
                        case 2:
                            component = Qt.createComponent("Figure3.qml")
                            my_obj = component.createObject(fig_field.contentItem, {y: fig_num * 150 + fig_num * 10, z:3})
                            my_obj.coor_y = fig_num * 150 + fig_num * 10
                            my_obj.index = fig_num
                            break
                        }
                        MyField.add_list_figure(my_obj.get_form())
                    }
                    var figure_list = fig_field.contentItem.children
                    var list = []
                    for(var fig_num = 0; fig_num< figure_list.length; fig_num++) {
                        list.push(figure_list[fig_num].index)
                        list.push(figure_list[fig_num].index_fig)
                    }
                    MyField.add_info_figure(list)
                }
            }
        z: 2


    }


    GridView {
        interactive: false
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


                Behavior on color {
                    ColorAnimation {
                        duration: 300
                    }
                }

                DropArea {
                    anchors.fill: parent
                    id: da
                    width: 100
                    height: 100

                    onEntered: {
                        if (MyField.check_field(index, drag.source.get_form())) {
                            MyField.fill_field(index, "grey", drag.source.get_form())
                        }
                    }

                    onExited: {
                        if (MyField.check_field(index, drag.source.get_form()))
                            MyField.fill_field(index, "white", drag.source.get_form())
                    }
                    onDropped: {
                        if(MyField.check_field(index, drag.source.get_form())) {
                            MyField.fill_field(index, "red", drag.source.get_form(), drag.source.index, drag.source.index_fig)
                            var figure_list = fig_field.contentItem.children
                            var list = []
                            for(var fig_num = 0; fig_num< figure_list.length; fig_num++) {
                                list.push(figure_list[fig_num].index)
                                list.push(figure_list[fig_num].index_fig)
                            }
                            MyField.add_info_figure(list)
                            var new_index = drag.source.index
                            drag.source.destroy()

                            switch(Math.floor(Math.random() * 3)) {
                            case 0:
                                var component = Qt.createComponent("Figure1.qml")
                                my_obj = component.createObject(fig_field.contentItem, {y: new_index * 150 + new_index * 10, z:3})
                                my_obj.coor_y = new_index * 150 + new_index * 10
                                my_obj.index = new_index
                                MyField.edit_list_figure(my_obj.get_form(), new_index)
                                if(!MyField.check_turns()) {
                                    console.log("No turns!")
                                    var figure_list = fig_field.contentItem.children
                                    for(var fig_num = 0; fig_num< figure_list.length; fig_num++)
                                        figure_list[fig_num].destroy()
                                    msg.visible = true
                                }
                                break

                            case 1:
                                component = Qt.createComponent("Figure2.qml")
                                my_obj = component.createObject(fig_field.contentItem, {y: new_index * 150 + new_index * 10, z:3})
                                my_obj.coor_y = new_index * 150 + new_index * 10
                                my_obj.index = new_index
                                MyField.edit_list_figure(my_obj.get_form(), new_index)
                                if(!MyField.check_turns()) {
                                    console.log("No turns!")
                                    var figure_list = fig_field.contentItem.children
                                    for(var fig_num = 0; fig_num< figure_list.length; fig_num++)
                                        figure_list[fig_num].destroy()
                                    msg.visible = true
                                }
                                break

                            case 2:
                                component = Qt.createComponent("Figure3.qml")
                                my_obj = component.createObject(fig_field.contentItem, {y: new_index * 150 + new_index * 10, z:3})
                                my_obj.coor_y = new_index * 150 + new_index * 10
                                my_obj.index = new_index
                                MyField.edit_list_figure(my_obj.get_form(), new_index)
                                if(!MyField.check_turns()) {
                                    console.log("No turns!")
                                    var figure_list = fig_field.contentItem.children
                                    for(var fig_num = 0; fig_num< figure_list.length; fig_num++)
                                        figure_list[fig_num].destroy()
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
