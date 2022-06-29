#include "mainwindow.h"
#include "homewindow.h"
#include "add_book_page.h"
#include"signupwindow.h"
#include "./ui_mainwindow.h"
#include"global_variables.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include<QMessageBox>

HomeWindow* h_login;
signupwindow* s;
add_book_page* test;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    QString backgroundImage_src= "/home/goutham/Coding/CS1023-SDF/Image/mainpage.jpg";
    QPixmap bkgnd(backgroundImage_src);
    bkgnd=bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    login_db = QSqlDatabase::addDatabase("QMYSQL","login_connect");
    login_db.setHostName(IP_address);
    login_db.setPort(3306);
    login_db.setDatabaseName("Project");
    login_db.setUserName(db_username);
    login_db.setPassword(db_pwd);
    login_db.open();
}

MainWindow::~MainWindow()
{
    login_db.close();
    delete ui;
}


void MainWindow::on_loginButton_clicked()
{
    bool valid_credentials = false;
    if((ui->usernameinput->text() != "")&&(ui->pwdinput->text() != ""))
    {
        QSqlQuery login_query(QSqlDatabase::database("login_connect"));
        login_query.exec("SELECT * FROM user_info WHERE user_info.username = '" + ui->usernameinput->text() + "'");
        while(login_query.next()){
            QString password;
            password = login_query.value(6).toString();
            if(password == ui->pwdinput->text()){
                valid_credentials = true;
                current_user.username = ui->usernameinput->text();
                current_user.password = password;
                current_user.first_name = login_query.value(1).toString();
                current_user.last_name = login_query.value(2).toString();
                current_user.mob_num = login_query.value(3).toInt();
                current_user.email = login_query.value(4).toString();
                current_user.add.city = login_query.value(8).toString();
                current_user.add.state = login_query.value(9).toString();
                current_user.add.street = login_query.value(7).toString();
                current_user.DOB = login_query.value(10).toString();
            }
            else{
                QMessageBox::information(this,"Invalid Credential","Please try again with Valid credentials");
            }
        }
        if(!login_query.exec()){
            QMessageBox::information(this,"Data not Found","Username does not exist");
        }
    }
    else{
        QMessageBox::information(this,"Incomplete Fields","Please fill all the fields with valid entries");
    }
    if(valid_credentials){
        h_login = new HomeWindow;
        h_login ->show();
        QWidget::close();
    }
}

void MainWindow::on_signupbutton_clicked()
{
    s = new signupwindow;
    s->show();
    QWidget::close();
}

void MainWindow::on_pwdinput_returnPressed()
{
    bool valid_credentials = false;
    if((ui->usernameinput->text() != "")&&(ui->pwdinput->text() != ""))
    {
        QSqlQuery login_query(QSqlDatabase::database("login_connect"));
        login_query.exec("SELECT * FROM user_info WHERE user_info.username = '" + ui->usernameinput->text() + "'");
        while(login_query.next()){
            QString password;
            password = login_query.value(6).toString();
            if(password == ui->pwdinput->text()){
                valid_credentials = true;
                current_user.username = ui->usernameinput->text();
                current_user.password = password;
                current_user.first_name = login_query.value(1).toString();
                current_user.last_name = login_query.value(2).toString();
                current_user.mob_num = login_query.value(3).toInt();
                current_user.email = login_query.value(4).toString();
                current_user.add.city = login_query.value(8).toString();
                current_user.add.state = login_query.value(9).toString();
                current_user.add.street = login_query.value(7).toString();
                current_user.DOB = login_query.value(10).toString();
            }
            else{
                QMessageBox::information(this,"Invalid Credential","Please try again with Valid credentials");
            }
        }
        if(!login_query.exec()){
            QMessageBox::information(this,"Data not Found","Username does not exist");
        }
    }
    else{
        QMessageBox::information(this,"Incomplete Fields","Please fill all the fields with valid entries");
    }
    if(valid_credentials){
        h_login = new HomeWindow;
        h_login ->show();
        QWidget::close();
    }
}
