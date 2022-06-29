#include "signupwindow.h"
#include "ui_signupwindow.h"
#include "homewindow.h"
#include"global_variables.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include<QMessageBox>

HomeWindow* h_signup;

signupwindow::signupwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signupwindow)
{
    ui->setupUi(this);
    QString backgroundImage_src="/home/goutham/Coding/CS1023-SDF/Image/mainpage.jpg";
    QPixmap bkgnd(backgroundImage_src);
    bkgnd=bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    signup_db = QSqlDatabase::addDatabase("QMYSQL","signup_connect");
    signup_db.setHostName(IP_address);
    signup_db.setPort(3306);
    signup_db.setDatabaseName("Project");
    signup_db.setUserName(db_username);
    signup_db.setPassword(db_pwd);
    signup_db.open();
}

signupwindow::~signupwindow()
{
    signup_db.close();
    delete ui;
}

void signupwindow::on_signupbutton_clicked()
{

    if(ui->fname->text() == nullptr || ui->lname->text()==nullptr || ui->add1->text()==nullptr || ui->add2->text()==nullptr || ui->city->text()==nullptr || ui->mobile->text()==nullptr ||
         ui->pwd->text()==nullptr || ui->state->text()==nullptr || ui->username->text()==nullptr)
    {
        QMessageBox::information(this,"Incomplete Data","Please fill all the fields with appropriate data");
    }
    else
    {
            QSqlQuery signup_query(QSqlDatabase::database("signup_connect"));
            signup_query.prepare("INSERT INTO user_info(fname,lname,mobile,email,username,password,address,city,state,DOB) VALUES (:fname,:lname,:mobile,:email,:username,:password,:address,:city,:state,:DOB)");

            signup_query.bindValue(":fname",ui->fname->text());
            signup_query.bindValue(":lname",ui->lname->text());
            signup_query.bindValue(":mobile",ui->mobile->text());
            signup_query.bindValue(":email",ui->email->text());
            signup_query.bindValue(":username",ui->username->text());
            signup_query.bindValue(":password",ui->pwd->text());
            signup_query.bindValue(":address",ui->add1->text()+ui->add2->text());
            signup_query.bindValue(":city",ui->city->text());
            signup_query.bindValue(":state",ui->state->text());
            signup_query.bindValue(":DOB",ui->dob->text());

            if(signup_query.exec())
            {
                current_user.username = ui->username->text();
                current_user.password = ui->pwd->text();
                current_user.first_name = signup_query.value(1).toString();
                current_user.last_name = signup_query.value(2).toString();
                current_user.mob_num = signup_query.value(3).toInt();
                current_user.email = signup_query.value(4).toString();
                current_user.add.city = signup_query.value(8).toString();
                current_user.add.state = signup_query.value(9).toString();
                current_user.add.street = signup_query.value(7).toString();
                current_user.DOB = signup_query.value(10).toString();
                h_signup = new HomeWindow;
                h_signup ->show();
                QWidget::close();
            }
            else{
                QMessageBox::information(this,"Database error","Database connection error");
                qDebug() << signup_query.lastError();
            }

     }

}

void signupwindow::on_pwd_returnPressed()
{
    if(ui->fname->text() == nullptr || ui->lname->text()==nullptr || (ui->add1->text()==nullptr && ui->add2->text()==nullptr) || ui->city->text()==nullptr || ui->mobile->text()==nullptr ||
         ui->pwd->text()==nullptr || ui->state->text()==nullptr || ui->username->text()==nullptr)
    {
        QMessageBox::information(this,"Incomplete Data","Please fill all the fields with appropriate data");
    }
    else
    {
            QSqlQuery signup_query(QSqlDatabase::database("signup_connect"));
            signup_query.prepare("INSERT INTO user_info(fname,lname,mobile,email,username,password,address,city,state,DOB) VALUES (:fname,:lname,:mobile,:email,:username,:password,:address,:city,:state,:DOB)");

            signup_query.bindValue(":fname",ui->fname->text());
            signup_query.bindValue(":lname",ui->lname->text());
            signup_query.bindValue(":mobile",ui->mobile->text());
            signup_query.bindValue(":email",ui->email->text());
            signup_query.bindValue(":username",ui->username->text());
            signup_query.bindValue(":password",ui->pwd->text());
            signup_query.bindValue(":address",ui->add1->text()+ui->add2->text());
            signup_query.bindValue(":city",ui->city->text());
            signup_query.bindValue(":state",ui->state->text());
            signup_query.bindValue(":DOB",ui->dob->text());

            if(signup_query.exec())
            {
                current_user.username = ui->username->text();
                current_user.password = ui->pwd->text();
                current_user.first_name = signup_query.value(1).toString();
                current_user.last_name = signup_query.value(2).toString();
                current_user.mob_num = signup_query.value(3).toInt();
                current_user.email = signup_query.value(4).toString();
                current_user.add.city = signup_query.value(8).toString();
                current_user.add.state = signup_query.value(9).toString();
                current_user.add.street = signup_query.value(7).toString();
                current_user.DOB = signup_query.value(10).toString();
                h_signup = new HomeWindow;
                h_signup ->show();
                QWidget::close();
            }
            else{
                QMessageBox::information(this,"Database error","Database connection error");
            }

     }
}
