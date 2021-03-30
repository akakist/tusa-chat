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

string is_checked(bool b)
{
    if (b) return "checked";
    return "";
}

void url_admin_privs(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);

    if (!(user$privileges(__U)&u_is_privs_admin)) return;

    map<string,hstring> m;
    m["~msg~"]="";
    m["~level~"]=itostring(cc->sub_level);
    hstring us;
    string cmd=cc->params["cmd"];
    unsigned int id=atoi(cc->params["id"].c_str());

    if (cmd=="change") {
        int p=0;
        {
            if (strupper(cc->params["forum_admin"])=="ON") p|=u_is_forum_admin;
            if (strupper(cc->params["view_logs"])=="ON") p|=u_allow_view_logs;
            if (strupper(cc->params["settings"])=="ON") p|=u_is_settings_admin;
            if (strupper(cc->params["funny_admin"])=="ON") p|=u_is_funny_admin;
            if (strupper(cc->params["vote_admin"])=="ON") p|=u_is_vote_admin;
            if (strupper(cc->params["privs_admin"])=="ON") p|=u_is_privs_admin;
            if (strupper(cc->params["accounts"])=="ON") p|=u_is_accounts_admin;
            if (strupper(cc->params["hints_admin"])=="ON") p|=u_is_hints_admin;
            if (strupper(cc->params["news_admin"])=="ON") p|=u_is_news_admin;

            if (strupper(cc->params["smiles_admin"])=="ON") p|=u_is_smiles_admin;
            if (strupper(cc->params["advertizer_admin"])=="ON") p|=u_is_advertizer_admin;
            if (strupper(cc->params["cansettopic"])=="ON") p|=u_allow_set_topic;
            if (strupper(cc->params["allow_tags"])=="ON") p|=u_allow_tags;
            if (strupper(cc->params["credit_operator"])=="ON") p|=u_is_credit_operator;
            if (strupper(cc->params["photo_admin"])=="ON") p|=u_is_photo_admin;

        }
        {
            PGLW(user_profile, z,user_profiles.find_by_id(id));
            z->db_privileges=p;

        }
        send_update_g3(user_profile$db_privileges,id,p);
        m["~msg~"]=_MSG("changed");
        logErr2("%s (%s) changed privileges for user id=%d [%s-%s]",GET_CNICK(__U).c_str(),user$login(__U).c_str(),id,cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str());
    }
    if (cmd=="add") {
        string nick=cc->params["add"];
        st_dbh d;
        unsigned int uid=atoi(d.dbh->select_1Q((QUERY)"select uid from nicks where nick='?'"<<nick).c_str());
        if (uid!=0) {
            int p;
            PTR_getter<user_profile> __Z(user_profiles.find_by_id(uid));
            if (__Z)
            {
                PGLR(user_profile, z,__Z);
                p=z->db_privileges;
            }
            if (p>0) {
                m["~msg~"]=_MSG("useralreadyexists");
            } else {
                p=u_allow_set_topic;
                {
                    PGLW(user_profile, z,__Z);
                    z->db_privileges=z->db_privileges|u_allow_set_topic;
                    send_update_g3(user_profile$db_privileges,uid,z->db_privileges);
                }

                m["~msg~"]=_MSG("useradded");
                logErr2("%s (%s) added privileges for user id=%d [%s-%s]",GET_CNICK(__U).c_str(),user$login(__U).c_str(),uid,cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str());
            }
        } else {
            m["~msg~"]=_MSG("usernotfound");
        }
    }
    st_dbh d;
    if (!cmd.size() && cc->params["id"].size()) {
        map<string,hstring> q;
        int p;
        string login;
        {
            PGLR(user_profile, z,user_profiles.find_by_id(id));
            p=z->db_privileges;
            login=z->login;
        }
        q["~id~"]=itostring(id);

        q["~login~"]=login;
        q["~forum_admin~"]=is_checked(p & u_is_forum_admin);
        q["~view_logs~"]=is_checked(p & u_allow_view_logs);
        q["~settings~"]=is_checked(p & u_is_settings_admin);
        q["~funny_admin~"]=is_checked(p & u_is_funny_admin);
        q["~vote_admin~"]=is_checked(p & u_is_vote_admin);
        q["~privs_admin~"]=is_checked(p & u_is_privs_admin);
        q["~accounts~"]=is_checked(p & u_is_accounts_admin);
        q["~hints_admin~"]=is_checked(p & u_is_hints_admin);
        q["~news_admin~"]=is_checked(p & u_is_news_admin);

        q["~smiles_admin~"]=is_checked(p & u_is_smiles_admin);
        q["~cansettopic~"]=is_checked(p & u_allow_set_topic);
        q["~allow_tags~"]=is_checked(p & u_allow_tags);
        q["~advertizer_admin~"]=is_checked(p & u_is_advertizer_admin);
        q["~credit_operator~"]=is_checked(p & u_is_credit_operator);
        q["~photo_admin~"]=is_checked(p & u_is_photo_admin);

        m["~user~"]=make_pair(q,"admin/privileges/edit_privilege");
    } else {
        m["~user~"]="";
    }
    vector< vector<string> > v=d.dbh->exec("select refid,login,db_privileges,level from user_profiles where db_privileges>0 order by login");

    for (unsigned int i=0;i<v.size();i++) {
        map<string,hstring> q;
        if (v[i].size()!=4) throw cError("select failed. size different.");
        q["~id~"]=v[i][0];
        q["~login~"]=v[i][1];
        int p=atoi(v[i][2].c_str());
        string pr;
        if (p & u_is_forum_admin) pr+="Forum admin, ";
        if (p & u_allow_view_logs) pr+="View logs, ";
        if (p & u_is_settings_admin) pr+=" Settings admin, ";
        if (p & u_is_funny_admin) pr+="Funny admin, ";
        if (p & u_is_vote_admin) pr+="Vote admin, ";
        if (p & u_is_privs_admin) pr+="Privs admin, ";
        if (p & u_is_accounts_admin) pr+="Accounts admin, ";
        if (p & u_is_hints_admin) pr+="Hints admin, ";
        if (p & u_is_news_admin) pr+="News admin, ";

        if (p & u_is_smiles_admin) pr+="Smiles admin, ";
        if (p & u_allow_set_topic) pr+="Can set topic, ";
        if (p & u_allow_tags) pr+="Allowed all tags, ";
        if (p & u_is_credit_operator) pr+="Credit operator, ";
        if (p & u_is_photo_admin) pr+="Photos admin, ";
        if (p & u_is_advertizer_admin) pr+="Advertizer admin, ";
        q["~privs~"]=pr.substr(0,pr.size()-2);
        us+=make_pair(q,"admin/privileges/privileges_user");
    }
    m["~users~"]=us;
    m["~cnt~"]=itostring(v.size());
    cc->html_out=make_pair(m,"admin/privileges/privileges");
}
