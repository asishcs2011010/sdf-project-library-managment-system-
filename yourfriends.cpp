#include "yourfriends.h"
#include "ui_yourfriends.h"
#include "global_variables.h"

yourfriends::yourfriends(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::yourfriends)
{
    ui->setupUi(this);

    yourfriends_db = QSqlDatabase::addDatabase("QMYSQL","yourfriends_connection");
    yourfriends_db.setDatabaseName("Project");
    yourfriends_db.setHostName(IP_address);
    yourfriends_db.setPassword(db_pwd);
    yourfriends_db.setPort(3306);
    yourfriends_db.setUserName(db_username);
    yourfriends_db.open();

    this->model = new QSqlQueryModel;
    model->setQuery("SELECT other_requests.req_from AS Username, user_info.mobile AS Mobile, user_info.email AS Email, user_info.address AS Address, user_info.city AS City, user_info.state AS State "
                    "FROM other_requests INNER JOIN user_info ON other_requests.req_from = user_info.username "
                    "WHERE other_requests.req_to = '"+current_user.username+"' AND other_requests.req_status = 'Accepted' AND other_requests.req_type = 'Friend';",QSqlDatabase::database("yourfriends_connection"));

    ui->yourfriends_table->setModel(model);
    ui->yourfriends_table->resizeColumnsToContents();
}

yourfriends::~yourfriends()
{
    yourfriends_db.close();
    delete ui;
}
