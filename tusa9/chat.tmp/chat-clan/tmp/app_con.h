#ifndef APP_CON__H
#define APP_CON__H
#include "web_connection.h"
#include "PTR.h"
#include "c_conn.h"
#include <string>
#include <map>
#include "DB_id.h"
class app_server;
class chat_user;
class app_connection: public web_connection
{
public:
	void process_web();
	app_connection(app_server *p,const PTR_getter<c_socket>&s);	
	app_connection(const app_connection* s);	
	app_server *server;

	void postinit_rvmap(map<string,string> &m);

	void redirect(const string &url);
	string redirect();
	////////////// COPY from CHATUSER
	DB_id __user_id;
	vector<string>vurl;
	bool user_unregistered;
	unsigned int sub_level;
	void init_temp_vars(const PTR_getter<chat_user> &__ZZ );
};


#endif
