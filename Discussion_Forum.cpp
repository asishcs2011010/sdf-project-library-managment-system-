#include"Discussion_Forum.h"


    Dis_Forum::Dis_Forum(QString _name, QString _book_followed, user_t _user){
        name = _name;
        book_followed = _book_followed;
        forum_head = _user;
    }

//Factory method to create a new forum.
void create_forum(QString forum_name, QString book_followed, user_t forum_head){
    Dis_Forum Dis_Forum(forum_name,book_followed,forum_head);
} 
