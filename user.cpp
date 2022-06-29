#include"user.h"
#include <QDebug>

void Send_borrow_request(Book book)
{
     bool request_status = book.isBorrowed();

    if(request_status)
    {
        qDebug()<<"Book is borrowed by other user and is not available at present.";
    }
    else if(!request_status)
    {
        qDebug()<<"Book is available.";
    }
}
