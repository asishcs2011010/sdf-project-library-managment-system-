#include "homewindow.h"
#include "add_book_page.h"
#include "ui_homewindow.h"
#include "borrowed_books.h"
#include "lent_books.h"
#include "create_forum.h"
#include "find_forum.h"
#include "search_books.h"
#include "view_profile.h"
#include "changepassword.h"
#include "find_friend.h"
#include "chatclient.h"
#include "pending_book_req.h"
#include "pending_friend_req.h"
#include "pending_forum_req.h"
#include "yourfriends.h"
#include "yourforums.h"


HomeWindow::HomeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomeWindow)
{
    ui->setupUi(this);

    QString backgroundImage_src= "/home/goutham/Coding/CS1023-SDF/Image/homewindow_page.jpg";
    QPixmap bkgnd(backgroundImage_src);
    bkgnd=bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    ui->newbook_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->searchbook_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->searchforum_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->viewprofile_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->change_pwd_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->newforum_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->yourfriends_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->findfriend_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->borrowedbooks->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->lentbooks->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->yourforums_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->publicchat_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->bookreqs_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->friendreqs_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->forumreq_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");

}

HomeWindow::~HomeWindow()
{
    delete ui;
}

void HomeWindow::on_newbook_button_clicked()
{
    add_book_page* add_book = new add_book_page;
    add_book->show();
}


void HomeWindow::on_newforum_button_clicked()
{
    create_forum* new_forum_page = new create_forum;
    new_forum_page->show();
}

void HomeWindow::on_searchforum_button_clicked()
{
    find_forum* find_forum_page = new find_forum;
    find_forum_page->show();
}

void HomeWindow::on_viewprofile_button_clicked()
{
    view_profile* view_profile_page = new view_profile;
    view_profile_page->show();
}

void HomeWindow::on_findfriend_button_clicked()
{
    find_friend* find_friend_page = new find_friend;
    find_friend_page->show();
}

void HomeWindow::on_borrowedbooks_clicked()
{
    borrowed_books* borrowed_book = new borrowed_books;
    borrowed_book->show();
}

void HomeWindow::on_lentbooks_clicked()
{
    lent_books* lent_book = new lent_books;
    lent_book->show();
}

void HomeWindow::on_searchbook_button_clicked()
{
    search_books* search_book_page = new search_books;
    search_book_page->show();
}

void HomeWindow::on_change_pwd_button_clicked()
{
    changepassword* change_pwd = new changepassword;
    change_pwd->show();
}

void HomeWindow::on_publicchat_button_clicked()
{
    chatclient* chat_window = new chatclient;
    chat_window->show();
}

void HomeWindow::on_bookreqs_button_clicked()
{
    pending_book_req* book_req = new pending_book_req;
    book_req->show();
}

void HomeWindow::on_friendreqs_button_clicked()
{
    pending_friend_req* friend_req = new pending_friend_req;
    friend_req->show();
}

void HomeWindow::on_forumreq_button_clicked()
{
    pending_forum_req* forum_req = new pending_forum_req;
    forum_req->show();
}

void HomeWindow::on_yourfriends_button_clicked()
{
    yourfriends* yourfriends_page = new yourfriends;
    yourfriends_page->show();
}

void HomeWindow::on_yourforums_button_clicked()
{
    yourforums* yourforums_page = new yourforums;
    yourforums_page->show();
}
