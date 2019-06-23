#ifndef FIGURE_H
#define FIGURE_H

#include <QQuickItem>
#include <QPainter>
#include <QQuickPaintedItem>
#include <QAbstractListModel>

class Figure: public QQuickPaintedItem
{
    Q_OBJECT

public:
    explicit Figure(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) Q_DECL_OVERRIDE;
    Q_INVOKABLE bool in_figure(double x, double y);
    Q_INVOKABLE QList<int> get_form() const;
    Q_INVOKABLE void set_form(QList<int> _form);
    Q_INVOKABLE void setColor(const QColor &value);
    Q_INVOKABLE void setSize_cell(int value);



private:
    int size_cell;
    QColor color;
    QList<int> form;

};

#endif // FIGURE_H
