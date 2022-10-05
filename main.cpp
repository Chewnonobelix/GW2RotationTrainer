#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "rotationhandler.h"
#include "dataprovider.h"

//#include "buildeditor.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    qmlRegisterType<RotationHandler>("com.chewnonobelix.gw2", 1, 0, "GW2RotationHandler");
//    qmlRegisterType<BuildEditorData>("com.chewnonobelix.gw2", 1, 0, "GW2BuildEditor");

    DataProvider dp;
    QObject::connect(&dp, &DataProvider::dataObjectReady, [] (auto obj) {
       qDebug()<<obj;
       QFile f("test.json");
       f.open(QIODevice::WriteOnly);
       QJsonDocument doc(obj);
       f.write(doc.toJson());
       f.close();
    });
    dp.request("https://api.guildwars2.com/v2/professions/Engineer");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
