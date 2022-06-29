#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QWidget>
#include<QtSql>

namespace Ui {
class signupwindow;
}

/*!
 * \brief The signupwindow class
 *
 * this window asks the user to enter his first name, last name, dob
 * address, email id, mobile number and the user has to set new username
 * and password, which he has to use at the time og login next time.
 */
class signupwindow : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief signupwindow constructor
     *
     * It connects to the database using the variables in global_variables.h as
     * credentials. Sets the ui background image, customises button style and design.
     *
     * \param parent
     */
    explicit signupwindow(QWidget *parent = nullptr);

    /*!
     * \brief ~signupwindow() destructor
     */
    ~signupwindow();


private slots:
    /*!
     * \brief on_signupbutton_clicked
     *
     * after entering the required data, clicking on signup button calls this function,
     * first checks if all the info is added or not, if anyone of them is empty, then a
     * message box appears telling that "Incomplete Data","Please fill all the fields with
     * appropriate data", else it inserts the data into database.
     */
    void on_signupbutton_clicked();

    /*!
     * \brief on_pwd_returnPressed
     *
     * This function is same as on_signupButton_clicked(). The only difference is that it
     * can be called by hitting enter key on the keyboard.
     */
    void on_pwd_returnPressed();

private:
    Ui::signupwindow *ui;

    /*!
     * \brief signup_db - This handles a connection to a database.
     */
    QSqlDatabase signup_db;
};

#endif // SIGNUPWINDOW_H
