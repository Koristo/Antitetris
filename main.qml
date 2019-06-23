import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.1

ApplicationWindow {
    id: root
    visible: true
    property int myField_width: MyField.getColumns() * MyField.getSize_cell()
    property int myField_height: MyField.getRows() * MyField.getSize_cell()

    property int size_figure: FiguresField.getSize_cell() * 3
    property int figuresField_width: size_figure + 25
    property int figuresField_height: FiguresField.getFigures_count() * size_figure + FiguresField.getFigures_count() * 15

    Component.onCompleted:
        console.log("Sizes:",
                    myField_width,
                    myField_height,
                    figuresField_width,
                    figuresField_height,
                    size_figure)
    property var my_obj
    width: myField_width + figuresField_width
    height: myField_height > figuresField_height ? myField_height:figuresField_height

    menuBar: MenuBar {
              Menu {
                  title: "Game"
                  MenuItem {
                      text: "Cancel the turn"
                      onTriggered: {
                          console.log("cansel the turn")
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
        z: 2
        width: figuresField_width
        height: root.height
        anchors.right: parent.right
        background:
            Rectangle {
                color: "grey"
                border.color: "black"
                border.width: 3
                radius: 3
            }
            ListView {
                interactive: false
                id: list_figure
                model: FiguresField
                width: parent.width
                height: parent.height
                contentWidth: parent.width
                contentHeight: parent.height
                delegate:
                    Rectangle {
                        id: figure
                        Component.onCompleted: {
                            var component = Qt.createComponent("Figure.qml")
                            var new_y = FigIndex * size_figure + FigIndex * 10
                            my_obj = component.createObject(list_figure.contentItem, {
                                                                y: new_y,
                                                                width: size_figure,
                                                                height: size_figure,
                                                                index: FigIndex,
                                                                coor_y: new_y,
                                                                "Drag.hotSpot.x": HotSpotX,
                                                                "Drag.hotSpot.y": HotSpotY})
                            my_obj.setSize_cell(FiguresField.getSize_cell())
                            my_obj.set_form(FiguresField.get_current_form(FigIndex))
                            my_obj.setColor(ColorData)
                        }
                    }
            }
    }


    GridView {
        interactive: false
        model: MyField
        width: myField_width
        height: myField_height
        cellHeight: MyField.getSize_cell()
        cellWidth: MyField.getSize_cell()
        delegate:
            Rectangle {
                id: field
                width: MyField.getSize_cell()
                height: MyField.getSize_cell()
                color: ColorData
                border.width: 1

                Behavior on color {
                    ColorAnimation {
                        duration: 300
                    }
                }

                DropArea {
                    anchors.fill: parent
                    id: da
                    width: parent.width
                    height: parent.height

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
                            MyField.fill_field(index, "red", drag.source.get_form())
                            var index_figure = drag.source.index
                            var new_form = FiguresField.change_form(index_figure)
                            var new_color = FiguresField.change_color(index_figure)
                            var spot_x = FiguresField.get_x(index_figure)
                            var spot_y = FiguresField.get_y(index_figure)
                            console.log(index_figure, spot_x, spot_y)
                            drag.source.destroy()

                            var new_y = index_figure * size_figure + index_figure * 10
                            console.log(new_y)
                            var component = Qt.createComponent("Figure.qml")
                            my_obj = component.createObject(list_figure.contentItem, {
                                                                y: new_y,
                                                                width: size_figure,
                                                                height: size_figure,
                                                                index: index_figure,
                                                                coor_y: new_y,
                                                                "Drag.hotSpot.x": spot_x,
                                                                "Drag.hotSpot.y": spot_y})
                            my_obj.setSize_cell(FiguresField.getSize_cell())
                            my_obj.set_form(new_form)
                            my_obj.setColor(new_color)

                            // проверка на возможность следующего хода
                            var forms = FiguresField.get_forms()
                            if (!MyField.check_turns(forms)) {
                                var figure_list = fig_field.contentItem.children
                                for(var fig_num = 0; fig_num< figure_list.length; fig_num++)
                                    figure_list[fig_num].destroy()
                                msg.visible = true
                            }
                        }
                    }
                }
            }
    }
}
