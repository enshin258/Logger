#include <QGuiApplication>
#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/models/LoggerDataModel.h"
#include "src/models/LoggerDataSortFilterProxyModel.h"
#include "src/providers/ExternalAppProvider.h"
#include "src/controllers/FileController.h"
#include "src/controllers/NetworkController.h"
#include "src/controllers/DatabaseController.h"

#include <Windows.h>

int main(int argc, char *argv[])
{
    if (argc > 2 && strcmp(argv[1], "-c")) {
        qDebug() << "\n--RUNNING APP ON CONSOLE---\n";

        QCoreApplication consoleApp(argc, argv);

        LoggerDataModel *loggerDataModel = new LoggerDataModel(&consoleApp);
        LoggerDataSortFilterProxyModel *loggerDataSortFilterProxtModel = new LoggerDataSortFilterProxyModel(&consoleApp);
        loggerDataSortFilterProxtModel->setSourceModel(loggerDataModel);
        loggerDataSortFilterProxtModel->setSortRole(LoggerDataModel::IdRole);
        loggerDataSortFilterProxtModel->sort(0, Qt::AscendingOrder);

        ExternalAppProvider *externalAppProvider = new ExternalAppProvider(loggerDataModel, &consoleApp);

        externalAppProvider->setExternalAppPath(argv[2]);
        externalAppProvider->runExternalApp();

        FileController *fileController = new FileController(loggerDataModel, &consoleApp);
        fileController->openFileToSave();

        NetworkController *networkController = new NetworkController(loggerDataModel, &consoleApp);
        networkController->connectToHost();

        DatabaseController *dataBaseController = new DatabaseController(loggerDataModel, &consoleApp);
        dataBaseController->initDatabase();

        return consoleApp.exec();
    } else {
        qDebug() << "\n--RUNNING APP WITH GUI---\n";

        QGuiApplication guiApp(argc, argv);

        LoggerDataModel *loggerDataModel = new LoggerDataModel(&guiApp);
        LoggerDataSortFilterProxyModel *loggerDataSortFilterProxtModel = new LoggerDataSortFilterProxyModel(&guiApp);
        loggerDataSortFilterProxtModel->setSourceModel(loggerDataModel);
        loggerDataSortFilterProxtModel->setSortRole(LoggerDataModel::IdRole);
        loggerDataSortFilterProxtModel->sort(0, Qt::AscendingOrder);

        ExternalAppProvider *externalAppProvider = new ExternalAppProvider(loggerDataModel, &guiApp);

        FileController *fileController = new FileController(loggerDataModel, &guiApp);
        NetworkController *networkController = new NetworkController(loggerDataModel, &guiApp);
        DatabaseController *dataBaseController = new DatabaseController(loggerDataModel, &guiApp);

        QQmlApplicationEngine engine;

        qmlRegisterType<LoggerDataModel>("logger.extra",1, 0, "LoggerDataModel");

        engine.rootContext()->setContextProperty("loggerDataModelOriginal", loggerDataModel);
        engine.rootContext()->setContextProperty("loggerDataModel", loggerDataSortFilterProxtModel);

        engine.rootContext()->setContextProperty("externalAppProvider", externalAppProvider);
        engine.rootContext()->setContextProperty("fileController", fileController);
        engine.rootContext()->setContextProperty("networkController", networkController);
        engine.rootContext()->setContextProperty("databaseController", dataBaseController);


        const QUrl url(u"qrc:/Logger/main.qml"_qs);
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &guiApp, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
        engine.load(url);

        return guiApp.exec();
    }
}
