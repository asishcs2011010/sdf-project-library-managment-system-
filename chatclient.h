#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class chatclient;
}

/*!
 * \brief The chatclient class
 */
class chatclient : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief chatclient constructor
     *
     * Sets up the ui window and the sets the window name to Chat Client,
     * sets the text in line edit corresponding to name
     * to username of the current user and sets the by default connectedToHost
     * variable to false.
     * \param parent
     */
    explicit chatclient(QWidget *parent = nullptr);

    /*!
     * ~chatclient() - destructor
     */
    ~chatclient();

    /*!
     * \brief printMessage
     *
     * This function appends the message to the text browser.
     * \param message
     */
    void printMessage(QString message);

private slots:

    /*!
     * \brief on_connectButton_clicked
     *
     * On clicking the connect button on the Chat Client window,
     * this function is called.
     * Firstly, it checks the value of connectedToHost variable. If its false,
     * then it creates a QTcpSocket object called socket and makes it to connect
     * to a host at local host - 127.0.0.1 on port 8801. And we also connect the
     * socket object to its respective slot functions when connected(),
     * disconnected() and readyRead() were trigerred.
     * If the client is already connected to the server, then the text on the button
     * shows disconnect, and on clicking this sends a disconnection message to the
     * server and the connection is terminated.
     */
    void on_connectButton_clicked();

    /*!
     * \brief socketConnected
     *
     * This function will be called if the client has connected successfully to the
     * server. First the client will display Connected to server message on both
     * application output and text browser widget. Now it takes the username that we set
     * in the line edit and incorporate it into a text message and send it to the server
     * so that all users can be notified. And at last, it changes the label of connect
     * push button to disconnect, and set the value of connectedToHost variable to true.
     *
     */
    void socketConnected();

    /*!
     * \brief socketDisconnected
     *
     * On being called, this function shows disconnected messages to both application output
     * and on text browser widget. It sets the value of connectedToHost variable to false.
     * And we can no longer send any message to the server.
     */
    void socketDisconnected();

    /*!
     * \brief socketReadyRead
     *
     * This function gets trigerred when the server is sending data to the client. It passes the
     * incoming data to the printMessage() function.
     */
    void socketReadyRead();

    /*!
     * \brief on_send_clicked
     *
     * On clicking the send button after entering the message, this function gets called. It combines the
     * message with the username. Then the name is set to blue color and after that the entire thing is
     * sent to the server by calling write(). After that, clear the message input field.
     */
    void on_send_clicked();

    /*!
     * \brief on_messageInput_returnPressed
     *
     * This is an alternative function for send_clicked function. Instead of clicking on send button, if
     * we press enter on keyboard, even then the message is sent.
     */
    void on_messageInput_returnPressed();


private:
    Ui::chatclient *ui;

    /*!
     * \brief connectedToHost
     *
     * This is a bool variable which holds the status of client-server connection.
     *
     * @retval TRUE if the client is connected to server.
     * @retval FALSE if the client is not connected to the server.
     */
    bool connectedToHost;

    /*!
     * \brief socket
     *
     * socket is an object of QTcpSocket pointer, which provides a TCP socket.
     */
    QTcpSocket* socket;
};

#endif // CHATCLIENT_H
