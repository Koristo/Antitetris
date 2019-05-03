#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QDebug>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQuickView view(&engine, nullptr);
    view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    view.show();

    return app.exec();
}
