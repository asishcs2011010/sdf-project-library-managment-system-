#ifndef YOURFORUMS_H
#define YOURFORUMS_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class yourforums;
}

/*!
 * \brief The yourforums class
 *
 * This class is for the forums that user has joined.
 */
class yourforums : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief yourforums
     *
     * First, sets the ui, then connects to the database. Next a new QSqlQueryModel is
     * made. Then we set the Query and then finally connect the data to table view widget.
     *
     *
     * \param parent
     */
    explicit yourforums(QWidget *parent = nullptr);

    /*!
     *  ~yourforums() - destructor
     *
     *  Closes the database and deletes the ui page.
     */
    ~yourforums();

private:
    Ui::yourforums *ui;
    /*!
     * \brief model
     *
     * This is a object of type QSqlQueryModel pointer, which provides a read-only data for
     * SQL result sets.
     */
    QSqlQueryModel* model;
    /*!
     * \brief yourforums_db
     *
     * This handles a connection to a database.
     */
    QSqlDatabase yourforums_db;
};

#endif // YOURFORUMS_H
