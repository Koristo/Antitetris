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
    Q_INVOKABLE void check_occupancy_field();
    Q_INVOKABLE bool check_field(int index, QList<char> form);
    Q_INVOKABLE void fill_field(int index, QString color, QList<char> form);

private:
    QHash<int, QByteArray> my_data;
    QList<QString> m_color;
    QList<int> m_coor_x;
    QList<int> m_coor_y;
    QList<int> m_index;
    QList<int> m_intData;
    int rows;
    int columns;
signals:

};

#endif // FIELD_H
