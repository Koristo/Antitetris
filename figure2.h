#ifndef FIGURE2_H
#define FIGURE2_H

#include <QQuickItem>
#include <QPainter>
#include <QQuickPaintedItem>
#include "field.h"
#include <QList>

class Figure2: public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit Figure2(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) Q_DECL_OVERRIDE;
    Q_INVOKABLE bool in_figure(double x, double y);
    Q_INVOKABLE QList<char> get_form() const;

private:
    int size_cell = 50;
    QColor color = QColor("green");
    QList<char> form = {'d', 'd'};
};

#endif // FIGURE2_H
