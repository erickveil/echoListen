/**
 * universallistener.h
 * Erick Veil
 * 2018-09-26
 */
#ifndef UNIVERSALLISTENER_H
#define UNIVERSALLISTENER_H

#include <functional>

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "staticlogger.h"

namespace stnctl {

/**
 * @brief The UniversalListener class
 * A simple to use listener.
 * Rather than build this same structure of slots and signals, and trying to
 * remember all the classes required to build a listener, we can just use this
 * class, initialize it, and run the start method.
 * Callbacks available for Ack generation, Parsing input, and error handling.
 */
class UniversalListener : public QObject
{
    Q_OBJECT

    QTcpServer _server;
    QTcpSocket *_connection = nullptr;

    bool _isSignalsConnected = false;
    int _port = -1;

    /**
     * @brief _parseCallback
     * This callback is called after the transaction is complete - The client
     * has already received its ack and the connection has ended.
     * The QByteArray passed to the function will be the message that was
     * sent from the client.
     *
     * Without this callback, nothing will be done with the data recieved.
     */
    std::function<void (QByteArray)> _parseCallback;

    /**
     * @brief _ackCallback
     * This callback is called to generate an ack message that gets sent back
     * to the client at the end of a transaction.
     * It is reccommended that this be a very fast method: relying on parsing,
     * database connections, or other socket connections could slow down ack
     * generation and cause the client to time out.
     * The QByteArray argument will be the data recieved from the client.
     *
     * Without this callback, the listener will respond immedately to the client
     * with an echo of the recieved data.
     */
    std::function<QByteArray (QByteArray)> _ackCallback;

    /**
     * @brief _errorCallback
     * This callback will be run whenever there is an error.
     * The QString argument will be the human readable error string.
     *
     * Without this callback, errors will be silent.
     */
    std::function<void (QAbstractSocket::SocketError, QString)> _errorCallback;

public:

    /**
     * @brief Name
     * Optional name to assign to listener if you want to refer to it by name.
     */
    QString Name;

    /**
     * @brief UniversalListener
     * Default constructor.
     * @param parent
     */
    explicit UniversalListener(QObject *parent = nullptr);

    /**
     * @brief UniversalListener
     * @param port
     */
    UniversalListener(int port);

    /**
     * @brief UniversalListener
     * @param port
     * @param parseCallback
     */
    UniversalListener(int port, std::function<void (QByteArray)> parseCallback);

    /**
     * @brief UniversalListener
     * @param port
     * @param parseCallback
     * @param ackCallback
     */
    UniversalListener(int port,
                      std::function<void (QByteArray)> parseCallback,
                      std::function<QByteArray (QByteArray)> ackCallback );

    /**
     * @brief UniversalListener
     * @param port
     * @param parseCallback
     * @param ackCallback
     * @param errorCallback
     */
    UniversalListener(int port,
                      std::function<void (QByteArray)> parseCallback,
                      std::function<QByteArray (QByteArray)> ackCallback,
                      std::function<void
                      (QAbstractSocket::SocketError, QString)> errorCallback );

    /**
     * @brief initData
     * @param port
     * @param parseCallback
     */
    void initData(int port, std::function<void (QByteArray)> parseCallback);

    /**
     * @brief initData
     * @param port
     * @param parseCallback
     * @param ackCallback
     */
    void initData(int port,
                      std::function<void (QByteArray)> parseCallback,
                      std::function<QByteArray (QByteArray)> ackCallback );

    /**
     * @brief initData
     * @param port
     * @param parseCallback
     * @param ackCallback
     * @param errorCallback
     */
    void initData(int port,
                      std::function<void (QByteArray)> parseCallback,
                      std::function<QByteArray (QByteArray)> ackCallback,
                      std::function<void
                      (QAbstractSocket::SocketError, QString)> errorCallback );

    /**
     * @brief setPort
     * @param port
     */
    void setPort(int port);

    /**
     * @brief setParseCallback
     * @param parseCallback
     */
    void setParseCallback(std::function<void (QByteArray)> parseCallback);

    /**
     * @brief setAckCallback
     * @param ackCallback
     */
    void setAckCallback(std::function<QByteArray (QByteArray)> ackCallback);

    /**
     * @brief setErrorCallback
     * @param errorCallback
     */
    void setErrorCallback(std::function<void
                      (QAbstractSocket::SocketError, QString)> errorCallback);

    /**
     * Destructor
     */
    ~UniversalListener();

    /**
     * @brief initConnections
     * Initializes all signal to slot connections for the listener.
     * If called more than once, will return without doing anything, so that
     * multiple signals are not slotted.
     * All of the init methods call this when used.
     * All but the default constructor call the init methods.
     */
    void initConnections();

    /**
     * @brief startListener
     */
    void startListener();

    /**
     * @brief stopListener
     */
    void stopListener();

    /**
     * @brief getPort
     * @return The current port assigned to this listener.
     */
    int getPort();

private slots:
    // --- QTcpServer ---
    void _eventListenerAcceptError(QAbstractSocket::SocketError err);
    void _eventListenerNewConnection();

    // --- QTcpSocket, QAbstractSocket ---
    void _eventSocketConnected();
    void _eventSocketDisconnected();
    void _eventSocketError(QAbstractSocket::SocketError err);
    void _eventSocketStateChanged();

    // --- QTcpSocket, QIODevice ---
    void _eventIODeviceAboutToClose();
    void _eventIODeviceBytesWritten(qint64 bytes);
    void _eventIODeviceReadyRead();
};

} // namespace stnctl

#endif // UNIVERSALLISTENER_H
