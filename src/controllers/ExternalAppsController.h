#pragma once

#include <QObject>
#include "QProcess"
#include "../datasets/LogEntry.h"
#include "../models/LoggerDataModel.h"

class ExternalAppsController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString externalAppPath READ externalAppPath WRITE setExternalAppPath NOTIFY externalAppPathChanged)

public:
    ExternalAppsController(LoggerDataModel *loggerDataModel, QObject *parent = nullptr);

    const QString &externalAppPath() const;
    void setExternalAppPath(const QString &newExternalAppPath);

public slots:
    void runExternalApp();

signals:
    void externalAppPathChanged();

private:
    QString m_externalAppPath;
    LoggerDataModel *m_loggerDataModel = nullptr;

};

