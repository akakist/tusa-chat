
#include "stdafx.h"
#include <list>
#include "_mutex.h"
#include "mutex_inspector.h"
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
#include <algorithm>
#include "app_con.h"
#include "web_server_data.h"
#include "file_set.h"
#include "tcp_stats.h"
#include "server_config.h"
#include "app_server.h"
#include "app_def.h"
#include "web_tools.h"
#include "DB_id.h"
#include "user.h"
#include "chat_def.h"

void  app_connection::redirect(const string &url)
{
	//string r;
	/*if(browser=="nn" && url.find("http://",0)==-1){
	r="http://";
	r+=headers["HOST"];
	r+=url;
	if(url.find("?",0)!=-1){
	r+="&";
	}else{
	r+="?";
	}
	r+="rr=";
	r+=itostring(rand());
	}else{
	r=url;
	}*/
	http_code=302;
	http_header_out["Location"]=url;
	return;
}
app_connection::app_connection(app_server *cs,const PTR_getter<c_socket>&s): web_connection(cs,s)
{
    handle_max_recv_limit=true;
    //parse_url=true;
    server=cs;
    //error_404_html=RVfiles("404");
    CONTAINER(__user_id)=0;
    user_unregistered=true;
    sub_level=0;

}
app_connection::app_connection(const app_connection* s): web_connection(s),server(s->server),__user_id(s->__user_id)
{
    
}
void app_connection::postinit_rvmap(map<string,string> &m)
{
    string s = itostring(rand());
    m["~random~"] = s;
    map<string,string> mm=server->get_replacements();
    for(map<string,string>::const_iterator i=mm.begin();i!=mm.end();i++){
        m[i->first]=global_config.files_get(i->second);
    }
    if(CONTAINER(__user_id)!=0){
        m["~menu~"]+=global_config.files_get("menu3");
    }
}

void app_connection::init_temp_vars(const PTR_getter<chat_user>  &__UU)
{
	MUTEX_INSPECTOR;
	if(!__UU)
	{
		return;
	}

	user_pair __U(__UU);

	{
		__UC_LOCK;
		user_unregistered=u->www_unregistered;
	}
	__user_id=user$id(__UU);
	sub_level=user$level(__U)/sub_levels;

}

string app_connection::redirect()
{
	MUTEX_INSPECTOR;
	return "<html><script>window.top.location='/relogin';</script>";
}
