#pragma once

#include <QObject>
#include <QDateTime>

class LogEntry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(unsigned int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QDateTime dateTime READ dateTime WRITE setDateTime NOTIFY dateTimeChanged)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(LogPriority priority READ priority WRITE setPriority NOTIFY priorityChanged)

public:
    enum class LogPriority {
        DEBUG,
        INFO,
        WARNING,
        // i know that this is misspeling but ERROR is defined as macro in wingdi.h file
        ERRORR
    };
    Q_ENUM(LogPriority)

    explicit LogEntry(QObject *parent = nullptr);
    LogEntry(unsigned int id, const QDateTime &dateTime, const QString &content, LogPriority priority, QObject *parent = nullptr);

    unsigned int id() const;
    void setId(unsigned int newId);

    const QDateTime &dateTime() const;
    void setDateTime(const QDateTime &newDateTime);

    const QString &content() const;
    void setContent(const QString &newContent);

    LogPriority priority() const;
    void setPriority(LogPriority newPriority);

signals:
    void idChanged();
    void dateTimeChanged();
    void contentChanged();
    void priorityChanged();

private:
    unsigned int m_id;
    QDateTime m_dateTime;
    QString m_content;
    LogPriority m_priority;
};

