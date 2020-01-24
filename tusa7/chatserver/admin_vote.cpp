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
#include "chat_globals.h"
#ifndef __CLAN
void recalc_vote();
void url_admin_vote(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);
    if (!(user$privileges(__U)&u_is_vote_admin)) return;

    map<string,hstring> m;
    m["~msg~"]="";
    m["~level~"]=itostring(cc->sub_level);

    if (cc->params["cmd"]=="update") {
        for (map<string,string>::iterator i=cc->params.begin();i!=cc->params.end();i++) {
            string c=i->first;
            if (c.substr(0,2)=="hb") {
                string id=c.substr(2,c.size()-2);
                {
                    PGLW(user_profile,z,user_profiles.find_by_id(atoi(id.c_str())));
                    z->vote_balls=atoi(i->second.c_str());
                    send_update_g3(user_profile$vote_balls,atoi(id.c_str()),z->vote_balls);
                }
            }
        }
        recalc_vote();
        m["~msg~"]=_MSG("changed");
    }

    if (cc->params["cmd"]=="remove") {
        unsigned int id=atoi(cc->params["remove"].c_str());
        {
            PGLW(user_profile,z,user_profiles.find_by_id(id));
            z->vote_balls=0;
            send_update_g3(user_profile$vote_balls,id,0);
        }
        st_dbh d;
        d.dbh->real_queryQ((QUERY)"delete from grant_agrees where uid=?"<<id);
        m["~msg~"]=_MSG("changed");
    }
    if (cc->params["cmd"]=="add") {
        st_dbh d;
        string nick=cc->params["add"];
        string id=d.dbh->select_1("select uid from nicks where str_nick like '"+MESL(str_nick(nick))+"'");
        if (!id.size()) {
            m["~msg~"]=_MSG("nicknotfound");
        } else {
            m["~msg~"]=_MSG("useradded");
            {
                PGLW(user_profile,z,user_profiles.find_by_id(atoi(id.c_str())));
                z->vote_balls=100;
                send_update_g3(user_profile$vote_balls,atoi(id.c_str()),100);
            }
        }
    }
    st_dbh d;
    vector< vector<string> > v=d.dbh->exec("select refid,login,vote_balls from user_profiles where vote_balls>0 order by refid");

    hstring usr;

    for (unsigned int i=0;i<v.size();i++) {
        map<string,hstring> q;
        if (v[i].size()!=3) throw cError("select failed.");
        q["~id~"]=v[i][0];
        q["~login~"]=v[i][1];
        q["~perc~"]=v[i][2];
        usr+=make_pair(q,"admin/vote/vote_user");
    }
    m["~users~"]=usr;

    cc->html_out=make_pair(m,"admin/vote/vote");
}

#endif
