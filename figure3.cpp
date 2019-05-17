#include "figure3.h"

Figure3::Figure3(QQuickItem *parent):
    QQuickPaintedItem(parent)
{

}

void Figure3::paint(QPainter *painter)
{
    QPainterPath path;
    path.moveTo(0, 0);
    path.lineTo(100, 0);
    path.lineTo(100, 50);
    path.lineTo(0, 50);
    path.lineTo(0, 0);
    painter->fillPath(path, QBrush(color));
    path.moveTo(50, 50);
    path.lineTo(150, 50);
    path.lineTo(150, 100);
    path.lineTo(50, 100);
    path.lineTo(50, 50);
    painter->fillPath(path, QBrush(color));
}

bool Figure3::in_figure(double x, double y)
{
    bool in = false;
    if((x>=0 && x<= 100 && y>=0 && y<=50) || (x>=50 && x<=150 && y>=50 && y<=100))
            in = true;

    return in;
}

bool Figure3::check_field(Field *field, int index)
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
    return check;
}

void Figure3::fill_field(Field *field, int index, QString color)
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
