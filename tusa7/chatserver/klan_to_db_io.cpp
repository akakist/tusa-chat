#include "stdafx.h"
#ifndef __CLAN
#include "mysql_extens.h"
#endif
#include "DB_id.h"
#include "str_lib.h"
#include "utils.h"
#include "chat_def.h"
#include "login_result.h"
#include "DR_types.h"
string str_nick(const string&);

#ifdef __CLAN
vector< vector<string> > gallery_request(const string &snick)
{
    vector< vector<string> > r;
    out_oscar_buffer v;
    v<<snick;
    string cr=clan_data_request(DR_gallery_request,v);
    oscar_buffer b(cr.data(),cr.size());
    b>>r;
    return r;

}
#else
vector< vector<string> > gallery_request(const string &_snick)
{

    string snick=str_replace("%","",_snick);
    snick=MESL(str_nick(snick));

    vector< vector<string> > r;
    st_dbh d;
    r=d.dbh->execQ((QUERY)"select id,uid,nick,ready_to_sale from nicks where str_nick like '?%' and banned=0 and uid!=0 order by str_nick"<<snick);
    return r;
}
#endif
#ifdef __CLAN
vector<string> select_uid_nick_by_ids(const DB_id &uid, unsigned int nid)
{
    vector<string> v;
    out_oscar_buffer o;
    o<<uid<<nid;
    string cr=clan_data_request(DR_select_uid_nick_by_ids,o);
    oscar_buffer b(cr.data(),cr.size());
    b>>v;
    return v;

}
#else
vector<string> select_uid_nick_by_ids(const DB_id &uid, unsigned int nid)
{
    st_dbh d;
    vector<string> v;

    v=d.dbh->select_1_rowQ((QUERY)"select uid,nick from nicks where id=? and uid=?"<<nid<<uid.container);
    return v;
}
#endif
#ifdef __CLAN
DB_id get_uid_by_nick(const string& nick)
{
    DB_id v;
    out_oscar_buffer o;
    o<<nick;
    string cr=clan_data_request(DR_get_uid_by_nick,o);
    oscar_buffer b(cr.data(),cr.size());
    b>>v;
    return v;
}
#else
DB_id get_uid_by_nick(const string& nick)
{
    st_dbh d;
    DB_id r;
    r.container=atoi(d.dbh->select_1Q((QUERY)"select uid from nicks where str_nick='?'"<<str_nick(nick)));
    return r;
}
#endif

#ifdef __CLAN
vector<string> get_id_uid_nick_by_nick(const string &to_nick)
{
    vector<string> v;
    out_oscar_buffer o;
    o<<to_nick;
    string cr=clan_data_request(DR_get_id_uid_nick_by_nick,o);
    oscar_buffer b(cr.data(),cr.size());
    b>>v;
    return v;
}
pair<string,DB_id> get_pass_by_nick(const string &nick)
{
    pair<string,DB_id> v;
    out_oscar_buffer o;
    o<<nick;
    string cr=clan_data_request(DR_get_pass_by_nick,o);
    oscar_buffer b(cr.data(),cr.size());
    b>>v;
    return v;
}
vector<string> get_uid_time_cnt_descr_from_banned_login_by_uid(const DB_id &uid)
{
    vector<string> v;

    out_oscar_buffer o;
    o<<uid;
    string cr=clan_data_request(DR_get_uid_time_cnt_descr_from_banned_login_by_uid,o);
    oscar_buffer b(cr.data(),cr.size());
    b>>v;
    return v;
}

#else
string MESL(const string &s);
vector<string> get_id_uid_nick_by_nick(const string &to_nick)
{
    vector<string> v;
    st_dbh d;
    v=d.dbh->select_1_row("select id,uid,nick from nicks where str_nick like '"+MESL(str_nick(to_nick))+"'");
    return v;
}
pair<string,DB_id> get_pass_by_nick(const string &nick)
{
    pair<string,DB_id> r;

    st_dbh d;
    vector<string> v=d.dbh->select_1_rowQ((QUERY)"select uid from nicks where str_nick='?' and banned<>'1'"<<str_nick(nick));

    if (v.size())
    {
        if (atoi(v[0]))
        {
            vector<string> v1=d.dbh->select_1_rowQ((QUERY)"select refid,pass from user_profiles where refid=?"<<v[0]);
            if (v1.size()==2) {
                r.first=v1[1];
                r.second.container=atoi(v1[0]);
            }
        }
    }
    return r;
}
vector<string> get_uid_time_cnt_descr_from_banned_login_by_uid(const DB_id &uid)
{
    vector<string> bb;
    {
        st_dbh d;
        bb=d.dbh->select_1_rowQ((QUERY)"select uid,time_cnt,descr from banned_login where uid='?'"<<uid.container);
    }
    return bb;

}
#endif

#ifdef __CLAN
map<string,string> calc_statistic()
{
    map<string,string> v;
    string cr=clan_data_request(DR_calc_statistic);
    oscar_buffer b(cr.data(),cr.size());
    b>>v;
    return v;
}
#else
map<string,string> calc_statistic()
{
    map<string,string> m;
    st_dbh d;
    {
        m["~allmsg~"]=d.dbh->select_1("select sum(m_count) from user_stats");
        m["~allhours~"]=make_time(atoi(d.dbh->select_1("select sum(t_count) from user_stats")));
        m["~allusers~"]=d.dbh->select_1("select count(*) from users");
        m["~allnicks~"]=d.dbh->select_1("select count(*) from nicks");
    }
    time_t t=time(NULL);
    struct tm q=LOCALTIME(t);
    {
        q.tm_min=0;
        q.tm_sec=0;
        q.tm_hour=0;
        t=mktime(&q);
    }
    {
        m["~regtoday~"]=d.dbh->select_1Q((QUERY)"select count(*) from user_profiles where UNIX_TIMESTAMP(reg_date)>='?'"<<t);
        m["~regyestoday~"]=d.dbh->select_1Q((QUERY)"select count(*) from user_profiles where UNIX_TIMESTAMP(reg_date)>='?'"<<t-86400);
        m["~newusers~"]=d.dbh->select_1Q((QUERY)"select count(*) from user_profiles where level<?"<<sub_levels*2);
        m["~users~"]=d.dbh->select_1Q((QUERY)"select count(*) from user_profiles where level<? and level>=?"<<sub_levels*3<<sub_levels*2);
        m["~chatters~"]=d.dbh->select_1Q((QUERY)"select count(*) from user_profiles where level<? and level>=?"<<sub_levels*4<<sub_levels*3);
        m["~tus~"]=d.dbh->select_1Q((QUERY)"select count(*) from user_profiles where level<? and level>=?"<<sub_levels*5<<sub_levels*4);
        m["~vips~"]=d.dbh->select_1Q((QUERY)"select count(*) from user_profiles where level<? and level>=?"<<sub_levels*6<<sub_levels*5);
        m["~adm~"]=d.dbh->select_1Q((QUERY)"select count(*) from user_profiles where level>=?"<<sub_levels*6);
    }
    string top50m;
    string top50h;
    vector< vector<string> > v;
    {
        {
            v=d.dbh->execQ((QUERY)
                           "select user_sets.last_nick_id,user_sets.last_nick,user_stats.m_count,user_sets.refid from user_sets,user_stats where user_sets.refid=user_stats.refid order by user_stats.m_count desc limit 50"
                          );
        }
        for (unsigned int i=0;i<v.size();i++) {
            if (v[i].size()!=4) throw cError("select failed. size different");
            top50m+="<tr><td align=right>"+itostring(i+1)+"</td><td><a class=nick href=\"/gallery?ni="+v[i][3]+"."+v[i][0]+"\" target=_blank>"+v[i][1]+"</td><td align=right>"+v[i][2]+"</td></tr>\r\n";
        }
    }
    {
        v=d.dbh->execQ((QUERY)

                       "select user_sets.last_nick_id,user_sets.last_nick,user_stats.t_count,user_sets.refid from user_sets,user_stats where user_sets.refid=user_stats.refid order by user_stats.t_count desc limit 50"
                      );
        {
            for (unsigned int i=0;i<v.size();i++) {
                if (v[i].size()!=4) throw cError("select failed. size different");
                top50h+="<tr><td align=right>"+itostring(i+1)+"</td><td><a class=nick href=\"/gallery?ni="+v[i][3]+"."+v[i][0]+"\" target=_blank>"+v[i][1]+"</td><td align=right>"+make_time(atoi(v[i][2]))+"</td></tr>\r\n";
            }
        }
    }
    {
        m["~topmess~"]=top50m;
        m["~tophour~"]=top50h;
    }
    return m;
}
#endif
#ifdef __CLAN
map<time_t,unsigned int> get_users_counts(time_t t, time_t rt)
{
    map<time_t,unsigned int> u;
    out_oscar_buffer o;
    o<<t<<rt;
    string cr=clan_data_request(DR_get_users_counts,o);
    oscar_buffer b(cr.data(),cr.size());
    b>>u;
    return u;
}
#else
map<time_t,unsigned int> get_users_counts(time_t t, time_t rt)
{
    map<time_t,unsigned int> u;
    vector< vector<string> > v;
    {
        st_dbh db;
        v=db.dbh->execQ((QUERY)"select UNIX_TIMESTAMP(dt),cnt from users_count where UNIX_TIMESTAMP(dt)>='?' and UNIX_TIMESTAMP(dt)<='?'"<<t<<rt);
    }
    for (unsigned int i=0;i<v.size();i++) {
        if (v[i].size()!=2) throw cError("select failed. size different");
        time_t st=atoi(v[i][0]);
        u[st]=atoi(v[i][1]);
    }
    return u;
}
#endif
#ifdef __CLAN
string login_io(const string& login, const string& pass)
{

    out_oscar_buffer b;
    b<<login<<pass;
    string rc=clan_data_request(DR_login_io,b);
    oscar_buffer bb(rc.data(),rc.size());
    string r;
    bb>>r;
    return r;
}
#else
string login_io(const string& login, const string& pass)
{
    int res=LOGIN_SUCCESS;
    st_dbh d;
    vector<string> __v=d.dbh->select_1_rowQ((QUERY)"select refid from user_profiles where login like '?'"<<str_nick(login));
    if (__v.size()==0) {
        __v=d.dbh->select_1_rowQ((QUERY)"select uid from nicks where str_nick like '?' and banned='0'"<<str_nick(login));
        if (__v.size()==0)
        {
            res=LOGIN_INCORRECT;
        }
    }
    DB_id uid;
    if (res==LOGIN_SUCCESS)
    {
        uid.container=atoi(__v[0]);
        if (uid.container==0)
        {
            res=LOGIN_INCORRECT;
        }
    }
    if (res==LOGIN_SUCCESS)
    {
        __v=d.dbh->select_1_rowQ((QUERY)"select pass from user_profiles where refid=?"<<uid.container);
        if (__v.size()!=1)
        {
            res=LOGIN_INCORRECT;
        }
    }
    if (res==LOGIN_SUCCESS)
    {
        string db_pass=__v[0];
        if (pass!=db_pass)
        {
            res=LOGIN_INCORRECT;
        }
    }
    string time_cnt,reason;
    int time_free,time_ban;
    if (res==LOGIN_SUCCESS)
    {
        vector <string> z=d.dbh->select_1_rowQ((QUERY)"select time_cnt,UNIX_TIMESTAMP(time_free),UNIX_TIMESTAMP(time_ban),descr from banned_login where uid='?'"<<uid.container);
        if (z.size()!=0) {	//login banned.

            if (z.size()==4)
            {
                time_cnt=z[0];
                time_free=atoi(z[1]);
                time_ban=atoi(z[2]);
                reason=z[3];

            }
            res=LOGIN_BANNED;
        }
    }
    out_oscar_buffer b;
    b<<res;
    if (res==LOGIN_BANNED)
    {
        b<<time_cnt<<time_free<<time_ban<<reason;

    }
    if (res==LOGIN_SUCCESS) b<<uid;
    return b.as_string();

}
#endif
