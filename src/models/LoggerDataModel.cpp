#include "LoggerDataModel.h"

LoggerDataModel::LoggerDataModel(QObject *parent)
    : QAbstractListModel{parent}
{
    beginResetModel();
    m_logEntries.clear();

    LogEntry *entry1 = new LogEntry(this);
    LogEntry *entry2 = new LogEntry(this);
    LogEntry *entry3 = new LogEntry(this);
    LogEntry *entry4 = new LogEntry(this);

    entry1->setId(1);
    entry1->setDateTime(QDateTime::fromMSecsSinceEpoch(100000));
    entry1->setContent("AAA");
    entry1->setPriority(LogEntry::LogPriority::DEBUG);

    entry2->setId(2);
    entry2->setDateTime(QDateTime::fromMSecsSinceEpoch(200000));
    entry2->setContent("BBB");
    entry2->setPriority(LogEntry::LogPriority::ERROR);

    entry3->setId(3);
    entry3->setDateTime(QDateTime::fromMSecsSinceEpoch(300000));
    entry3->setContent("CCC");
    entry3->setPriority(LogEntry::LogPriority::INFO);

    entry4->setId(4);
    entry4->setDateTime(QDateTime::fromMSecsSinceEpoch(400000));
    entry4->setContent("DDD");
    entry4->setPriority(LogEntry::LogPriority::WARNING);

    m_logEntries.append(entry1);
    m_logEntries.append(entry2);
    m_logEntries.append(entry3);
    m_logEntries.append(entry4);

    endResetModel();
}

LoggerDataModel::~LoggerDataModel()
{
    m_logEntries.clear();
}

int LoggerDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_logEntries.length();
}

int LoggerDataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}

QVariant LoggerDataModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.row() < m_logEntries.length()) {
        const auto &logEntry = m_logEntries[index.row()];

        switch ((Roles) role) {
        case LoggerDataModel::IdRole:
            return logEntry->id();
        case LoggerDataModel::DateTimeRole:
            return logEntry->dateTime();
        case LoggerDataModel::ContentRole:
            return logEntry->content();
        case LoggerDataModel::PriorityRole:
            switch(logEntry->priority()) {
            case LogEntry::LogPriority::DEBUG: {
                return "DEBUG";
            }
            case LogEntry::LogPriority::ERROR: {
                return "ERROR";
            }
            case LogEntry::LogPriority::INFO: {
                return "INFO";
            }
            case LogEntry::LogPriority::WARNING: {
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
    qDebug() << "ADDING LOG ENTRY WITH CONTENT: " << logEntry->content();

    m_logEntries.append(logEntry);
    endInsertRows();
}
