#include "figure1.h"
#include "figure2.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QDebug>
#include <QQmlContext>
#include "field.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Figure1>("Figure_1", 1, 0, "Fig_1");
    qmlRegisterType<Figure2>("Figure_2", 1, 0, "Fig_2");

    QQmlApplicationEngine engine;
    int rows = 5;
    int columns = 5;
    Field *my_field = new Field(rows, columns, &engine);
    for(int i=0; i<rows; i++)
        for(int j=0; j<columns; j++)
            my_field->add(i, 100 * i, 100 * j);


    engine.rootContext()->setContextProperty("MyField", my_field);
    QQuickView view(&engine, nullptr);
    view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    view.show();

    return app.exec();
}
