#ifndef REGISTER_H__
#define REGISTER_H__
#include "user.h"
#include <time.h>
#include <vector>
class app_connection;
void pre_init_for_info(map<string,hstring> &m);

bool check_for_ipban(const string &ip,const string &proxyip);
void url_login(PTR_getter<chat_user> &__UU,app_connection * cc);
void url_logout(const user_pair&__U, app_connection*);
string check_reg_map(map<string,string> &m, bool all);
void  fill_map_from_map(map<string,hstring>&m,map<string,string>&from);
void update_DB_from_reg_map(const DB_id& uid,map<string,string>&m, bool all);

#endif
