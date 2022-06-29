#include "borrowed_books.h"
#include "./ui_borrowed_books.h"
#include "global_variables.h"

borrowed_books::borrowed_books(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::borrowed_books)
{
    ui->setupUi(this);
    borrowed_books_db = QSqlDatabase::addDatabase("QMYSQL","borrowed_books_connection");
    borrowed_books_db.setDatabaseName("Project");
    borrowed_books_db.setHostName(IP_address);
    borrowed_books_db.setPassword(db_pwd);
    borrowed_books_db.setPort(3306);
    borrowed_books_db.setUserName(db_username);
    borrowed_books_db.open();

    this->model = new QSqlQueryModel;
    model->setQuery("SELECT book_name,borrowed_from,borrowed_till FROM book_requests where borrowed_by ='"+current_user.username+"'AND (status = 'Lent' OR status = 'Returned') ORDER BY borrowed_till DESC;",QSqlDatabase::database("borrowed_books_connection"));
    model->setHeaderData(0,Qt::Horizontal,tr("Book Name"));
    model->setHeaderData(1,Qt::Horizontal,tr("Owner of the Book"));
    model->setHeaderData(2,Qt::Horizontal,tr("Borrowed until"));

    ui->borrowed_books_table->setModel(model);
    ui->borrowed_books_table->resizeColumnsToContents();
}

borrowed_books::~borrowed_books()
{
    borrowed_books_db.close();
    delete ui;
}

