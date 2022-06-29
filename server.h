#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QVector>

/*!
 * \brief The server class
 */
class server : public QObject
{
    Q_OBJECT
private:
    /*!
     * \brief QTcpServer* chatServer
     *
     * chatServer is an object of QTcpServer pointer, which provides a
     * TCP-based server.
     */
    QTcpServer* chatServer;

    /*!
     * \brief QVector<QTcpSocket*>* allClients
     *
     * allClients is a vector array that stores all the connected clients so
     * that we can make use of it later to redirect incoming messages to all users.
     */
    QVector<QTcpSocket*>* allClients;

public:
    /*!
     * \brief server constructor
     *
     * \param parent
     */
    explicit server(QObject *parent = nullptr);

    /*!
     * \brief startServer
     *
     * It makes the chatServer to listen to port 8801, and the server starts.
     * If the chatServer couldn't listen, then the server has failed to start.
     */
    void startServer();

    /*!
     * \brief sendMessageToClients
     *
     * Here, we loop through the allClients array and pass the message data
     * to all the connected clients.
     * \param message
     */
    void sendMessageToClients(QString message);

public slots:
    /*!
     * \brief newClientConnection
     *
     * chatServer will trigger the newConnection() signal whenever a new client
     * has connected to the server and then we connect that signal to our custom
     * slot function called newClientConnection().
     */
    void newClientConnection();

    /*!
     * \brief socketDisconnected
     *
     * When a client is disconnected from the server, the disconnected() signal from
     * the server will be triggered, and subsequently the socketDisconnected() function
     * will be called. This function just displays the message  that Socket disconnected
     * from socket-ip address and port number.
     */
    void socketDisconnected();

    /*!
     * \brief socketReadReady
     *
     * Whenever the client is sending a message to the server, the readReady() signal will
     * be triggerred and this signal gets connected to socketReadReady() slot function and
     * it will be called. This redirects the message to sendMessageToClients(), which
     * passes the message to all connected clients.
     */
    void socketReadReady();

    /*!
     * \brief socketStateChanged
     * Whenever there's a change in client's network state, like connected, disconnected,
     * listening and so on, stateChanged() gets trigerred and this signal is connected to
     * socketStateChanged() function. This function prints a message according to its new state.
     * \param state
     */
    void socketStateChanged(QAbstractSocket::SocketState state);
};

#endif // SERVER_H
