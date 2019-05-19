#include "field.h"



Field::Field(int _rows, int _columns, QObject *parent) :
    QAbstractListModel(parent)
{
    my_data.insert(color, "ColorData");
    my_data.insert(coor_x, "field_x");
    my_data.insert(coor_y, "field_y");
    my_data.insert(index, "field_index");
    rows = _rows;
    columns = _columns;
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
   QModelIndex mod_index = createIndex(index, 0);
   emit dataChanged(mod_index, mod_index, QVector<int>() << 0);
}

void Field::clear_row(int row)
{
    for (int index = row; index<row + rows; index++)
        setColor(index, "white");
}

void Field::clear_column(int column)
{
    for (int index = column; index<rows * columns; index+=columns)
        setColor(index, "white");
}

void Field::check_occupancy_field()
{
    QList<int> filled_columns;
    QList<int> filled_rows;

    for(int col_num = 0; col_num<columns; col_num++) {
        bool check = true;
        for (int index_col = col_num; index_col<25; index_col+=5)
            if (getColor(index_col) != "red") {
                check = false;
                break;
            }
        if (check)
            filled_columns.append(col_num);

    }

    for(int row_num = 0; row_num<rows * columns; row_num+=rows) {

        bool check = true;
        for(int index_row = row_num; index_row<row_num + rows; index_row++)
            if (getColor(index_row) != "red") {
                check = false;
                break;
            }
        if (check)
            filled_rows.append(row_num);
    }

    for(auto row : filled_rows)
        clear_row(row);

    for(auto column : filled_columns)
        clear_column(column);
}

bool Field::check_field(int index)
{
    int current_index = index;
    bool check = true;

        if (getColor(current_index) == QColor("red"))
            check = false;
        else
            for (auto num : list_figure[index])
                switch(num) {
                    case 'u': {
                        if (current_index >= 0 && current_index <=4)
                            return false;
                        if (getColor(current_index - 5) == "red")
                            return false;
                        else current_index -= 5;
                        break;
                    }
                    case 'r': {
                        if (current_index == 4 || current_index == 9 || current_index == 14
                                || current_index == 19 || current_index == 24)
                            return false;
                        if (getColor(current_index + 1) == "red")
                            return false;
                        else current_index += 1;
                        break;
                    }
                    case 'd': {
                        if (current_index >= 20 && current_index <=24)
                            return false;
                        if (getColor(current_index + 5) == "red")
                            return false;
                        else current_index += 5;
                        break;
                    }
                    case 'l': {
                        if (current_index % 5 == 0)
                            return false;
                        if (getColor(current_index - 1) == "red")
                            return false;
                        else current_index -= 1;
                        break;
                    }

                }

    qDebug() << check;
    return check;
}

void Field::fill_field(int index, QString color)
{
    int current_index = index;
    setColor(current_index, color);
    for (auto num : list_figure[index])
        switch(num) {
            case 'u': {
                current_index -= 5;
                setColor(current_index, color);
                break;
            }
            case 'r': {
                current_index += 1;
                setColor(current_index, color);
                break;
            }
            case 'd': {
                current_index += 5;
                setColor(current_index, color);
                break;
            }
            case 'l': {
                current_index -= 1;
                setColor(current_index, color);
                break;
            }
        }
    if (color == "red")
        check_occupancy_field();
}

void Field::add_list_figure(const QList<char> &value)
{
    list_figure.append(value);
}

void Field::edit_list_figure(const QList<char> &value, int index)
{
    list_figure.replace(index, value);
}

bool Field::check_turns()
{
    qDebug() << "hello";
    for (auto figure : list_figure)
        for (int cell_num=0; cell_num < rows * columns; cell_num++)
            if (check_figure(cell_num, figure))
                return true;

    return false;
}

bool Field::check_figure(int cell_num, QList<char> figure) {
    int current_index = cell_num;
    bool check = true;

        if (getColor(current_index) == QColor("red"))
            check = false;
        else
            for (auto num : figure)
                switch(num) {
                    case 'u': {
                        if (current_index >= 0 && current_index <=4)
                            return false;
                        if (getColor(current_index - 5) == "red")
                            return false;
                        else current_index -= 5;
                        break;
                    }
                    case 'r': {
                        if (current_index == 4 || current_index == 9 || current_index == 14
                                || current_index == 19 || current_index == 24)
                            return false;
                        if (getColor(current_index + 1) == "red")
                            return false;
                        else current_index += 1;
                        break;
                    }
                    case 'd': {
                        if (current_index >= 20 && current_index <=24)
                            return false;
                        if (getColor(current_index + 5) == "red")
                            return false;
                        else current_index += 5;
                        break;
                    }
                    case 'l': {
                        if (current_index % 5 == 0)
                            return false;
                        if (getColor(current_index - 1) == "red")
                            return false;
                        else current_index -= 1;
                        break;
                    }
                }

    qDebug() << check;
    return check;
}
