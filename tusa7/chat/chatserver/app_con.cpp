#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include <list>
#include "_mutex.h"
#include <stdio.h>
#include "web_server.h"
#include "errs.h"
#include <signal.h>
#include "st_stuff.h"
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include "_mutex.h"
#include <time.h>
#include "mysql_extens.h"
#include "utils.h"
#include <algorithm>
#include "user.h"
#include "message.h"
#include "app_con.h"
#include "web_server_data.h"
#include "file_set.h"
#include "register.h"
#include "tcp_stats.h"
#include "server_config.h"
#include "app_server.h"
#include "app_def.h"
#include "chat_globals.h"
#include "web_tools.h"
#include "chat_def.h"
#include "user_set.h"
void app_connection::init_temp_vars(const PTR_getter<chat_user>  &__UU)
{
    if (!__UU)
    {
        return;
    }

    user_pair __U(__UU);

    {
        __UC_LOCK;
        user_unregistered=u->www_unregistered;
    }
    user_id=user$id(__U);
    sub_level=user$level(__U)/sub_levels;

}



void  app_connection::redirect(const string &url)
{

    string r;
    if (browser=="nn" && url.find("http://",0)==-1) {
        r="http://";
        r+=params["HOST"];
        r+=url;
        if (url.find("?",0)!=-1) {
            r+="&";
        } else {
            r+="?";
        }
        r+="rr=";
        r+=itostring(rand());
    } else {
        r=url;
    }
    http_code=302;
    http_header_out["Location"]=r;
    return;
}
app_connection::app_connection(app_server *cs,const PTR_getter<c_socket>&s
#ifdef __MCASSA
                               ,bool _is_cassa
#endif
                              ): web_connection(cs,s)
#ifdef __MCASSA
        ,is_cassa(_is_cassa)
#endif
{
    handle_max_recv_limit=true;
    parse_url=true;
    server=cs;
    error_404_html=RVfiles("404");
    user_id.container=0;
    sub_level=0;
#ifdef __MCASSA
    is_cassa=_is_cassa;
#endif

}


void app_connection::postinit_rvmap(map<string,string> &m)
{
    string s = itostring(rand());
    m["~random~"] = s;
    map<string,string> mm=server_ref->get_replacements();
    for (map<string,string>::iterator i=mm.begin();i!=mm.end();i++) {
        m[i->first]=global_config.files_get(i->second);
    }
    if (user_id.container!=0/*need_add_menu2*/) {
        m["~menu~"]+=global_config.files_get("menu3");
    }
}

