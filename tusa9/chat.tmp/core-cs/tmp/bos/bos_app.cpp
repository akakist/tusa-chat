#include "stdafx.h"
#include <signal.h>
#include <errno.h>
#include "file_set.h"
#include "PTR.h"
#include "PTR.h"
#include "tcp_server_data.h"
#include "bos_server.h"
#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include "version.h"

#include "str_lib.h"
#include "server_config.h"

#include "copy_file.h"
//#include "tcp_sender.h"
#include "globals.h"
#include "serviceTimer.h"
#ifdef DEBUG
#pragma comment(lib, "lib_win32d.lib")
#else
#pragma comment(lib, "lib_win32r.lib")
#endif

bos_server* pserver=NULL;
m_var<bool> ex(false);

void onterm(int signum);
string thread_info_txt();

//extern m_var<string> __APPNAME;
m_var<string> __PORT;
const char* __root_cfg="./conf/BOS.conf";



void load_bos_server_config()
{
    MUTEX_INSPECTOR;
    printf("Loading config\n");
    string pn=__root_cfg;
    logErr2("using root config '%s'",pn.c_str());
//    global_config.load_config(pn,false);
    map<string,string> m=load_m_file(pn);
    logErr2("config done");
}
int app_main(int argc,char *argv[])
{

    string an=argv[0];
    vector<string> v=splitTOK("/",an);
    if (v.size())
    {
		globals::g_AppName=strdup(v[v.size()-1].c_str());
        //__APPNAME=v[v.size()-1];
    }


    printf("BOS %s, build %%d.%d.%d\n %s -d to run as daemon\n\n",__version[0],__version[1],__version[2],__DATE__,argv[0]);
    {
        vector<string> v=splitTOK("/",argv[0]);
        if (v.size()!=2)
        {
            printf("Invalid executable name must be like 'BOS.2003'\n");
            exit(1);
        }
        if (argc==2)
        {
            __root_cfg=argv[1];
        }
        string bname=v[v.size()-1];
        vector<string>vv=splitTOK(".",bname);
        if (vv.size()!=2)
        {
            printf("Invalid executable name must be like 'BOS.2003'\n");
            exit(1);
        }
        if (atoi(vv[1])==0)
        {
            printf("Invalid executable name must be like 'BOS.2003'\n");
            exit(1);
        }
        __PORT=vv[1];
    }


    if (argc>1){
        if (strcmp(argv[1],"-d")==0){
            printf("Continuing as daemon\n");
#ifndef WIN32
            if (fork()) exit(1);
#endif
        }
        if (strcmp(argv[1],"--help")==0){
            printf("\t -d - to run as deamon\n");
            exit(1);
        }
    }



    srand(time(NULL));

#ifndef WIN32
    if (argc>1 && (string)argv[1]==(string)"-b"){
        int ppd=fork();
        if (ppd!=0){exit(0);}
    }
#endif
    try{
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
        signal(SIGUSR1,onterm);
        signal(SIGUSR2,onterm);

        signal(10,onterm);
#endif

        printf("Starting camim server\n");
        load_bos_server_config();


        string g_conf_pn="./conf/BOS.conf";
        map<string,string> g_conf=load_m_file(g_conf_pn);
        init_senders(g_conf_pn,"sender_",g_conf);

        pserver=new bos_server();
        g_conf["bos_udp_listen_port"]=__PORT.get();
        g_conf["bos_listen_port"]=__PORT.get();

        pserver->start(g_conf_pn,"bos_",g_conf);

        while (1){
            sleep(10);
        }

    }catch(CommonError e){
#ifdef DEBUG
        logErr2("--Error in start_main() - %s %s %d",e.what(),__FILE__,__LINE__);
#else
        logErr2("--Error in start_main() - %s %s %d",e.what(),__FILE__,__LINE__);
#endif
    }catch(...){
#ifdef DEBUG
        logErr2("--Error in start_main() - unknow error! %s %d",__FILE__,__LINE__);
#else
        logErr2("--Error in start_main() - unknow error! %s %d",__FILE__,__LINE__);
#endif
    }
    return 0;
}
#ifndef WIN32
void onterm(int signum)
{
    int n=rand();
    if (!ex){
        logErr2("Received signal %d",signum);
#ifdef MUTEX_INSPECTOR_DBUG
        logErr2("%s",dump_mutex_inspectors().c_str());
#endif
    }
    try{
        if (!ex){
            string out;
            if (signum==SIGUSR1)
            {
                ex=true;
                logErr2("BACKUP mode switched on");
                sleep(1);
                ex=false;
                return;
            }
            if (signum==SIGUSR2)
            {
                ex=true;
                logErr2("Print statistics");
                string di=pserver->do_adminfo_bos();
                di+=thread_info_txt();
#ifdef MUTEX_INSPECTOR_DBUG
                di+=dump_mutex_inspectors();
#endif
                string fn="stat."+itostring(time(NULL));
                {
                    st_FILE f(fn,"wb");
                    f.write(di);
                }
                logErr2("BACKUP mode switched off");
                sleep(1);
                ex=false;
                return;
            }
            if (signum==SIGHUP&&pserver){
                ex=true;
                load_bos_server_config();
                sleep(1);
                ex=false;
                return;
            }
            if (signum!=10){
                ex=true;
                logErr2("Terminating on SIGNAL %d",signum);
            }
#ifdef MUTEX_INSPECTOR_DBUG
            out+=dump_mutex_inspectors();
#endif
            string fn;
            if (signum!=10){
                fn=(string)"TERM."+itostring(time(NULL));
            }else{
                fn=(string)"USERTERM."+itostring(time(NULL));
            }

            if (out.size())
            {
                out="Terminating on SIGNAL "+itostring(signum)+"\n"+out;

                FILE *f=fopen(fn.c_str(),"wb");
                if (f){
                    fprintf(f,"%s",out.c_str());
                    fclose(f);
                }
            }
            if (signum!=10){
                if (pserver)
                {
                    logErr2("kill threads");
                    delete pserver;
                    pserver->kill_threads();
                    pserver=NULL;
                    g_kill_threads();
                }

                exit(signum);
            }
        }
    }catch(CommonError e){
    }catch(...){
        logErr2("--Error: unknow error in on_term() %s %d",__FILE__,__LINE__);
    }
}
#endif

