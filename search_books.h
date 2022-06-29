#ifndef SEARCH_BOOKS_H
#define SEARCH_BOOKS_H

#include <QMainWindow>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class search_books; }
QT_END_NAMESPACE

/*!
 * \brief The search_books class
 *
 * This class is for searching books from the database.
 */
class search_books : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief search_books constructor
     *
     * First it sets the ui, background, the buttons style and design, then it connects
     * to the database.
     *
     * \param parent
     */
    search_books(QWidget *parent = nullptr);

    /*!
     * ~search_books() - destructor
     *
     * It closes the database connection and deletes the ui page.
     */
    ~search_books();

private slots:
    /*!
     * \brief on_searchbooksbutton_clicked
     *
     * After entering the book's name, clicking on search button calls this function.
     * It runs the query model and displays the info of the book in the table view widget.
     *
     */
    void on_searchbooksbutton_clicked();

    /*!
     * \brief on_sendbookreq_button_clicked
     *
     * This function will be called after clicking the send book request. This function sends
     * a borrow request to the owner of the book.
     */
    void on_sendbookreq_button_clicked();

    /*!
     * \brief on_booksearch_returnPressed
     *
     * This function is same as on_searchbooksbutton_clicked(). The only difference is this
     * function gets called, when the user hits enter key and has same function as of the
     * on_searchbooksbutton_clicked()
     */
    void on_booksearch_returnPressed();

private:
    Ui::search_books *ui;

    /*!
     * \brief model
     *
     * This is a object of type QSqlQueryModel pointer, which provides a read-only data for
     * SQL result sets.
     */
    QSqlQueryModel* model;

    /*!
     * \brief search_books_db
     *
     * This handles a connection to a database.
     */
    QSqlDatabase search_books_db;

};
#endif // SEARCH_BOOKS_H
