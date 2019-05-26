#include "figure1.h"

Figure1::Figure1(QQuickItem *parent):
    QQuickPaintedItem(parent)
{

}

void Figure1::paint(QPainter *painter)
{
    QPainterPath path;
    path.moveTo(0, 0);
    path.lineTo(size_cell * 3, 0);
    path.lineTo(size_cell * 3, size_cell);
    path.lineTo(0, size_cell);
    path.lineTo(0, 0);
    painter->fillPath(path, QBrush(color));
    path.moveTo(size_cell, size_cell);
    path.lineTo(size_cell, size_cell * 2);
    path.lineTo(size_cell * 2, size_cell * 2);
    path.lineTo(100, size_cell);
    painter->fillPath(path, QBrush(color));
}

bool Figure1::in_figure(double x, double y)
{
    bool in = false;
    if((x>=0 && x<= 150 && y>=0 && y<=50) || (x>=50 && x<=100 && y>=50 && y<=100))
            in = true;

    return in;
}


QList<char> Figure1::get_form() const
{
    return form;
}
