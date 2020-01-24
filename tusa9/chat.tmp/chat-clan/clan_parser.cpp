#include "stdafx.h"
#ifdef _DEBUG
#define New DEBUG_NEW
#endif

#include <signal.h>
#include <errno.h>
#include "file_set.h"
#include "PTR.h"
#include "mutex_inspector.h"
#include "chat_def.h"
#include "web_server_data.h"
#include "PTR.h"
#include "tcp_server_data.h"
#include "app_server.h"
#include "app_def.h"
#include "version.h"
#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif


#include "RTYPES_CORE.h"
#include "RTYPES_CLAN.h"
#include "oscar_buffer.h"
#include "DB_id.h"
#include "html_out.h"
#include "web_connection.h"
#include "clan_con.h"
#include "app_con.h"
#include "user.h"
#include "chat_thread_event.h"
#include "user_stat.h" 
#include "ignore_vec.h"  
#include "contact_vec.h" 
#include "fotos.h" 
#include "irc_server.h"
#include "irc_server_config.h"
#include "DR_types.h"
#include "chat_config.h"
#include "clan_client.h"
#include "user_info.h"
void send_packet_to_cs(bool immed,CLAN_MSG,const out_oscar_buffer & b);
extern M_DEQUE<string> update_commands;
extern unsigned int clan_id;


void unpack_levels(oscar_buffer &b);
void unpack_channels(oscar_buffer &bb);

void start_update_processor();
//void start_chat_processor();
struct parser_req
{
    CLAN_MSG msg;
    string buf;
};
M_DEQUE<parser_req> clan_parser_reqs;
size_t clan_parser_req_size(){return clan_parser_reqs.size();}



string clan_data_request(int reqtype,const DB_id& s)
{ MUTEX_INSPECTOR;
    out_oscar_buffer b;
    b<<s;
    return clan_data_request(reqtype,b);
}

bool load_channels();



extern app_server* wwwserver;
extern irc_server *ircserver;

int fnum=0;

void clan_parser_thread()
{
    while(1)
    {
        try{
            deque<parser_req> dr=clan_parser_reqs.extract_all();
            for(unsigned i=0;i<dr.size();i++)
            {MUTEX_INSPECTOR;
                oscar_buffer in_b(dr[i].buf.data(),dr[i].buf.size());
                {
                    {
                        switch(dr[i].msg)
                        {
                        
                        
                        default: logErr2("invalid msg %d (%s %d)",dr[i].msg,__FL__);
                        }
                    }
                    break;
                }


            }
            {MUTEX_INSPECTORS("SLEEP");
                usleep(20000);
            }
        }
        catch(cError e)
        {
            logErr2("catched %s %d %s",__FL__,e.what());

        }
        catch(...)
        {
            logErr2("catched %s %d",__FL__);
        }
    }

}
//#endif
void clan_client::on_data_event(int cmd,oscar_buffer & in_b)
{
    CLAN_MSG msg=(CLAN_MSG)  cmd;
    switch(msg)
    {
    

    case __TYPE_SEND_CHAT_DATA:
        {MUTEX_INSPECTOR;
            string cmd;
            in_b>>cmd;
            update_commands.push_back(cmd);

        }break;
    case __TYPE_SEND_CHAT_EVENT:
        {MUTEX_INSPECTOR;
            int etype;
            in_b>>etype;
            chat_event *e=NULL;
            switch(etype)
            {
            case chat_event::INVITE					 : e=new chat_event_G_INVITE(in_b);LEAKCTL_ADD(e);break;
            case chat_event::CHMODE                  : e=new chat_event_G_CHMODE(in_b);LEAKCTL_ADD(e);break;
            case chat_event::CHVOICE                 : e=new chat_event_G_CHVOICE(in_b);LEAKCTL_ADD(e);break;
            case chat_event::SEND_MESSAGE            : e=new chat_event_G_SEND_MESSAGE(in_b);LEAKCTL_ADD(e);break;
            case chat_event::SET_USER_STATE          : e=new chat_event_G_SET_USER_STATE(in_b);LEAKCTL_ADD(e);break;
            case chat_event::CHTOPIC                 : e=new chat_event_G_CHTOPIC(in_b);LEAKCTL_ADD(e);break;
//            case chat_event::__IGNORE                : e=new chat_event_G_IGNORE(in_b);LEAKCTL_ADD(e);break;
            //case chat_event::USER_PING               : e=new chat_event_G_USER_PING(in_b);LEAKCTL_ADD(e);break;
			default: logErr2("----Errrorr::::              INVALID event type %d %s %d",etype,__FILE__,__LINE__);


            }
            if(e)
            {MUTEX_INSPECTOR;
                __chat_events.push_back(e);
            }
        }
        break;

    case __TYPE_SET_DATA:
        {MUTEX_INSPECTOR;
            int dtype;
            in_b>>dtype;
            DB_id uid;
            switch(dtype)
            {
            case TSD_user_profile:
                in_b>>uid;
                user_profiles.init(CONTAINER(uid),in_b);break;
            case TSD_user_set:
                in_b>>uid;
                user_sets.init(CONTAINER(uid),in_b);break;
            case TSD_user_stat:
                in_b>>uid;
                user_stats.init(CONTAINER(uid),in_b);break;
            case TSD_nick_vec:
                in_b>>uid;
                nick_vecs.init(CONTAINER(uid),in_b);
                user_register_all_nicks(uid);

                break;
            case TSD_ignore_vec:
                in_b>>uid;
                ignore_vecs.init(CONTAINER(uid),in_b);break;
            case TSD_user_info:
                in_b>>uid;
                user_infos.init(CONTAINER(uid),in_b);break;
            case TSD_contact_vec:
                in_b>>uid;
                contact_vecs.init(CONTAINER(uid),in_b);break;
            case TSD_user_fotos:
                in_b>>uid;
                users_fotos.init(CONTAINER(uid),in_b);break;
            
            case TSD_levels:
		logErr2("levels in");
                unpack_levels(in_b); break;
            
            
            case TSD_channels:
		logErr2("channels in");
                unpack_channels(in_b); 
				break;
            case TSD_chat_config2:
		logErr2("chat_config2 in");
                chat_config2.unpack(in_b); break;

            default:
                logErr2("undefined TYPE_SET_DATA type %d",dtype);
            }
        }break;

    case __TYPE_SEND_STUFF_DATA:
        {MUTEX_INSPECTOR;
            string s;
            in_b>>s;
            chat_event_L_EVT_chat_thread_stuff_restore *e=new chat_event_L_EVT_chat_thread_stuff_restore(s);LEAKCTL_ADD(e);
            send_chat_event_push_back(e,false);
        }break;
    case __TYPE_START_SERVICE:
        {MUTEX_INSPECTOR;
            string conf="./conf/CLAN.conf";

            map<string,string>m=load_m_file(conf);
	    if(!wwwserver)
	    {MUTEX_INSPECTOR;
    		logErr2("Starting webserver");
                wwwserver=new app_server();LEAKCTL_ADD(wwwserver);
	        wwwserver->start(conf,"www_server_",m);
	    }

            logErr2("Starting ircd");
	    if(!ircserver)
	    {MUTEX_INSPECTOR;
		{MUTEX_INSPECTOR;
        	ircserver=new irc_server();LEAKCTL_ADD(ircserver);
		}
		{MUTEX_INSPECTOR;
        	ircserver->start(conf,"irc_server_",m);
		}
	    }
	    {
		{
		    MUTEX_INSPECTOR;
        	    //start_chat_processor();
				chat_processor * processor=new chat_processor;
				processor->start(conf,"chat_processor_",m);

		}
		{
		MUTEX_INSPECTOR;
		
        	start_update_processor();
		}
	    }
        }
        break;


    default:
        logErr2("clan_parser MSG undefined 0x%X (%s %d),",msg,__FL__);
    }

}
