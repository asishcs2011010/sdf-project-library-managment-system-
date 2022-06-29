#include "search_books.h"
#include "./ui_search_books.h"
#include "global_variables.h"
#include <QMessageBox>

search_books::search_books(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::search_books)
{
    ui->setupUi(this);

    QString backgroundImage_src="/home/goutham/Coding/CS1023-SDF/Image/books.jpg";
    QPixmap bkgnd(backgroundImage_src);
    bkgnd=bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    ui->searchbooksbutton->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    ui->sendbookreq_button->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");

    search_books_db = QSqlDatabase::addDatabase("QMYSQL","search_books_connection");
    search_books_db.setDatabaseName("Project");
    search_books_db.setHostName(IP_address);
    search_books_db.setPassword(db_pwd);
    search_books_db.setPort(3306);
    search_books_db.setUserName(db_username);
    search_books_db.open();
}

search_books::~search_books()
{
    search_books_db.close();
    delete ui;
}


void search_books::on_searchbooksbutton_clicked()
{
    if(ui->booksearch->text() == nullptr){
        QMessageBox::information(this,"Incomplete Data Fields","Please type what to search for");
    }
    else{
            this->model = new QSqlQueryModel;
            model->setQuery("SELECT all_books.name AS \"Book Name\",all_books.author AS Author,all_books.owner AS Owner, all_books.edition AS Edition, all_books.ISBN, all_books.genre AS Genre,all_books.status AS \"With Owner\" user_info.address AS Address, user_info.city AS City, user_info.state AS State "
                            "FROM all_books INNER JOIN user_info ON all_books.owner = user_info.username "
                            "WHERE all_books.name LIKE '%"+ui->booksearch->text()+"%';",QSqlDatabase::database("search_books_connection"));

            ui->search_books_table->setModel(model);
            ui->search_books_table->resizeColumnsToContents();
        }
}

void search_books::on_sendbookreq_button_clicked()
{
    if(ui->search_books_table->selectionModel()->selectedRows(0).value(0).data().toString() == nullptr){
        QMessageBox::information(this,"Select a Row","Please select the whole row before continuing");
        qDebug() << ui->search_books_table->selectionModel()->selectedRows(0).value(0).data().toString();
    }
    else if(ui->search_books_table->selectionModel()->selectedRows(6).value(0).data().toBool()){
        QString status;
        QSqlQuery request_check_query(QSqlDatabase::database("search_books_connection"));
        request_check_query.exec("SELECT status FROM book_requests WHERE book_requests.borrowed_by ='"+current_user.username+"' AND book_requests.borrowed_from LIKE '"+ui->search_books_table->selectionModel()->selectedRows(2).value(0).data().toString()+"';");
        while (request_check_query.next()) {
            status = request_check_query.value(0).toString();
        }
        if(status == "Pending"){
            QMessageBox::information(this,"Pending Request","There is already an active pending request in queue. Please wait for the recievers reply");
        }
        else if(status != "Lent"){
            QSqlQuery request_query(QSqlDatabase::database("search_books_connection"));
            request_query.prepare("INSERT INTO book_requests(borrowed_by,borrowed_from,borrowed_till,book_name,ISBN,status) VALUES (:borrowed_by,:borrowed_from,:borrowed_till,:book_name,:ISBN, 'Pending');");

            request_query.bindValue(":borrowed_by",current_user.username);
            request_query.bindValue(":borrowed_from",ui->search_books_table->selectionModel()->selectedRows(2).value(0).data().toString());
            request_query.bindValue(":borrowed_till",ui->borrowedtilldate->text());
            request_query.bindValue(":book_name",ui->search_books_table->selectionModel()->selectedRows(0).value(0).data().toString());
            request_query.bindValue(":ISBN",ui->search_books_table->selectionModel()->selectedRows(4).value(0).data().toString());

            if(current_user.username == ui->search_books_table->selectionModel()->selectedRows(2).value(0).data().toString()){
                QMessageBox::information(this,"Error","Book is yours. Cannot send Request");
            }
            else{
                if(request_query.exec()){
                    QMessageBox::information(this,"Successful Request sent","Request sent successfully");
                }
                else{
                    QMessageBox::information(this,"Unsuccessful Request","Could not send Request");
                    qDebug() << request_query.lastError();
                }
            }
        }
    }
}

void search_books::on_booksearch_returnPressed()
{
    if(ui->booksearch->text() == nullptr){
        QMessageBox::information(this,"Incomplete Data Fields","Please type what to search for");
    }
    else{
            this->model = new QSqlQueryModel;
            model->setQuery("SELECT all_books.name AS \"Book Name\",all_books.author AS Author,all_books.owner AS Owner, all_books.edition AS Edition, all_books.ISBN, all_books.genre AS Genre,all_books.status AS \"With Owner\" user_info.address AS Address, user_info.city AS City, user_info.state AS State "
                            "FROM all_books INNER JOIN user_info ON all_books.owner = user_info.username "
                            "WHERE all_books.name LIKE '%"+ui->booksearch->text()+"%';",QSqlDatabase::database("search_books_connection"));

            ui->search_books_table->setModel(model);
            ui->search_books_table->resizeColumnsToContents();
        }
}
