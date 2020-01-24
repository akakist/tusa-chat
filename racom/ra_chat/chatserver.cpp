#include "stdafx.h"
#include <signal.h>
#include <errno.h>
#include "file_set.h"
#include "PTR.h"

#include "chat_def.h"
#include "web_server_data.h"
#include "mysql_extens.h"
#include "user.h"
#include "utils.h"
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
#include "irc_server.h"

#include "irc_server_config.h"
#include "web_connection.h"
#include "tcp_sender.h"
#include "server_config.h"
extern app_server* wwwserver;
extern irc_server *ircserver;
void start_pgate_server_threads();




cMYSQL *dbh=NULL;

m_var<bool> ex(false);

void onterm(int signum);

void kaak1();


void	load_app_configuration();
void load_license_rsa_pub_key();
void load_app_configuration();
void start_update_processor();

extern m_var<string> license_pathname;
void start_chat_processor();
int app_main(int argc,char *argv[])
{
    try{
        printf("%s, build %s\n\n",SERVER_VERSION,__DATE__);
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




                start_date=time(NULL);
                char ss[300];
                tm TM=LOCALTIME(start_date);
                int z=strftime(ss,sizeof(ss)-2,"%a, %d %b %Y %T %Z",&TM);
                start_date_string=ss;

                srand(time(NULL));
        /*        {
                    st_dbh d;
                }*/
        

        /*#ifndef WIN32
                if(argc>1 && (string)argv[1]==(string)"-b"){
                    int ppd=fork();
                    if(ppd!=0){exit(0);}
                }
        #endif*/

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

        try{
    	    load_app_configuration();
            string conf="./conf/CS.conf";
		license_pathname=global_config.server_params["license"];
		logErr2("license file '%s',",license_pathname.get().c_str());
	    
            map<string,string> m=load_m_file(conf);
	    init_senders(conf,"sender_",m);
	    
            logErr2("Starting webserver");
            wwwserver=new app_server();
            wwwserver->start(conf,"www_server_",m);

            logErr2("Starting cassaserver");



            start_chat_processor();
            start_update_processor();


            logErr2("Starting ircd");
            ircserver=new irc_server();
            ircserver->start(conf,"irc_server_",m);

        }STDCATCHS("init_tusa_clan");


        while(1){
            sleep(10);
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
                load_app_configuration();
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
                    wwwserver->kill_threads();

                }
                if(ircserver){
                    ircserver->kill_threads();
                }
                exit(signum);
            }
        }
    }catch(cError e){
    }catch(...){
        logErr2("--Error: unknow error in on_term()");
    }
}


