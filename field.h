#ifndef FIELD_H
#define FIELD_H

#include <QObject>
#include <QAbstractListModel>
#include <QHash>
#include <QColor>
#include <QDebug>

class Field : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        color,
        index
    };
    explicit Field(int _rows, int _columns, int _size_cell, QObject *parent = nullptr);
    void add(int i, QString _color = "white");
    int rowCount(const QModelIndex &parent) const ;
    QHash<int, QByteArray> roleNames() const ;
    QVariant data(const QModelIndex &index, int role) const;

    void setColor(const int index, const QColor &color);
    QColor getColor(int index) const;
    void clear_row(int row);
    void clear_column(int column);
    bool check_figure(int cell_num, QList<char> figure);
    void check_occupancy_field();
    Q_INVOKABLE bool check_field(int index, QList <int> form);
    Q_INVOKABLE void fill_field(int index, QColor color, QList <int> form);
    Q_INVOKABLE bool check_turns(QList<QList<int>> forms);

    Q_INVOKABLE void add_list_figure(const QList<char> &value);
    Q_INVOKABLE void add_info_figure(const QList<int> list_figure);
    Q_INVOKABLE QList<int> get_info_figure();
    Q_INVOKABLE void edit_list_figure(const QList<char> &value, int index);

    Q_INVOKABLE void cancel_turn();
    Q_INVOKABLE void save_game();
    Q_INVOKABLE void load_game();

    Q_INVOKABLE int getSize_cell() const;

    Q_INVOKABLE int getRows() const;

    Q_INVOKABLE int getColumns() const;

private:
    QHash<int, QByteArray> my_data;
    QList<QColor> m_color;
    QList<int> m_index;
    QList<int> m_intData;

    QList<QList<char>> list_figure;
    QList<QMap<int, QColor>> cells_info;
    QList<QList<int>> used_figure;
    int rows;
    int columns;
    int size_cell;
};

#endif // FIELD_H
