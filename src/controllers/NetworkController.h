#pragma once

#include <QTcpSocket>
#include "BasicController.h"

class NetworkController : public BasicController
{
    Q_OBJECT
    Q_PROPERTY(QString hostAddress READ hostAddress WRITE setHostAddress NOTIFY hostAddressChanged)
    Q_PROPERTY(int hostPort READ hostPort WRITE setHostPort NOTIFY hostPortChanged)
    Q_PROPERTY(bool isConnected READ isConnected WRITE setIsConnected NOTIFY isConnectedChanged)
public:
    /*!
     * \brief NetworkController constructs object of NetworkController class
     * \param loggerDataModel is pointer to LoggerDataModel instance
     * \param parent is pointer to parent QObject
     */
    explicit NetworkController(LoggerDataModel *loggerDataModel, QObject *parent = nullptr);

    /*!
     * \brief hostAddress return server host address
     * \return server host address
     */
    const QString &hostAddress() const;

    /*!
     * \brief setHostAddress sets server host address
     * \param newHostAddress is server host address
     */
    void setHostAddress(const QString &newHostAddress);

    /*!
     * \brief hostPort return server port
     * \return server port
     */
    int hostPort() const;

    /*!
     * \brief setHostPort sets server host port
     * \param newHostPortis server host port
     */
    void setHostPort(int newHostPort);

    /*!
     * \brief isConnected return if application is connected with servers
     * \return state of connection
     */
    bool isConnected() const;

    /*!
     * \brief setIsConnected is set when application connect with server
     * \param newIsConnected is state of connection with server
     */
    void setIsConnected(bool newIsConnected);

    // BasicController interface
    virtual void handleLogs(const QModelIndex &parent, int first, int last) override;

public slots:
    /*!
     * \brief connectToHost connects application with server
     * \return if connected succesfully
     */
    bool connectToHost();

    /*!
     * \brief disconnectFromHost disconnect application from server
     */
    void disconnectFromHost();

signals:
    /*!
     * \brief hostAddressChanged signal is emmited when server address changeds
     */
    void hostAddressChanged();

    /*!
     * \brief hostPortChanged signal is emmited when server port changes
     */
    void hostPortChanged();

    /*!
     * \brief isConnectedChanged is emmited when connection state chages
     */
    void isConnectedChanged();

private:
    QString m_hostAddress = "127.0.0.1";
    int m_hostPort = 4242;
    bool m_isConnected = false;

    QTcpSocket *m_socket = nullptr;
};

