#include "LoggerDataModel.h"

LoggerDataModel::LoggerDataModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this]() {

        LogEntry *entry = new LogEntry(this);

        entry->setId(this->rowCount());
        entry->setDateTime(QDateTime::currentDateTime());

        int random = QRandomGenerator::global()->bounded(0, 4);

        switch(random) {
        case 0:
            entry->setContent("Normal debug message");
            entry->setPriority(LogEntry::LogPriority::DEBUG_PRIORITY);
            break;
        case 1:
            entry->setContent("Some information from the work of the program");
            entry->setPriority(LogEntry::LogPriority::INFO_PRIORITY);
            break;
        case 2:
            entry->setContent("Oh, something went wrong, warning!");
            entry->setPriority(LogEntry::LogPriority::WARNING_PRIORITY);
            break;
        case 3:
            entry->setContent("CRITICAL ERROR!!!");
            entry->setPriority(LogEntry::LogPriority::ERROR_PRIORITY);
            break;
        }

        addLogEntry(entry);
    });
}

int LoggerDataModel::rowCount(const QModelIndex &parent) const
{    
    if (!parent.isValid()) {
        return m_logEntries.getItemsCount();
    }
    return 0;
}

int LoggerDataModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
       return 1;
    }
    return 0;
}

QVariant LoggerDataModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.row() < m_logEntries.getItemsCount()) {
        const auto logEntry = m_logEntries.getItemAtIndex(index.row());

        switch ((Roles) role) {
        case LoggerDataModel::IdRole:
            return logEntry->id();
        case LoggerDataModel::DateTimeRole:
            return logEntry->dateTime().toString("dd.MM.yyyy-hh:mm:ss.z");
        case LoggerDataModel::ContentRole:
            return logEntry->content();
        case LoggerDataModel::PriorityRole:
            switch(logEntry->priority()) {
            case LogEntry::LogPriority::DEBUG_PRIORITY: {
                return "DEBUG";
            }
            case LogEntry::LogPriority::ERROR_PRIORITY: {
                return "ERROR";
            }
            case LogEntry::LogPriority::INFO_PRIORITY: {
                return "INFO";
            }
            case LogEntry::LogPriority::WARNING_PRIORITY: {
                return "WARNING";
            }
            }
        }
    }
    return {};
}

QHash<int, QByteArray> LoggerDataModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[DateTimeRole] = "dateTime";
    roles[ContentRole] = "content";
    roles[PriorityRole] = "priority";

    return roles;
}

void LoggerDataModel::addLogEntry(LogEntry *logEntry)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_logEntries.appendItemToVector(logEntry);
    endInsertRows();
}

LogEntry* LoggerDataModel::getLogEntry(int index)
{
    return m_logEntries.getItemAtIndex(index);
}

void LoggerDataModel::startSimulation()
{
    m_timer->start(200);
}

void LoggerDataModel::stopSimulation()
{
    m_timer->stop();
}
