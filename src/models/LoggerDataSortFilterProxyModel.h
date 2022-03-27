#pragma once

#include <QSortFilterProxyModel>
#include <QObject>
#include "../models/LoggerDataModel.h"
#include "../datasets/LogEntry.h"

class LoggerDataSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(Qt::SortOrder sortOrder READ sortOrder WRITE setSortOrder NOTIFY sortOrderChanged)
    Q_PROPERTY(bool filteringEnabled READ filteringEnabled WRITE setFilteringEnabled NOTIFY filteringEnabledChanged)
    Q_PROPERTY(LogEntry::LogPriority priorityFilter READ priorityFilter WRITE setPriorityFilter NOTIFY priorityFilterChanged)

public:
    LoggerDataSortFilterProxyModel(QObject *parent = nullptr);

    Qt::SortOrder sortOrder() const;
    void setSortOrder(Qt::SortOrder newSortOrder);

    const LogEntry::LogPriority &priorityFilter() const;
    void setPriorityFilter(const LogEntry::LogPriority &newPriorityFilter);

    // QSortFilterProxyModel interface
    bool filteringEnabled() const;
    void setFilteringEnabled(bool newFilteringEnabled);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const override;

signals:
    void sortOrderChanged();
    void priorityFilterChanged();
    void filteringEnabledChanged();

private:
    Qt::SortOrder m_sortOrder = Qt::AscendingOrder;
    LogEntry::LogPriority m_priorityFilter = LogEntry::LogPriority::DEBUG;
    bool m_filteringEnabled = false;
};

