#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H
#include "user.h"
#include<QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

extern QString IP_address;/**< String IP_address - stores the ip address */
extern QString db_username;/**< String db_username - stores the username used for connecting to database */
extern QString db_pwd;/**< String db_pwd - stores the password used for connecting to database */
extern QString server_ip;/**< String server_ip - stores server's ip address */
extern user_t current_user;/**< class object current_user - stores user details */

#endif // GLOBAL_VARIABLES_H
