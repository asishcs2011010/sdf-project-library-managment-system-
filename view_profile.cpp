#include "view_profile.h"
#include "./ui_view_profile.h"
#include "global_variables.h"

view_profile::view_profile(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::view_profile)
{
    ui->setupUi(this);

    QString backgroundImage_src="/home/goutham/Coding/CS1023-SDF/Image/profile_page.jpg";
    QPixmap bkgnd(backgroundImage_src);
    bkgnd=bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    view_profile_db = QSqlDatabase::addDatabase("QMYSQL","view_profile_connection");
    view_profile_db.setDatabaseName("Project");
    view_profile_db.setHostName(IP_address);
    view_profile_db.setPassword(db_pwd);
    view_profile_db.setPort(3306);
    view_profile_db.setUserName(db_username);
    view_profile_db.open();

    QSqlQuery view_profile_query(QSqlDatabase::database("view_profile_connection"));
    view_profile_query.exec("SELECT * FROM user_info WHERE username ='"+current_user.username+"';");
    while(view_profile_query.next()){
        ui->fname->append(view_profile_query.value(1).toString());
        ui->lname->append(view_profile_query.value(2).toString());
        ui->mobile->append(view_profile_query.value(3).toString());
        ui->email->append(view_profile_query.value(4).toString());
        ui->username->append(view_profile_query.value(5).toString());
        ui->address_1->append(view_profile_query.value(7).toString());
        ui->city->append(view_profile_query.value(8).toString());
        ui->state->append(view_profile_query.value(9).toString());
        ui->DOB->append(view_profile_query.value(10).toString());
    }
}

view_profile::~view_profile()
{
    view_profile_db.close();
    delete ui;
}

