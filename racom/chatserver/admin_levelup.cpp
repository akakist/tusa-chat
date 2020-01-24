#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <time.h>
#include <map>
#include "mysql_extens.h"
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

#include "channels.h"
#include "levels.h"
#include "server_config.h"

#include "chat_config.h"
#include "app_def.h"
#include "update_cmd.h"
#include "user_set.h"
#include "cs_conn_data.h"
#include "html_out.h"
#ifndef __CLAN

void url_admin_levelup(const PTR_getter<chat_user>&__UU,cs_conn_data *cc)
{

    user_pair __U(__UU);
    int levelup_ability=LEVELS(user$level(__U)).levelup_ability;
    if (levelup_ability==0) return;
    DB_id uid=user$id(__U);
    map<string,hstring> m;
    st_dbh d;
    if (cc->params["nick"]=="" && cc->params["login"]=="") {
        cc->html_out=make_pair(m,"admin/levelup/levelup_template");
        return;
    }
    m["~nick~"]=cc->params["nick"];
    m["~login~"]=cc->params["login"];
    m["~level~"]=itostring(cc->sub_level);

    if (cc->params["cmd"]=="change") {
        DB_id id;
        id.container=atoi(cc->params["id"].c_str());
        unsigned int ul;
        {
            PGLR(user_profile, up,user_profiles.find_by_id(id.container));
            ul=up->level;
        }

        if (levelup_ability>ul) {
            unsigned int nl=atoi(cc->params["level"].c_str());
            if (nl<=levelup_ability) {
                logErr2("%s (%s) changed level for user %d, set to %d",GET_CNICK_DBID(id).c_str(),user$login(id).c_str(),id.container,nl);
                {
                    PGLW(user_profile,z,user_profiles.find_by_id(id));
                    z->level=LEVELS(nl).id;
                    send_update_g3(user_profile$level,id,z->level);
                }
                {
                    PGLW(user_set,z,user_sets.find_by_id(id));
                    z->poweshen=cc->user_id;
                    send_update_g3(user_set$poweshen,id,cc->user_id.container);
                }
            }
        }
    }
    vector< vector<string> > v;
    if (cc->params["nick"].size()) {
        v=d.dbh->execQ((QUERY)"select b.refid,b.login,b.level,user_stats.m_count,user_stats.t_count from nicks a,user_profiles b,user_stats where a.banned=0 and a.str_nick like '?%' and a.uid=b.refid and b.refid=user_stats.refid group by 1"<<str_nick(cc->params["nick"]));
    }
    if (cc->params["login"].size()) {
        v=d.dbh->execQ((QUERY)"select a.refid,a.login,a.level,b.m_count,b.t_count from user_profiles a,user_stats b where a.refid=b.refid and a.login like '?%'"<<cc->params["login"]);
    }
    m["~cnt~"]=itostring(v.size());
    hstring rows;
    for (unsigned int i=0;i<v.size();i++) {
        if (v[i].size()!=5) throw cError("select failed.");
        unsigned int ul=atoi(v[i][2].c_str());
        map<string,hstring> q;
        q["~id~"]=v[i][0];
        q["~login~"]=v[i][1];
        string s="<SELECT name=level"+v[i][0];
        if (levelup_ability<ul) {
            s+=" DISABLED";
            q["~disabled~"]="DISABLED";
        } else {
            q["~disabled~"]="";
        }
        s+=">";
        map<unsigned int, c_level> lvl;
        lvl=LEVELS_GET();
        for (map<unsigned int,c_level>::iterator j=lvl.begin();j!=lvl.end();j++) {
            if (j->first>levelup_ability) continue;
            if (j->first<ul) continue;
            s+="<option value="+itostring(j->first);
            if (j->first==ul) s+=" SELECTED";
            s+=">"+j->second.name(0)+"\r\n";
        }
        s+="</SELECT>";
        q["~level~"]=s;
        q["~mcount~"]=v[i][3];
        q["~tcount~"]=make_time(atoi(v[i][4].c_str()));
        rows+=make_pair(q,"admin/levelup/levelup_row");
    }
    m["~users~"]=rows;
    cc->html_out=make_pair(m,"admin/levelup/levelup");
}
void url_admin_leveldown(const PTR_getter<chat_user>&__UU,cs_conn_data *cc)
{

    user_pair __U(__UU);
    int leveldown_ability=LEVELS(user$level(__U)).leveldown_ability;
    if (leveldown_ability==0) return;
    DB_id uid=user$id(__U);
    map<string,hstring> m;
    st_dbh d;
    if (cc->params["nick"]=="" && cc->params["login"]=="") {
        cc->html_out=make_pair(m,"admin/leveldown/leveldown_template");
        return;
    }
    m["~nick~"]=cc->params["nick"];
    m["~login~"]=cc->params["login"];
    m["~level~"]=itostring(cc->sub_level);

    if (cc->params["cmd"]=="change") {
        DB_id id;
        id.container=atoi(cc->params["id"].c_str());
        unsigned int ul;
        {
            PGLR(user_profile, up,user_profiles.find_by_id(id));
            ul=up->level;
        }

        if (leveldown_ability>=ul) {
            unsigned int nl=atoi(cc->params["level"].c_str());
            if (nl<=leveldown_ability) {
                logErr2("%s (%s) changed level for user %d, set to %d",GET_CNICK_DBID(id).c_str(),user$login(id).c_str(),id.container,nl);
                {
                    PGLW(user_profile,z,user_profiles.find_by_id(id));
                    z->level=LEVELS(nl).id;

                    send_update_g3(user_profile$level,id,z->level);

                }
                {
                    PGLW(user_set,z,user_sets.find_by_id(id));
                    z->poweshen=cc->user_id;
                    send_update_g3(user_set$poweshen,id,cc->user_id.container);
                }
            }
        }
    }
    vector< vector<string> > v;
    if (cc->params["nick"].size()) {
        v=d.dbh->execQ((QUERY)"select b.refid,b.login,b.level,user_stats.m_count,user_stats.t_count from nicks a,user_profiles b,user_stats where a.banned=0 and a.str_nick like '?%' and a.uid=b.refid and b.refid=user_stats.refid group by 1"<<str_nick(cc->params["nick"]));
    }
    if (cc->params["login"].size()) {
        v=d.dbh->execQ((QUERY)"select a.refid,a.login,a.level,b.m_count,b.t_count from user_profiles a,user_stats b where a.refid=b.refid and a.login like '?%'"<<cc->params["login"]);
    }
    m["~cnt~"]=itostring(v.size());
    hstring rows;
    for (unsigned int i=0;i<v.size();i++) {
        if (v[i].size()!=5) throw cError("select failed.");
        unsigned int ul=atoi(v[i][2].c_str());
        map<string,hstring> q;
        q["~id~"]=v[i][0];
        q["~login~"]=v[i][1];
        string s="<SELECT name=level"+v[i][0];
        if (leveldown_ability<ul) {
            s+=" DISABLED";
            q["~disabled~"]="DISABLED";
        } else {
            q["~disabled~"]="";
        }
        s+=">";
        map<unsigned int, c_level> lvl;
        lvl=LEVELS_GET();
        for (map<unsigned int,c_level>::iterator j=lvl.begin();j!=lvl.end();j++) {
            if (j->first>leveldown_ability) continue;
            if (j->first>ul) continue;
            s+="<option value="+itostring(j->first);
            if (j->first==ul) s+=" SELECTED";
            s+=">"+j->second.name(0)+"\r\n";
        }
        s+="</SELECT>";
        q["~level~"]=s;
        q["~mcount~"]=v[i][3];
        q["~tcount~"]=make_time(atoi(v[i][4].c_str()));
        rows+=make_pair(q,"admin/leveldown/leveldown_row");
    }
    m["~users~"]=rows;
    cc->html_out=make_pair(m,"admin/leveldown/leveldown");
}
#endif
