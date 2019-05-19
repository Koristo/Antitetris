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
        coor_x,
        coor_y,
        index
    };

    explicit Field(int _rows, int _columns, QObject *parent = nullptr);
    void add(int i, int x, int y, QString _color = "white");
    int rowCount(const QModelIndex &parent) const ;
    QHash<int, QByteArray> roleNames() const ;
    QVariant data(const QModelIndex &index, int role) const;
    void setColor(const int index, const QString &color);
    QColor getColor(int index) const;
    void clear_row(int row);
    void clear_column(int column);
    bool check_figure(int cell_num, QList<char> figure);


    Q_INVOKABLE void check_occupancy_field();
    Q_INVOKABLE bool check_field(int index);
    Q_INVOKABLE void fill_field(int index, QString color);
    Q_INVOKABLE void add_list_figure(const QList<char> &value);
    Q_INVOKABLE void edit_list_figure(const QList<char> &value, int index);
    Q_INVOKABLE bool check_turns();

private:
    QHash<int, QByteArray> my_data;
    QList<QString> m_color;
    QList<int> m_coor_x;
    QList<int> m_coor_y;
    QList<int> m_index;
    QList<int> m_intData;
    QList<QList<char>> list_figure;
    int rows;
    int columns;

//private slots:
//    static void add_in_list(QList<char> form);

};

#endif // FIELD_H
