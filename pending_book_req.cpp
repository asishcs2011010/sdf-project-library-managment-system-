#include "pending_book_req.h"
#include "ui_pending_book_req.h"
#include "global_variables.h"

pending_book_req::pending_book_req(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pending_book_req)
{
    ui->setupUi(this);

    book_req_db = QSqlDatabase::addDatabase("QMYSQL","book_req_connection");
    book_req_db.setDatabaseName("Project");
    book_req_db.setHostName(IP_address);
    book_req_db.setPassword(db_pwd);
    book_req_db.setPort(3306);
    book_req_db.setUserName(db_username);
    book_req_db.open();

    this->model = new QSqlQueryModel;
    model->setQuery("SELECT borrowed_by AS \"Borrower\", borrowed_till AS \"Borrowed Till\", book_name AS Book, status AS Status WHERE borrowed_from = '"+current_user.username+"';",QSqlDatabase::database("book_req_connection"));

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    ui->acceptreq_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->rejectreq_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->returnedbook_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
}

pending_book_req::~pending_book_req()
{
    book_req_db.close();
    delete ui;
}

void pending_book_req::on_acceptreq_button_clicked()
{
    if(ui->tableView->selectionModel()->selectedRows(0).value(0).data().toString() == nullptr){
            QMessageBox::information(this,"Select a Row","Please select the whole row before continuing");
        }
        else{
            bool can_accept;
            QSqlQuery can_accept_query(QSqlDatabase::database("book_req_connection"));
            can_accept_query.exec("SELECT status FROM all_books WHERE name = '"+ui->tableView->selectionModel()->selectedRows(2).value(0).data().toString()+"';");
            while (can_accept_query.next()) {
                can_accept = can_accept_query.value(0).toBool();
            }
            if(can_accept){
                QSqlQuery accept_req_query(QSqlDatabase::database("book_req_connection"));
                accept_req_query.prepare("UPDATE book_requests SET status = 'Lent' WHERE (borrowed_by = :borrowed_by AND borrowed_from = :borrowed_from AND book_name = :book_name );");
                accept_req_query.bindValue(":borrowed_by",ui->tableView->selectionModel()->selectedRows(0).value(0).data().toString());
                accept_req_query.bindValue(":borrowed_from",current_user.username);
                accept_req_query.bindValue(":book_name",ui->tableView->selectionModel()->selectedRows(2).value(0).data().toString());
                if(accept_req_query.exec()){
                    QSqlQuery accept_req_update_query(QSqlDatabase::database("book_req_connection"));
                    accept_req_update_query.exec("UPDATE all_books SET status = false WHERE (owner = '"+current_user.username+"' AND name = '"+ui->tableView->selectionModel()->selectedRows(2).value(0).data().toString()+"');");
                    if(accept_req_update_query.exec()){
                        QMessageBox::information(this,"Success","Successfully Accepted and updated");
                    }
                    else{
                        QMessageBox::information(this,"Update Error","Successfully accepted but not updated");
                        qDebug() << accept_req_update_query.lastError();
                    }
                }
                else{
                    QMessageBox::information(this,"Accept Failed","Could not accept Request");
                    qDebug() << accept_req_query.lastError();
                }
            }
            else{
                QMessageBox::information(this,"Error","Book Lent. Cannot accept request");
            }
        }
}

void pending_book_req::on_rejectreq_button_clicked()
{
    if(ui->tableView->selectionModel()->selectedRows(0).value(0).data().toString() == nullptr){
        QMessageBox::information(this,"Select a Row","Please select the whole row before continuing");
    }
    else{
        if(ui->tableView->selectionModel()->selectedRows(3).value(0).data().toString() == "Pending"){
            QSqlQuery reject_req_query(QSqlDatabase::database("book_req_connection"));
            reject_req_query.prepare("UPDATE book_requests SET status = 'Rejected' WHERE (borrowed_by = :borrowed_by AND borrowed_from = :borrowed_from AND book_name = :book_name );");
            reject_req_query.bindValue(":borrowed_by",ui->tableView->selectionModel()->selectedRows(0).value(0).data().toString());
            reject_req_query.bindValue(":borrowed_from",current_user.username);
            reject_req_query.bindValue(":book_name",ui->tableView->selectionModel()->selectedRows(2).value(0).data().toString());
            if(reject_req_query.exec()){
                    QMessageBox::information(this,"Success","Successfully Rejected");
            }
            else{
                QMessageBox::information(this,"Reject Failed","Could not reject Request");
                qDebug() << reject_req_query.lastError();
            }
        }
        else{
            QMessageBox::information(this,"Error","You cannot Rejct this Request");
        }
    }
}

void pending_book_req::on_returnedbook_button_clicked()
{
    if(ui->tableView->selectionModel()->selectedRows(0).value(0).data().toString() == nullptr){
        QMessageBox::information(this,"Select a Row","Please select the whole row before continuing");
    }
    else{
        if(ui->tableView->selectionModel()->selectedRows(3).value(0).data().toString() == "Lent"){
            QSqlQuery return_req_query(QSqlDatabase::database("book_req_connection"));
            return_req_query.prepare("UPDATE book_requests SET status = 'Returned' WHERE (borrowed_by = :borrowed_by AND borrowed_from = :borrowed_from AND book_name = :book_name );");
            return_req_query.bindValue(":borrowed_by",ui->tableView->selectionModel()->selectedRows(0).value(0).data().toString());
            return_req_query.bindValue(":borrowed_from",current_user.username);
            return_req_query.bindValue(":book_name",ui->tableView->selectionModel()->selectedRows(2).value(0).data().toString());
            if(return_req_query.exec()){
                QSqlQuery return_req_status_update_query(QSqlDatabase::database("book_req_connection"));
                QSqlQuery return_req_count_update_query(QSqlDatabase::database("book_req_connection"));
                return_req_status_update_query.exec("UPDATE all_books SET status = true WHERE owner = '"+current_user.username+"' AND name = '"+ui->tableView->selectionModel()->selectedRows(2).value(0).data().toString()+"';");
                return_req_status_update_query.exec("UPDATE all_books SET borrowed_no = borrowed_no+1 WHERE owner = '"+current_user.username+"' AND name = '"+ui->tableView->selectionModel()->selectedRows(2).value(0).data().toString()+"';");
                if(return_req_status_update_query.exec()&&return_req_count_update_query.exec()){
                    QMessageBox::information(this,"Success","Successfully Returned and updated");
                }
                else{
                    QMessageBox::information(this,"Update Error","Successfully Returned but not updated");
                    qDebug() << return_req_status_update_query.lastError();
                    qDebug() << return_req_count_update_query.lastError();
                }
            }
            else{
                QMessageBox::information(this,"Return Failed","Could not Return book");
                qDebug() << return_req_query.lastError();
            }
        }
        else{
            QMessageBox::information(this,"Error","Book not lent. It cannot be returned");
        }
    }
}

