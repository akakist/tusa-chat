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
#include "tcp_sender.h"
#include "web_tools.h"
#include "version.h"
#include "user_credits.h"
#include "chat_def.h"
#include "irc_server_config.h"

#include "chat_config.h"
#include "notes.h"
#include "fotos.h"
#include "channels.h"
#include "irc_utils.h"
#include "update_cmd.h"
#include "ignore_vec.h"
#include "user_stat.h"
#include "contact_vec.h"
#include "chat_globals.h"

#define NO_USERS_COUNT

#define	IRC_TIMEOUT	60
void  log_start_thread(const std::string &n);

void update_db_cache();
void LK_get_users();
map<string,string> calc_statistic();
void load_app_configuration();
extern irc_server *ircserver;
void irc_iterate();
void local_users_iterate();
void dump_url_log();

app_server::~app_server()
{

}
void app_server::start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{
    web_server::start(pn,prefix,m);
    load_config(pn,prefix,m);
    srand(time(NULL));
    SERVERNAME.set(SERVER_VERSION);
#ifdef __MCASSA
    logErr2("void app_server::start(const std::string& pn,co is_cassa %d",is_cassa);
    if (!is_cassa)
#endif
    {
        pthread_t t;
        int r=pthread_create(&t,NULL,users_handler,(void *)this);
        pth_users_handler=t;
        if (r!=0) {
            throw cError("--Error while creating pthread_ceate");
        }
    }

}
app_server::app_server(
#ifdef __MCASSA
    bool _iscassa
#endif
)
#ifdef __MCASSA
        :
        is_cassa(_iscassa)
#endif
{

}
void *app_server::new_connection(const PTR_getter<c_socket>&s)
{
    return new app_connection(this,s
#ifdef __MCASSA
                              ,is_cassa
#endif
                             );
}

void app_server::on_inspector_iterate()
{
    sleep(100);
}

string update_to_db(const PTR_getter<user_credit>&__P,const string &tblname);
string update_to_db(const PTR_getter<u_notes>&__P,const string &tblname);
string update_to_db(const PTR_getter<note_text>&__P,const string &tblname);
string update_to_db(const PTR_getter<user_stat>&__P,const string &tblname);
string update_to_db(const PTR_getter<user_set>&__P,const string &tblname);
string update_to_db(const PTR_getter<user_profile>&__P,const string &tblname);
string update_to_db(const PTR_getter<nick_vec>&__P,const string &tblname);


string update_to_db(const PTR_getter<user_fotos>&__P,const string &tblname);

class ignore_vec;
class contact_vec;
string update_to_db(const PTR_getter<ignore_vec>&__P,const string &tblname);

string update_to_db(const PTR_getter<contact_vec>&__P,const string &tblname);


static M_MAP<time_t,int> users_counts;
static M_MAP<time_t,int> local_users_counts;
static m_var<time_t> last_update_time_users_counts(0);
//time_t total_wtime();
static m_var<int> last_wtime(0);
#ifdef WIN32
static m_var<__int64> last_tcp_total_accepted_connections(0);
static m_var<__int64> last_tcp_total_recv(0);
static m_var<__int64> last_tcp_total_send(0);
#else
static m_var<long long> last_tcp_total_accepted_connections(0);
static m_var<long long> last_tcp_total_recv(0);
static m_var<long long> last_tcp_total_send(0);
#endif
void cpu_state()
{
    int _DT,_MIU,_MLU;
    double _WT,_WTDT;
#ifdef WIN32
    __int64
#else
    long long
#endif
    dtcp_recv=tcp_total_recv-last_tcp_total_recv;
    last_tcp_total_recv=tcp_total_recv.get();
    unsigned int _TCPRECV=dtcp_recv;

#ifdef WIN32
    __int64
#else
    long long
#endif
    dtcp_send=tcp_total_send-last_tcp_total_send;
    last_tcp_total_send=tcp_total_send.get();
    unsigned int _TCPSEND=dtcp_send;

#ifdef WIN32
    __int64
#else
    long long
#endif
    dtcp_total_accepted_connections=tcp_total_accepted_connections-last_tcp_total_accepted_connections;
    last_tcp_total_accepted_connections=tcp_total_accepted_connections.get();
    unsigned int _TCPACCONN=dtcp_total_accepted_connections;



    time_t dt=time(NULL)-last_update_time_users_counts.get();
    if (dt==0) return ;
    int _TCPRECVs;
    _TCPRECVs=_TCPRECV/dt;
    int _TCPSENDs;
    _TCPSENDs=_TCPSEND/dt;
    int _TCPACCONNs;
    _TCPACCONNs=_TCPACCONN/dt;

//    time_t twt=0total_wtime();
//    int dtwt=twt-last_wtime.get();
//    if (dtwt==0) return ;
//    last_wtime=twt;
//    double nnn=dtwt;
//    double DTWT=dtwt;
//    DTWT/=100;
/*    nnn/=100;
    {
        if (dt!=0)
            nnn/=dt;
        else nnn=0;
        nnn*=100;
        _DT=dt;
        _WT=DTWT;
        _WTDT=nnn;
    }*/
    {
        int mu=0;
        map<time_t,int> mm=local_users_counts.get_container();
        local_users_counts.clear();
        for (map<time_t,int>::iterator i=mm.begin();i!=mm.end();i++)
        {
            if (i->second>mu)mu=i->second;
        }
        _MLU=mu;
    }
    {
        int mu=0;
        map<time_t,int> mm=users_counts.get_container();
        users_counts.clear();
        for (map<time_t,int>::iterator i=mm.begin();i!=mm.end();i++)
        {
            if (i->second>mu)mu=i->second;
        }
        time_t dt=time(NULL);
        dt-=dt%600;
        _MIU=mu;
    }
    logErr2("CPU_USAGE DT=%d WT=%2.2f WT/DT=%2.2f% MAX_INCHAT_USERS=%d MAX_LOCAL_USERS=%d TCPRECV=%d,%d/s TCPSEND=%d,%d/s TCPACCONN=%d,%d/s ",_DT,_WT,_WTDT,_MIU,_MLU,_TCPRECV,_TCPRECVs,_TCPSEND,_TCPSENDs,_TCPACCONN,_TCPACCONNs);
    if (ircserver) ircserver->dump_state();
}
#ifndef __CLAN
void iterate_levelup_new_users()
{
    st_dbh d;
    vector<string> v=d.dbh->select_1_columnQ((QUERY)
                     "select user_stats.refid from user_stats,user_profiles where user_stats.m_count>100 and user_stats.v_count>9 and user_stats.t_count>3600 and user_profiles.level=? and UNIX_TIMESTAMP(user_profiles.reg_date)<(NOW()-86400) and user_stats.refid=user_profiles.refid"<<sub_levels);
    for (unsigned i=0;i<v.size();i++)
    {
        PGLW(user_profile, u,user_profiles.find_by_id(atoi(v[i].c_str())));
        u->level=sub_levels*2;
        send_update_g3(user_profile$level,atoi(v[i].c_str()),u->level);
    }
}
#endif
void iterate_bans()
{
    st_dbh d;
    d.dbh->real_query("delete from banned_ip where time_free<NOW() and UNIX_TIMESTAMP(time_free)!=0");
    //remove banned login's
    d.dbh->real_query("delete from banned_login where time_free<NOW() and UNIX_TIMESTAMP(time_free)!=0");

}
void update_user_counts()
{
    st_dbh d;

    {
        int mu=0;
        map<time_t,int> mm=users_counts.get_container();
        users_counts.clear();
        for (map<time_t,int>::iterator i=mm.begin();i!=mm.end();i++)
        {//;
            if (i->second>mu)mu=i->second;
        }
        time_t dt=time(NULL);
        dt-=dt%600;
        try {
            d.dbh->real_queryQ((QUERY)"insert into users_count (dt,cnt) values(FROM_UNIXTIME(?),?)"<<dt<<mu);
        } catch (...) {}
    }

}
static void users_handler__update_users_counts()
{
    if (time(NULL)-last_update_time_users_counts.get()>600)
    {
        try {
            update_user_counts();
            iterate_bans();
            iterate_levelup_new_users();
            cpu_state();
            dump_url_log();

        }
        catch (cError e) {
            logErr2("-Err: %s",e.what());
        } catch (...) {}
        last_update_time_users_counts=time(NULL);
    }

}


void iterate_topics()
{
    st_dbh d;
    vector<vector<string> > vZ=d.dbh->execQ((QUERY)"select channel,UNIX_TIMESTAMP(last_recalc),current_price from topics where disabled='0'");
    for (unsigned i=0;i<vZ.size();i++)
    {
        if (vZ[i].size()==3)
        {
            vector<string> &v=vZ[i];
            time_t last_recalc=atoi(v[1].c_str());
            if (time(NULL)-last_recalc>3600)
            {
                double current_price=atof(v[2].c_str());
                current_price=current_price*0.95;
                last_recalc=time(NULL);
                unsigned int channel=atoi(v[0].c_str());
                d.dbh->real_queryQ((QUERY)"update topics set last_recalc=FROM_UNIXTIME(?), current_price=? where disabled='0' and channel=?"<<last_recalc<<current_price<<channel);
            }
        }
    }
}

void* app_server::users_handler(void *pr)
{
    app_server*srv=(app_server*)pr;

    string thread_name=srv->server_name()+" app_server::users_handler";
    log_start_thread(thread_name);

    unsigned int n=61;
    unsigned int cs=600;
    unsigned int avg_cnt=0;

    struct tm new_tm;
    int last_min;
    new_tm=LOCALTIME(time(NULL));
    last_min=new_tm.tm_min;

    bool started=false;
    while (1) {
        {
            if (srv->SLEEP(30))return NULL;
        }

        try {
            irc_iterate();


            update_db_cache();



            chat_channels_backup_messages();
            if (cs>=600) {	//calc statistic & save messages


                cs=0;
                iterate_topics();
                map<string,string> m;
                m=calc_statistic();
                chat_stat.assign(m);
            }



            local_users_iterate();

            int pc=local_users.size();
            users_counts.set(time(NULL),pc);
            local_users_counts.set(time(NULL),local_users.size());
            users_handler__update_users_counts();
            n++;
            cs++;
        }
        STDCATCHS("users_handler");
    }

}
void app_server::load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{

}
