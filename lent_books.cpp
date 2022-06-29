#include "lent_books.h"
#include "./ui_lent_books.h"
#include "global_variables.h"

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

lent_books::lent_books(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::lent_books)
{
    ui->setupUi(this);

    lent_books_db = QSqlDatabase::addDatabase("QMYSQL","lent_books_connection");
    lent_books_db.setDatabaseName("Project");
    lent_books_db.setHostName(IP_address);
    lent_books_db.setPassword(db_pwd);
    lent_books_db.setPort(3306);
    lent_books_db.setUserName(db_username);
    lent_books_db.open();

    model = new QSqlQueryModel;
    model->setQuery("SELECT book_name,borrowed_by,borrowed_till FROM book_requests WHERE borrowed_from ='"+current_user.username+"' AND (status = 'lent' OR status = 'Returned') ORDER BY borrowed_until DESC;",QSqlDatabase::database("lent_books_connection"));
    model->setHeaderData(0,Qt::Horizontal,tr("Book Name"));
    model->setHeaderData(1,Qt::Horizontal,tr("Borrowed by"));
    model->setHeaderData(2,Qt::Horizontal,tr("Borrowed until"));

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

lent_books::~lent_books()
{
    lent_books_db.close();
    delete ui;
}

