#ifndef FIGURE3_H
#define FIGURE3_H

#include <QQuickItem>
#include <QPainter>
#include <QQuickPaintedItem>
#include "field.h"

class Figure3: public QQuickPaintedItem
{
    Q_OBJECT

public:
    explicit Figure3(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) Q_DECL_OVERRIDE;
    Q_INVOKABLE bool in_figure(double x, double y);
    Q_INVOKABLE QList<char> get_form() const;

private:
    int size_cell = 50;
    QColor color = QColor("orange");
    QList<char> form = {'r', 'd', 'r'};
};

#endif // FIGURE3_H
