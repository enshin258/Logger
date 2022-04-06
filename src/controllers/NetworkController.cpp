#include "NetworkController.h"
#include <QNetworkInterface>

NetworkController::NetworkController(LoggerDataModel *loggerDataModel, QObject *parent) :
    BasicController(loggerDataModel, parent)
{
    m_socket = new QTcpSocket(this);

    connect(m_socket, &QTcpSocket::errorOccurred, this, [this]() {
        qDebug() << "SOCKET ERROR: " << m_socket->errorString();
    });
}

const QString &NetworkController::hostAddress() const
{
    return m_hostAddress;
}

void NetworkController::setHostAddress(const QString &newHostAddress)
{
    if (m_hostAddress == newHostAddress)
        return;
    m_hostAddress = newHostAddress;
    emit hostAddressChanged();
}

int NetworkController::hostPort() const
{
    return m_hostPort;
}

void NetworkController::setHostPort(int newHostPort)
{
    if (m_hostPort == newHostPort)
        return;
    m_hostPort = newHostPort;
    emit hostPortChanged();
}

bool NetworkController::connectToHost()
{
    qDebug() << "Connecting to server: " << m_hostAddress + " on port: " << m_hostPort;

    m_socket->connectToHost(QHostAddress(m_hostAddress), m_hostPort);

    if (m_socket->waitForConnected()) {
        qDebug() << "Socket connected!";

        m_socket->write("Greeting from Logger :)");

        setIsConnected(true);
        return true;

    } else {
        qCritical() << "FAILED TO CONNECT TO HOST";
        return false;
    }
}

void NetworkController::disconnectFromHost()
{
    m_socket->flush();
    m_socket->close();
    setIsConnected(false);
}

bool NetworkController::isConnected() const
{
    return m_isConnected;
}

void NetworkController::setIsConnected(bool newIsConnected)
{
    if (m_isConnected == newIsConnected)
        return;
    m_isConnected = newIsConnected;
    emit isConnectedChanged();
}


void NetworkController::handleLogs(const QModelIndex &parent, int first, int last)
{
    if (m_socket->isOpen() && m_socket->isWritable() && m_isConnected) {
        qDebug () << "Sending to server...";
        for (int i = first; i <= last ; i++) {
            QString logMessage;
            QModelIndex index = m_loggerDataModel->index(i, 0 , parent);
            logMessage += m_loggerDataModel->data(index, LoggerDataModel::IdRole).toString() += "|";
            logMessage += m_loggerDataModel->data(index, LoggerDataModel::DateTimeRole).toString() += "|";
            logMessage += m_loggerDataModel->data(index, LoggerDataModel::PriorityRole).toString() += "|";
            logMessage += m_loggerDataModel->data(index, LoggerDataModel::ContentRole).toString();
            m_socket->write(logMessage.toUtf8());
        }
    }
}
