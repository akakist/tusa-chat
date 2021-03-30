#ifndef CHAT_GLBLS
#define CHAT_GLBLS
#include <map>
#include "_mutex.h"
#include "PTR.h"
#include "user.h"
#include "M_DEQUE.h"
#include "M_MAP.h"

DB_id  all_user_nick_2_DB_id(const string & nick);
class params_map;
extern M_MAP<string,string> chat_MSG;

extern M_MAP<string,string> chat_stat;		//URL /stat top 50 table
extern M_DEQUE<string> gSQL;
extern M_DEQUE<string> g_update;
string _MSG(const string &n);

#endif
