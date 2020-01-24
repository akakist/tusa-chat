
#include "stdafx.h"
#ifdef _DEBUG
#define New DEBUG_NEW
#endif

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
#include "tcp_sender.h"
#include "web_tools.h"
#include "DR_types.h"
#include "CH_id.h"
#include "user_status.h"
#include "user_nick.h"
#include "user_state.h"
#include "user.h"
#include "utils.h"
void irc_iterate();
map<string,string> calc_statistic();
extern M_MAP<string,string> chat_stat;
void local_users_iterate();




unsigned int clan_id=0;

void *app_server::PTHR_users_handler(void *pr)
{
	app_server *p=(app_server *) pr;
    string ss=p->server_name()+" chat users handler";
    log_start_thread(ss);

    while (1) {
        try {
            ((app_server *) pr)->users_handler(NULL);
            logErr2("--Error: run_users_handler: handler - exited. ???");
        }
        catch(...) {
            logErr2("--Error: run_users_handler: unknow error! %s %d",__FILE__,__LINE__);
        }
    }
    return NULL;
}
void clan_parser_thread();

void *app_server::PTHR_clan_parser(void *pr)
{
    string ss=/*((tcp_server *) pr)->server_name()+*/"clan parser";
    log_start_thread(ss);

    while (1) {
        try {
	    clan_parser_thread();
            logErr2("--Error: clan parser - exited. ???");
        }
        catch(...) {
            logErr2("--Error: rclan parser! %s %d",__FILE__,__LINE__);
        }
    }
    return NULL;
}


void app_server::start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{
        web_server::start(pn,prefix,m);
    try {
		create_thread(PTHR_users_handler,"users_handler");
		g_create_thread(PTHR_clan_parser,NULL,"PTHR_clan_parser");

        
        


        logErr2("start done");
    }
    catch(cError e) {
        logErr2("--Error: %s",e.error_string.c_str());
        return ;
    }
    catch(...) {
        logErr2("unknow Error");
        return ;
    }
}
app_server::app_server()
{
    srand(time(NULL));
}
app_server::~app_server()
{
}
void *app_server::new_connection(const PTR_getter<c_socket>&s)
{
    return new app_connection(this,s);
}

bool conf_loaded=false;
bool load_channels();

void update_db_cache();


void app_server::on_inspector_iterate()
{
	try{
		{
			bool logged=false;

			{
				MUTEX_INSPECTORS("SLEEP");
				sleep(1);
			}
		}
	}catch(cError e)
	{
		logErr2("catched %s %s %d",e.what(),__FL__);

	}
	catch(...)
	{
		logErr2("catched %s %d",__FL__);
	}

}




void s_cont_check();

void app_server::users_handler(void *)
{
    while(1)
    {
        try{

            unsigned int n=61;
            unsigned int cs=600;
            unsigned int avg_cnt=0;

            struct tm New_tm;
            int last_min;
            New_tm=LOCALTIME(time(NULL));
            last_min=New_tm.tm_min;

            bool started=false;
            while (1){
                {MUTEX_INSPECTORS("SLEEP");
                    sleep(3);
                }
                irc_iterate();
				s_cont_check();
				




                try{MUTEX_INSPECTOR;


                    chat_channels_backup_messages();

                    if(cs>=600){	//calc statistic & save messages
                        MUTEX_INSPECTOR;

                        cs=0;
                        map<string,string> m;
                        m=calc_statistic();
                        chat_stat.assign(m);
        		update_db_cache();
			
                    }



                    local_users_iterate();

                    n++;
                    cs++;
                }catch(cError e){
                    logErr2("--Error in users_handler: %s",e.what());
                }catch(...){
                    logErr2("--Error in users_handler: UNKNOW!!!");
                }
            }
	    {MUTEX_INSPECTORS("SLEEP");
            sleep(100);
	    }
        }catch(cError e)
        {
            logErr2("catched %s %s %d",e.what(),__FL__);

        }
        catch(...)
        {
            logErr2("catched %s %d",__FL__);
        }
    }

}

time_t app_server::get_socket_inactive_kill_timeout()
{
	return 5;
}
