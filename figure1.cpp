#include "figure1.h"

Figure1::Figure1(QQuickItem *parent):
    QQuickPaintedItem(parent)
{

}

void Figure1::paint(QPainter *painter)
{
    QPainterPath path;
    path.moveTo(0, 0);
    path.lineTo(300, 0);
    path.lineTo(300, 100);
    path.lineTo(0, 100);
    path.lineTo(0, 0);
    painter->fillPath(path, QBrush(color));
    path.moveTo(100, 100);
    path.lineTo(100, 200);
    path.lineTo(200, 200);
    path.lineTo(200, 100);
    painter->fillPath(path, QBrush(color));
}

bool Figure1::in_figure(double x, double y)
{
    bool in = false;
    if((x>=0 && x<= 300 && y>=0 && y<=100) || (x>=100 && x<=200 && y>=100 && y<=200))
            in = true;
    return in;
}
