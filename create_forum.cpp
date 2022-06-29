#include "create_forum.h"
#include "./ui_create_forum.h"
#include "global_variables.h"

create_forum::create_forum(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::create_forum)
{
    ui->setupUi(this);

    QString backgroundImage_src="/home/goutham/Coding/CS1023-SDF/Image/forum_page.jpg";
    QPixmap bkgnd(backgroundImage_src);
    bkgnd=bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    ui->createforum->setStyleSheet("QPushButton{font-size: 16px;color: rgb(38,56,76);background-color: rgb(170, 255, 255);}");
    ui->cancelbutton->setStyleSheet("QPushButton{font-size: 16px;color: rgb(38,56,76);background-color: rgb(170, 255, 255);}");


    forum_database = QSqlDatabase::addDatabase("QMYSQL","forum_add_connect");
    forum_database.setHostName(IP_address);
    forum_database.setUserName(db_username);
    forum_database.setPassword(db_pwd);
    forum_database.setDatabaseName("Project");
    forum_database.setPort(3306);
    forum_database.open();
}

create_forum::~create_forum()
{
    forum_database.close();
    delete ui;
}


void create_forum::on_createforum_clicked()
{ 
    if(ui->forumname->text()==nullptr || ui->bookfollowed->text()==nullptr){
        QMessageBox::information(this,"Incomplete Data Fields","Please fill all the fields with valid entries");
    }
    else{
        QSqlQuery forum_add_query(QSqlDatabase::database("forum_add_connect"));
        forum_add_query.prepare("INSERT INTO all_forums(name, book_followed, forum_head) VALUES (:name,:book,:forum_head);");
        forum_add_query.bindValue(":name",ui->forumname->text());
        forum_add_query.bindValue(":book_followed",ui->bookfollowed->text());
        forum_add_query.bindValue(":forum_head",current_user.username);

        if(forum_add_query.exec()){
            QMessageBox::information(this,"Succesfully Created","New Forum created successfully");
            ui->bookfollowed->clear();
            ui->forumname->clear();
        }
        else{
            QMessageBox::information(this,"Unsuccessful Attempt","Could not create the forum");
            qDebug() << forum_add_query.lastError();
        }
    }
}

void create_forum::on_bookfollowed_returnPressed()
{
    if(ui->forumname->text()==nullptr || ui->bookfollowed->text()==nullptr){
        QMessageBox::information(this,"Incomplete Data Fields","Please fill all the fields with valid entries");
    }
    else{
        QSqlQuery forum_add_query(QSqlDatabase::database("forum_add_connect"));
        forum_add_query.prepare("INSERT INTO all_forums(name, book_followed, forum_head) VALUES (:name,:book,:forum_head);");
        forum_add_query.bindValue(":name",ui->forumname->text());
        forum_add_query.bindValue(":book_followed",ui->bookfollowed->text());
        forum_add_query.bindValue(":forum_head",current_user.username);
        if(forum_add_query.exec()){
            QMessageBox::information(this,"Succesfully Created","New Forum created successfully");
        }
        else{
            QMessageBox::information(this,"Unsuccessful Attempt","Could not create the forum");
        }
        }
}

void create_forum::on_cancelbutton_clicked()
{
    QWidget::close();
}
