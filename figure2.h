#ifndef FIGURE2_H
#define FIGURE2_H

#include <QQuickItem>
#include <QPainter>
#include <QQuickPaintedItem>
#include "field.h"
#include "figure.h"
#include <QList>

class Figure2: public QQuickPaintedItem
{
    Q_OBJECT

public:
    explicit Figure2(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) Q_DECL_OVERRIDE;
    Q_INVOKABLE bool in_figure(double x, double y);
    Q_INVOKABLE bool check_field(Field *field, int index);
    Q_INVOKABLE void fill_field(Field *field, int index, QString color);

private:
    QColor color = QColor("green");
    char form[3] = {'d', 'd'};
};

#endif // FIGURE2_H
