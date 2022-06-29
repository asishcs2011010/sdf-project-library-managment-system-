#ifndef _DIS_FORUM_H
#define _DIS_FORUM_H
#include <QtCore>
#include"user.h"
/*!
 * \brief The Dis_Forum class
 *
 * This class is for a discussion forum.
 */
class Dis_Forum{
    private:
    QString name; //name of discussion forum
    QString book_followed;//The book followed by the forum
    user_t forum_head;        //Sort of like the group admin

    //there will be a members list for every forum on the database
    public :
    Dis_Forum()=default;
    Dis_Forum(QString , QString, user_t );
};

//Factory method to create a new forum.
void create_forum(QString , QString, user_t );

#endif
