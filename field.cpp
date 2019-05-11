#include "field.h"

Field::Field(QObject *parent) :
    QAbstractListModel(parent)
{
    my_data.insert(color, "ColorData");
    my_data.insert(coor_x, "field_x");
    my_data.insert(coor_y, "field_y");
    my_data.insert(index, "field_index");
}

void Field::add(int i, int x, int y, QString _color)
{
    int index = m_intData.size();
    beginInsertRows(QModelIndex(), index, index);
    m_color.append(_color);
    m_coor_x.append(x);
    m_coor_y.append(y);
    m_intData.append(i);
    m_index.append(index);
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

QVariant Field::data(const QModelIndex &_index, int role) const
{
    switch (role) {
    case color:
        return m_color.at(_index.row());

    case coor_x:
        return m_coor_x.at(_index.row());

    case coor_y:
        return m_coor_y.at(_index.row());

    case index:
        return m_index.at(_index.row());

    default: return QVariant();

    }

}

QColor Field::getColor(int index) const
{
    return m_color.at(index);
}

void Field::setColor(const int index, const QString &color)
{
   m_color.replace(index, color);
}
