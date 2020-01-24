#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <time.h>
#include <map>
#ifndef __CLAN
#include "mysql_extens.h"
#endif
#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include "message.h"
#include "chat_def.h"
#include "register.h"

#include <algorithm>
#include "web_server_data.h"
#include "file_set.h"
#include "copy_file.h"

#include "channels.h"
#include "server_config.h"
#include "admin.h"
#include "cs_conn_data.h"
#include "html_out.h"
#include "chat_globals.h"
#include "DR_types.h"
static string get_name_of_ban_time(time_t t)
{
    string r=_MSG("manytime");
    switch (t) {
    case 60:
        r="1 "+_MSG("min");
        break;
    case 300:
        r="5 "+_MSG("min");
        break;
    case 600:
        r="10 "+_MSG("min");
        break;
    case 1200:
        r="20 "+_MSG("min");
        break;
    case 1800:
        r="30 "+_MSG("min");
        break;
    case 3600:
        r="1 "+_MSG("hour1");
        break;
    case 7200:
        r="2 "+_MSG("hour2");
        break;
    case 21600:
        r="6 "+_MSG("hour3");
        break;
    case 43200:
        r="12 "+_MSG("hour3");
        break;
    case 86400:
        r="1 "+_MSG("day1");
        break;
    case 172800:
        r="2 "+_MSG("day2");
        break;
    case 604800:
        r="1 "+_MSG("week1");
        break;
    case 1209600:
        r="2 "+_MSG("week2");
        break;
    default:
        r=itostring(t)+_MSG("sec");
        break;
    }
    return r;
}

#ifdef __CLAN
int do_ipban(const string &ip_orig,const string &proxy_orig,time_t t,const DB_id& id)
{
    int r;
    out_oscar_buffer v;
    v<<ip_orig<<proxy_orig<<t<<id;
    string cr=clan_data_request(DR_do_ipban,v);
    oscar_buffer b(cr.data(),cr.size());
    b>>r;
    return r;

}
int do_loginban(const DB_id &zuid,const string &descr,time_t t,const DB_id& adm_uid,unsigned int level)
{
    int r;
    out_oscar_buffer v;
    v<<zuid<<descr<<t<<adm_uid<<level;
    string cr=clan_data_request(DR_do_loginban,v);
    oscar_buffer b(cr.data(),cr.size());
    b>>r;
    return r;

}
int do_nickban(const string &nick_orig,const DB_id& id,unsigned int level)
{
    int r;
    out_oscar_buffer v;
    v<<nick_orig<<id<<level;
    string cr=clan_data_request(DR_do_nickban,v);
    oscar_buffer b(cr.data(),cr.size());
    b>>r;
    return r;

}
bool check_for_ipban(const string &ip,const string &proxyip)
{
    bool r;
    out_oscar_buffer v;
    v<<ip<<proxyip;
    string cr=clan_data_request(DR_check_for_ipban,v);
    oscar_buffer b(cr.data(),cr.size());
    b>>r;
    return r;

}

#else
int do_ipban(const string &ip_orig,const string &proxy_orig,time_t t,const DB_id& id)
{

    string ip=remove_spaces(ip_orig);
    string proxy=remove_spaces(proxy_orig);
    st_dbh d;
    vector<string> v=d.dbh->select_1_rowQ((QUERY)"select id from banned_ip where ip='?' and proxy='?'" << ip << proxy);
    if (v.size()>0) return 1;

    time_t t_remove=time(NULL)+t;
    d.dbh->real_queryQ((QUERY)
                       "insert into banned_ip "
                       "(ip,time_ban,time_free,time_cnt,uid,proxy) values "
                       "('?',NOW(),FROM_UNIXTIME(?),'?',?,'?')"
                       <<ip<<t_remove<<get_name_of_ban_time(t)<<id.container<<proxy
                      );
    return 0;
}
int do_loginban(const DB_id &zuid,const string &descr,time_t t,const DB_id& adm_uid,unsigned int level)
{
    st_dbh d;
    vector<string> v=d.dbh->select_1_rowQ((QUERY)"select uid from banned_login where uid='?'"<<zuid.container);
    if (v.size()==0) {
        unsigned int l=atoi(d.dbh->select_1Q((QUERY)"select level from user_profiles where refid='?'"<<zuid.container).c_str())/sub_levels;
        if (level<=l) {
            return -1;
        }
        time_t t_remove=time(NULL)+t;
        d.dbh->real_queryQ((QUERY)
                           "insert into banned_login "
                           "(uid,time_ban,time_free,time_cnt,adm_uid,descr) values "
                           "('?',NOW(),FROM_UNIXTIME(?),'?','?','?')"
                           <<zuid.container<<t_remove<<get_name_of_ban_time(t)<<adm_uid.container<<descr
                          );
        return 0;
    } else {
        return 1;
    }
    return 0;
}
int do_nickban(const string &nick_orig,const DB_id& id,unsigned int level)
{

    string nick=remove_spaces(nick_orig);
    unsigned int uid;
    st_dbh d;
    vector<string> z=d.dbh->select_1_rowQ((QUERY)"select id,banned,uid from nicks where str_nick like '?'"<<str_nick(nick));
    if (z.size()!=0 && z.size()!=3) {//;
        throw cError("select() failed. Size different in first select.");
    }
    if (z.size()==3) {
        uid=atoi(z[2].c_str());
    }
    if (z.size()==0) {
        d.dbh->real_queryQ((QUERY)
                           "insert into nicks (nick,str_nick,banned,uid,bby) values('?','?',1,0,?)"
                           <<nick<<str_nick(nick)<<id.container
                          );
        return 2;
    }
    else if (z[1]=="1") {
        return 1;
    }
    else {
        vector<string> q=d.dbh->select_1_rowQ((QUERY)"select level from user_profiles where refid=?"<<uid);
        if (q.size()!=1) {//;
            throw cError("select failed. size different.");
        }
        unsigned int bl=atoi(q[0].c_str())/sub_levels;
        if (level>bl) {//;
            d.dbh->real_queryQ((QUERY)"update nicks set banned='1',bby=? where id=? and uid=?"
                               <<id.container<<z[0]<<z[2]
                              );
            return 0;
        } else {
            return -1;
        }
    }
}
bool check_for_ipban(const string &ip,const string &proxyip)
{
    st_dbh d;
    if (proxyip.size()) {
        vector<string> q=d.dbh->select_1_rowQ((QUERY)"select ip,proxy from banned_ip where ip='?'"<<proxyip);
        if (q.size()) return false;
    }
    vector<string> q=d.dbh->select_1_rowQ((QUERY)"select ip,proxy from banned_ip where ip='?'"<<ip);
    if (q.size()) return false;

    return true;
}

#endif
