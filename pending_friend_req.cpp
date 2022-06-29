#include "pending_friend_req.h"
#include "ui_pending_friend_req.h"
#include "global_variables.h"

pending_friend_req::pending_friend_req(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pending_friend_req)
{
    ui->setupUi(this);

    ui->accept_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->reject_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");

    friend_req_db = QSqlDatabase::addDatabase("QMYSQL","friend_req_connection");
    friend_req_db.setDatabaseName("Project");
    friend_req_db.setHostName(IP_address);
    friend_req_db.setPassword(db_pwd);
    friend_req_db.setPort(3306);
    friend_req_db.setUserName(db_username);
    friend_req_db.open();

    this->model = new QSqlQueryModel;
    model->setQuery("SELECT req_from AS Username,req_status AS Status FROM other_requests WHERE (req_to = '"+current_user.username+"' AND req_status = 'Pending');",QSqlDatabase::database("friend_req_connection"));

    ui->friend_req_table->setModel(model);
    ui->friend_req_table->resizeColumnsToContents();
}

pending_friend_req::~pending_friend_req()
{
    friend_req_db.close();
    delete ui;
}

void pending_friend_req::on_accept_button_clicked()
{
    if(ui->friend_req_table->selectionModel()->selectedRows(0).value(0).data().toString() == nullptr){
        QMessageBox::information(this,"Select a Row","Please select the whole row before continuing");
    }
    else{
        if(ui->friend_req_table->selectionModel()->selectedRows(1).value(0).data().toString() == "Pending"){
            QSqlQuery accept_friend_req_query(QSqlDatabase::database("friend_req_connection"));
            accept_friend_req_query.prepare("UPDATE other_requests SET req_status = 'Accepted' WHERE (req_from = :req_from AND req_to = :req_to AND object_name = :object_name );");
            accept_friend_req_query.bindValue(":req_from",ui->friend_req_table->selectionModel()->selectedRows(0).value(0).data().toString());
            accept_friend_req_query.bindValue(":req_to",current_user.username);
            accept_friend_req_query.bindValue(":object_name",current_user.username);
            if(accept_friend_req_query.exec()){
                    QMessageBox::information(this,"Success","Successfully accepted the request");

            }
            else{
                QMessageBox::information(this,"Database error","Could not accept Request");
                qDebug() << accept_friend_req_query.lastError();
            }
        }
        else{
            QMessageBox::information(this,"Error","No Request to accept");
        }
    }
}

void pending_friend_req::on_reject_button_clicked()
{
    if(ui->friend_req_table->selectionModel()->selectedRows(0).value(0).data().toString() == nullptr){
        QMessageBox::information(this,"Select a Row","Please select the whole row before continuing");
    }
    else{
        if(ui->friend_req_table->selectionModel()->selectedRows(1).value(0).data().toString() == "Pending"){
            QSqlQuery reject_friend_req_query(QSqlDatabase::database("friend_req_connection"));
            reject_friend_req_query.prepare("UPDATE other_requests SET req_status = 'Rejected' WHERE (req_from = :req_from AND req_to = :req_to AND object_name = :object_name );");
            reject_friend_req_query.bindValue(":req_from",ui->friend_req_table->selectionModel()->selectedRows(0).value(0).data().toString());
            reject_friend_req_query.bindValue(":req_to",current_user.username);
            reject_friend_req_query.bindValue(":object_name",current_user.username);
            if(reject_friend_req_query.exec()){
                    QMessageBox::information(this,"Success","Successfully rejected the request");

            }
            else{
                QMessageBox::information(this,"Database error","Could not Reject Request");
                qDebug() << reject_friend_req_query.lastError();
            }
        }
        else{
            QMessageBox::information(this,"Error","No Request to reject");
        }
    }
}

