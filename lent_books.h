#ifndef LENT_BOOKS_H
#define LENT_BOOKS_H
#include <QtSql>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class lent_books; }
QT_END_NAMESPACE

/*!
 * \brief The lent_books class
 *
 * This class is for the books that are lent by the user to others.
 */
class lent_books : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief lent_books constructor
     *
     * First it connects to the database.
     * After a successful connection, it runs a query model for the lent books,
     * and creates a table that shows book's name, who has borrowed it and the date till which
     * the other person has borrowed.
     *
     * \param parent
     */
    lent_books(QWidget *parent = nullptr);

    /*!
     * ~lent_books() - destructor
     */
    ~lent_books();

private:
    Ui::lent_books *ui;

    /*!
     * \brief model
     *
     * This is a object of type QSqlQueryModel pointer, which provides a read-only data for
     * SQL result sets.
     */
    QSqlQueryModel* model;

    /*!
     * \brief lent_books_db
     *
     * This handles a connection to a database.
     */
    QSqlDatabase lent_books_db;
};
#endif // LENT_BOOKS_H
