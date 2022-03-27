#include "LoggerDataSortFilterProxyModel.h"

LoggerDataSortFilterProxyModel::LoggerDataSortFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{

}


Qt::SortOrder LoggerDataSortFilterProxyModel::sortOrder() const
{
    return m_sortOrder;
}

void LoggerDataSortFilterProxyModel::setSortOrder(Qt::SortOrder newSortOrder)
{
    if (m_sortOrder == newSortOrder)
        return;
    m_sortOrder = newSortOrder;
    emit sortOrderChanged();
}

const LogEntry::LogPriority &LoggerDataSortFilterProxyModel::priorityFilter() const
{
    return m_priorityFilter;
}

void LoggerDataSortFilterProxyModel::setPriorityFilter(const LogEntry::LogPriority &newPriorityFilter)
{
    if (m_priorityFilter == newPriorityFilter)
        return;
    m_priorityFilter = newPriorityFilter;
    emit priorityFilterChanged();
    invalidateFilter();
}


bool LoggerDataSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{

    QModelIndex sourceIndex = sourceModel()->index(sourceRow, 0, sourceParent);

    if (sourceIndex.isValid()) {
        if (m_filteringEnabled) {
            LogEntry *logEntry = static_cast<LogEntry*>(sourceIndex.internalPointer());

            if (logEntry->priority() != m_priorityFilter) {
                return false;
            }
        }

        return true;
    }

    return false;
}

bool LoggerDataSortFilterProxyModel::lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const
{
    qDebug() << "LEST THAN";
    qDebug() << "SORT ROLE: " << this->sortRole();
    const QVariant leftData = sourceModel()->data(sourceLeft, sortRole());
    const QVariant rightData = sourceModel()->data(sourceRight, sortRole());

    switch (sortRole()) {
    case LoggerDataModel::IdRole:
    {
        const auto &leftId = leftData.toUInt();
        const auto &rightId = rightData.toUInt();

        return leftId < rightId;
    }
    case LoggerDataModel::DateTimeRole:
    {
        const auto &leftDate = leftData.toDateTime();
        const auto &rightDate = rightData.toDateTime();

        return leftDate < rightDate;
    }
    case LoggerDataModel::ContentRole:
    {
        const auto &leftContent = leftData.toString();
        const auto &rightContent = rightData.toString();

        return leftContent < rightContent;
    }

    case LoggerDataModel::PriorityRole:
    {
        const auto &leftPriority = leftData.toString();
        const auto &rightPriority = rightData.toString();

        return leftPriority < rightPriority;
    }
    }
    return false;
}

bool LoggerDataSortFilterProxyModel::filteringEnabled() const
{
    return m_filteringEnabled;
}

void LoggerDataSortFilterProxyModel::setFilteringEnabled(bool newFilteringEnabled)
{
    if (m_filteringEnabled == newFilteringEnabled)
        return;
    m_filteringEnabled = newFilteringEnabled;
    emit filteringEnabledChanged();
}

