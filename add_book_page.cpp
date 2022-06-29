#include "add_book_page.h"
#include "./ui_add_book_page.h"
#include"global_variables.h"

add_book_page::add_book_page(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::add_book_page)
{
    ui->setupUi(this);
    QString backgroundImage_src="/home/goutham/Coding/CS1023-SDF/Image/books.jpg";
    QPixmap bkgnd(backgroundImage_src);
    bkgnd=bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    ui->addbutton->setStyleSheet("QPushButton{font-size: 16px;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");

    ui->bookname->setPlaceholderText("Enter Book Name");
    ui->authorname->setPlaceholderText("Enter Author Name");
    ui->edition->setPlaceholderText("Enter Edition");
    ui->ISBN->setPlaceholderText("Enter ISBN Number");

    //book genre combo-box options
    ui->genre_options->addItem("--SELECT--");
    ui->genre_options->addItem("Fiction");
    ui->genre_options->addItem("Sci Fi");
    ui->genre_options->addItem("Fantasy");
    ui->genre_options->addItem("Non Fiction");
    ui->genre_options->addItem("Mystery");
    ui->genre_options->addItem("Thriller");
    ui->genre_options->addItem("Poetry");
    ui->genre_options->addItem("Horror");
    ui->genre_options->addItem("Action/Adventure");
    ui->genre_options->addItem("Historical");
    ui->genre_options->addItem("Reference/Text Book");
    ui->genre_options->addItem("Romance");

    add_book_db = QSqlDatabase::addDatabase("QMYSQL","add_book_connection");
    add_book_db.setHostName(IP_address);
    add_book_db.setPort(3306);
    add_book_db.setDatabaseName("Project");
    add_book_db.setUserName(db_username);
    add_book_db.setPassword(db_pwd);
    add_book_db.open();
}

add_book_page::~add_book_page()
{
    add_book_db.close();
    delete ui;
}

void add_book_page::on_addbutton_clicked()
{
    if(ui->bookname->text() == nullptr || ui->authorname->text() == nullptr || ui->edition->text() == nullptr || ui->ISBN->text() == nullptr){
        QMessageBox::information(this,"Incomplete Fields","Please fill all fields with appropriate data");
    }
    else{
        int serial_no = 0;
        QSqlQuery find_serial_query(QSqlDatabase::database("add_book_connection"));
        find_serial_query.exec("SELECT owner,serial_no FROM all_books WHERE name Like '" + ui->bookname->text() + "' AND ISBN = '"+ui->ISBN->text()+"' ORDER BY serial_no DESC;");
        while(find_serial_query.next()){
            if(find_serial_query.size())
            {
                if(current_user.username == find_serial_query.value(0).toString()){
                    serial_no = -2;
                }
                else{
                    serial_no = find_serial_query.value(1).toInt();
                }
            }
        }
        serial_no++;
        if(serial_no == -1){
            QMessageBox::information(this,"Duplicate Entry","This book has already been added in your account");
        }
        else{
            QSqlQuery add_book_query(QSqlDatabase::database("add_book_connection"));
            add_book_query.prepare("INSERT INTO all_books VALUES(:name, :author, :owner, :edition, :ISBN, :serial_no, true , :genre, :borrowed_no);");
            add_book_query.bindValue(":name", ui->bookname->text());
            add_book_query.bindValue(":author", ui->authorname->text());
            add_book_query.bindValue(":owner", current_user.username);
            add_book_query.bindValue(":edition", ui->edition->text().toInt());
            add_book_query.bindValue(":ISBN", ui->ISBN->text());
            add_book_query.bindValue(":serial_no", serial_no);
            add_book_query.bindValue(":genre", ui->genre_options->currentText());
            add_book_query.bindValue(":borrowed_no", 0);

            if(add_book_query.exec()){
                QMessageBox::information(this,"Successful Entry","New Book added Successfully");
                ui->authorname->clear();
                ui->bookname->clear();
                ui->edition->clear();
                ui->ISBN->clear();
                ui->genre_options->setCurrentIndex(0);
            }
            else
            {
                QMessageBox::information(this,"Unsuccessful Attempt","Data Not entered");
            }
        }
    }
}

