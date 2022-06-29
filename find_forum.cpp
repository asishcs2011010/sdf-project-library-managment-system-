#include "find_forum.h"
#include "./ui_find_forum.h"
#include "global_variables.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include<QMessageBox>

find_forum::find_forum(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::find_forum)
{
    ui->setupUi(this);

    QString backgroundImage_src="/home/goutham/Coding/CS1023-SDF/Image/forum_page.jpg";
    QPixmap bkgnd(backgroundImage_src);
    bkgnd=bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    ui->searchforumbutton->setStyleSheet("QPushButton{font-size: 16px;color: rgb(38,56,76);background-color: rgb(170, 255, 255);}");
    ui->joinforum_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(38,56,76);background-color: rgb(170, 255, 255);}");

    find_forum_db = QSqlDatabase::addDatabase("QMYSQL","find_forum_connection");
    find_forum_db.setDatabaseName("Project");
    find_forum_db.setHostName(IP_address);
    find_forum_db.setPassword(db_pwd);
    find_forum_db.setPort(3306);
    find_forum_db.setUserName(db_username);
    find_forum_db.open();
}

find_forum::~find_forum()
{
    find_forum_db.close();
    delete ui;
}


void find_forum::on_searchforumbutton_clicked()
{

    if(ui->forumsearch->text() == nullptr){
        QMessageBox::information(this,"Incomplete Data Fields","Please type what to search for");
    }
    else{
            this->model = new QSqlQueryModel;
            model->setQuery("SELECT name AS \"Forum Name\",book_followed AS \"Book Followed\", forum_head AS \"Forum Head\"  FROM all_forums WHERE name LIKE '%"+ui->forumsearch->text()+"%';", QSqlDatabase::database("find_forum_connection"));
            ui->forum_search_table->setModel(model);
            ui->forum_search_table->resizeColumnsToContents();
        }

}

void find_forum::on_joinforum_button_clicked()
{
    if(ui->forum_search_table->selectionModel()->selectedRows(0).value(0).data().toString() == nullptr){
        QMessageBox::information(this,"Select a Row","Please select the whole row before continuing");
        qDebug() << ui->forum_search_table->selectionModel()->selectedRows(0).value(0).data().toString();
    }
    else{
        QString status;
        QSqlQuery forum_req_check_query(QSqlDatabase::database("find_forum_connection"));
        forum_req_check_query.exec("SELECT req_status FROM other_requests where req_from ='"+current_user.username+"' AND req_to LIKE '"+ui->forum_search_table->selectionModel()->selectedRows(2).value(0).data().toString()+"';");
        while(forum_req_check_query.next()){
            status = forum_req_check_query.value(0).toString();
        }
        if(status == "Pending"){
            QMessageBox::information(this,"Pending Request Active","There is an active request already in queue. Wait for the reciever to respond");
        }
        else if(status == "Accepted"){
            QMessageBox::information(this,"Already joined Forum","You have already joined this forum");
        }
        else{
            QSqlQuery forum_req_query(QSqlDatabase::database("find_forum_connection"));
            forum_req_query.prepare("INSERT INTO other_requests(req_from,req_to,req_type,object_name,req_status) VALUES(:req_from,:req_to,'Forum',:object_name,'Pending');");
            forum_req_query.bindValue(":req_from",current_user.username);
            forum_req_query.bindValue(":req_to",ui->forum_search_table->selectionModel()->selectedRows(2).value(0).data().toString());
            forum_req_query.bindValue(":object_name",ui->forum_search_table->selectionModel()->selectedRows(0).value(0).data().toString());

            if(forum_req_query.exec()){
                QMessageBox::information(this,"Request Sent","Request Sent successfully");
            }
            else{
                QMessageBox::information(this,"Request not Sent","Failed to send request");
            }
        }
    }
}

void find_forum::on_forumsearch_returnPressed()
{
    if(ui->forumsearch->text() == nullptr){
        QMessageBox::information(this,"Incomplete Data Fields","Please type what to search for");
    }
    else{
            this->model = new QSqlQueryModel;
            model->setQuery("SELECT name AS \"Forum Name\",book_followed AS \"Book Followed\", forum_head AS \"Forum Head\"  FROM all_forums WHERE name LIKE '%"+ui->forumsearch->text()+"%';", QSqlDatabase::database("find_forum_connection"));
            ui->forum_search_table->setModel(model);
            ui->forum_search_table->resizeColumnsToContents();
        }
}
