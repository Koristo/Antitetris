#include "figure2.h"

Figure2::Figure2(QQuickItem *parent):
    QQuickPaintedItem(parent)
{

}

void Figure2::paint(QPainter *painter)
{
    //сдвинута вправо на 1 ячейку для центрирования в области показа фигуры
    QPainterPath path;
    path.moveTo(size_cell, 0);
    path.lineTo(size_cell * 2, 0);
    path.lineTo(size_cell * 2, size_cell * 3);
    path.lineTo(size_cell, size_cell * 3);
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


QList<char> Figure2::get_form() const
{
    return form;
}
