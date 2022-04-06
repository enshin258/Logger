#include "LoggerDataSortFilterProxyModel.h"

LoggerDataSortFilterProxyModel::LoggerDataSortFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    connect(this, &LoggerDataSortFilterProxyModel::sortRoleChanged, this, [this]() {
        this->sort(0, m_sortOrder);
    });
    connect(this, &LoggerDataSortFilterProxyModel::sortOrderChanged, this, [this]() {
        this->sort(0, m_sortOrder);
    });

    invalidateFilter();
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

bool LoggerDataSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (!sourceParent.isValid()) {
        QModelIndex sourceIndex = sourceModel()->index(sourceRow, 0, sourceParent);

        bool filteringEnbaled = !m_contentFilter.isEmpty() ||
                !m_debugFilter ||
                !m_infoFilter ||
                !m_warningFilter ||
                !m_errorFilter;

        if (sourceIndex.isValid()) {
            if (filteringEnbaled) {

                LoggerDataModel *sourceLoggerModel = dynamic_cast<LoggerDataModel*>(sourceModel());
                LogEntry *logEntry = sourceLoggerModel->getLogEntry(sourceIndex.row());

                if (!(logEntry->content().contains(m_contentFilter, Qt::CaseInsensitive))) {
                    return false;
                }

                switch(logEntry->priority()) {
                case LogEntry::LogPriority::DEBUG_PRIORITY: {
                    if (!m_debugFilter) {
                        return false;
                    }
                    break;
                }
                case LogEntry::LogPriority::INFO_PRIORITY: {
                    if (!m_infoFilter) {
                        return false;
                    }
                    break;

                }
                case LogEntry::LogPriority::WARNING_PRIORITY: {
                    if (!m_warningFilter) {
                        return false;
                    }
                    break;

                }
                case LogEntry::LogPriority::ERROR_PRIORITY: {
                    if (!m_errorFilter) {
                        return false;
                    }
                    break;
                }
                }

                return true;
            }

            return true;
        }

        return false;
    }
    else {
        return false;
    }
}

bool LoggerDataSortFilterProxyModel::lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const
{
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
        const auto &leftDate = QDateTime::fromString(rightData.toString(), "dd.MM.yyyy-hh:mm:ss.z");
        const auto &rightDate = QDateTime::fromString(leftData.toString(), "dd.MM.yyyy-hh:mm:ss.z");

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
        const auto &leftPriority = getPriorityValue(leftData.toString());
        const auto &rightPriority = getPriorityValue(rightData.toString());

        return leftPriority < rightPriority;
    }
    }
    return false;
}

const QString &LoggerDataSortFilterProxyModel::contentFilter() const
{
    return m_contentFilter;
}

void LoggerDataSortFilterProxyModel::setContentFilter(const QString &newContentFilter)
{
    if (m_contentFilter == newContentFilter)
        return;
    m_contentFilter = newContentFilter;
    emit contentFilterChanged();
    invalidateFilter();
}

bool LoggerDataSortFilterProxyModel::debugFilter() const
{
    return m_debugFilter;
}

void LoggerDataSortFilterProxyModel::setDebugFilter(bool newDebugFilter)
{
    if (m_debugFilter == newDebugFilter)
        return;
    m_debugFilter = newDebugFilter;
    emit debugFilterChanged();
    invalidateFilter();
}

bool LoggerDataSortFilterProxyModel::infoFilter() const
{
    return m_infoFilter;
}

void LoggerDataSortFilterProxyModel::setInfoFilter(bool newInfoFilter)
{
    if (m_infoFilter == newInfoFilter)
        return;
    m_infoFilter = newInfoFilter;
    emit infoFilterChanged();
    invalidateFilter();
}

bool LoggerDataSortFilterProxyModel::warningFilter() const
{
    return m_warningFilter;
}

void LoggerDataSortFilterProxyModel::setWarningFilter(bool newWarningFilter)
{
    if (m_warningFilter == newWarningFilter)
        return;
    m_warningFilter = newWarningFilter;
    emit warningFilterChanged();
    invalidateFilter();
}

bool LoggerDataSortFilterProxyModel::errorFilter() const
{
    return m_errorFilter;
}

void LoggerDataSortFilterProxyModel::setErrorFilter(bool newErrorFilter)
{
    if (m_errorFilter == newErrorFilter)
        return;
    m_errorFilter = newErrorFilter;
    emit errorFilterChanged();
    invalidateFilter();
}

int LoggerDataSortFilterProxyModel::getPriorityValue(const QString priority) const
{
    if (priority == "DEBUG") {
        return 1;
    } else if (priority == "INFO") {
        return 2;
    } else if (priority == "WARNING") {
        return 3;
    } else if (priority == "ERROR") {
        return 4;
    } else {
        return 0;
    }
}

void LoggerDataSortFilterProxyModel::startSimulation()
{
    LoggerDataModel *sourceLoggerModel = dynamic_cast<LoggerDataModel*>(sourceModel());
    sourceLoggerModel->startSimulation();
}

void LoggerDataSortFilterProxyModel::stopSimulation()
{
    LoggerDataModel *sourceLoggerModel = dynamic_cast<LoggerDataModel*>(sourceModel());
    sourceLoggerModel->stopSimulation();
}
