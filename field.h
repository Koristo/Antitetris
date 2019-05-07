#ifndef FIELD_H
#define FIELD_H

#include <QObject>
#include <QAbstractListModel>
#include <QHash>
#include <QColor>

class Field : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        color,
        coor_x,
        coor_y
    };

    explicit Field(QObject *parent = nullptr);
    Q_INVOKABLE void add(int i, int x, int y, QColor _color = "white");
    int rowCount(const QModelIndex &parent) const ;
    QHash<int, QByteArray> roleNames() const ;
    QVariant data(const QModelIndex &index, int role) const;

private:
    QHash<int, QByteArray> my_data;
    QList<QColor> m_color;
    QList<int> m_coor_x;
    QList<int> m_coor_y;
    QList<int> m_intData;
signals:

};

#endif // FIELD_H
