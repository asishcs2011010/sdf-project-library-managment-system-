#ifndef ADD_BOOK_PAGE_H
#define ADD_BOOK_PAGE_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class add_book_page; }
QT_END_NAMESPACE

/*!
 * \brief The add_book_page class
 *
 * This window asks the user to enter the book's name, it's ISBN number, edition
 * author's name and book's genre has to be selected from the dropdown list on the
 * Add a new book page.
 */
class add_book_page : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief add_book_page constructor
     *
     * Sets the ui background image, customises button style, and design.
     * It also sets placeholder text for the line edits and sets the items of
     * the combo box that are to be shown in the dropdown list of book genre.
     *
     * \param parent
     */
    add_book_page(QWidget *parent = nullptr);

    /*!
     * ~add_book_page() - destructor
     */
    ~add_book_page();

private slots:
    /*!
     * \brief on_addbutton_clicked
     *
     * After entering all the info about the book, clicking on add book button
     * calls this function. This function first connects to the database, then checks if
     * all the entries are filled, if not a error message is displayed. If all the info is
     * entered properly, then the sql query model adds the book's info to the database.
     */
    void on_addbutton_clicked();

private:
    Ui::add_book_page *ui;
    /*!
     * \brief add_book_db
     *
     * This handles a connection to a database
     */
    QSqlDatabase add_book_db;
};
#endif // ADD_BOOK_PAGE_H
