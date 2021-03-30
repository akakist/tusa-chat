#ifndef ADMIN_H__
#define ADMIN_H__
#include <string>
#include "PTR.h"

// 0 - success, 1 - already banned

int do_ipban(const string &ip_orig,const string &proxy_orig,time_t t,const DB_id& id);

// 0 - success, 1 - already banned, -1 - no enought level
int do_loginban(const DB_id& user_uid,const string &descr,time_t t,const DB_id& adm_uid,unsigned int level);

// 0 - success, 1 - already banned, -1 - no enought level 2 - banned for system acc
int do_nickban(const string &nick_orig,const DB_id& id,unsigned int level);

#endif
