#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class changepassword;
}

/*!
 * \brief The changepassword class
 *
 * This class is for changing password.
 */
class changepassword : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief changepassword
     *
     *First it sets the ui background, the buttons style and design, then it connects
     * to the database.
     *
     * \param parent
     */
    explicit changepassword(QWidget *parent = nullptr);

    /*!
     * ~changepassword() - destructor
     */
    ~changepassword();

private slots:

    /*!
     * \brief on_changepwd_button_clicked
     *
     * After entering old and new password, clicking on change password button
     * calls this function. It first checks that both the fields are not empty,
     * and then checks if old and new password are same or not. If they are same,
     * then a error message gets displayed saying that old and new password cannot
     * be same. Now if old and new aren't same,it checks if the old password entered
     * is correct or not, if its correct then the query model gets executed,
     * if the execution is successful, then message appears, "successfully changed"
     * else "unsuccessful entry". If the old password is wrong, then a error message
     * is shown, "old password is incorrect".
     *
     */
    void on_changepwd_button_clicked();

    /*!
     * \brief on_new_passwordtxt_returnPressed
     * This function has same functionality as that of on_changepwd_button_clicked().
     * the only difference is that it gets called on hitting enter key.
     *
     */
    void on_new_passwordtxt_returnPressed();

private:
    Ui::changepassword *ui;
    QSqlDatabase change_pwd_db;
};

#endif // CHANGEPASSWORD_H
