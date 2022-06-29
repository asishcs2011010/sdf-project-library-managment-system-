#ifndef _BOOK_H
#define _BOOK_H

#include<QtCore>

/*!
 * \brief The address class
 *
 * this is for the address of a user.
 */
class address
{
  public :
  QString street;// street name
  QString city;//city name
  QString state;// state name
};

/*!
 * \brief The Book class
 *
 * This is the book class, which has members that hold
 * info related to book.
 */
class Book
{
 QString name;
 QString author;
 QString owner;
 address adr;
 unsigned edition;
 QString ISBN;
 unsigned serialNo;
 //If ISBN numbers are same,then serial number is given to books
 bool status; //If status is true it means that the book is with the owner, else it means it is borrowed.

  public:
    bool isBorrowed(); 
    void Borrow();
    void returnBook();
    QString getOwnerName();
    address getOwnerAddress();
};

#endif
