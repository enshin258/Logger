#pragma once

#include <QObject>
#include <QProcess>
#include "../datasets/LogEntry.h"
#include "../models/LoggerDataModel.h"

/*!
 * \brief The ExternalAppProvider class is responsible for running external applications from which logs are taken
 */
class ExternalAppProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool externalAppRunning READ externalAppRunning WRITE setExternalAppRunning NOTIFY externalAppRunningChanged)
    Q_PROPERTY(QString externalAppPath READ externalAppPath WRITE setExternalAppPath NOTIFY externalAppPathChanged)

public:
    /*!
     * \brief ExternalAppProvider constructs object of ExternalAppProvider class
     * \param loggerDataModel is pointer to LoggerDataModel instance
     * \param parent is pointer to parent QObject
     */
    ExternalAppProvider(LoggerDataModel *loggerDataModel, QObject *parent = nullptr);

    /*!
     * \brief externalAppPath returns external application path
     * \return external application path
     */
    const QString &externalAppPath() const;

    /*!
     * \brief setExternalAppPath sets path to external application
     * \param newExternalAppPath is path to external application
     */
    void setExternalAppPath(const QString &newExternalAppPath);

    /*!
     * \brief externalAppRunning return if external app is currently running
     * \return state of external app
     */
    bool externalAppRunning() const;

    /*!
     * \brief setExternalAppRunning sets state of extrnal app (running or not)
     * \param newExternalAppRunning is state of external app
     */
    void setExternalAppRunning(bool newExternalAppRunning);

public slots:
    /*!
     * \brief runExternalApp run external application
     */
    void runExternalApp();

    /*!
     * \brief stopExternalApp stops external application
     */
    void stopExternalApp();

signals:
    /*!
     * \brief externalAppPathChanged signal is emmited when external app path changes
     */
    void externalAppPathChanged();

    /*!
     * \brief externalAppRunningChanged
     */
    void externalAppRunningChanged();

private:
    QString m_externalAppPath = "";
    LoggerDataModel *m_loggerDataModel = nullptr;
    bool m_externalAppRunning = false;
    QProcess *m_externalAppProcess = nullptr;
};

