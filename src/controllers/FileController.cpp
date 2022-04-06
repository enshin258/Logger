#include "FileController.h"

FileController::FileController(LoggerDataModel *loggerDataModel, QObject *parent)
    : BasicController(loggerDataModel, parent)
{

}

const QString &FileController::fileName() const
{
    return m_fileName;
}

void FileController::setFileName(const QString &newFileName)
{
    if (m_fileName == newFileName)
        return;
    m_fileName = newFileName;
    emit fileNameChanged();
}

void FileController::handleLogs(const QModelIndex &parent, int first, int last)
{
    if (m_file && m_file->isReadable()) {
        for (int i = first; i <= last ; i++) {
            QTextStream stream(m_file);
            QModelIndex index = m_loggerDataModel->index(i, 0 , parent);
            stream << m_loggerDataModel->data(index, LoggerDataModel::IdRole).toString() << "|";
            stream << m_loggerDataModel->data(index, LoggerDataModel::DateTimeRole).toString() << "|";
            stream << m_loggerDataModel->data(index, LoggerDataModel::PriorityRole).toString() << "|";
            stream << m_loggerDataModel->data(index, LoggerDataModel::ContentRole).toString() << "\n";
        }
    }
}

bool FileController::openFileToSave()
{
    m_file = new QFile(m_fileName + ".txt");

    if (!m_file->open(QIODevice::ReadWrite)) {
        qCritical() << "Failed to create file!" << m_fileName;
        return false;
    } else {
        qCritical() << "Succesfully opened file!" << m_fileName;
        return true;
    }
}



