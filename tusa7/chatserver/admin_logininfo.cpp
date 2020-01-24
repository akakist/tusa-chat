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
#include "user_credits.h"
#include "update_cmd.h"
#include "user_stat.h"
#include "user_set.h"
#include "web_tools.h"
#include "cs_conn_data.h"
#include "html_out.h"
#include "chat_globals.h"

void url_admin_logininfo(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);


    if (cc->sub_level<am_admin) {
        return;
    }
    DB_id zid;
    zid.container=atoi(cc->params["id"].c_str());
    st_dbh d;
    if (zid.container==0) {
        string login=cc->params["login"];
        zid.container=atoi(d.dbh->select_1Q((QUERY)"select refid from user_profiles where login='?'"<<login).c_str());
    }
    if (zid.container==0) {
        cc->html_out+="<script>alert('"+_MSG("loginnotfound")+"');window.close();</script>";
        return;
    }
    time_t last_date;
    string last_ip;
    int v_count;
    int m_count;
    time_t t_count;
    unsigned int kick_count;
    unsigned int kicked_count;
    {
        PGLR(user_stat,u,user_stats.find_by_id(zid));
        last_date=u->last_date;
        last_ip=u->last_ip;
        v_count=u->v_count;
        m_count=u->m_count;
        t_count=u->t_count;
        kick_count=u->kick_count;
        kicked_count=u->kicked_count;

    }
    DB_id poweshen;
    {
        PGLR(user_set, z,user_sets.find_by_id(zid));
        poweshen=z->poweshen;
    }
    map<string,hstring> m;
    {
        PGLR(user_profile, z,user_profiles.find_by_id(zid));
        if (z->info!="") {
            map<string,string>q;
            m["~hr~"]=RVfiles(q,"admin/login_info_hr");
        } else {
            m["~hr~"]="";
        }
    }
    m["~userinfo~"]=make_user_info(zid,cc->user_id,true,false,"","",cc->user_id.container!=0);
    m["~lnick~"]=GET_CNICK_DBID(zid);
    {

        {
            PGLR(user_set, z,user_sets.find_by_id(zid));
            m["~invisibility~"]=itostring(z->bought_invisibility);
        }
        {
            PGLR(user_credit, z,user_credits.find_by_id(zid));
            m["~credits~"]=get_f22(z->summa);
        }
        {
            PGLR(user_profile, z,user_profiles.find_by_id(zid));
            m["~login~"]=z->login;
            m["~id~"]=itostring(zid.container);
            if (t_count<3600) {
                m["~msgperhour~"]="N/A";
            } else {
                m["~msgperhour~"]=itostring( m_count / (t_count/3600) );
            }
            m["~msgcount~"]=itostring(m_count);
            m["~timecount~"]=make_time(t_count);
            m["~viscount~"]=itostring(v_count);
            m["~regdate~"]=datetime2rus(z->reg_date);
            m["~lastip~"]=last_ip;
            m["~lastdate~"]=datetime2rus(last_date);
            m["~kick~"]=itostring(kick_count);
            m["~kicked~"]=itostring(kicked_count);
            m["~vote_balls~"]=itostring(z->vote_balls);
            m["~level~"]=itostring(z->level);
        }
        vector<string> n;
        {
            PGLR(nick_vec, z,nick_vecs.find_by_id(zid));
            for (typeof(z->u_nicks.begin()) i=z->u_nicks.begin();i!=z->u_nicks.end();i++) {
                n.push_back(i->second.name);
            }
            if (cc->sub_level==am_sadmin) {
                m["~nicks~"]=join(", ",n);
            } else {
                m["~nicks~"]=itostring(n.size())+" "+_MSG("count");
            }
        }
        if (poweshen.container)
            m["~poweshen~"]=GET_CNICK_DBID(poweshen);
        else m["~poweshen~"]="VOTE";
    }
    cc->html_out+=make_pair(m,"admin/logininfo");
}
