#include "changepassword.h"
#include "ui_changepassword.h"
#include "global_variables.h"


changepassword::changepassword(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::changepassword)
{
    ui->setupUi(this);

    QString backgroundImage_src="/home/goutham/Coding/CS1023-SDF/Image/profile_page.jpg";
    QPixmap bkgnd(backgroundImage_src);
    bkgnd=bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    ui->changepwd_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");

    change_pwd_db = QSqlDatabase::addDatabase("QMYSQL","change_pwd_connection");
    change_pwd_db.setDatabaseName("Project");
    change_pwd_db.setHostName(IP_address);
    change_pwd_db.setPassword(db_pwd);
    change_pwd_db.setPort(3306);
    change_pwd_db.setUserName(db_username);
    change_pwd_db.open();
}

changepassword::~changepassword()
{
    change_pwd_db.close();
    delete ui;
}

void changepassword::on_new_passwordtxt_returnPressed()
{
    if(ui->old_passwordtxt->text() == nullptr || ui->new_passwordtxt->text() == nullptr){
        QMessageBox::information(this,"Incomplete Fields","Please fill all the required Fields with appropriate data");
    }
    else{
        if(ui->old_passwordtxt->text() == ui->new_passwordtxt->text()){
            QMessageBox::information(this,"Notice","Old password cannot be same as new password");
        }
        else{
            if(current_user.password == ui->old_passwordtxt->text()){
                QSqlQuery change_pwd_query(QSqlDatabase::database("change_pwd_connection"));
                change_pwd_query.exec("UPDATE user_info SET password = '"+ui->new_passwordtxt->text()+"' WHERE password = '"+ui->old_passwordtxt->text()+"';");
                if(change_pwd_query.exec()){
                    QMessageBox::information(this,"Successfully changed","Password changed succesfully");
                    ui->old_passwordtxt->clear();
                    ui->new_passwordtxt->clear();
                }
                else{
                    QMessageBox::information(this,"Unsuccessful Entry","Password was not changed successfully");
                }
            }
            else{
                QMessageBox::information(this,"Wrong Password","Old password is incorrect");
            }
        }
    }
}

void changepassword::on_changepwd_button_clicked()
{
    if(ui->old_passwordtxt->text() == nullptr || ui->new_passwordtxt->text() == nullptr){
        QMessageBox::information(this,"Incomplete Fields","Please fill all the required Fields with appropriate data");
    }
    else{
        if(ui->old_passwordtxt->text() == ui->new_passwordtxt->text()){
            QMessageBox::information(this,"Notice","Old password cannot be same as new password");
        }
        else{
            if(current_user.password == ui->old_passwordtxt->text()){
                QSqlQuery change_pwd_query(QSqlDatabase::database("change_pwd_connection"));
                change_pwd_query.exec("UPDATE user_info SET password = '"+ui->new_passwordtxt->text()+"' WHERE password = '"+ui->old_passwordtxt->text()+"';");
                if(change_pwd_query.exec()){
                    QMessageBox::information(this,"Successfully changed","Password changed succesfully");
                }
                else{
                    QMessageBox::information(this,"Unsuccessful Entry","Password was not changed successfully");
                }
            }
            else{
                QMessageBox::information(this,"Wrong Password","Old password is incorrect");
            }
        }
    }
}
