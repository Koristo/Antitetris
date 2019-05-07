#ifndef FIGURE1_H
#define FIGURE1_H

#include <QQuickItem>
#include <QPainter>
#include <QQuickPaintedItem>
#include "figure.h"

class Figure1: public QQuickPaintedItem
{
    Q_OBJECT

public:
    explicit Figure1(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) Q_DECL_OVERRIDE;
    Q_INVOKABLE bool in_figure(double x, double y);

signals:
private:
    QColor color = QColor("blue");
};

#endif // FIGURE1_H
