#include "figuresModel.h"

FiguresModel::FiguresModel(int _size_cell, int _figures_count, QObject *parent) :
    QAbstractListModel(parent)
{
    my_data.insert(color, "ColorData");
    my_data.insert(index, "FigIndex");
    my_data.insert(rand_num, "RandNum");
    my_data.insert(hotspot_x, "HotSpotX");
    my_data.insert(hotspot_y, "HotSpotY");

    size_cell = _size_cell;
    figures_count = _figures_count;
    srand(time(0));
}

void FiguresModel::add(int _index)
 {

    int index = i_figure.size();

    int rand_num = rand() % list_forms.size();
    list_current_colors.append(list_colors[rand_num]);
    list_current_forms.append(list_forms[rand_num]);
    int x = -1;
    int y = -1;

    for(int i_cell = 0; i_cell < 3; i_cell++) {
        if (x != -1)
            break;
        for(int j_cell = 0; j_cell < 3; j_cell++) {
            if (list_current_forms[index][i_cell + j_cell * 3] == 1) {
                x = i_cell * size_cell;
                y = j_cell * size_cell;
                break;
            }
        }
    }
    beginInsertRows(QModelIndex(), index, index);
    m_rand_num.append(rand_num);
    m_color.append(list_colors[rand_num]);
    m_hot_spot_x.append(x);
    m_hot_spot_y.append(y);
    i_figure.append(_index);

    endInsertRows();
 }

int FiguresModel::rowCount(const QModelIndex &parent) const
{
    return i_figure.count();
}

QVariant FiguresModel::data(const QModelIndex &_index, int role) const
{

    switch (role) {
    case color:
        return m_color.at(_index.row());

    case index:
        return i_figure.at(_index.row());

    case hotspot_x:
        return m_hot_spot_x.at(_index.row());

    case hotspot_y:
        return m_hot_spot_y.at(_index.row());

    case rand_num:
        return m_rand_num.at(_index.row());
    default: return QVariant();

    }

}

QHash<int, QByteArray> FiguresModel::roleNames() const
{
    return my_data;
}

void FiguresModel::load_figures(const QString json)
{
    QFile loadFile(json);

    if (!loadFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
              qDebug("Couldn't open file");
              return;
          }
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject data = loadDoc.object();

    if(data.contains("figures")) {
        QJsonArray figures = data["figures"].toArray();
        qDebug() << "Size: " << figures.size();
        for (int figure_index = 0; figure_index < figures.size(); figure_index++) {
            QJsonObject figure_object = figures[figure_index].toObject();

            QJsonArray form = figure_object["form"].toArray();
            QList<int> buf_form;
            for (int form_index = 0; form_index < form.size(); form_index ++) {
                buf_form.append(form[form_index].toInt());
            }
            list_forms.append(buf_form);

            QString color_object = figure_object["color"].toString();
            list_colors.append(color_object);
        }
    }
    qDebug() << list_forms;
    qDebug() << list_colors;
    loadFile.close();
}

void FiguresModel::init_figures()
{
    for (int i_figure = 0; i_figure < figures_count; i_figure++) {
        int rand = qrand() % list_forms.size();
        list_current_forms.append(list_forms[rand]);
        list_current_colors.append(list_colors[rand]);
    }
}


QList<int> FiguresModel::change_form(int index) {
    int new_rand_num = rand() % list_forms.size();
    m_rand_num.replace(index, new_rand_num);
    list_current_forms.replace(index, list_forms[new_rand_num]);

    int x = -1;
    int y = -1;

    for(int i_cell = 0; i_cell < 3; i_cell++) {
        if (x != -1)
            break;
        for(int j_cell = 0; j_cell < 3; j_cell++) {
            if (list_current_forms[index][i_cell + j_cell * 3] == 1) {
                x = i_cell * size_cell;
                y = j_cell * size_cell;
                break;
            }
        }
    }
    m_hot_spot_x.replace(index, x);
    m_hot_spot_y.replace(index, y);
    return list_forms[new_rand_num];
}

QColor FiguresModel::change_color(int index) {
    qDebug() << "Change color: " << index;
    int new_rand_num = m_rand_num.at(index);
    list_current_colors.replace(index, list_colors[new_rand_num]);
    return list_colors[new_rand_num];
}

int FiguresModel::getSize_cell()
{
    return size_cell;
}

int FiguresModel::get_index_figure(int index) const
{
    return m_rand_num.at(index);
}

int FiguresModel::get_x(int index) const
{
    return m_hot_spot_x.at(index);
}

int FiguresModel::get_y(int index) const
{
    return m_hot_spot_y.at(index);
}

QList<QList<int> > FiguresModel::get_forms() const
{
    return list_current_forms;
}

int FiguresModel::getFigures_count()
{
    return figures_count;
}

QList<int> FiguresModel::get_current_form(int index) const
{
    return list_current_forms[index];
}

QString FiguresModel::get_current_color(int index) const
{
    return list_current_colors[index].name();
}
