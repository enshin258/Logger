#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/models/LoggerDataModel.h"
#include "src/controllers/ExternalAppsController.h"

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);


    LoggerDataModel *loggerDataModel = new LoggerDataModel(&app);
    ExternalAppsController *externalAppsController = new ExternalAppsController(loggerDataModel, &app);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("loggerDataModel", loggerDataModel);
    engine.rootContext()->setContextProperty("externalAppsController", externalAppsController);

    const QUrl url(u"qrc:/Logger/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
