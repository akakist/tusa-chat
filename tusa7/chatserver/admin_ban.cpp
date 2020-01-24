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
#include "message.h"
#include "chat_def.h"
#include "register.h"

#include <algorithm>
#include "web_server_data.h"
#include "file_set.h"
#include "copy_file.h"

#include "channels.h"
#include "server_config.h"
#include "app_def.h"
#include "admin.h"
#include "cs_conn_data.h"
#include "html_out.h"
#include "chat_globals.h"


void url_admin_ipban(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
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
        m["~sort~"]="ip";
    }
    string cmd=cc->params["cmd"];
    st_dbh d;
    if (cmd=="remove") {
        vector<string> v=d.dbh->select_1_rowQ((QUERY)"select banned_ip.uid,user_profiles.level from banned_ip,user_profiles where banned_ip.id='?' and user_profiles.refid=banned_ip.uid"<<cc->params["id"]);
        if (v.size()!=2) {
            m["~msg~"]=_MSG("rec_not_found");
        } else {
            unsigned int ul=cc->sub_level;
            unsigned int bl=atoi(v[1].c_str())/sub_levels;
            DB_id id;
            id.container=atoi(v[0].c_str());
            if (id==cc->user_id || ul==am_sadmin || bl<=ul) {
                vector<string> ip=d.dbh->select_1_rowQ((QUERY)"select ip,proxy from banned_ip where id=?"<<cc->params["id"]);
                if (ip.size()==2) {
                    d.dbh->real_queryQ((QUERY)"delete from banned_ip where id='?'"<<cc->params["id"]);
                    m["~msg~"]=_MSG("ipunbanned");
                    logErr2("%s (%s) unbanned address %s-%s [%s - %s]",GET_CNICK(__U).c_str(),user$login(__U).c_str(),ip[0].c_str(),ip[1].c_str(),cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str());
                }
            } else {
                m["~msg~"]=_MSG("ipnopriv");
            }
        }
    }
    if (cmd=="add") {
        if (cc->sub_level<am_spy) {
            m["~msg~"]=_MSG("iplowlevel");
        } else {
            string ip=cc->params["addip"];
            string pip=cc->params["addproxy"];
            if (pip.size()) {
                ip=pip;
                pip=cc->params["addip"];
            }
            int r=do_ipban(ip,pip,atoi(cc->params["how"].c_str()),cc->user_id);
            if (r!=0) {
                m["~msg~"]=_MSG("ipalreadybanned");
            } else {
                m["~msg~"]=_MSG("ipbanned");
                logErr2("%s (%s) banned address %s-%s [%s - %s]",GET_CNICK(__U).c_str(),user$login(__U).c_str(),ip.c_str(),pip.c_str(),cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str());
            }
        }
    }
    string data;
//    vector<string>vout;
    string orderby="ip";
    if (cc->params["sort"]=="ip") orderby="proxy";
    if (cc->params["sort"]=="proxy") orderby="ip";
    if (cc->params["sort"]=="date") orderby="time_ban";
    if (cc->params["sort"]=="how") orderby="time_cnt";
    if (cc->params["sort"]=="rdate") orderby="time_free";

    vector< vector<string> > v=d.dbh->exec(
                                   "select banned_ip.id,banned_ip.ip,banned_ip.proxy,"
                                   "UNIX_TIMESTAMP(banned_ip.time_ban),"
                                   "UNIX_TIMESTAMP(banned_ip.time_free),"
                                   "banned_ip.time_cnt,banned_ip.uid,"
                                   "user_profiles.level,user_profiles.login from banned_ip,user_profiles where user_profiles.refid=banned_ip.uid order by "+orderby
                               );
    for (unsigned int i=0;i<v.size();i++) {
        if (v[i].size()!=9) {
            throw cError("select() failed. Size different.");
        }
        DB_id id;
        id.container=atoi(v[i][7].c_str());
        string ip=v[i][1];
        string pip=v[i][2];
        if (pip.size()) {
            ip=v[i][2];
            pip=v[i][1];
        }
        if (cc->sub_level<8) {
            ip=ip.substr(0,ip.find(".",0))+".???.???.???";
            if (pip.size()) pip=pip.substr(0,pip.find(".",0))+".???.???.???";
        }
//	string row;
        data+="<tr><td>";
        if (cc->sub_level>=am_spy) {
            data+="<a class=nick href=\"#\" onclick=\"return ip_inf('"+ip+"')\"><b>"+ip+"</b></a>";
        } else {
            data+="<b>"+ip+"</b>";		//ip
        }
        data+="</td><td>";
        if (cc->sub_level>=am_spy && pip!="") {
            data+="<a class=nick href=\"#\" onclick=\"return ip_inf('"+pip+"')\">"+pip+"</a></td>";
        } else {
            data+=pip+"</td>";		//proxy
        }
        data+="<td>"+datetime2rus(atoi(v[i][3].c_str()))+"</td>";		//time ban
        data+="<td>"+v[i][5]+"</td>";		//time cnt
        if (atoi(v[i][4].c_str())==0) {
            data+="<td></td>";
        } else {
            data+="<td>"+datetime2rus(atoi(v[i][4].c_str()))+"</td>";		//time free
        }
        unsigned int ul=cc->sub_level;
        unsigned int bl=atoi(v[i][7].c_str())/sub_levels;
        data+="<td>"+v[i][8]+"</td>";		//banned by
        if (cc->user_id==id || ul==am_sadmin || bl<=ul) {
            data+="<td><input type=button value=\""+_MSG("removeban")+"\" onclick=\"b_remove('"+v[i][0]+"')\"></td>";
        } else {
            data+="<td></td>";
        }
        data+="</tr>";
    }
    m["~data~"]=data;
    m["~cnt~"]=itostring(v.size());
    cc->html_out=make_pair(m,"admin/ipban/ipban");
}



void url_admin_loginban(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
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
        m["~sort~"]="login";
    }
    string cmd=cc->params["cmd"];
    st_dbh d;
    if (cmd=="remove" && cc->sub_level>=am_guard) {
        DB_id uid;
        uid.container=atoi(cc->params["id"].c_str());
        DB_id adm_uid;
        vector<string> v=d.dbh->select_1_columnQ((QUERY)"select adm_uid from banned_login where uid=?"<<uid.container);
        if (v.size()==1) adm_uid.container=atoi(v[0].c_str());
        unsigned int adm_level;
        string zlogin;
        {
            PGLR(user_profile,u,user_profiles.find_by_id(adm_uid));
            adm_level=u->level;
        }
        {
            PGLR(user_profile,u,user_profiles.find_by_id(uid));
            zlogin=u->login;
        }

        if (adm_level/sub_levels>=cc->sub_level && adm_uid!=cc->user_id)
        {
            m["~msg~"]=_MSG("loginnopriv");
        }
        else
        {
            d.dbh->real_queryQ((QUERY)"delete from banned_login where uid=?"<<uid.container);
            m["~msg~"]=_MSG("loginunbanned");
            logErr2("%s (%s) unbanned login %s [%s - %s]",GET_CNICK(__U).c_str(),user$login(__U).c_str(),zlogin.c_str(),cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str());
        }


    }
    if (cmd=="add") {
        string login;
        DB_id uid;
        bool found=false;
        if (cc->params["addnick"].size()) {
            login=cc->params["addnick"];
            vector<string> z=d.dbh->select_1_rowQ((QUERY)"select uid from nicks where str_nick='?'"<<str_nick(login));
            if (z.size()==0) {
                m["~msg~"]=_MSG("nicknotfound");

            } else {
                uid.container=atoi(z[0].c_str());
                found=true;
            }
        }
        if (cc->params["addlogin"].size()) {
            login=cc->params["addlogin"];
            vector<string> z=d.dbh->select_1_rowQ((QUERY)"select refid from user_profiles where login='?'"<<cc->params["addlogin"]);
            if (z.size()==0) {
                m["~msg~"]=_MSG("loginnotfound");
            }
            else
            {
                uid.container=atoi(z[0].c_str());
                found=true;
            }
        }
        if (found) {
            int r=do_loginban(uid,cc->params["descr"],atoi(cc->params["how"].c_str()),cc->user_id,cc->sub_level);
            if (r==-1) {
                m["~msg~"]=_MSG("loginnopriv");
            }
            if (r==0) {
                m["~msg~"]=_MSG("loginbanned");
                logErr2("%s (%s) banned login %s [%s - %s]",GET_CNICK(__U).c_str(),user$login(__U).c_str(),login.c_str(),cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str());
            }
            if (r==1) {
                m["~msg~"]=_MSG("loginalreadybanned");
            }
        }
    }
    string sort=cc->params["sort"];
    map<string,string>mout;

    vector< vector<string> > v=d.dbh->exec("select uid,adm_uid,UNIX_TIMESTAMP(time_ban),descr,time_cnt from banned_login");
    for (unsigned int i=0;i<v.size();i++) {
        if (v[i].size()!=5) {
            throw cError("select() failed. Size different.");
        }
        DB_id zid;
        zid.container=atoi(v[i][0].c_str());
        DB_id adm_uid;
        adm_uid.container=atoi(v[i][1].c_str());
        time_t time_ban=atoi(v[i][2].c_str());
        string descr=v[i][3];
        string time_cnt=v[i][4];
        string zlogin,adm_login;
        unsigned int zlevel,adm_level;
        string mkey;
        {
            PGLR(user_profile,u,user_profiles.find_by_id(zid));
            zlogin=u->login;
            zlevel=u->level;
        }
        {
            PGLR(user_profile,u,user_profiles.find_by_id(adm_uid));
            adm_login=u->login;
            adm_level=u->level;
        }
        string znick,adm_nick;
        {
            PGLR(user_set,u,user_sets.find_by_id(zid));
            znick=u->last_nick;

        }
        {
            PGLR(user_set,u,user_sets.find_by_id(adm_uid));
            adm_nick=u->last_nick;

        }
        string row;
        row+="<tr><td><b>";		//login
        if (cc->sub_level<am_admin) {
            row+=znick +" ("+zlogin+")";
        } else {
            row+="<a class=nick href=\"#\" onclick=\"return login_inf('"+zlogin+"')\">"+znick +" ("+zlogin+")"+"</a>";
        }
        row+="</b></td>";
        mkey=znick +" "+zlogin;

        row+="<td>"+datetime2rus(time_ban)+"</td>";		//time ban
        if (sort=="date")mkey=itostring(time_ban);

        row+="<td>"+time_cnt+"</td>";		//time cnt
        if (sort=="how")mkey=time_cnt+itostring(i);

        unsigned int ul=cc->sub_level;
        row+="<td>"+adm_nick +" ("+adm_login+")"+"</td>";		//banned by
        if (sort=="who")mkey=adm_nick +" ("+adm_login+")"+itostring(i);

        row+="<td>"+descr+"</td>";
        if (cc->user_id==adm_uid || ul==am_sadmin || adm_level/sub_levels<=ul) {
            row+="<td><input type=button value=\""+_MSG("removeban")+"\" onclick=\"b_remove('"+itostring(zid.container)+"')\"></td>";
        } else {
            row+="<td></td>";
        }
        row+="</tr>";
        mout[mkey]=row;
    }
    string data;
    for (typeof(mout.begin())i=mout.begin();i!=mout.end();i++)
    {
        data+=i->second+"\n";
    }
    m["~data~"]=data;
    m["~cnt~"]=itostring(v.size());
    cc->html_out=make_pair(m,"admin/loginban/loginban");
}


