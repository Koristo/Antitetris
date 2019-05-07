#include "field.h"

Field::Field(QObject *parent) :
    QAbstractListModel(parent)
{
    my_data.insert(color, "ColorData");
    my_data.insert(coor_x, "field_x");
    my_data.insert(coor_y, "field_y");
}

void Field::add(int i, int x, int y, QColor _color)
{
    beginInsertRows(QModelIndex(), m_intData.size(), m_intData.size());
    m_color.append(_color);
    m_coor_x.append(x);
    m_coor_y.append(y);
    m_intData.append(i);
    endInsertRows();
}

int Field::rowCount(const QModelIndex &parent) const
{
    return m_intData.count();
}

QHash<int, QByteArray> Field::roleNames() const
{
    return my_data;
}

QVariant Field::data(const QModelIndex &index, int role) const
{
    if (role == color) {
        return m_color.at(index.row());
    }
    else {
        if(role == coor_x)
            return m_coor_x.at(index.row());
        else {
            if(role == coor_y)
                return m_coor_y.at(index.row());
        }
    }

    return QVariant();
}
