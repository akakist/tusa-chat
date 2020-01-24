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
#include "admin.h"

#include "app_def.h"
#include "update_cmd.h"
#include "chat_thread_event.h"
#include "user_set.h"
#include "cs_conn_data.h"
#include "html_out.h"
#include "chat_globals.h"
#ifndef __CLAN


void url_admin_userlist_command(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);
    if (cc->sub_level<am_killer) {
        return;
    }
    DB_id zid;
    {
        if (cc->params["id"]!="")
        {
            zid.container=atoi(cc->params["id"].c_str());
        }
    }
    {
        if (cc->params["nick"]!="")
        {
            string n=cc->params["nick"];
            zid=all_user_nick_2_DB_id(n);
        }

    }
    {
        string msg;
        string ad=itostring(rand())+"&sort="+cc->params["sort"];
        cc->html_out="<link href=\"/css/main.css\" rel=stylesheet type=text/css><body>";
        string left="<script>alert('"+_MSG("usernotfound")+"');document.location='userlist?"+ad+"';</script>";
        if (!zid.container) {
            cc->html_out+=left;
            return;
        }
        string cnick=GET_CNICK(__U);
        string login=user$login(__U);
        unsigned int zlevel;
        {
            PGLR(user_profile,u,user_profiles.find_by_id(zid));
            zlevel=u->level;

        }

        if (cc->sub_level<=zlevel/sub_levels) {
            cc->html_out+="<script>alert('"+_MSG("lowlevel")+"');document.location='userlist?"+ad+"';</script>";
            return;
        }
        string cmd=cc->params["cmd"];


        c_level z_lv=LEVELS(zlevel);
        c_level u_lv=LEVELS(user$level(__U));
        int u_kick_ability=u_lv.kick_ability;
        int z_kick_shield=z_lv.kick_shield;
        if (u_kick_ability>z_kick_shield)
        {
            kick_user(zid,cc->params["msg"]);
        } else {
            cc->html_out+="<script>alert('"+_MSG("noen_kickability")+"');</script>";
            return;
        }

        PTR_getter<chat_user>__ZZ=local_users.get(zid);

        if (__ZZ)
        {
            PGLW(chat_user,z,__ZZ);
            z->erased=true;
        }

        string zcnick,zlogin,zip,zpip;

        time_t zspenttime=-1;
        {
            PGLR(user_set,u,user_sets.find_by_id(zid));
            zcnick=u->last_nick;//GET_CNICK(__Z);
        }
        {
            PGLR(user_profile,u,user_profiles.find_by_id(zid));
            zlogin=u->login;
        }
        if (__ZZ)
        {
            user_pair __Z(__ZZ);
            zspenttime=user$get_spent_time(__Z);
            {
                __ZC_LOCK;
                zip=z->cu_ip;
                if (z->user_type==TYPE_WWW)
                    zpip=z->www_proxy_ip;
            }
        }
        logErr2("User %s (%s) was kicked by %s (%s) %s [%s - %s] {%d}",zcnick.c_str(),zlogin.c_str(),cnick.c_str(),login.c_str(),cc->params["msg"].c_str(),cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str(),zspenttime);
        if (cmd=="kick") {
            cc->html_out+="<script>document.location='userlist?"+ad+"';</script>";
        }
        if (cmd=="bl" && cc->sub_level>am_killer) {
            int r=do_loginban(zid,"",600,cc->user_id,cc->sub_level);
            if (r!=0) {
                cc->html_out+="<script>alert('"+_MSG("userkickedbutlogin")+"'); document.location='userlist?"+ad+"';</script>";
            } else {
                logErr2("%s (%s) banned login %s [%s - %s]",cnick.c_str(),login.c_str(),zlogin.c_str(),cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str());
                cc->html_out+="<script>document.location='userlist?"+ad+"';</script>";
            }
        }
        if (cmd=="bn" && cc->sub_level>am_killer) {
            int r=do_nickban(zcnick,cc->user_id,cc->sub_level);
            if (r!=0 && r!=2) {
                cc->html_out+="<script>alert('"+_MSG("userkickedbutnick")+"'); document.location='userlist?"+ad+"';</script>";
            } else {
                logErr2("%s (%s) banned nick %s (%s) [%s - %s]",cnick.c_str(),login.c_str(),zcnick.c_str(),zlogin.c_str(),cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str());
                cc->html_out+="<script>document.location='userlist?"+ad+"';</script>";
            }
        }
        if (cmd=="bi" || cmd=="bp" && cc->sub_level>am_killer) {
            int r=do_ipban(zip,zpip,600,cc->user_id);
            if (r==1) {
                string sss;
                sss<<"<script>alert('"<<_MSG("ipalreadybanned")<<"'); document.location='userlist?"<<ad<<"';</script>";
                cc->html_out+=sss;
            } else
                if (r!=0) {
                    string sss;
                    sss<<"<script>alert('"<<_MSG("userkickedbutip")<<"'); document.location='userlist?"<<ad<<"';</script>";
                    cc->html_out+=sss;
                } else {
                    logErr2("%s (%s) was banned ip %s-%s [%s - %s]",cnick.c_str(),login.c_str(),zip.c_str(),zpip.c_str(),cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str());
                    cc->html_out+="<script>document.location='userlist?"+ad+"';</script>";
                }
        }
    }
    send_update_g2(user_stat$inc_kick_count,cc->user_id);
}
#endif
