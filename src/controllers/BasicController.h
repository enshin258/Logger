#pragma once

#include <QObject>
#include "../datasets/LogEntry.h"
#include "../models/LoggerDataModel.h"

/*!
 * \brief The BasicController is an abstract class from which the controllers that send logs inherit
 */
class BasicController : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief BasicController is constructor that is used for class that inherits BasicController
     * \param loggerDataModel is pointer to LoggerDataModel instance
     * \param parent is pointer to parent QObject
     */
    explicit BasicController(LoggerDataModel *loggerDataModel, QObject *parent = nullptr);

    /*!
     * \brief handleLogs is a purely virtual function that the inheriting classes must implement.
     *  It consists in handling the received logs from loggerDataModel and saving them
     * \param parent is pointer to parent QModelIndex of current index
     * \param first is index of first log
     * \param last is index of last log
     */
    virtual void handleLogs(const QModelIndex &parent, int first, int last) = 0;

    /*!
     * \brief m_loggerDataModel is pointer to LoggerDataModel instance
     */
    LoggerDataModel* m_loggerDataModel = nullptr;
};

