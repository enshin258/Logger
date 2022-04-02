#pragma once

#include <QSortFilterProxyModel>
#include <QObject>
#include "../models/LoggerDataModel.h"
#include "../datasets/LogEntry.h"

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
    LoggerDataSortFilterProxyModel(QObject *parent = nullptr);

    Qt::SortOrder sortOrder() const;
    void setSortOrder(Qt::SortOrder newSortOrder);

    const QString &contentFilter() const;
    void setContentFilter(const QString &newContentFilter);

    bool debugFilter() const;
    void setDebugFilter(bool newDebugFilter);

    bool infoFilter() const;
    void setInfoFilter(bool newInfoFilter);

    bool warningFilter() const;
    void setWarningFilter(bool newWarningFilter);

    bool errorFilter() const;
    void setErrorFilter(bool newErrorFilter);

    int getPriorityValue(const QString priority) const;
public slots:
    void clearLogs();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const override;

signals:
    void sortOrderChanged();
    void contentFilterChanged();
    void debugFilterChanged();
    void infoFilterChanged();
    void warningFilterChanged();
    void errorFilterChanged();

private:
    Qt::SortOrder m_sortOrder = Qt::AscendingOrder;

    QString m_contentFilter = "";
    bool m_debugFilter = true;
    bool m_infoFilter = true;
    bool m_warningFilter = true;
    bool m_errorFilter = true;
};

