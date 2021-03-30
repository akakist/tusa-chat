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
#include "oscar_buffer.h"
#include "CH_id.h"
#include "DB_id.h"
#include "chat_msg.h"
#include "chat_thread_event.h"
#include "user_set.h"
#include "cs_conn_data.h"
#include "html_out.h"
#include "chat_globals.h"
void load_app_configuration();
void url_admin_settings(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);
    if (!(user$privileges(__U)&u_is_settings_admin)) return;


    map<string,hstring> m;
    m["~msg~"]="";
    string srt=cc->params["sort"];
    if (srt=="") srt="nick";
    m["~sort~"]=srt;
    string cmd=cc->params["cmd"];

    if (cmd=="sendsysmsgtoall") {	//send system message to all rooms
        string msg=cc->params["smsg"];
        if (msg.size()>1024) msg=msg.substr(0,1024);
        if (!(user$privileges(__U)&u_allow_tags))  msg=remove_tags(msg);
        msg=replace_links(msg);

        vector<CH_id> cids=chat_channels.keys();
        for (unsigned int i=0;i<cids.size();i++) {
            chat_msg_SYS *ms=new chat_msg_SYS;
            ms->channel=cids[i];
            ms->msg=msg;
            send_chat_msg(ms);
        }
        m["~msg~"]=_MSG("sysmsgsent");
    }
    if (cmd=="senddatatoall") {	//send data to all
        string msg=cc->params["datatoall"];
        if (msg.size()>1024) msg=msg.substr(0,1024);

        chat_event_SEND_DATA_TO_WWW_USERS *e=new chat_event_SEND_DATA_TO_WWW_USERS;
        e->msg=msg;
        send_chat_event(e,false);


        m["~msg~"]=_MSG("datasenttoall");
        logErr2("%s (%s) sended data to all '%s' [%s-%s]",GET_CNICK(__U).c_str(),user$login(__U).c_str(),msg.c_str(),cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str());
    }
    if (cmd=="refresh") {		//refresh chat

        chat_event_SEND_DATA_TO_WWW_USERS *e=new chat_event_SEND_DATA_TO_WWW_USERS;
        e->msg="<script>window.top.location='/chat/';</script>";
        send_chat_event(e,false);

        m["~msg~"]=_MSG("chatrefreshed");
        logErr2("%s (%s) refreshed chat. [%s-%s]",GET_CNICK(__U).c_str(),user$login(__U).c_str(),cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str());
    }
    if (cmd=="reload") {		//reload files
        logErr2("%s (%s) reloaded all files. [%s-%s]",GET_CNICK(__U).c_str(),user$login(__U).c_str(),cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str());
        load_app_configuration();
        m["~msg~"]=_MSG("filesreloaded");
    }
    if (cmd=="killsession") {		//kill session
        DB_id id;
        id.container=atoi(cc->params["id"].c_str());
        PTR_getter<chat_user> __ZZ=local_users.get(id);
        if (!__ZZ) {
            m["~msg~"]=_MSG("usernotfound");
        } else {
            user_pair __Z(__ZZ);
            user_destroy(__ZZ);
            m["~msg~"]=_MSG("sessionkilled");
        }
    }
    if (cmd=="senddatatouser") {	//send data to user
        DB_id id;
        id.container=atoi(cc->params["id"].c_str());
        string msg=cc->params["msg"];
        if (msg.size()>1024) msg=msg.substr(0,1024);
        PTR_getter<chat_user> __ZZ =local_users.get(id);
        if (!__ZZ) {
            m["~msg~"]=_MSG("usernotfound");
        } else {
            user_pair __Z(__ZZ);
            string cnick=GET_CNICK(__U);
            string login=user$login(__U);
            {
                logErr2("%s (%s) sended data to user %s (%s) '%s' [%s-%s]",cnick.c_str(),login.c_str(),GET_CNICK(__Z).c_str(),user$login(__Z).c_str(),msg.c_str(),cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str());

                m["~msg~"]=_MSG("datasent");
            }
            data_push_back(__Z.cu,msg);

        }
    }

    vector<PTR_getter<chat_user> > v=local_users.values();

    hstring us;
    for (unsigned int i=0;i<v.size();i++) {
        bool zinchat=false;
        user_pair __Z(v[i]);
        map<string,hstring> q;
        zinchat=inchat$(__Z.cu);
        q["~nick~"]=GET_CNICK(__Z);
        q["~login~"]=user$login(__Z);

        if (zinchat) {
            q["~inchat~"]=_MSG("yes");
        } else {
            q["~inchat~"]="";
        }
        DB_id zid;
        string ip,zip,pip;
        time_t ld;
        zid=user$id(__Z);
        {
            __ZC_LOCK;
            ip=z->cu_ip;
            zip=z->cu_ip;
            if (z->user_type==TYPE_WWW)
                pip=z->www_proxy_ip;
        }
        {
            __ZC_LOCK;
            ld=z->login_date;
        }
        if (pip.size()) {
            ip=pip;
            pip=zip;
        }
        q["~ip~"]=ip;
        if (pip.size()) q["~ip~"]+=" - "+pip;
        q["~id~"]=itostring(zid.container);
        q["~time~"]=itostring(time(NULL)-ld);
        us+=make_pair(q,"admin/settings/settings_user");
    }
    m["~users~"]=us;
    m["~cnt~"]=itostring(v.size());
    cc->html_out=make_pair(m,"admin/settings/settings");
}
