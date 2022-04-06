#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <QRandomGenerator>
#include <QTimer>

#include "../datasets/LogEntry.h"
#include "../templates/MyVector.h"

/*!
 * \brief The LoggerDataModel class is the model responsible for storing all logs
 */
class LoggerDataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    /*!
     * \brief The Roles enum stores the possible roles that can be used to get information from a specific log
     */
    enum Roles {
        IdRole = Qt::UserRole + 1,
        DateTimeRole,
        ContentRole,
        PriorityRole
    };
    Q_ENUM(Roles);

    /*!
     * \brief LoggerDataModel constructs object of LoggerDataModel class
     * \param parent is pointer to parent QObject
     */
    explicit LoggerDataModel(QObject *parent = nullptr);

public:
    /*!
     * \brief rowCount returns the number of rows under the given parent.
     *  When the parent is valid it means that rowCount is returning the number of children of parent
     * \param parent is pointer to parent QModelIndex
     * \return number of rows in model
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /*!
     * \brief columnCount returns the number of columns for the children of the given parent.
     * In this example return number of columns used in whole model
     * \param parent is pointer to parent QModelIndex
     * \return number of columns in model
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    /*!
     * \brief data returns the data stored under the given role for the item referred to by the index.
     * \param index is index of intrests elemetn
     * \param role describes us wchic information we want to retrive
     * \return stored data
     */
    QVariant data(const QModelIndex &index, int role) const override;

    /*!
     * \brief roleNames return model's role names.
     * \return model's role names.
     */
    QHash<int, QByteArray> roleNames() const override;

public slots:

    /*!
     * \brief addLogEntry add new log entry to model
     * \param logEntry is newly added log entry
     */
    void addLogEntry(LogEntry *logEntry);

    /*!
     * \brief getLogEntry returns pointer o log entry under given index
     * \param index is index of searched log entry
     * \return pointer to log entry
     */
    LogEntry* getLogEntry(int index);

    /*!
     * \brief startSimulation start filling model with simulated logs
     */
    void startSimulation();

    /*!
     * \brief stopSimulation stops filling model
     */
    void stopSimulation();

private:
    MyVector<LogEntry*> m_logEntries;
    bool m_simulate = false;
    QTimer *m_timer = nullptr;
};

