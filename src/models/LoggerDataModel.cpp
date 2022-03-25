#include "LoggerDataModel.h"

LoggerDataModel::LoggerDataModel(QObject *parent)
    : QAbstractListModel{parent}
{
    beginResetModel();
    m_logEntries.clear();

    for (int i=0; i < 3; i++) {
        LogEntry *entry = new LogEntry(this);

        entry->setId(i);
        entry->setDateTime(QDateTime::currentDateTime());

        QString content = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam vitae lorem nec odio mollis ullamcorper nec at enim. Phasellus feugiat, felis nec fringilla sodales, lorem ante tristique eros, id placerat justo libero eget lacus. Mauris nulla est, sollicitudin vitae purus eu, lobortis sodales dui. Duis quis urna id turpis pharetra vulputate et eu odio. Etiam ac feugiat urna. Nunc in volutpat neque, id rutrum diam. Aliquam ultrices lectus vitae lorem fringilla elementum. Mauris ut nunc quis dolor sollicitudin pretium id sit amet risus. Praesent id mollis risus. Morbi consequat vitae est ac hendrerit.";
        entry->setContent(content);
        entry->setPriority(LogEntry::LogPriority::WARNING);
        m_logEntries.append(entry);

    }
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
