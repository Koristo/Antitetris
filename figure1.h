#ifndef FIGURE1_H
#define FIGURE1_H

#include <QQuickItem>
#include <QPainter>
#include <QQuickPaintedItem>
#include "field.h"
#include "figure.h"

class Figure1: public QQuickPaintedItem
{
    Q_OBJECT

public:
    explicit Figure1(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) Q_DECL_OVERRIDE;
    Q_INVOKABLE bool in_figure(double x, double y);
    Q_INVOKABLE bool check_field(Field *field, int index);
    Q_INVOKABLE void fill_field(Field *field, int index, QString color);

signals:
private:
    QColor color = QColor("blue");
    char form[4] = {'r', 'd', 'u', 'r'};

};

#endif // FIGURE1_H
