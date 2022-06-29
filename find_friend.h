#ifndef FIND_FRIEND_H
#define FIND_FRIEND_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class find_friend;
}

/*!
 * \brief The find_friend class
 *
 * This class is for searching friends from the database.
 */
class find_friend : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief find_friend
     *
     * First it sets the ui background, the buttons style and design, then it connects
     * to the database.
     *
     * \param parent
     */
    explicit find_friend(QWidget *parent = nullptr);

    /*!
     * ~find_friend() - destructor
     *
     * It closes the database connection and deletes the ui page.
     */
    ~find_friend();

private slots:
    /*!
     * \brief on_friendsearchbutton_clicked
     *
     * After entering the friend's name, clicking on search button calls this function.
     * It runs the query model. checks if the user is already friend with the another user or not.
     * If the user is not friend, then a request is sent to the other user.
     */
    void on_friendsearchbutton_clicked();

    /*!
     * \brief on_friend_req_button_clicked
     *
     *checks if the user is already friend with the another user or not.
     * If the user is not friend, then a request is sent to the other user.
     */
    void on_friend_req_button_clicked();

    /*!
     * \brief on_search_bartxt_returnPressed
     *
     * This function is same as on_friendsearchbutton_clicked(). The only difference is this
     * function gets called, when the user hits enter key and has same function as of the
     * on_friendsearchbutton_clicked().
     */
    void on_search_bartxt_returnPressed();

private:
    Ui::find_friend *ui;

    /*!
     * \brief find_friend_db
     *
     * This handles a connection to a database.
     */
    QSqlDatabase find_friend_db;

    /*!
     * \brief model
     *
     * This is a object of type QSqlQueryModel pointer, which provides a read-only data for
     * SQL result sets.
     */
    QSqlQueryModel* model;
};

#endif // FIND_FRIEND_H
