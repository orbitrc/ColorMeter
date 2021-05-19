#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <blusher/blusher.h>

#include "ColorMeter.h"
#include "Preview.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    qmlRegisterType<Preview>("ColorMeter", 1, 0, "Preview");

    ColorMeter colorMeter;

    bl::Application app(argc, argv);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));

    app.engine()->rootContext()->setContextProperty("ColorMeter", &colorMeter);
    app.engine()->load(url);

    return app.exec();
}
