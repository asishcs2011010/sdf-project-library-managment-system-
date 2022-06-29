#ifndef PENDING_FRIEND_REQ_H
#define PENDING_FRIEND_REQ_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class pending_friend_req;
}

/*!
 * \brief The pending_friend_req class
 *
 * This is a class for pending book requests.
 */
class pending_friend_req : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief pending_friend_req
     *
     * It sets the ui background, button style and connects to the database.
     * And it also makes a new query model.
     *
     * \param parent
     */
    explicit pending_friend_req(QWidget *parent = nullptr);

    /*!
     * ~pending_friend_req() - destructor
     */
    ~pending_friend_req();

private slots:
    /*!
     * \brief on_accept_button_clicked
     *
     * On clicking accept button, this function gets called.
     * It accepts the request to become friend with the other user.
     */
    void on_accept_button_clicked();

    /*!
     * \brief on_reject_button_clicked
     *
     * On clicking reject button this function is called.
     * It rejects the request sent by the other user.
     */
    void on_reject_button_clicked();

private:
    Ui::pending_friend_req *ui;

    /*!
     * \brief model
     *
     * This is a object of type QSqlQueryModel pointer, which provides a read-only data for
     * SQL result sets.
     */
    QSqlQueryModel* model;

    /*!
     * \brief friend_req_db
     *
     * This handles a connection to a database.
     */
    QSqlDatabase friend_req_db;
};

#endif // PENDING_FRIEND_REQ_H
