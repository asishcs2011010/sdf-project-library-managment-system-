#ifndef VIEW_PROFILE_H
#define VIEW_PROFILE_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include<QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class view_profile; }
QT_END_NAMESPACE
/*!
 * \brief The view_profile class
 *
 * Allows the user to view his/her details.
 */
class view_profile : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief view_profile constructor
     *
     * Sets the ui background image, customises button style and design.
     *
     * \param parent
     */
    view_profile(QWidget *parent = nullptr);

    /*!
     * \brief ~view_profile() destructor
     */
    ~view_profile();

private:
    Ui::view_profile *ui;

    /*!
     * \brief view_profile_db - This handles a connection to a database.
     */
    QSqlDatabase view_profile_db;
};
#endif // VIEW_PROFILE_H
