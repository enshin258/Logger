#include "DatabaseController.h"

DatabaseController::DatabaseController(LoggerDataModel *loggerDataModel, QObject *parent)
    : BasicController(loggerDataModel, parent)
{

}

const QString &DatabaseController::databaseFileName() const
{
    return m_databaseFileName;
}

void DatabaseController::setDatabaseFileName(const QString &newDatabaseFileName)
{
    if (m_databaseFileName == newDatabaseFileName)
        return;
    m_databaseFileName = newDatabaseFileName;
    emit databaseFileNameChanged();
}


void DatabaseController::handleLogs(const QModelIndex &parent, int first, int last)
{
    if (m_database.isOpen()) {
        for (int i = first; i <= last ; i++) {
            QModelIndex index = m_loggerDataModel->index(i, 0 , parent);

            QSqlQuery query;
            query.prepare("INSERT INTO logs (id, dateTime, content, priority) VALUES (:id, :dateTime, :content, :priority)");

            query.bindValue(":id", m_loggerDataModel->data(index, LoggerDataModel::IdRole).toString());
            query.bindValue(":dateTime", m_loggerDataModel->data(index, LoggerDataModel::DateTimeRole).toString());
            query.bindValue(":content", m_loggerDataModel->data(index, LoggerDataModel::ContentRole).toString());
            query.bindValue(":priority", m_loggerDataModel->data(index, LoggerDataModel::PriorityRole).toString());

            if (!query.exec()) {
                qWarning() << "Failed to add log to database!: " << query.lastError();
            }
        }
    }
}

bool DatabaseController::initDatabase()
{
    const QString driver("QSQLITE");

    if (QSqlDatabase::isDriverAvailable(driver)) {
        m_database = QSqlDatabase::addDatabase(driver);

        m_database.setDatabaseName(m_databaseFileName + ".sqlite");

        if (!m_database.open()) {
            qCritical() << "Failed to open database" << m_database.lastError().text();
            return false;
        } else {
            QSqlQuery clearQuerry("DROP TABLE IF EXISTS logs");

            if (!clearQuerry.isActive()) {
                qCritical() << "Failed to clear database" << clearQuerry.lastError().text();
                return false;
            } else {
                QSqlQuery createQuerry("CREATE TABLE logs (id INTEGER PRIMARY KEY, dateTime TEXT, content TEXT, priority TEXT)");
                if (!createQuerry.isActive()) {
                    qCritical() << "Failed to create database" << createQuerry.lastError().text();
                    return false;
                } else {
                    return true;
                }
            }
        }
    }
    else {
        qCritical() << "Failed to initiate driver !";
        return false;
    }
}
