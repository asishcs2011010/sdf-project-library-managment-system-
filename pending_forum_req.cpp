#include "pending_forum_req.h"
#include "ui_pending_forum_req.h"
#include "global_variables.h"

pending_forum_req::pending_forum_req(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pending_forum_req)
{
    ui->setupUi(this);

    ui->reject_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->accept_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");

    forum_req_db = QSqlDatabase::addDatabase("Qmysql","forum_req_connection");
    forum_req_db.setDatabaseName("Project");
    forum_req_db.setHostName(IP_address);
    forum_req_db.setPassword(db_pwd);
    forum_req_db.setPort(3306);
    forum_req_db.setUserName(db_username);
    forum_req_db.open();

    this->model = new QSqlQueryModel;
    model->setQuery("SELECT req_from AS Username, object_name AS Forum, req_status AS Status WHERE (req_to = '"+current_user.username+"' AND req_status = 'Pending')",QSqlDatabase::database("forum_req_connection"));
}

pending_forum_req::~pending_forum_req()
{
    forum_req_db.close();
    delete ui;
}

void pending_forum_req::on_accept_button_clicked()
{
    if(ui->forumreq_table->selectionModel()->selectedRows(0).value(0).data().toString() == nullptr){
        QMessageBox::information(this,"Select a Row","Please select the whole row before continuing");
    }
    else{
        if(ui->forumreq_table->selectionModel()->selectedRows(2).value(0).data().toString() == "Pending"){
            QSqlQuery accept_forum_req_query(QSqlDatabase::database("forum_req_connection"));
            accept_forum_req_query.prepare("UPDATE other_requests SET req_status = 'Accepted' WHERE (req_from = :req_from AND req_to = :req_to AND object_name = :object_name );");
            accept_forum_req_query.bindValue(":req_from",ui->forumreq_table->selectionModel()->selectedRows(0).value(0).data().toString());
            accept_forum_req_query.bindValue(":req_to",current_user.username);
            accept_forum_req_query.bindValue(":object_name",ui->forumreq_table->selectionModel()->selectedRows(1).value(0).data().toString());
            if(accept_forum_req_query.exec()){
                    QMessageBox::information(this,"Success","Successfully accepted the request");

            }
            else{
                QMessageBox::information(this,"Database error","Could not accept Request");
                qDebug() << accept_forum_req_query.lastError();
            }
        }
        else{
            QMessageBox::information(this,"Error","No Request to accept");
        }
    }
}

void pending_forum_req::on_reject_button_clicked()
{
    if(ui->forumreq_table->selectionModel()->selectedRows(0).value(0).data().toString() == nullptr){
        QMessageBox::information(this,"Select a Row","Please select the whole row before continuing");
    }
    else{
        if(ui->forumreq_table->selectionModel()->selectedRows(2).value(0).data().toString() == "Pending"){
            QSqlQuery reject_forum_req_query(QSqlDatabase::database("forum_req_connection"));
            reject_forum_req_query.prepare("UPDATE other_requests SET req_status = 'Rejected' WHERE (req_from = :req_from AND req_to = :req_to AND object_name = :object_name );");
            reject_forum_req_query.bindValue(":req_from",ui->forumreq_table->selectionModel()->selectedRows(0).value(0).data().toString());
            reject_forum_req_query.bindValue(":req_to",current_user.username);
            reject_forum_req_query.bindValue(":object_name",ui->forumreq_table->selectionModel()->selectedRows(1).value(0).data().toString());
            if(reject_forum_req_query.exec()){
                    QMessageBox::information(this,"Success","Successfully rejected the request");

            }
            else{
                QMessageBox::information(this,"Database error","Could not reject Request");
                qDebug() << reject_forum_req_query.lastError();
            }
        }
        else{
            QMessageBox::information(this,"Error","No Request to reject");
        }
    }
}
