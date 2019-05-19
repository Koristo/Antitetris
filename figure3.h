#ifndef FIGURE3_H
#define FIGURE3_H

#include <QQuickItem>
#include <QPainter>
#include <QQuickPaintedItem>
#include "field.h"
#include "figure.h"

class Figure3: public QQuickPaintedItem
{
    Q_OBJECT

public:
    explicit Figure3(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) Q_DECL_OVERRIDE;
    Q_INVOKABLE bool in_figure(double x, double y);
    Q_INVOKABLE bool check_field(Field *field, int index);
    Q_INVOKABLE void fill_field(Field *field, int index, QString color);
    Q_INVOKABLE QList<char> get_form() const;
    Q_INVOKABLE void edit_figure_in_list(Field *field, int index);

private:
    QColor color = QColor("orange");
    QList<char> form = {'r', 'd', 'r'};
};

#endif // FIGURE3_H
