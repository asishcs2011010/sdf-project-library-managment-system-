#ifndef BORROWED_BOOKS_H
#define BORROWED_BOOKS_H
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class borrowed_books; }
QT_END_NAMESPACE

/*!
 * \brief The borrowed_books class
 *
 * This class is for the books that are borrowed by the user.
 */
class borrowed_books : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief borrowed_books constructor
     *
     * First it connects to the database.
     * After a successful connection, it runs a query model for the borrowed books,
     * and creates a table that shows book's name, it's owner and the date till which
     * the user borrowed.
     *
     * \param parent
     */
    borrowed_books(QWidget *parent = nullptr);

    /*!
     * ~borrowed_books() - destructor
     */
    ~borrowed_books();

private:
    Ui::borrowed_books *ui;

    /*!
     * \brief QSqlQueryModel* model
     *
     * This is a object of type QSqlQueryModel pointer, which provides a read-only data for
     * SQL result sets.
     */
    QSqlQueryModel* model;

    /*!
     * \brief borrowed_books_db
     *
     * This handles a connection to a database.
     */
    QSqlDatabase borrowed_books_db;
};
#endif // BORROWED_BOOKS_H
