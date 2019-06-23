#include "figure.h"

Figure::Figure(QQuickItem *parent):
    QQuickPaintedItem(parent)
{

}

void Figure::paint(QPainter *painter)
{

    int x = 0;
    int y = 0;

    for (auto cell : form) {
        QPainterPath path;

        path.moveTo(x, y);
        path.lineTo(x + size_cell, y);
        path.lineTo(x + size_cell, y + size_cell);
        path.lineTo(x, y + size_cell);
        path.lineTo(x, y);

        if (cell)
            painter->fillPath(path, color);

        x += size_cell;

        if (x > size_cell * 2) {
            x = 0;
            y += size_cell;
        }
    }
}

bool Figure::in_figure(double mouse_x, double mouse_y)
{

    bool in = false;

    int x = 0;
    int y = 0;

    for (auto cell : form) {
        if (cell) {
            if (mouse_x >= x && mouse_x <= x + size_cell && mouse_y >= y && mouse_y <= y + size_cell) {
                in = true;
                break;
            }
        }

        x += size_cell;
        if (x > size_cell * 2) {
            x = 0;
            y += size_cell;
        }
    }
    return in;
}


QList<int> Figure::get_form() const
{
    return form;
}

void Figure::set_form(QList<int> _form)
{
    form = _form;
}

void Figure::setColor(const QColor &value)
{
    color = value;
}

void Figure::setSize_cell(int value)
{
    size_cell = value;
}
