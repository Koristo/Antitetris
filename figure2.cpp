#include "figure2.h"

Figure2::Figure2(QQuickItem *parent):
    QQuickPaintedItem(parent)
{

}

void Figure2::paint(QPainter *painter)
{
    //сдвинута вправо на 1 ячейку для центрирования в области показа фигуры
    QPainterPath path;
    path.moveTo(50, 0);
    path.lineTo(100, 0);
    path.lineTo(100, 150);
    path.lineTo(50, 150);
    path.lineTo(50, 0);
    painter->fillPath(path, QBrush(color));
}

bool Figure2::in_figure(double x, double y)
{
    bool in = false;
    if(x>=50 && x<= 100 && y>=0 && y<=150)
            in = true;

    return in;
}

bool Figure2::check_field(Field *field, int index)
{
    int current_index = index;
    bool check = true;

    if (field->getColor(current_index) == QColor("red"))
        check = false;
    else
        for (auto num : form)
            switch(num) {
                case 'u': {
                    if (current_index >= 0 && current_index <=4)
                        return false;
                    if (field->getColor(current_index - 5) == "red")
                        return false;
                    else current_index -= 5;
                    break;
                }
                case 'r': {
                    if (current_index == 4 || current_index == 9 || current_index == 14
                            || current_index == 19 || current_index == 24)
                        return false;
                    if (field->getColor(current_index + 1) == "red")
                        return false;
                    else current_index += 1;
                    break;
                }
                case 'd': {
                    if (current_index >= 20 && current_index <=24)
                        return false;
                    if (field->getColor(current_index + 5) == "red")
                        return false;
                    else current_index += 5;
                    break;
                }
                case 'l': {
                    if (current_index % 5 == 0)
                        return false;
                    if (field->getColor(current_index - 1) == "red")
                        return false;
                    else current_index -= 1;
                    break;
                }

            }

qDebug() << check;
return check;
}

void Figure2::fill_field(Field *field, int index, QString color)
{
    int current_index = index;
    field->setColor(current_index, color);
    for (auto num : form)
        switch(num) {
            case 'u': {
                current_index -= 5;
                field->setColor(current_index, color);
                break;
            }
            case 'r': {
                current_index += 1;
                field->setColor(current_index, color);
                break;
            }
            case 'd': {
                current_index += 5;
                field->setColor(current_index, color);
                break;
            }
            case 'l': {
                current_index -= 1;
                field->setColor(current_index, color);
                break;
            }
        }
    if (color == "red")
        field->check_occupancy_field();
}
