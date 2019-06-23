#ifndef FIGURES_MODEL_H
#define FIGURES_MODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QHash>
#include <QColor>
#include <QDebug>
#include <ctime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

class FiguresModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        color,
        form,
        index,
        rand_num,
        hotspot_x,
        hotspot_y
    };

    explicit FiguresModel(int _size_cell, int _figures_count, QObject *parent = nullptr);
    void add(int _index);
    int rowCount(const QModelIndex &parent) const;
    QHash<int, QByteArray> roleNames() const ;
    QVariant data(const QModelIndex &index, int role) const;

    void load_figures(const QString json);
    void init_figures();
    Q_INVOKABLE int getFigures_count();
    Q_INVOKABLE QList<int> get_current_form(int index) const;
    Q_INVOKABLE QString get_current_color(int index) const;

    Q_INVOKABLE QList<int> change_form(int index);
    Q_INVOKABLE QColor change_color(int index);
    Q_INVOKABLE int getSize_cell();
    Q_INVOKABLE int get_index_figure(int index) const;
    Q_INVOKABLE int get_x(int index) const;
    Q_INVOKABLE int get_y(int index) const;

    Q_INVOKABLE QList<QList<int> > get_forms() const;

private:
    QHash<int, QByteArray> my_data;
    QList<QColor> m_color;
    QList<int> i_figure;
    QList<int> m_hot_spot_x;
    QList<int> m_hot_spot_y;
    QList<int> m_rand_num;

    QList<QList<int>> list_forms;
    QList<QColor> list_colors;

    QList<QList<int>> list_current_forms;
    QList<QColor> list_current_colors;

    int size_cell;
    int figures_count;
};

#endif // FIGURES_MODEL_H
