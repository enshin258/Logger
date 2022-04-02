#include "ExternalAppsController.h"
#include "Windows.h"

ExternalAppsController::ExternalAppsController(LoggerDataModel *loggerDataModel, QObject *parent) : QObject(parent),
    m_loggerDataModel(loggerDataModel)
{}

const QString &ExternalAppsController::externalAppPath() const
{
    return m_externalAppPath;
}

void ExternalAppsController::setExternalAppPath(const QString &newExternalAppPath)
{
    if (m_externalAppPath == newExternalAppPath) {
        return;
    }

    m_externalAppPath = newExternalAppPath;
    emit externalAppPathChanged();

    if (m_externalAppRunning) {
        stopExternalApp();
    }
}

void ExternalAppsController::runExternalApp()
{
    m_externalAppProcess = new QProcess(this);

    connect(m_externalAppProcess, &QProcess::readyReadStandardOutput, this, [this](){
        QByteArray output = m_externalAppProcess->readAllStandardOutput();

        LogEntry *entry = new LogEntry(m_loggerDataModel);
        entry->setId(m_loggerDataModel->rowCount());
        entry->setDateTime(QDateTime::currentDateTime());
        entry->setPriority(LogEntry::LogPriority::DEBUG);
        entry->setContent(output);

        m_loggerDataModel->addLogEntry(entry);
    });

    connect(m_externalAppProcess, &QProcess::readyReadStandardError, this, [this](){

        QByteArray output = m_externalAppProcess->readAllStandardError();

        LogEntry *entry = new LogEntry(m_loggerDataModel);
        entry->setId(m_loggerDataModel->rowCount());
        entry->setDateTime(QDateTime::currentDateTime());
        entry->setPriority(LogEntry::LogPriority::ERRORR);
        entry->setContent(output);

        m_loggerDataModel->addLogEntry(entry);
    });


    connect(m_externalAppProcess, &QProcess::finished, this, [this](){
        setExternalAppRunning(false);
    });


    qDebug() << "Starting program: " <<m_externalAppPath;
    m_externalAppProcess->setCreateProcessArgumentsModifier([] (QProcess::CreateProcessArguments *args)
    {
        args->flags |= CREATE_NEW_CONSOLE;

    });
    m_externalAppProcess->start(m_externalAppPath);
    setExternalAppRunning(true);
}

void ExternalAppsController::stopExternalApp()
{
    m_externalAppProcess->kill();
    setExternalAppRunning(false);
}

bool ExternalAppsController::externalAppRunning() const
{
    return m_externalAppRunning;
}

void ExternalAppsController::setExternalAppRunning(bool newExternalAppRunning)
{
    if (m_externalAppRunning == newExternalAppRunning)
        return;
    m_externalAppRunning = newExternalAppRunning;
    emit externalAppRunningChanged();
}
