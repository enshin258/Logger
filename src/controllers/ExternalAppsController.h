#pragma once

#include <QObject>
#include "QProcess"
#include "../datasets/LogEntry.h"
#include "../models/LoggerDataModel.h"

class ExternalAppsController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool externalAppRunning READ externalAppRunning WRITE setExternalAppRunning NOTIFY externalAppRunningChanged)
    Q_PROPERTY(QString externalAppPath READ externalAppPath WRITE setExternalAppPath NOTIFY externalAppPathChanged)

public:
    ExternalAppsController(LoggerDataModel *loggerDataModel, QObject *parent = nullptr);

    const QString &externalAppPath() const;
    void setExternalAppPath(const QString &newExternalAppPath);

    bool externalAppRunning() const;
    void setExternalAppRunning(bool newExternalAppRunning);

public slots:
    void runExternalApp();
    void stopExternalApp();

signals:
    void externalAppPathChanged();
    void externalAppRunningChanged();

private:
    QString m_externalAppPath = "";
    LoggerDataModel *m_loggerDataModel = nullptr;
    bool m_externalAppRunning = false;
    QProcess *m_externalAppProcess = nullptr;
};

