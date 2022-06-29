#ifndef _USER_H
#define _USER_H
#include<QtCore>
#include <Book.h>


/*!
 * \brief The person_t class
 *
 * This class has members for storing a person's first name, last name, address,
 * mobile number, date of birth and email address.
 */
class person_t{
    public:
    QString first_name; //first name of the person
    QString last_name; //last name of the person
    address add; // address of the person
    unsigned mob_num; //moblie number of the person
    QString DOB; // date of birth of the person
    QString email; // email address of the person

};

/*!
 * \brief The user_t class
 *
 * It inherits from person_t class. It has members that store username and
 * password of the user.
 */
class user_t : public person_t{
    public:
    QString password;// user's password
    QString username;// user's username
};


void Send_borrow_request(Book);

#endif
