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
    if (m_externalAppPath == newExternalAppPath)
        return;
    m_externalAppPath = newExternalAppPath;
    emit externalAppPathChanged();
}

void ExternalAppsController::runExternalApp()
{
    QProcess *process = new QProcess(this);

    connect(process, &QProcess::readyReadStandardOutput, this, [this, process](){
        QByteArray output = process->readAllStandardOutput();

        LogEntry *entry = new LogEntry(m_loggerDataModel);
        entry->setId(m_loggerDataModel->rowCount());
        entry->setDateTime(QDateTime::currentDateTime());
        entry->setPriority(LogEntry::LogPriority::DEBUG);
        entry->setContent(output);

        m_loggerDataModel->addLogEntry(entry);
    });

    connect(process, &QProcess::readyReadStandardError, this, [this, process](){

        QByteArray output = process->readAllStandardError();

        LogEntry *entry = new LogEntry(m_loggerDataModel);
        entry->setId(m_loggerDataModel->rowCount());
        entry->setDateTime(QDateTime::currentDateTime());
        entry->setPriority(LogEntry::LogPriority::WARNING);
        entry->setContent(output);

        m_loggerDataModel->addLogEntry(entry);
    });


    QString programPath = m_externalAppPath.remove(0,8);
    qDebug() << "Starting program: " <<programPath;
    process->setCreateProcessArgumentsModifier([] (QProcess::CreateProcessArguments *args)
    {
        args->flags |= CREATE_NEW_CONSOLE;

    });
    process->start(programPath);
}


