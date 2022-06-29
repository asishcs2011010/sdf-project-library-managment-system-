#ifndef FIND_FORUM_H
#define FIND_FORUM_H

#include <QMainWindow>
#include<QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class find_forum; }
QT_END_NAMESPACE

/*!
 * \brief The find_forum class
 *
 * This class is for searching forums from the database.
 */
class find_forum : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief find_forum constructor
     *
     * First it sets the ui background, the buttons style and design, then it connects
     * to the database.
     *
     * \param parent
     */
    find_forum(QWidget *parent = nullptr);

    /*!
     * ~find_forum() - destructor
     *
     * It closes the database connection and deletes the ui page.
     */
    ~find_forum();

private slots:
    /*!
     * \brief on_searchforumbutton_clicked
     *
     * After entering the forum's name, clicking on search button calls this function.
     * It runs the query model and displays the info of the forum like the book the forum
     * follows and head of the forum in the table view widget.
     */
    void on_searchforumbutton_clicked();

    /*!
     * \brief on_joinforum_button_clicked
     *
     * This function will be called after clicking the join forum request. This function sends
     * a join request to the head of the forum, if the user is not a part of the forum and if
     * the user is part of the forum then a message box appears saying that you have already
     * joined forum.
     */
    void on_joinforum_button_clicked();

    /*!
     * \brief on_forumsearch_returnPressed
     *
     * This function is same as on_searchforumbutton_clicked(). The only difference is this
     * function gets called, when the user hits enter key and has same function as of the
     * on_searchforumbutton_clicked()
     */
    void on_forumsearch_returnPressed();

private:
    Ui::find_forum *ui;

    /*!
     * \brief model
     *
     * This is a object of type QSqlQueryModel pointer, which provides a read-only data for
     * SQL result sets.
     */
    QSqlQueryModel* model;

    /*!
     * \brief find_forum_db
     *
     * This handles a connection to a database.
     */
    QSqlDatabase find_forum_db;
};
#endif // FIND_FORUM_H
