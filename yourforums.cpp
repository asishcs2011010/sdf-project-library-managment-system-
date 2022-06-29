#include "yourforums.h"
#include "ui_yourforums.h"
#include "global_variables.h"

yourforums::yourforums(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::yourforums)
{
    ui->setupUi(this);

    yourforums_db = QSqlDatabase::addDatabase("QMYSQL","yourforums_connection");
    yourforums_db.setDatabaseName("Project");
    yourforums_db.setHostName(IP_address);
    yourforums_db.setPassword(db_pwd);
    yourforums_db.setPort(3306);
    yourforums_db.setUserName(db_username);
    yourforums_db.open();

    this->model = new QSqlQueryModel;
    model->setQuery("SELECT other_requests.object_name AS Forum, all_forums.book_followed AS \"Book Followed\", all_forums.forum_head AS \"Forum Head\" "
                    "FROM other_requests INNER JOIN all_forums ON other_requests.object_name = all_forums.name "
                    "WHERE other_requests.req_from = '"+current_user.username+"' AND other_requests.req_status = 'Accepted' AND other_requests.req_type = 'Forum';",QSqlDatabase::database("yourforums_connection"));

    ui->yourforums_table->setModel(model);
    ui->yourforums_table->resizeColumnsToContents();
}

yourforums::~yourforums()
{
    yourforums_db.close();
    delete ui;
}
