#pragma once

#include <QFile>
#include "BasicController.h"

/*!
 * \brief The FileController class is responsible for writing logs to a text file
 */
class FileController : public BasicController
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

public:
    /*!
     * \brief FileController constructs object of FileController class
     * \param loggerDataModel is pointer to LoggerDataModel instance
     * \param parent  is pointer to parent QObject
     */
    explicit FileController(LoggerDataModel *loggerDataModel, QObject *parent = nullptr);

    /*!
     * \brief fileName returns logs text file name
     * \return logs text file name
     */
    const QString &fileName() const;

    /*!
     * \brief setFileName sets file name  to logs text file
     * \param newFileName is new file name to logs text file
     */
    void setFileName(const QString &newFileName);

    virtual void handleLogs(const QModelIndex &parent, int first, int last) override;

public slots:

    /*!
     * \brief openFileToSave opens logs text file and connect it with updating loggerDataModel instance
     * \return if file was succesfully opened
     */
    bool openFileToSave();

signals:
    /*!
     * \brief fileNameChanged signal is emmited when logs text file name changes
     */
    void fileNameChanged();

private:
    QString m_fileName = "Logs_" + QDateTime::currentDateTime().toString("dd-MM-yyyy_hh_mm_ss");
    QFile *m_file = nullptr;
};

