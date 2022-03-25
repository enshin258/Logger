#pragma once

#include <QObject>
#include <QAbstractListModel>

#include "../datasets/LogEntry.h"

class LoggerDataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        DateTimeRole,
        ContentRole,
        PriorityRole
    };
    Q_ENUM(Roles);

    explicit LoggerDataModel(QObject *parent = nullptr);
    ~LoggerDataModel();

signals:
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void addLogEntry(LogEntry *logEntry);

private:
    QList<LogEntry*> m_logEntries;
};

