#include "field.h"



Field::Field(int _rows, int _columns, int _size_cell, QObject *parent) :
    QAbstractListModel(parent)
{
    my_data.insert(color, "ColorData");
    my_data.insert(index, "field_index");
    rows = _rows;
    columns = _columns;
    size_cell = _size_cell;
}


void Field::add(int i, QString _color)
{
    int index = m_intData.size();
    beginInsertRows(QModelIndex(), index, index);
    m_color.append(_color);
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

    case index:
        return m_index.at(_index.row());

    default: return QVariant();

    }

}

QColor Field::getColor(int index) const
{
    return m_color.at(index);
}

void Field::setColor(const int index, const QColor &color)
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

bool Field::check_field(int index, QList<int> form)
{
    int start_figure;

    for (int index_form = 0; index_form < form.size(); index_form++)
        if(form[index_form]) {
            start_figure = index_form;
            break;
        }

    int current_row = index / rows;
    int current_column = index - current_row * rows;
    int current_row_figure =  start_figure / 3;
    int current_column_figure = start_figure - current_row_figure * 3;
    qDebug() << "start";
    int buf_row = current_row;
    int buf_column = current_column;
    int buf_column_figure = current_column_figure;
    qDebug() << current_row << current_column << current_row_figure << current_column_figure;
    for (int row_figure = current_row_figure; row_figure >= 0; row_figure--) {
        for (int column_figure = buf_column_figure; column_figure >= 0; column_figure--) {
            if (buf_column < 0) {
                if (form[row_figure * 3 + column_figure]) {
                    qDebug() << "1out left column and not empty figure:" << buf_row
                             << buf_column
                             << row_figure << column_figure;
                    return false;
                }
                else  {
                    buf_column --;
                    continue;
                }
            }
            if (buf_column > columns - 1) {
                if (form[row_figure * 3 + column_figure]) {
                    qDebug() << "1out right column and not empty figure:" << buf_row
                             << buf_column
                             << row_figure << column_figure;
                    return false;
                }
                else  {
                    buf_column --;
                    continue;
                }
            }
            if (buf_row < 0) {
                if (form[row_figure * 3 + column_figure]) {
                    qDebug() << "1out up row and not empty figure:" << buf_row
                             << buf_column
                             << row_figure << column_figure;
                    return false;
                }
                else  {
                    // buf_row --;
                    continue;
                }
            }

            if (getColor(buf_row * columns + buf_column) == "red")
                if (form[row_figure * 3 + column_figure])
                    return false;
            buf_column --;
        }
        buf_row--;
        buf_column = current_column + current_column_figure;
        buf_column_figure = 0;
    }

    buf_row = current_row;
    buf_column = current_column;
    buf_column_figure = current_column_figure;
    for(int row_figure = current_row_figure; row_figure < 3; row_figure++) {
        for (int column_figure = buf_column_figure; column_figure < 3; column_figure++) {
            if (buf_column < 0) {
                if (form[row_figure * 3 + column_figure]) {
                    qDebug() << "2out left column and not empty figure:" << buf_row
                             << buf_column
                             << row_figure << column_figure;
                    return false;
                }
                else  {
                    buf_column ++;
                    continue;
                }
            }
            if (buf_column > columns - 1) {
                if (form[row_figure * 3 + column_figure]) {
                    qDebug() << "2out right column and not empty figure:" << buf_row
                             << buf_column
                             << row_figure << column_figure;
                    return false;
                }
                else  {
                    buf_column ++;
                    continue;
                }
            }

            if (buf_row > rows - 1) {
                if (form[row_figure * 3 + column_figure]) {
                    qDebug() << "2out down row and not empty figure:" << buf_row
                             << buf_column
                             << row_figure << column_figure;
                    return false;
                }
                else  {
                    // buf_row --;
                    continue;
                }
            }
            if (getColor(buf_row * columns + buf_column) == "red")
                if (form[row_figure * 3 + column_figure])
                    return false;
            buf_column ++;
        }
        buf_row ++;
        buf_column = current_column - current_column_figure;
        buf_column_figure = 0;
    }

    return true;
}

void Field::fill_field(int index, QColor color, QList <int> form)
{

    int start_figure;

    for (int index_form = 0; index_form < form.size(); index_form++)
        if(form[index_form]) {
            start_figure = index_form;
                    break;
        }

    int current_row = index / rows;
    int current_column = index - current_row * rows;
    int current_row_figure =  start_figure / 3;
    int current_column_figure = start_figure - current_row_figure * 3;

    int buf_row = current_row;
    int buf_column = current_column;
    int buf_column_figure = current_column_figure;
    qDebug() << current_row << current_column << current_row_figure << current_column_figure;
    for (int row_figure = current_row_figure; row_figure >= 0; row_figure--) {
        for (int column_figure = buf_column_figure; column_figure >= 0; column_figure--) {
            if (buf_column < 0) {
                buf_column --;
                continue;
            }
            if (buf_column > columns - 1) {
                buf_column --;
                continue;
            }
            if (buf_row < 0) {
                // buf_row --;
                continue;
            }

            int index_cell = buf_row * columns + buf_column;
            if (form[row_figure * 3 + column_figure])
                setColor(index_cell, color);
            buf_column --;
        }
        buf_row--;
        buf_column = current_column + current_column_figure;
        buf_column_figure = 0;
    }

    buf_row = current_row;
    buf_column = current_column;
    buf_column_figure = current_column_figure;
    for(int row_figure = current_row_figure; row_figure < 3; row_figure++) {
        for (int column_figure = buf_column_figure; column_figure < 3; column_figure++) {
            if (buf_column < 0) {
                buf_column ++;
                continue;
            }

            if (buf_column > columns - 1) {
                buf_column ++;
                continue;
            }

            if (buf_row > rows - 1) {
                    continue;
            }
            int index_cell = buf_row * columns + buf_column;
            if (form[row_figure * 3 + column_figure])
                setColor(index_cell, color);
            buf_column ++;
        }
        buf_row ++;
        buf_column = current_column - current_column_figure;
        buf_column_figure = 0;
    }

    if (color == "red")
        check_occupancy_field();
}

void Field::add_list_figure(const QList<char> &value)
{
    list_figure.append(value);
}

void Field::add_info_figure(const QList<int> list_figure)
{
    used_figure.append(list_figure);
}

QList<int> Field::get_info_figure()
{
    return used_figure.last();
}

void Field::edit_list_figure(const QList<char> &value, int index)
{
    list_figure.replace(index, value);
}

void Field::cancel_turn()
{
    qDebug() << "Canсel the turn";
    if (!cells_info.isEmpty()) {
        for(auto cell = cells_info.last().begin(); cell != cells_info.last().end(); cell++) {
            setColor(cell.key(), cell.value());
        }
        cells_info.pop_back();
        if(used_figure.length() != 1)
            used_figure.pop_back();
    }
}

void Field::save_game()
{
    qDebug() << "Save the game";
}

void Field::load_game()
{
    qDebug() << "Load the game";
}

int Field::getSize_cell() const
{
    return size_cell;
}

int Field::getRows() const
{
    return rows;
}

int Field::getColumns() const
{
    return columns;
}

bool Field::check_turns(QList<QList<int>> forms)
{
    for (auto form : forms)
        for (int cell_num=0; cell_num < rows * columns; cell_num++)
            if (check_field(cell_num, form))
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

    return check;
}
