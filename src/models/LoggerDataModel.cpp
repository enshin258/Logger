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
    entry1->setContent("Lorem ipsum dolor sit amet, consectetur adipiscing elit."
                       " Quisque sit amet luctus sem. Nullam id pharetra mi, non pellentesque dui."
                       " Quisque in nunc ut turpis iaculis vestibulum. Etiam malesuada justo ut nulla tincidunt maximus."
                       " Quisque tincidunt lacus nulla, eu porttitor tellus placerat vel."
                       " Integer consequat turpis id eros egestas maximus.");
    entry1->setPriority(LogEntry::LogPriority::DEBUG);

    entry2->setId(2);
    entry2->setDateTime(QDateTime::fromMSecsSinceEpoch(200000));
    entry2->setContent("Main method started"
                       "Exception in thread main java.lang.StackOverflowError"
                       "at com.program.stackoverflow.Factorial.factorial(Factorial.java:9)"
                       "at com.program.stackoverflow.Factorial.factorial(Factorial.java:9)"
                       "at com.program.stackoverflow.Factorial.factorial(Factorial.java:9)");
    entry2->setPriority(LogEntry::LogPriority::ERRORR);

    entry3->setId(3);
    entry3->setDateTime(QDateTime::fromMSecsSinceEpoch(300000));
    entry3->setContent("AAA");
    entry3->setPriority(LogEntry::LogPriority::INFO);

    entry4->setId(4);
    entry4->setDateTime(QDateTime::fromMSecsSinceEpoch(400000));
    entry4->setContent("TEST");
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
            return logEntry->dateTime().toString("dd.MM.yyyy - hh:mm:ss.z");
        case LoggerDataModel::ContentRole:
            return logEntry->content();
        case LoggerDataModel::PriorityRole:
            switch(logEntry->priority()) {
            case LogEntry::LogPriority::DEBUG: {
                return "DEBUG";
            }
            case LogEntry::LogPriority::ERRORR: {
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

void LoggerDataModel::clearLogs()
{
    beginResetModel();
    m_logEntries.clear();
    endResetModel();
}

void LoggerDataModel::addLogEntry(LogEntry *logEntry)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    qDebug() << "ADDING LOG ENTRY WITH CONTENT: " << logEntry->content();

    m_logEntries.append(logEntry);
    endInsertRows();
}

LogEntry* LoggerDataModel::getLogEntry(int index)
{
    return m_logEntries[index];
}
