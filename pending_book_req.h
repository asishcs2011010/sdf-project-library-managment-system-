#ifndef PENDING_BOOK_REQ_H
#define PENDING_BOOK_REQ_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class pending_book_req;
}

/*!
 * \brief The pending_book_req class
 *
 * This is a class for pending book requests.
 */
class pending_book_req : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief pending_book_req
     *
     * It sets the ui background, button style and connects to the database.
     * And it also makes a new query model.
     *
     * \param parent
     */
    explicit pending_book_req(QWidget *parent = nullptr);
    /*!
     *  ~pending_book_req() - destructor
     */
    ~pending_book_req();

private slots:
    /*!
     * \brief on_acceptreq_button_clicked
     *
     * On clicking accept button, this function gets called.
     * It accepts the borrow book requests from the other user.
     */
    void on_acceptreq_button_clicked();

    /*!
     * \brief on_rejectreq_button_clicked
     *
     * On clicking reject button this function is called.
     * It rejects the request sent by the other user.
     */
    void on_rejectreq_button_clicked();

    /*!
     * \brief on_returnedbook_button_clicked
     *
     * On clicking returned button, it calls this function.
     * If the return query model gets excecuted properly then,
     * then the book has been returned successfully, and if
     * the update query model has also executed, then the book
     *  status has been updated to returned. Else, the book
     *  status hasn't updated. And if the return query model
     *  doesn't execute then the return has failed, and couldn't
     *  return book.
     */
    void on_returnedbook_button_clicked();


private:
    Ui::pending_book_req *ui;
    /*!
     * \brief book_req_db
     *
     * This handles a connection to a database.
     */
    QSqlDatabase book_req_db;
    /*!
     * \brief model
     *
     * This is a object of type QSqlQueryModel pointer, which provides a read-only data for
     * SQL result sets.
     */
    QSqlQueryModel* model;
};

#endif // PENDING_BOOK_REQ_H
