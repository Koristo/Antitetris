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
    Q_PROPERTY(QVariant _form)

public:
    QVariant _form() const {
            return QVariant::fromValue(form);
        }
    explicit Figure1(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) Q_DECL_OVERRIDE;
    Q_INVOKABLE bool in_figure(double x, double y);
    Q_INVOKABLE bool check_field(Field *field, int index);
    Q_INVOKABLE void fill_field(Field *field, int index, QString color);
    Q_INVOKABLE void edit_figure_in_list(Field *field, int index);
    Q_INVOKABLE void add_figure();
    Q_INVOKABLE QList<char> get_form() const;

signals:
    void new_figure(QList<char> form);
    void edit_list(int index);

private slots:

    bool check_end_of_game(Field *field);

private:
    QColor color = QColor("blue");
    QList<char> form = {'r', 'd', 'u', 'r'};

};

#endif // FIGURE1_H
