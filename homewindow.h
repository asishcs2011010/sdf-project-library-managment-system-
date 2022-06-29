#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>

namespace Ui {
class HomeWindow;
}

/*!
 * \brief The HomeWindow class
 *
 * This is the homewindow which allows user to add a new book, see the list of books
 * which he has borrowed and lent to others, find friends, change password, view profile,
 * search for books.
 */
class HomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief HomeWindow constructor.
     *
     * Sets the ui background image, customises button style and design.
     *
     * \param parent
     */
    explicit HomeWindow(QWidget *parent = nullptr);

    /*!
     * \brief ~HomeWindow() destructor
     */
    ~HomeWindow();

private slots:
    /*!
     * \brief on_newbook_button_clicked
     *
     * On clicking Add book Button, this function is called.
     * It creates a new object of add_book_page and shows the ui
     * page for adding new books into the database.
     */
    void on_newbook_button_clicked();

    /*!
     * \brief on_newforum_button_clicked
     *
     * On clicking Create New Forum button, this function is called.
     * It creates a new object of create_forum and shows the ui
     * page for creating a new forum.
     */
    void on_newforum_button_clicked();

    /*!
     * \brief on_searchforum_button_clicked
     *
     * On clicking Find a Forum button, this function is called.
     * It creates a new object of find_forum and shows the ui
     * page for searching for the forum.
     */
    void on_searchforum_button_clicked();

    /*!
     * \brief on_viewprofile_button_clicked
     *
     * On clicking view my profile button, this function is called.
     * It creates a new object of view_profile and shows the ui
     * page which shows the user's details.
     */
    void on_viewprofile_button_clicked();

    /*!
     * \brief on_findfriend_button_clicked
     *
     * On clicking Find friends button, this function is called.
     * It creates a new object of find_friends and shows the ui
     * page for searching friends.
     */
    void on_findfriend_button_clicked();

    /*!
     * \brief on_borrowedbooks_clicked
     *
     * On clicking borrowed books button, this function is called.
     * It creates a new object of borrowed_books and shows the ui
     * page which shows the list of books that you borrowed from others.
     */
    void on_borrowedbooks_clicked();

    /*!
     * \brief on_lentbooks_clicked
     *
     * On clicking lent books button, this function is called.
     * It creates a new object of lent_books and shows the ui
     * page which shows the list of your books that you lent to others.
     */
    void on_lentbooks_clicked();

    /*!
     * \brief on_searchbook_button_clicked
     *
     * On clicking Search for books button, this function is called.
     * It creates a new object of search_books and shows the ui
     * page that is used for searching the book.
     */
    void on_searchbook_button_clicked();

    /*!
     * \brief on_change_pwd_button_clicked
     *
     * On clicking change password button, this function is called.
     * it creates a new object of changepassword and shows the ui
     * page which is used for changing password.
     */
    void on_change_pwd_button_clicked();

    /*!
     * \brief on_publicchat_button_clicked
     *
     * On clicking public chat button, it calls this function.
     * It creates a new object of chatclient class and shows the ui page
     * where user can chat with others.
     */
    void on_publicchat_button_clicked();

    /*!
     * \brief on_bookreqs_button_clicked
     *
     * On clicking book request button, this function gets called,
     * It creates a new object of pending_book_req and shows the ui page
     * of the pending requests.
     */
    void on_bookreqs_button_clicked();

    /*!
     * \brief on_friendreqs_button_clicked
     *
     * On clicking friend request button, this function gets called,
     * It creates a new object of pending_friend_req and shows the ui page
     * of the pending requests.
     */
    void on_friendreqs_button_clicked();

    /*!
     * \brief on_forumreq_button_clicked
     *
     * On clicking forum request button, this function gets called,
     * It creates a new object of pending_forum_req and shows the ui page
     * of the pending requests.
     */
    void on_forumreq_button_clicked();

    /*!
     * \brief on_yourfriends_button_clicked
     *
     * On clicking your forum button, this function gets called,
     * It creates a new object of yourforums and shows the ui page
     * which contains the list of forums that user has joined.
     */
    void on_yourfriends_button_clicked();

    /*!
     * \brief on_yourforums_button_clicked
     *
     * On clicking your friends button, this function gets called,
     * It creates a new object of yourfriends and shows the ui page
     * which contains the list of user's friends.
     */
    void on_yourforums_button_clicked();

private:
    Ui::HomeWindow *ui;
};

#endif // HOMEWINDOW_H
