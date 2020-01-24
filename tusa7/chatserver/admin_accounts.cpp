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
#include "fotos.h"
#include "update_cmd.h"
#include "user_set.h"
#include "fotos_ui.h"
#include "cs_conn_data.h"
#include "html_out.h"
#include "chat_globals.h"


string homedir(unsigned int uid);
void get_DB_to_map(const PTR_getter<user_profile> &__UP, const PTR_getter<user_set>&__US, map<string,string> &m) ;

void url_admin_accounts(const PTR_getter<chat_user>&__UU,cs_conn_data *cc)
{

    user_pair __U(__UU);
    if (!(user$privileges(__U)&u_is_accounts_admin)) return;

    map<string,hstring> m;
    st_dbh d;
    m["~error~"]="";
    m["~level~"]=itostring(cc->sub_level);
    if (cc->params["id"].size()) {
        DB_id id;
        id.container=atoi(cc->params["id"].c_str());
        if (id.container==0)
        {
            map<string,hstring> K;
            cc->html_out=make_pair(K,"admin/accounts/alert_rec_not_found");
            return;
        }

        vector<string>	 v=d.dbh->select_1_rowQ((QUERY)"select id from users where id=?"<<id.container);
        {
            if (v.size()==0)
            {
                map<string,hstring> K;
                cc->html_out=make_pair(K,"admin/accounts/alert_rec_not_found");
                return;
            }
            PGLR(user_profile,z,user_profiles.find_by_id(id));
            {
                if (z->level/sub_levels>cc->sub_level) {
                    map<string,hstring> K;
                    cc->html_out=make_pair(K,"admin/accounts/alert_low_level");
                    return;
                }
            }
        }
        if (cc->params["DATA"]=="YES") {
            string e;
            if (cc->params["pass"].size()) {
                if (cc->params["pass"]!=cc->params["pass2"]) {
                    e+=_MSG("passwordsmismatch");
                }
                if (cc->params["pass"].size()<3) {
                    e+=_MSG("passwordisshort");
                }

                if (e=="") {
                    {
                        PGLW(user_profile, u,user_profiles.find_by_id(id));
                        u->pass=bin2hex(MD5(cc->params["pass"]),0);
                        send_update_g3(user_profile$pass,id,u->pass);

                    }
                }
            }
            e+=check_reg_map(cc->params,false);
            if (e.size()==0) {
                m["~error~"]=_MSG("changed2");
                string cnick;
                update_DB_from_reg_map(id,cc->params, false);
            } else {
                m["~error~"]=e;
            }
        }
        if (cc->params["rm_ph"]!="-1") {
            string n=cc->params["rm_ph"];
            vector<string> vv=splitTOK(".",n);

            if (vv.size()==2)
            {

                unsigned int uid=atoi(vv[0].c_str());
                unsigned int fid=atoi(vv[1].c_str());
                PGLW(user_fotos, z,users_fotos.find_by_id(uid));
                {
                    if (z->fotos.count(fid))
                    {
                        send_update_g4(foto$remove,uid,fid,z->fotos.find(fid)->second.ext);
                        z->fotos.erase(fid);
                    }
                }

            }
        }

        unsigned int size=0;
        string cnick;
        {
            PGLR(user_fotos, z,users_fotos.find_by_id(id));
            size=z->getsize();
        }

        map<string,string> mu;
        get_DB_to_map(user_profiles.find_by_id(id), user_sets.find_by_id(id), mu);
        fill_map_from_map(m,mu);
//        build_fotos_list(id,m,false);
        m["~pass~"]="";
        m["~allfsize~"]=number2text(size);
        cc->html_out=make_pair(m,"admin/accounts/user");
        return;
    }

    if (cc->params["nick"]=="" && cc->params["login"]=="") {
        cc->html_out=make_pair(m,"admin/accounts/template");
        return;
    }
    m["~nick~"]=cc->params["nick"];
    m["~login~"]=cc->params["login"];
    vector< vector<string> > v;
    if (cc->params["nick"].size()) {
        v=d.dbh->execQ((QUERY)"select a.uid,b.login from nicks a,user_profiles b where a.banned=0 and a.str_nick like '?%' and a.uid=b.refid group by 1"<<str_nick(cc->params["nick"]));
    }
    if (cc->params["login"].size()) {
        v=d.dbh->execQ((QUERY)"select refid,login from user_profiles where login like '?%'"<<cc->params["login"]);
    }
    m["~cnt~"]=itostring(v.size());
    hstring rows;
    for (unsigned int i=0;i<v.size();i++) {
        if (v[i].size()!=2) throw cError("select failed.");
        map<string,hstring> q;
        q["~id~"]=v[i][0];
        q["~login~"]=v[i][1];
        rows+=make_pair(q,"admin/accounts/row");
    }
    m["~users~"]=rows;
    cc->html_out=make_pair(m,"admin/accounts/index");
}
