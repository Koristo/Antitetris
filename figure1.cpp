#include "figure1.h"

Figure1::Figure1(QQuickItem *parent):
    QQuickPaintedItem(parent)
{
    int test = qrand() % 3;

    switch (test) {
        case 0: {
            new_form = {1, 1, 1, 0, 1, 0, 0, 0, 0};
            break;
        }
        case 1: {
            new_form = {1, 1, 0, 0, 1, 1, 0, 0, 0};
            break;}
        case 2: {
            new_form = {0, 1, 0, 0, 1, 0, 0, 1, 0};
            break;
        }
    }
    color = QColor(qrand()%255,qrand()%255,qrand()%255);

}

void Figure1::paint(QPainter *painter)
{
//    qDebug() << "Test";
//    std::random_device random_device; // Источник энтропии.
//    std::mt19937 generator(random_device()); // Генератор случайных чисел.
//    std::uniform_int_distribution<> distribution(0, 2);
//    int test = distribution(generator); // Случайное число.

//    qDebug() << test;
//    switch (test) {
//        case 0: {
//            new_form = {1, 1, 1, 0, 1, 0, 0, 0, 0};
//            break;
//        }
//        case 1: {
//            new_form = {1, 1, 0, 0, 1, 1, 0, 0, 0};
//            break;}
//        case 2: {
//            new_form = {0, 1, 0, 0, 1, 0, 0, 1, 0};
//            break;
//        }
//    }


    // QList<int> figure = {1, 1, 1, 0, 1, 0, 0, 0, 0};

    int x = 0;
    int y = 0;
    qDebug() << new_form;
    for (auto cell : new_form) {
        QColor buf_color = color;
        QPainterPath path;

        path.moveTo(x, y);
        path.lineTo(x + size_cell, y);
        path.lineTo(x + size_cell, y + size_cell);
        path.lineTo(x, y + size_cell);
        path.lineTo(x, y);

        if (cell)
            painter->fillPath(path, buf_color);

        x += size_cell;

        if (x > size_cell * 2) {
            x = 0;
            y += size_cell;
        }
    }
}

bool Figure1::in_figure(double mouse_x, double mouse_y)
{

    bool in = false;

    int x = 0;
    int y = 0;

    for (auto cell : new_form) {
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


QList<char> Figure1::get_form() const
{
    return form;
}
