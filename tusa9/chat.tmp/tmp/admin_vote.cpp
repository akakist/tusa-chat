#include "stdafx.h"
#ifdef _DEBUG
#define New DEBUG_NEW
#endif

#include "_mutex.h"
#include <list>
#include "mutex_inspector.h"
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

#include <algorithm>
#include "file_set.h"
#include "copy_file.h"

#include "channels.h"
#include "levels.h"
#include "server_config.h"

#include "chat_config.h"
#include "app_def.h"
#include "update_cmd.h"
#include "user_profile.h"
#include "app_con.h"
#include "web_tools.h"

#include "chat_globals.h"
#ifdef __WITH_LICENSE
#include "license.h"
#endif

DB_id get_uid_by_nick(const string& nick);

void recalc_vote();
void url_admin_vote(const PTR_getter<chat_user> &__UU,app_connection*cc)
{
    MUTEX_INSPECTOR;
	st_dbh d;
	st_update stu;
    if (!__UU){ cc->html_out=cc->redirect();return;}
    user_pair __U(__UU);
    if (!user__privileges(__U,"$vote")) return;
    LICENSE_CK(4);
    map<string,string> m;
    m["~msg~"]="";
    m["~level~"]=itostring(user$level(__U)/sub_levels);

    if (cc->params["cmd"]=="update"){
        for (map<string,string>::const_iterator i=cc->params.begin();i!=cc->params.end();i++){
            string c=i->first;
            if (c.substr(0,2)=="hb"){
                string id=c.substr(2,c.size()-2);
				d.dbh->real_queryQ((QUERY)"update tbl_users set vote_balls='?' where id='?'"<<atoi(i->second)<<id);
                /*{
                    PGLW(user_profile,z,user$profiles.FindByID(atoi(id)));
					z->vote_balls=atoi(i->second);
//					__send_update_d3(user_profile$vote_balls$3,atoi(id),z->vote_balls);
                }*/
            }
        }
        recalc_vote();
        m["~msg~"]=_MSG("changed");
    }

    if (cc->params["cmd"]=="remove"){
        unsigned int id=atoi(cc->params["remove"]);
		d.dbh->real_queryQ((QUERY)"update tbl_users set vote_balls=0 where id=?"<<id);
        /*{
            PGLW(user_profile,z,user$profiles.FindByID(id));
			//z->vote_balls=0;
			//__send_update_d3(user_profile$vote_balls$3,id,0);
		}*/
        st_dbh d;
        d.dbh->real_queryQ((QUERY)"delete from grant_agrees where uid=?"<<id);
        m["~msg~"]=_MSG("changed");
    }
    if (cc->params["cmd"]=="add"){
        st_dbh d;
        string nick=cc->params["add"];
        DB_id id=get_uid_by_nick(nick);
        if (CONTAINER(id)==0){
            m["~msg~"]=_MSG("nicknotfound");
        }else{
            m["~msg~"]=_MSG("useradded");
            {
                //PGLW(user_profile,z,user$profiles.FindByID(CONTAINER(id)));
				//z->vote_balls=100;
				d.dbh->real_queryQ((QUERY)"update tbl_users set vote_balls='100' where id='?'"<<CONTAINER(id));
				//__send_update_d3(user_profile$vote_balls$3,CONTAINER(id),100);
			}
        }
    }
//    st_dbh d;
    vector< vector<string> > v=d.dbh->exec("select id,vote_balls from tbl_users where vote_balls>0 order by id");

    string usr;

    for (unsigned int i=0;i<v.size();i++){
        map<string,string> q;
        if (v[i].size()!=2) throw cError("select failed."+_DMI());
        q["~id~"]=v[i][0];

        q["~perc~"]=v[i][1];
        {
            PGLR(user_profile,u,user$profiles.FindByID(atoi(v[i][0])));
			q["~login~"]=u->login;
        }
        usr+=RVfiles(q,"admin/vote/vote_user");
    }
    m["~users~"]=usr;

    cc->html_out=cc->rvfiles(m,"admin/vote/vote");
}


