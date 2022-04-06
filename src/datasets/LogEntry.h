#pragma once

#include <QObject>
#include <QDateTime>

/*!
 * \brief The LogEntry class is responsible for storing single log data
 */
class LogEntry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(unsigned int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QDateTime dateTime READ dateTime WRITE setDateTime NOTIFY dateTimeChanged)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(LogPriority priority READ priority WRITE setPriority NOTIFY priorityChanged)

public:
    /*!
     * \brief The LogPriority enum is an enumeration specifying the log priority
     */
    enum class LogPriority {
        DEBUG_PRIORITY,
        INFO_PRIORITY,
        WARNING_PRIORITY,
        ERROR_PRIORITY
    };
    Q_ENUM(LogPriority)

    /*!
     * \brief LogEntry
     * \param parent
     */
    explicit LogEntry(QObject *parent = nullptr);

    /*!
     * \brief LogEntry constructs Log Entry instance
     * \param id is id of log entry
     * \param dateTime is creation datetime of log entry
     * \param content is text repressentation of log
     * \param priority is level of priority
     * \param parent is pointer to parent Object
     */
    LogEntry(unsigned int id, const QDateTime &dateTime, const QString &content, LogPriority priority, QObject *parent = nullptr);

    /*!
     * \brief id return id of log entry
     * \return id of log entry
     */
    unsigned int id() const;

    /*!
     * \brief setId sets new id of log entry
     * \param newId is new id of log entry
     */
    void setId(unsigned int newId);

    /*!
     * \brief dateTime return creation datetime of log entry
     * \return creation datetime of log entry
     */
    const QDateTime &dateTime() const;

    /*!
     * \brief setDateTime sets new creation datetime of log entry
     * \param newDateTime is new creation datetime of log entry
     */
    void setDateTime(const QDateTime &newDateTime);

    /*!
     * \brief content return text representation of log
     * \return text representation of log
     */
    const QString &content() const;

    /*!
     * \brief setContent sets log entry text content
     * \param newContent is log entry text content
     */
    void setContent(const QString &newContent);

    /*!
     * \brief priority return log entry priority level
     * \return log entry priority level
     */
    LogPriority priority() const;

    /*!
     * \brief setPriority sets log entry priority
     * \param newPriority is new log entry priority
     */
    void setPriority(LogPriority newPriority);

signals:

    /*!
     * \brief idChanged signal is emmited when log entry id changes
     */
    void idChanged();

    /*!
     * \brief dateTimeChanged signal is emmited when log creation date time changes
     */
    void dateTimeChanged();

    /*!
     * \brief contentChanged signal is emmited when log content changes
     */
    void contentChanged();

    /*!
     * \brief priorityChanged signal is emmited when log priority changes
     */
    void priorityChanged();

private:
    unsigned int m_id;
    QDateTime m_dateTime;
    QString m_content;
    LogPriority m_priority;
};

