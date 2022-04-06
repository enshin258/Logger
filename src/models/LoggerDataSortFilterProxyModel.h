#pragma once

#include <QSortFilterProxyModel>
#include <QObject>
#include "LoggerDataModel.h"
#include "../datasets/LogEntry.h"

/*!
 * \brief The LoggerDataSortFilterProxyModel class is responsible for filtering and sorting source LoggerDataModel
 */
class LoggerDataSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(Qt::SortOrder sortOrder READ sortOrder WRITE setSortOrder NOTIFY sortOrderChanged)
    Q_PROPERTY(QString contentFilter READ contentFilter WRITE setContentFilter NOTIFY contentFilterChanged)
    Q_PROPERTY(bool debugFilter READ debugFilter WRITE setDebugFilter NOTIFY debugFilterChanged)
    Q_PROPERTY(bool infoFilter READ infoFilter WRITE setInfoFilter NOTIFY infoFilterChanged)
    Q_PROPERTY(bool warningFilter READ warningFilter WRITE setWarningFilter NOTIFY warningFilterChanged)
    Q_PROPERTY(bool errorFilter READ errorFilter WRITE setErrorFilter NOTIFY errorFilterChanged)

public:
    /*!
     * \brief LoggerDataSortFilterProxyModel constructs object of LoggerDataSortFilterProxyModel class
     * \param parent is pointer to parent QObject
     */
    LoggerDataSortFilterProxyModel(QObject *parent = nullptr);

    /*!
     * \brief sortOrder returns current model sort order
     * \return current model sort order
     */
    Qt::SortOrder sortOrder() const;

    /*!
     * \brief setSortOrder sets new model sort order
     * \param newSortOrder is new model sort order
     */
    void setSortOrder(Qt::SortOrder newSortOrder);

    /*!
     * \brief contentFilter retruns current log content filter
     * \return current log content filter
     */
    const QString &contentFilter() const;

    /*!
     * \brief setContentFilter sets log content filter
     * \param newContentFilter is new log content filter
     */
    void setContentFilter(const QString &newContentFilter);

    /*!
     * \brief debugFilter return if debug filter is active
     * \return if debug filter is active
     */
    bool debugFilter() const;

    /*!
     * \brief setDebugFilter changes debug filter active state
     * \param newDebugFilter is new debug filter active state
     */
    void setDebugFilter(bool newDebugFilter);

    /*!
     * \brief infoFilter return if info filter is active
     * \return if info filter is active
     */
    bool infoFilter() const;

    /*!
     * \brief setInfoFilter changes debug filter active state
     * \param newInfoFilter is new debug filter active state
     */
    void setInfoFilter(bool newInfoFilter);

    /*!
     * \brief warningFilter return if info filter is active
     * \return if warning filter is active
     */
    bool warningFilter() const;

    /*!
     * \brief setWarningFilter changes warning filter active state
     * \param newWarningFilter is new warning filter active state
     */
    void setWarningFilter(bool newWarningFilter);

    /*!
     * \brief errorFilter return if error filter is active
     * \return if error filter is active
     */
    bool errorFilter() const;

    /*!
     * \brief setErrorFilter changes error filter active state
     * \param newErrorFilter is new error filter active state
     */
    void setErrorFilter(bool newErrorFilter);

    /*!
     * \brief getPriorityValue is helper function used in filtering by priority
     * \param priority is QString representation of priority
     * \return int priority value
     */
    int getPriorityValue(const QString priority) const;

public slots:
    /*!
     * \brief startSimulation function is used to run LoggerDataModel startSimulation function
     */
    void startSimulation();

    /*!
     * \brief stopSimulation function is used to run LoggerDataModel stopSimulation function
     */
    void stopSimulation();

protected:
    /*!
     * \brief filterAcceptsRow returns true if the item in the row indicated by the given sourceRow and sourceParent
     *  should be included in the model, otherwise returns false.
     * \param sourceRow is source row number
     * \param sourceParent is parent QModelIndex
     * \return if item should be included in model
     */
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

    /*!
     * \brief lessThan returns true if the value of the item referred to by the given index sourceLeft
     *  is less than the value of the item referred to by the given index sourceRight, otherwise returns false.
     * \param sourceLeft is index of left item
     * \param sourceRight is index of right item
     * \return true if value of left item is less than right item
     */
    bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const override;

signals:

    /*!
     * \brief sortOrderChanged signal is emmited when sort order changes
     */
    void sortOrderChanged();

    /*!
     * \brief contentFilterChanged signal is emmited when content filter changes
     */
    void contentFilterChanged();

    /*!
     * \brief debugFilterChanged signal is emmited when debug filter changes
     */
    void debugFilterChanged();

    /*!
     * \brief infoFilterChanged signal is emmited when info filter changes
     */
    void infoFilterChanged();

    /*!
     * \brief warningFilterChanged signal is emmited when warning filter changes
     */
    void warningFilterChanged();

    /*!
     * \brief errorFilterChanged signal is emmited when error filter changes
     */
    void errorFilterChanged();

private:
    Qt::SortOrder m_sortOrder = Qt::AscendingOrder;

    QString m_contentFilter = "";
    bool m_debugFilter = true;
    bool m_infoFilter = true;
    bool m_warningFilter = true;
    bool m_errorFilter = true;
};

