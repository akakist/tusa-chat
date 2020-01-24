#include "stdafx.h"
/*#ifdef _DEBUG
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
#include "mysql_extens.h"
#include "utils.h"
#include <algorithm>
#include "user.h"
#include "message.h"
#include "command_con.h"
#include "web_server_data.h"
#include "file_set.h"
#include "tcp_stats.h"
#include "server_config.h"
#include "command_server.h"
#include "app_def.h"
#include "tcp_sender.h"
#include "web_tools.h"
#include "version.h"
#include "user_credits.h"
#include "chat_def.h"
#include "irc_server_config.h"

#include "chat_config.h"
#include "notes.h"
#include "channels.h"
#include "irc_utils.h"
#include "update_cmd.h"
#include "ignore_vec.h"
#include "contact_vec.h"
#include "chat_globals.h"
#include "chat_thread_event.h"
#include "global_state.h"
#include "copy_file.h"



command_server::~command_server()
{

}
void command_server::start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{
    web_server::start(pn,prefix,m);
    load_config(pn,prefix,m);
    srand(time(NULL));
    SERVERNAME.set(SERVER_VERSION);
//    {
//        create_thread(users_handler,"users_handler");
//    }

}
command_server::command_server()
{
}
void *command_server::new_connection(const PTR_getter<c_socket>&s)
{
    command_connection*a =new command_connection(this,s);LEAKCTL_ADD(a);
    return a;
}









void command_server::load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{

}


time_t command_server::get_socket_inactive_kill_timeout()
{
    return 5;
}
*/