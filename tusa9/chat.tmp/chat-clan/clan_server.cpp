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
#include "user.h"
#include "irc_server.h"
#include "tcp_sender.h"
#include "irc_server_config.h"
//#include "bos_client.h"

#include "str_lib.h"
#include "server_config.h"
#include "chat_config.h"
#ifdef WIN32
#include <conio.h>
#endif
#include "clan_client.h"
#include "db_config2.h"
#include "RTYPES_CLAN.h"
app_server* wwwserver;
irc_server *ircserver;

//void start_chat_processor();

void clan_parser(int fam,int subt,oscar_buffer & in_b);

int start_connect(void);



m_var<bool> ex(false);
extern m_var<string> __APPNAME;
void onterm(int signum);

void kaak1();


void load_license_rsa_pub_key();
void run_senders();

clan_client *clc=NULL;
void send_packet_to_cs(bool immed, CLAN_MSG msg, out_oscar_buffer const& b)
{
    if(clc)clc->send_packet(immed,msg,b.as_string());
}
string clan_data_request(int reqtype)
{
	MUTEX_INSPECTOR;
    if(clc)
    {
	string in;
	bool res=clc->send_request(reqtype,in,"",30);
	if(!res)throw cError("clan_data_request failed #"+itostring(reqtype)+_DMI());
	return in;
    }
    return "";
}
string clan_data_request(int reqtype,const out_oscar_buffer &b)
{MUTEX_INSPECTOR;
    if(clc)
    {
	string in;
	bool res=clc->send_request(reqtype,in,b.as_string(),30);
	if(!res)throw cError("clan_data_request failed #"+itostring(reqtype)+_DMI());
	return in;
    }
    return "";
}

void clear_containers();
void load_app_configuration();
void load_app_configuration()
{MUTEX_INSPECTOR;
	clear_containers();
	
    global_config.scan_opts(global_config.server_params,global_config.__cmd_args);
    string pn;


    {
        if(global_config.server_params.exists("server_config"))
            pn=global_config.server_params["server_config"];
        else
            pn="./conf/server.conf";
    }
        global_config.load_config(pn,true);
	map<string,string> m=load_m_file(pn);
        irc_server_config.load_config(get_cfg_str(m,"irc_server_config",pn, "./conf/irc_server.conf"));
	{

	}
		db_config2.load_config(get_cfg_str(m,"db_config",pn, "./conf/db2.conf"));
        chat_config.load_config(get_cfg_str(m,"chat_config",pn, "./conf/chat.conf"));
}


int app_main(int argc,char *argv[])
{
    string an=argv[0];
//    logErr2("%s\n",an.c_str());
    vector<string> v;
#ifdef WIN32
	v=splitTOK("\\",an);
#else
	v=splitTOK("/",an);
#endif
    if(v.size())
    {
	 __APPNAME=v[v.size()-1];
    }
    try{
        printf("%s (CLAN SERVER), build %s\n\n",SERVER_VERSION,__DATE__);
#ifndef WIN32

        if(argc>1){
            if(strcmp(argv[1],"-d")==0){
                printf("Continuing as daemon\n");
                if(fork()) exit(1);
            }
            if(strcmp(argv[1],"--help")==0){
                printf("\t -d - to run as deamon\n");
                exit(1);
            }
        }
#endif


        load_app_configuration();


        srand(time(NULL));
#ifndef WIN32
        if(argc>1 && (string)argv[1]==(string)"-b"){
            int ppd=fork();
            if(ppd!=0){exit(0);}
        }
#endif

#ifndef WIN32
        signal(SIGPIPE,SIG_IGN);
        signal(SIGABRT,onterm);
        signal(SIGTERM,onterm);
        signal(SIGINT,onterm);
        signal(SIGSEGV,onterm);
        signal(SIGFPE,onterm);
        signal(SIGQUIT,onterm);
        signal(SIGILL,onterm);
        signal(SIGBUS,onterm);
        signal(SIGHUP,onterm);

        signal(10,onterm);
#endif		

	string g_conf_pn="./conf/CLAN.conf";
	map<string,string> g_conf=load_m_file(g_conf_pn);
	init_senders(g_conf_pn,"sender_",g_conf);


	clc=new clan_client(); LEAKCTL_ADD(clc);
	clc->start(g_conf_pn,"bos_client_",g_conf); 
	//start_chat_processor();

	map<string,string> mm;
	mm["login"]=clc->auth_login;
	mm["pass"]=clc->auth_password;
	mm["client_type"]="2";
	mm["SV"]=SERVER_VERSION_INT;

	clc->do_auth(mm);
        while(1){MUTEX_INSPECTORS("SLEEP");
#ifdef WIN32	
			int c=_getch();
			//if(c==VK_ESCAPE)
			return 0;
			//	else continue;
#else
			sleep(1);			
#endif			
        }

    }catch(cError e){
        logErr2("--Error in start_main() - %s",e.error_string.c_str());
    }catch(...){
        logErr2("--Error in start_main() - unknow error!");
    }
    return 0;
}

void print_term(int signum)
{
	string out;
#ifdef MUTEX_INSPECTOR_DBUG
    out+=dump_mutex_inspectors();
#endif			
    string fn;
    if(signum!=10){
        fn=(string)"TERM."+itostring(time(NULL));
    }else{
        fn=(string)"USERTERM."+itostring(time(NULL));
    }
    if(out.size())
    {
        out="Received on SIGNAL "+itostring(signum)+"\n"+out;

        FILE *f=fopen(fn.c_str(),"wb");
        if(f){
            fprintf(f,"%s",out.c_str());
            fclose(f);
        }
    }
    logErr2("%s",out.c_str());
}

void onterm(int signum)
{
    int n=rand();

    try{
        if(!ex){
            string out;
            if(signum==1&&wwwserver){
                ex=true;
                print_term(signum);
                sleep(10);
                ex=false;
                return;

            }
			
            if(signum!=10 && signum!=1){
                ex=true;

                logErr2("Terminating on SIGNAL %d",signum);
            }
            print_term(signum);

            if(signum!=10){
		if(wwwserver){
		    LEAKCTL_REMOVE(wwwserver);delete wwwserver;
		    wwwserver=NULL;
		 }
		if(ircserver){
		 LEAKCTL_REMOVE(ircserver);delete ircserver;
		    ircserver=NULL;
		 }
                exit(signum);
            }
        }
    }catch(cError e){
	logErr2("catched %s %d",__FILE__,__LINE__);
    }catch(...){
        logErr2("--Error: unknow error in on_term()");
    }
}
