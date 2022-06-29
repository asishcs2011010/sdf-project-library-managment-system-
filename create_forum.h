#ifndef CREATE_FORUM_H
#define CREATE_FORUM_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class create_forum; }
QT_END_NAMESPACE

/*!
 * \brief The create_forum class
 *
 * This is a class for creating a new forum
 */
class create_forum : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief create_forum
     *
     * First it sets the ui, background, the buttons style and design, then it connects
     * to the database.
     *
     * \param parent
     */
    create_forum(QWidget *parent = nullptr);

    /*!
     * ~create_forum() - destructor
     *
     * It closes the database connection and deletes the ui page.
     */
    ~create_forum();

private slots:
    /*!
     * \brief on_createforum_clicked
     *
     * After entering all the info required, clicking on create forum button calls this
     * function.It first checks that no entry is empty. Next this function inserts the
     * name of forum, book followed and forum head i.e., the user's name into the database.
     * And if the query gets executed, then a message will be shown that the forum has been
     * added successfully.
     */
    void on_createforum_clicked();

    /*!
     * \brief on_cancelbutton_clicked
     *
     * On clicking the cancel button this function is called and it just closes the window.
     *
     */
    void on_cancelbutton_clicked();

    /*!
     * \brief on_bookfollowed_returnPressed
     *
     * This function is same as on_createforum_clicked(). The only difference is this
     * function gets called, when the user hits enter key and has same function as of the
     * on_createforum_clicked().
     */
    void on_bookfollowed_returnPressed();

private:
    Ui::create_forum *ui;

    /*!
     * \brief forum_database
     *
     * This handles a connection to a database.
     */
    QSqlDatabase forum_database;
};
#endif // CREATE_FORUM_H
