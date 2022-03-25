#include "LogEntry.h"

LogEntry::LogEntry(QObject *parent)
    : QObject{parent}
{

}


LogEntry::LogEntry(unsigned int id, const QDateTime &dateTime, const QString &content, LogEntry::LogPriority priority, QObject *parent) : QObject(parent),
    m_id(id),
    m_dateTime(dateTime),
    m_content(content),
    m_priority(priority)
{}


unsigned int LogEntry::id() const
{
    return m_id;
}

void LogEntry::setId(unsigned int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

const QDateTime &LogEntry::dateTime() const
{
    return m_dateTime;
}

void LogEntry::setDateTime(const QDateTime &newDateTime)
{
    if (m_dateTime == newDateTime)
        return;
    m_dateTime = newDateTime;
    emit dateTimeChanged();
}

const QString &LogEntry::content() const
{
    return m_content;
}

void LogEntry::setContent(const QString &newContent)
{
    if (m_content == newContent)
        return;
    m_content = newContent;
    emit contentChanged();
}

LogEntry::LogPriority LogEntry::priority() const
{
    return m_priority;
}

void LogEntry::setPriority(LogPriority newPriority)
{
    if (m_priority == newPriority)
        return;
    m_priority = newPriority;
    emit priorityChanged();
}

