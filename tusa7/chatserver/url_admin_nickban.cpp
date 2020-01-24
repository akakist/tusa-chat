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
#include "server_config.h"
#include "user.h"
#include "update_cmd.h"
#include "user_set.h"
#include "admin.h"
#include "cs_conn_data.h"
#include "html_out.h"
#include "chat_globals.h"
#include "app_def.h"

void url_admin_nickban(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    user_pair __U(__UU);
    if (cc->sub_level<am_guard) {
        return;
    }
    map<string,hstring> m;
    m["~msg~"]="";
    if (cc->params.find("sort")!=cc->params.end()) {
        m["~sort~"]=cc->params["sort"];
    } else {
        m["~sort~"]="nick";
    }
    string cmd=cc->params["cmd"];
    st_dbh d;
    if (cmd=="remove" && cc->sub_level>=am_guard) {
        vector<string> vn=splitTOK(".",cc->params["id"]);
        if (vn.size()==2)
        {
            vector<string> v=d.dbh->select_1_rowQ((QUERY)"select nicks.uid,nicks.bby,user_profiles.level,nicks.nick from nicks,user_profiles where nicks.uid='?' and nicks.id='?' and user_profiles.refid=nicks.bby"<<vn[0]<<vn[1]);
            if (v.size()!=4) {
                m["~msg~"]=_MSG("rec_not_found");
            } else {
                unsigned int uid=atoi(v[0].c_str());
                DB_id id;
                id.container=atoi(v[1].c_str());
                unsigned int bl=atoi(v[2].c_str())/sub_levels;
                unsigned int ul=cc->sub_level;
                if (id==cc->user_id || ul==am_sadmin || bl<=ul) {

                    if (v[0]=="0") {
                        d.dbh->real_queryQ((QUERY)"delete from nicks where uid='0' and id=?"<<vn[1]);
                    } else {
                        d.dbh->real_queryQ((QUERY)"update nicks set banned=0, bby=0 where uid=? and id=?"<<vn[0]<<vn[1]);
                    }
                    m["~msg~"]=_MSG("nickunbanned");
                    logErr2("%s (%s) unbanned nick %s [%s - %s]",GET_CNICK(__U).c_str(),user$login(__U).c_str(),v[3].c_str(),cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str());
                } else {
                    m["~msg~"]=_MSG("nicknopriv");
                }
            }
        }
    }
    if (cmd=="add") {
        string nick;
        if (remove_spaces(cc->params["addnick"])!="") {
            nick=cc->params["addnick"];
            int r=do_nickban(nick,cc->user_id,cc->sub_level);
            if (r==2) {
                m["~msg~"]=_MSG("nickbannedforsystem");
                logErr2("%s (%s) banned nick %s [%s - %s]",GET_CNICK(__U).c_str(),user$login(__U).c_str(),nick.c_str(),cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str());
            }
            if (r==1) {
                m["~msg~"]=_MSG("nickalreadybanned");
            }
            if (r==0) {
                m["~msg~"]=_MSG("nickbanned");
                logErr2("%s (%s) banned nick %s [%s - %s]",GET_CNICK(__U).c_str(),user$login(__U).c_str(),nick.c_str(),cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str());
            }
            if (r==-1) {
                m["~msg~"]=_MSG("nicknopriv");
            }
        }
    }
    string data;

    string orderby="a.nick";
    if (cc->params["sort"]=="login") orderby="a.login";
    if (cc->params["sort"]=="nick") orderby="a.str_nick";
    if (cc->params["sort"]=="who") orderby="5";

    string wh;
    string snick;
    if (cc->params["snick"].size()) {
        snick=cc->params["snick"];
        if (snick.size()>16) snick=snick.substr(0,16);
        string wnick=MESL(str_nick(snick));
        wh="and a.str_nick like '"+wnick+"%' ";
    }
    m["~snick~"]=cc->params["snick"];

    int cnt=atoi(d.dbh->select_1("select count(*) from nicks a where a.banned=1 "+wh).c_str());
    int start=atoi(cc->params["l"].c_str());
    int end=start+100;
    if (end>cnt) end=cnt;
    m["~numb~"]=itostring(start);
    string l;
    for (int i=0;i<=cnt;i+=100) {
        if (i==start) {
            l+="["+itostring(i)+"] ";
        } else {
            l+="<a href=\"?l="+itostring(i)+"&sort="+cc->params["sort"];
            if (wh.size()) l+="&snick="+snick;
            l+="\" class=nick>["+itostring(i)+"]</a> ";
        }
    }
    m["~list~"]=l;
    m["~start~"]=itostring(start);
    m["~end~"]=itostring(end);


    vector< vector<string> > v=d.dbh->exec("select a.id,a.uid,a.nick,a.bby,b.login,b.level from nicks a,user_profiles b where a.banned=1 and b.refid=a.bby  "+wh+"order by "+orderby+" limit "+itostring(start)+",100");

    {
        for (unsigned int i=0;i<v.size();i++) {
            if (v[i].size()!=6) {
                throw cError("select() failed. Size different.");
            }
            data+="<tr><td><b>"+v[i][2]+"</b></td>";		//nick
            unsigned int bby=atoi(v[i][3].c_str());
            data+="<td>"+v[i][4]+"</td>";
            unsigned int ul=cc->sub_level;
            unsigned int bl=atoi(v[i][5].c_str())/sub_levels;
            if (ul==am_sadmin || bby==cc->user_id.container || bl<=ul) {
                data+="<td><input type=button value=\""+_MSG("removeban")+"\" onclick=\"b_remove('"+v[i][1]+"."+v[i][0]+"')\"></td>";
            } else {
                data+="<td></td>";
            }
            data+="</tr>";
        }
    }
    m["~data~"]=data;
    m["~cnt~"]=itostring(cnt);
    cc->html_out=make_pair(m,"admin/nickban/nickban");
}
