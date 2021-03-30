#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include "map"
#include "_mutex.h"
#include <list>
#include <time.h>
#include <errno.h>
#include <map>
#include "mysql_extens.h"
#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include "web_server.h"
#include "message.h"

#include <sys/types.h>
#include <sys/stat.h>
#include "chat_def.h"
#include "_mutex.h"
#include <stdio.h>
#include "errs.h"
#include "utils.h"
#include "M_MAP.h"
#include "file_set.h"
#include "web_tools.h"
#include "web_server_data.h"
#include "web_server.h"
#include "chat_funny.h"
#include "channels.h"
#include "levels.h"
#include "irc_server_config.h"
#include "db_config.h"

#include "chat_config.h"
#include "server_config.h"
void load_app_configuration();
M_MAP<string,string> chat_stat;


params_map levels_conf;
M_MAP<string,string> chat_MSG;


vector<string> load_l_file(const string &fn)
{
    string body;
    int r=load_1_file(body,fn);
    if (r==-1)
    {
        logErr2("--Error: Failed to read file %s (%s)", fn.c_str(), strerror(errno));
        vector<string> v;
        return v;

    }
    return splitTOK("\r\n",body.c_str());
}

void load_app_configuration()
{


    global_config.scan_opts(global_config.server_params,global_config.__cmd_args);
    string pn;


    {
        if (global_config.server_params.exists("server_config"))
            pn=global_config.server_params["server_config"];
        else
            pn="./conf/server.conf";
    }
    global_config.load_config(pn,true);
    map<string,string> m=load_m_file(pn);
    db_config.load_config(get_cfg_str(m,"db_config",pn, "./conf/db.conf"));
    irc_server_config.load_config(get_cfg_str(m,"irc_server_config",pn, "./conf/irc_server.conf"));
    chat_config.load_config(get_cfg_str(m,"chat_config",pn, "./conf/chat.conf"));
    chat_config2.load_config(get_cfg_str(m,"chat2_config",pn, "./conf/chat2.conf"));
}

bool load_messages()
{
    logErr("Loading messages...");
    params_map ms;
    string fn="./conf/messages.conf";
    ms.read(fn.c_str());
    map<string,string> m=ms.get_container();
    for (map<string,string>::iterator j=m.begin();j!=m.end();j++) {
        chat_MSG.set(j->first,j->second);
    }
    return true;
}

string _MSG(const string &n)
{
    if (!chat_MSG.is_key_exists(n)) {
        logErr2("---Error: _MSG chat_MSG not exists with  key='%s' %s",n.c_str(),"");
        return "";
    }
    return chat_MSG.get(n);
}


static unsigned int __session_gen(rand());
static _mutex m__session_gen("");

S_id next_session_id()
{
    MUTEX_LOCK kall(m__session_gen);
    while (1)
    {
        ++__session_gen;
        if (__session_gen!=0)
        {
            S_id s;
            s.container=__session_gen;
            return s;
        }
    }
    S_id ss;
    return ss;
}


