#include "ExternalAppProvider.h"
#include "Windows.h"

ExternalAppProvider::ExternalAppProvider(LoggerDataModel *loggerDataModel, QObject *parent) : QObject(parent),
    m_loggerDataModel(loggerDataModel)
{}

const QString &ExternalAppProvider::externalAppPath() const
{
    return m_externalAppPath;
}

void ExternalAppProvider::setExternalAppPath(const QString &newExternalAppPath)
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

void ExternalAppProvider::runExternalApp()
{
    m_externalAppProcess = new QProcess(this);

    connect(m_externalAppProcess, &QProcess::readyReadStandardOutput, this, [this](){
        QByteArray output = m_externalAppProcess->readAllStandardOutput();

        LogEntry *entry = new LogEntry(m_loggerDataModel);
        entry->setId(m_loggerDataModel->rowCount());
        entry->setDateTime(QDateTime::currentDateTime());
        entry->setPriority(LogEntry::LogPriority::DEBUG_PRIORITY);
        entry->setContent(output);

        m_loggerDataModel->addLogEntry(entry);
    });

    connect(m_externalAppProcess, &QProcess::readyReadStandardError, this, [this](){

        QByteArray output = m_externalAppProcess->readAllStandardError();

        LogEntry *entry = new LogEntry(m_loggerDataModel);
        entry->setId(m_loggerDataModel->rowCount());
        entry->setDateTime(QDateTime::currentDateTime());
        entry->setPriority(LogEntry::LogPriority::ERROR_PRIORITY);
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

void ExternalAppProvider::stopExternalApp()
{
    m_externalAppProcess->kill();
    setExternalAppRunning(false);
}

bool ExternalAppProvider::externalAppRunning() const
{
    return m_externalAppRunning;
}

void ExternalAppProvider::setExternalAppRunning(bool newExternalAppRunning)
{
    if (m_externalAppRunning == newExternalAppRunning)
        return;
    m_externalAppRunning = newExternalAppRunning;
    emit externalAppRunningChanged();
}
