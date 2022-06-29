#include "find_friend.h"
#include "ui_find_friend.h"
#include "global_variables.h"
#include <QMessageBox>

find_friend::find_friend(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::find_friend)
{
    ui->setupUi(this);
    QString backgroundImage_src="/home/goutham/Coding/CS1023-SDF/Image/friend_page.jpg";
    QPixmap bkgnd(backgroundImage_src);
    bkgnd=bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    ui->friendsearchbutton->setStyleSheet("QPushButton{font-size: 16px;color: rgb(38,56,76);background-color: rgb(170, 255, 255);}");
    ui->friend_req_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(38,56,76);background-color: rgb(170, 255, 255);}");

    find_friend_db = QSqlDatabase::addDatabase("QMYSQL","find_friend_connection");
    find_friend_db.setDatabaseName("Project");
    find_friend_db.setHostName(IP_address);
    find_friend_db.setPassword(db_pwd);
    find_friend_db.setPort(3306);
    find_friend_db.setUserName(db_username);
    find_friend_db.open();
}

find_friend::~find_friend()
{
    find_friend_db.close();
    delete ui;
}

void find_friend::on_friendsearchbutton_clicked()
{
    if(ui->search_bartxt->text() == nullptr){
        QMessageBox::information(this,"Incomplete Fields","Please enter a username to search");
    }
    else{
        this->model = new QSqlQueryModel;
        model->setQuery("SELECT username AS Username, address AS Address,city AS City, state AS State FROM user_info WHERE username LIKE '%"+ui->search_bartxt->text()+"%';",QSqlDatabase::database("find_friend_connection"));

        ui->friends_table->setModel(model);
        ui->friends_table->resizeColumnsToContents();
    }
}

void find_friend::on_friend_req_button_clicked()
{
    if(ui->friends_table->selectionModel()->selectedRows(0).value(0).data().toString() == nullptr){
        QMessageBox::information(this,"Select a Row","Please select the whole row before continuing");
        qDebug() << ui->friends_table->selectionModel()->selectedRows(0).value(0).data().toString();
    }
    else{
        QString status;
        QSqlQuery friend_req_check_query(QSqlDatabase::database("find_friend_connection"));
        friend_req_check_query.exec("SELECT req_status FROM other_requests where req_from ='"+current_user.username+"' AND req_to LIKE '"+ui->friends_table->selectionModel()->selectedRows(0).value(0).data().toString()+"';");
        while(friend_req_check_query.next()){
            status = friend_req_check_query.value(0).toString();
        }
        if(status == "Pending"){
            QMessageBox::information(this,"Pending Request Active","There is an active request already in queue. Wait for the reciever to respond");
        }
        else if(status == "Accepted"){
            QMessageBox::information(this,"Already your Friend","You are already friends with this user");
        }
        else{
            QSqlQuery friend_req_query(QSqlDatabase::database("find_friend_connection"));
            friend_req_query.prepare("INSERT INTO other_requests(req_from,req_to,req_type,object_name,req_status) VALUES(:req_from, :req_to, 'Friend' , :object_name, 'Pending');");
            friend_req_query.bindValue(":req_from",current_user.username);
            friend_req_query.bindValue(":req_to",ui->friends_table->selectionModel()->selectedRows(0).value(0).data().toString());
            friend_req_query.bindValue(":object_name",ui->friends_table->selectionModel()->selectedRows(0).value(0).data().toString());

            if(friend_req_query.exec()){
                QMessageBox::information(this,"Request Sent","Request Sent successfully");
            }
            else{
                QMessageBox::information(this,"Request not Sent","Failed to send request");
                qDebug() << friend_req_query.lastError();
            }
        }
    }
}

void find_friend::on_search_bartxt_returnPressed()
{
    if(ui->search_bartxt->text() == nullptr){
        QMessageBox::information(this,"Incomplete Fields","Please enter a username to search");
    }
    else{
        this->model = new QSqlQueryModel;
        model->setQuery("SELECT username AS Username, address AS Address,city AS City, state AS State FROM user_info WHERE username LIKE '%"+ui->search_bartxt->text()+"%';",QSqlDatabase::database("find_friend_connection"));

        ui->friends_table->setModel(model);
        ui->friends_table->resizeColumnsToContents();
    }
}
