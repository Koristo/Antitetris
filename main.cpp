#include "figure1.h"
#include "figure2.h"
#include "figure3.h"
#include "field.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QDebug>
#include <QQmlContext>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Figure1>("Figure_1", 1, 0, "Fig_1");
    qmlRegisterType<Figure2>("Figure_2", 1, 0, "Fig_2");
    qmlRegisterType<Figure3>("Figure_3", 1, 0, "Fig_3");

    qRegisterMetaType<QList<char>>("char_list");

    QQmlApplicationEngine engine;
    int rows = 5;
    int columns = 5;
    Field *my_field = new Field(rows, columns, &engine);
    for(int i=0; i<rows; i++)
        for(int j=0; j<columns; j++)
            my_field->add(i, 100 * i, 100 * j);


    engine.rootContext()->setContextProperty("MyField", my_field);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
