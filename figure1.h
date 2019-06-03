#ifndef FIGURE1_H
#define FIGURE1_H

#include <QQuickItem>
#include <QPainter>
#include <QQuickPaintedItem>
#include <QAbstractListModel>
//#include "field.h"

class Figure1: public QQuickPaintedItem
{
    Q_OBJECT

public:
    explicit Figure1(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) Q_DECL_OVERRIDE;
    Q_INVOKABLE bool in_figure(double x, double y);
    Q_INVOKABLE QList<char> get_form() const;

private:
    int size_cell = 50;
    QColor color = QColor("blue");
    QList<char> form = {'r', 'd', 'u', 'r'};

};

#endif // FIGURE1_H
