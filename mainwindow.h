#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/*!
 * \brief The MainWindow class
 *
 * This window asks for login information, here enter the username
 * and password and then press the login button.if the credentials
 * are correct, you can see a homewindow.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief MainWindow constructor
     *
     * It connects to the database using the variables in global_variables.h as
     * credentials. Sets the ui background image, customises button style and design.
     *
     * \param parent
     */
    MainWindow(QWidget *parent = nullptr);
    //! A destructor
    ~MainWindow();

private slots:
    /*!
     * \brief on_loginButton_clicked
     *
     * After entering the username and password, clicking the login button on
     * mainwindow, first checks if the username exists, if it exists,then
     * checks if the corresponding password matches the entered password,if both
     * the credentials match, then the login was successful and a homewindow appears.
     * If they don't match, then a message box pops up, saying that "Please try again
     * using valid credentials."
     */
    void on_loginButton_clicked();


    /*!
     * \brief on_signupbutton_clicked
     *
     * If there is a new user, he/she can click sign up button on the ui window and
     * a new signup window appears.
     */
    void on_signupbutton_clicked();

    /*!
     * \brief on_pwdinput_returnPressed
     *
     * This function is same as on_loginButton_clicked(). The only difference is that it
     * can be called by hitting enter key on the keyboard.
     */
    void on_pwdinput_returnPressed();

private:
    Ui::MainWindow *ui;

    /*!
     * \brief login_db This handles a connection to a database.
     */
    QSqlDatabase login_db;
};
#endif // MAINWINDOW_H
