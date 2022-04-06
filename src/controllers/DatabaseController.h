#pragma once

#include "BasicController.h"
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

/*!
 * \brief The DatabaseController class is responsible for writing logs to the SqlLite database
 */
class DatabaseController : public BasicController
{
    Q_OBJECT
    Q_PROPERTY(QString databaseFileName READ databaseFileName WRITE setDatabaseFileName NOTIFY databaseFileNameChanged)

public:
    /*!
     * \brief DatabaseController
     * \param loggerDataModel
     * \param parent
     */
    explicit DatabaseController(LoggerDataModel *loggerDataModel, QObject *parent = nullptr);


    /*!
     * \brief databaseFileName return database file name
     * \return database file name
     */
    const QString &databaseFileName() const;

    /*!
     * \brief setDatabaseFileName sets new database file name
     * \param newDatabaseFileName new database file name
     */
    void setDatabaseFileName(const QString &newDatabaseFileName);

    /*!
     * \brief handleLogs is the implementation of the virtual method from BasicController class
     * It saves the received logs to the database
     * \param parent is pointer to parent QModelIndex of current index
     * \param first is index of first log
     * \param last is index of last log
     */
    virtual void handleLogs(const QModelIndex &parent, int first, int last) override;

public slots:
    /*!
     * \brief initDatabase creates sql lite database
     * \return if init database was succesfull
     */
    bool initDatabase();

signals:

    /*!
     * \brief databaseFileNameChanged signal is emmited when database file name changes
     */
    void databaseFileNameChanged();

private:
    QString m_databaseFileName = "Database";
    QSqlDatabase m_database;
};

