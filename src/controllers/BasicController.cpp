#include "BasicController.h"

BasicController::BasicController(LoggerDataModel *loggerDataModel, QObject *parent) : QObject(parent),
    m_loggerDataModel(loggerDataModel)
{
    connect(m_loggerDataModel, &LoggerDataModel::rowsInserted, this, &BasicController::handleLogs);
}
