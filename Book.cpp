#include"Book.h"

bool Book::isBorrowed()
 {
    if(status)
      return false;
    else
      return true;
 }
void Book::Borrow()
 {
   status=0;
 }
void Book::returnBook()
 {
    status = 1;
 }
QString Book::getOwnerName()
 {
    return owner;
 }
address Book::getOwnerAddress()
  {
      return adr;
  }
 
