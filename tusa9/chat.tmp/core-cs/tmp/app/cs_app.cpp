#include "stdafx.h"
#ifdef _DEBUG
#define New DEBUG_NEW
#endif

#include <signal.h>
#include <errno.h>

#include "file_set.h"
#include "PTR.h"
#include "mysql_extens.h"
#include "PTR.h"
#include "tcp_server_data.h"

#include "app_cs_server.h"
#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include "version.h"


#include "str_lib.h"
#include "server_config.h"
#include "db_config.h"
#include "db_config2.h"

#include "st_stuff.h"


#include "app_cs_server_iface.h"
#include "tcp_sender.h"
//#include "web_cache.h"
#include "DB_id.h"
#include "CH_id.h"
#include "user_status.h"
#include "user_nick.h"
#include "user_state.h"
#include "global_state.h"
#include "user.h"
central_server* p__server=NULL;
m_var<bool> ex(false);
extern m_var<string> __APPNAME;

_mutex destroy_MX;
void onterm(int signum);
string thread_info_txt();
void __get_interfaces(map<int,app_interface *> &);
void load_central_server_config()
{
    MUTEX_INSPECTOR;
    printf("Loading config\n");
    string pn="./conf/_cs.conf";
    global_config.load_config(pn,false);

    map<string,string> m=load_m_file(pn);

    map<int,app_interface*> mf;
    __get_interfaces(mf);
    for (map<int,app_interface*>::const_iterator i=mf.begin();i!=mf.end();i++)
    {
        MUTEX_INSPECTOR;
        //LOAD_CONFIG_FUNCTION
        string s1=(string)"app_"+itostring(i->first)+"_config";
        string s2=(string)"./conf/app_"+itostring(i->first)+".conf";
        if (i->second)
            i->second->_LOAD_CONFIG_FUNCTION(get_cfg_str(m,s1.c_str(),pn, s2.c_str()));
        else
            logErr2("LOAD_CONFIG_FUNCTION not found for %d",i->first);
    }
}
#include "config.cpp"

#ifdef _WIN32
#define SVN_VERSION "win32"
#endif
static void local_free_handler()
{
    if (p__server)
    {
        logErr2("shutting down server");
        map<int,app_interface*> mf;
        __get_interfaces(mf);
        for (map<int,app_interface*>::const_iterator i=mf.begin();i!=mf.end();i++)
        {
            if (i->second)
            {
                i->second->_DEINIT_FUNCTION();
            }
        }
        central_server*  p=p__server;
        p__server=NULL;
        p->kill_threads();
        LEAKCTL_REMOVE(p);delete p;

    }
    else
        logErr2("pserver not found");
    destroy_senders();
    g_kill_threads();
}
string des_encrypt(const string&key, const string& str);
string des_decrypt(const string&key, const string& str);


int app_main(int argc,char *argv[])
{
    string eout=des_encrypt("kall","tipa togo");
//	string eeout=des_decrypt("kall",eout);
    logErr2("eout %s",eout.c_str());
//	logErr2("eeout %s",eeout.c_str());

    add_free_handler(local_free_handler);
    try{

        string an=argv[0];
        vector<string> v=splitTOK("/",an);
        if (v.size())
        {
            __APPNAME=v[v.size()-1];
        }

        printf("CS %s, rev %s, build %s\n %s -d to run as daemon\n\n",SERVER_VERSION_INT,SVN_VERSION,__DATE__,argv[0]);

        if (argc>1){
#ifndef WIN32
            if (strcmp(argv[1],"-d")==0){
                printf("Continuing as daemon\n");
                if (fork()) exit(1);
            }
#endif
            if (strcmp(argv[1],"--help")==0){
                printf("\t -d - to run as deamon\n");
                exit(1);
            }
        }


        init_handlers();



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

            printf("Starting central server\n");

            load_central_server_config();


            string g_conf_pn="./conf/CS.conf";
            map<string,string> g_conf=load_m_file(g_conf_pn);

            init_senders(g_conf_pn,"sender_",g_conf);

            p__server=new app_cs_server(); LEAKCTL_ADD(p__server);
            p__server->start(g_conf_pn,"cs_",g_conf);

            map<int,app_interface*> mf;
            __get_interfaces(mf);
            for (map<int,app_interface*>::const_iterator i=mf.begin();i!=mf.end();i++)
            {
                if (i->second)
                {
                    i->second->_INIT_FUNCTION();
                }
            }
            while (1){
                sleep(10);
            }

        }
        STDCATCHS("Error in start_main");
        return 0;

    }
    STDCATCHS("Error in start_main2");
    return 0;
}

//void save_states();

void onterm(int signum)
{
    int n=rand();
    if (!ex)	logErr2("Received signal %d",signum);
    try{
        if (!ex){
            ex=true;
            string out;
//	    save_states();
#ifndef WIN32
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
                string di;

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
#endif
#ifndef WIN32
            if (signum==SIGHUP/*&&pserver*/){
                if (!p__server)
                {
                    logErr2("!pserver");
                    exit(1);
                }
                ex=true;
                load_central_server_config();
//                sleep(1);
                ex=false;
                return;
            }
#endif
            if (signum!=10){
                ex=true;
                logErr("Terminating on SIGNAL %d",signum);
            }
//            www_cache_clean(www_cache_root,0);

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
                {
                    if (p__server)
                    {
                        logErr2("shutting down server");
                        map<int,app_interface*> mf;
                        __get_interfaces(mf);
                        for (map<int,app_interface*>::const_iterator i=mf.begin();i!=mf.end();i++)
                        {
                        }
                        central_server*  p=p__server;
                        p__server=NULL;
                        LEAKCTL_REMOVE(p);delete p;

                    }
                    else
                        logErr2("pserver not found");

                }
                exit(signum);
            }
        }
    }
    STDCATCHS("term");
}


