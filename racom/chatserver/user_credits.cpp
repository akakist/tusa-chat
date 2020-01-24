#ifdef __GNUC__
#pragma implementation
#endif

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
#include "web_server.h"
#include "message.h"
#include "chat_def.h"
#include "register.h"
#include <algorithm>
#include "web_server_data.h"
#include "file_set.h"
#include "copy_file.h"
#include "user_credits.h"
#include "db_var.h"
#include "server_config.h"
#include "update_cmd.h"
#include "DR_types.h"


db_map<user_credit> user_credits("user_credits",DBMAP_MYSQL,DBMAP_REFID);
static _mutex __LOG_dump("__LOG_dump");

string update_to_db(const PTR_getter<user_credit>&__P,const string &tblname);

static void ___dump_log(const string & pn_pref, const string &s)
{
    tm tt=LOCALTIME(time(NULL));
    char ss[200];
    snprintf(ss,sizeof(ss)-1,"%s.%04d%02d%02d",pn_pref.c_str(),1900+tt.tm_year,tt.tm_mon+1,tt.tm_mday);
    M_LOCK(__LOG_dump);
    check_path_wfn(ss);
    FILE *f = ::fopen(ss, "a");
    if (f) {
        if (s.size())
            ::fprintf(f, "%s\n", s.c_str());
        ::fclose(f);
    }

}

M_DEQUE<credit_transaction> credit_transactions;
#ifdef __CLAN
void dump_credits_log()
{

}
#else
void dump_credits_log()
{
    credit_transaction ct;
    st_dbh d;
    while (credit_transactions.extract_first(ct))
    {
        char s[100];
        snprintf(s,sizeof(s)-1,"%f",ct.summa);
        d.dbh->real_queryQ((QUERY)"insert into credit_log (dt,from_uid,to_uid,summa,opcode) values (FROM_UNIXTIME(?),'?','?','?','?')"
                           <<ct.t<<ct.from_user_id.container<<ct.to_user_id.container<<s<<ct.operation_code);
    }
}
#endif

#ifdef __CLAN
string update_to_db(const PTR_getter<user_credit>&__U,const string& table_name)
{
    throw cError("user_credit update_to_db UNDEF");
    return "";
}
int user_credit::load_from_db(const string& table_name) const // 0 - no error
{

    DB_id id;
    id.container=get_db_row_id().as_int();
//    logErr2("user_credit::load_from_db %d",id.container);

    string r=clan_data_request(DR_user_credit,id);
    oscar_buffer bb(r.data(),r.size());
    ((user_credit*)this)->unpack(bb);
    return 0;
}
#else
string update_to_db(const PTR_getter<user_credit>&__U,const string& table_name)
{
    unsigned int uid;
    vector<string>v;
    {
        PGLR(user_credit, u,__U);
        uid=u->get_db_row_id().as_int();
        u->summa.update_str(v,"summa");
        (time_t&)u->last_access=time(NULL);
        u->last_access.update_strtime(v,"last_access");
    }
    if (v.size())
    {
        string s;
        s<<"update "<<table_name<<" set "<< join(",",v)<<" where refid="<<itostring(uid);
        return s;
    }
    return "";
}

int user_credit::load_from_db(const string& table_name) const // 0 - no error
{
    st_dbh d;
    vector<string> v=d.dbh->select_1_rowQ((QUERY)
                                          "select summa,UNIX_TIMESTAMP(last_access) "
                                          "from ? "
                                          "where refid=?"<<table_name<<get_db_row_id().as_int());
    if (v.size()!=2) {
        return -1;
    }
    summa.load(atof(v[0].c_str()));
    last_access.load(atoi(v[1].c_str()));

    return 0;
}
#endif
user_credit::user_credit()
{
    summa.load(0);
    last_access.load(0);
}


bool buy_thing(const DB_id& from_uid,const DB_id& to_uid,double price, const string &opcode) // true if success
{
    {
        PGLR( user_credit , b,user_credits.find_by_id(from_uid));
        if (b->summa<price) {
            return false;
        }
    }
    double rs;
    {
        PGLW( user_credit , b,user_credits.find_by_id(from_uid));
        rs=double (b->summa) - price;
        b->summa.dbset(rs);
    }
#ifndef __CLAN
    user_credits.make_1st_update(from_uid);
#endif
    send_update_d3(credit$set_summa,from_uid,rs);
    {
        PGLW( user_credit , b,user_credits.find_by_id(to_uid));
        rs=double (b->summa) + price;
        b->summa.dbset(rs);
    }
#ifndef __CLAN
    user_credits.make_1st_update(to_uid);
#endif
    send_update_d3(credit$set_summa,to_uid,rs);
    credit_transaction ct;
    ct.from_user_id = from_uid;
    ct.to_user_id = to_uid;
    ct.summa = price;
    ct.operation_code = opcode;
    ct.t = time(NULL);
    credit_transactions.push_back(ct);

    return true;

}
double credit_reminder(const DB_id& uid)
{
    {
        PGLR(user_credit, b,user_credits.find_by_id(uid));
        return b->summa;
    }
    return 0;
}


void user_credit::pack(out_oscar_buffer &b) const
{
    char s[100];
    snprintf(s,sizeof(s),"%f",summa.get());
    b
    <<string(s)
    <<last_access.get();
}
void user_credit::unpack(oscar_buffer &b)
{
    string _summa;
    time_t _last_access;
    b>>_summa>>_last_access;
    summa.load(atof(_summa.c_str()));
    last_access.load(_last_access);
}
