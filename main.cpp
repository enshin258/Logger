#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/models/LoggerDataModel.h"
#include "src/models/LoggerDataSortFilterProxyModel.h"
#include "src/controllers/ExternalAppsController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    LoggerDataModel *loggerDataModel = new LoggerDataModel(&app);
    LoggerDataSortFilterProxyModel *loggerDataSortFilterProxtModel = new LoggerDataSortFilterProxyModel(&app);
    loggerDataSortFilterProxtModel->setSourceModel(loggerDataModel);
    loggerDataSortFilterProxtModel->setSortRole(LoggerDataModel::IdRole);
    loggerDataSortFilterProxtModel->sort(0, Qt::AscendingOrder);

    ExternalAppsController *externalAppsController = new ExternalAppsController(loggerDataModel, &app);

    QQmlApplicationEngine engine;


    qmlRegisterType<LoggerDataModel>("logger.extra",1, 0, "LoggerDataModel");

    engine.rootContext()->setContextProperty("loggerDataModel", loggerDataSortFilterProxtModel);
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
