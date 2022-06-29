#include "chatclient.h"
#include "ui_chatclient.h"
#include "global_variables.h"

chatclient::chatclient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chatclient)
{
    ui->setupUi(this);

    ui->connectButton->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->send->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    this->setWindowTitle("Chat Client");
    ui->nameInput->setText(current_user.username);
    connectedToHost = false;
}

chatclient::~chatclient()
{
    delete ui;
}

void chatclient::on_connectButton_clicked()
{
    if(!connectedToHost)
        {
            socket=new QTcpSocket();

            connect(socket, SIGNAL(connected()), this, SLOT(socketConnected()));
            connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
            connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));

            socket->connectToHost(server_ip, 8801);
        }
        else
        {
            socket->write("<font color = \"Orange\">" + current_user.username.toUtf8() + " has left the chat room.</font> ");

            socket->disconnectFromHost();
        }
}

void chatclient::socketConnected()
{
    qDebug()<<"Connected to server. ";
    printMessage("<font color=\"Green\">Connected to server.</font>");

    socket->write("<font color = \"Purple\">"+ current_user.username.toUtf8() + " has joined chat room.</font>" );

    ui->connectButton->setText("Disconnect");
    connectedToHost = true;

}

void chatclient::socketDisconnected()
{
    qDebug()<<"DisConnected from server. ";
    printMessage("<font color=\"Red\">DisConnected from server.</font>");

    ui->connectButton->setText("Connect");
    connectedToHost = false;

}

void chatclient::socketReadyRead()
{
    ui->chatDisplay->append(socket->readAll());
}

void chatclient::printMessage(QString message)
{
    ui->chatDisplay->append(message);
}

void chatclient::on_send_clicked()
{
    QString message = ui->messageInput->text();
    socket->write("<font color=\"Blue\">" + current_user.username.toUtf8() + "</font>: " + message.toUtf8());

    ui->messageInput->clear();
}

void chatclient::on_messageInput_returnPressed()
{
    if(ui->messageInput->text() != nullptr)
    {
        QString message = ui->messageInput->text();
        socket->write("<font color=\"Blue\">" + current_user.username.toUtf8() + "</font>: " + message.toUtf8());

        ui->messageInput->clear();
    }
}
