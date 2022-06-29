#ifndef YOURFRIENDS_H
#define YOURFRIENDS_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class yourfriends;
}

/*!
 * \brief The yourfriends class
 *
 * This class is for the friends of user.
 */
class yourfriends : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief yourfriends
     *
     * First, sets the ui, then connects to the database. Next a new QSqlQueryModel is
     * made. Then we set the Query and then finally connect the data to table view widget.
     *
     * \param parent
     */
    explicit yourfriends(QWidget *parent = nullptr);

    /*!
     * ~yourfriends() - destructor
     *
     * Closes the database and deletes the ui page.
     */
    ~yourfriends();

private:
    Ui::yourfriends *ui;

    /*!
     * \brief model
     *
     * This is a object of type QSqlQueryModel pointer, which provides a read-only data for
     * SQL result sets.
     */
    QSqlQueryModel* model;

    /*!
     * \brief yourfriends_db
     *
     * This handles a connection to a database.
     */
    QSqlDatabase yourfriends_db;
};

#endif // YOURFRIENDS_H
