#include "figure.h"
#include "field.h"
#include "figuresModel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QDebug>
#include <QQmlContext>
#include <QDir>


int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Figure>("Figure", 1, 0, "Figure");

    qRegisterMetaType<QList<char>>("Qlist<char>");
    qRegisterMetaType<QList<int>>("Qlist<int>");
    qRegisterMetaType<QList<QList<int>>>("<QList<int>1");
    qRegisterMetaType<QColor>("QColor");
    qRegisterMetaType<QList<QList<int>>>("QList<QList<int>>");

    QQmlApplicationEngine engine;
    int rows = 5;
    int columns = 5;
    int size_cell = 100;
    int figures_count = 3;
    Field *my_field = new Field(rows, columns, size_cell, &engine);
    for(int i=0; i<rows; i++)
        for(int j=0; j<columns; j++)
            my_field->add(i);

    FiguresModel *figure_model = new FiguresModel(size_cell / 2, figures_count);
    QDir dir = QDir::currentPath();
    dir.cd("..");
    dir.cd("./Antitetris/JSON");
    QString path = dir.path() + "/figures.json";
    qDebug() << path;
    figure_model->load_figures(path);
    for(int fig_num = 0; fig_num < figure_model->getFigures_count(); fig_num++) {
        figure_model->add(fig_num);
    }

    engine.rootContext()->setContextProperty("FiguresField", figure_model);
    engine.rootContext()->setContextProperty("MyField", my_field);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
