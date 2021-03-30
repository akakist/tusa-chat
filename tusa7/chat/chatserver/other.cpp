#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <map>
#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include "web_server.h"
#include "message.h"
#include "chat_def.h"
#include "copy_file.h"
#include "file_set.h"
#include "chat_funny.h"
#include "app_con.h"

#include "tcp_stats.h"
#include "chat_config.h"
#include "user_credits.h"
#include <algorithm>

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#ifndef WIN32
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
//#include "tcp_oscar_dialog_server.h"
#ifndef _NO_PROXY
#endif
#include "oscar_buffer.h"
#include "cs_conn_data.h"
#include "chat_globals.h"
#include "DR_types.h"
m_var<time_t> inf_start_time(time(NULL));
//time_t total_wtime();

out_oscar_buffer & operator<<(out_oscar_buffer&b, const user_state& n);
oscar_buffer & operator>>(oscar_buffer&b, user_state& n);
string dump_mutex_inspectors_www();
#define CHK_NULL(x) if ((x)==NULL) return -1;
#define CHK_ERR(err,s) if ((err)==-1) { return -1; }
#define CHK_SSL(err) if ((err)==-1) { return -1; }
void cpu_state();
map<string,string> calc_statistic();
map<time_t,unsigned int> get_users_counts(time_t t, time_t rt);

void url_statistic(cs_conn_data *cc)
{

    map<string,string> m=chat_stat.get_container();
    time_t t=time(NULL);
    time_t td=atoi(cc->params["b"]);
    struct tm q=LOCALTIME(t);
    q.tm_min=0;
    q.tm_sec=0;
    if (td==0) td=mktime(&q);
    m["~ctime~"]=cc->params["b"];
    m["~time~"]=itostring(td-86400);
    m["~date~"]=date2rus(td);
    map<string,hstring> mm;
    for (map<string,string> ::iterator i=m.begin();i!=m.end();i++)
    {
        mm[i->first]=i->second;
    }
    cc->html_out=make_pair(mm,"statistic");
}
void url_users_statistic(cs_conn_data *cc)
{

    map<string,hstring> m;

    time_t t=atoi(cc->params["b"]);
    if (t==0) t=time(NULL)-82800;
    struct tm q=LOCALTIME(t);
    q.tm_min=q.tm_min/10*10;
    q.tm_sec=0;
    t=mktime(&q);

    time_t rt=t+82800;

    vector<string> h;	//hours row
    vector<string> d;	//data row
    vector<string> alts;	//data alts
    vector<string> uc;	//users count row
    //makeing hours
    for (time_t i=t;i<=rt;i+=7200) {
        q=LOCALTIME(i);
        h.push_back(itostring(q.tm_hour));
    }
    map<time_t,unsigned int> u=get_users_counts(t,  rt) ;
    unsigned int max_u=0;
    //searching for max users
    {
        for (map<time_t,unsigned int>::iterator i=u.begin();i!=u.end();i++) {
            if (i->second>max_u) max_u=i->second;
        }
    }
    unsigned int lmax_u=max_u;
    if (max_u%10!=0) max_u=max_u/10*10+10;
    if (max_u==0) {
        max_u=lmax_u;
        uc.push_back("0");
        uc.push_back(itostring(max_u));
    } else {
        double u_per_row=(double)max_u/4;//u_per;
        if (u_per_row==0) u_per_row=1;
        double curcnt=u_per_row*4;
        for (unsigned int i=0;i<5;i++) {
            uc.push_back(itostring((int)curcnt));
            curcnt-=u_per_row;
        }
    }
    {
        for (time_t i=t;i<=rt;i+=600) {
            double r=0;
            r=(double)u[i]/(double)max_u*100;
            d.push_back(itostring((int)r));
            alts.push_back("'"+itostring(u[i])+"'");
        }
    }

    m["~hours~"]=join(",",h);
    m["~count~"]=join(",",uc);
    m["~data~"]=join(",",d);
    m["~al~ts"]=join(",",alts);

    cc->html_out=make_pair(m,"users_statistic");
}


extern M_MAP<pthread_t,string> pthread_2_url_map;

string info_value(const char *format,
#ifndef WIN32
                  long long v
#else
                  __int64 v
#endif

                  , time_t dt)
{
    char s[1000];
    double p1=v;
    p1/=dt;
    snprintf(s, sizeof(s) - 1, format, v,p1);
    return s;
}
#ifndef _NO_PROXY
extern global_proxy_stats __global_proxy_stats;
#endif

void do_adminfo(app_connection * cc, const string & title)
{

    time_t dt = time(NULL) - inf_start_time.get();
    if (dt == 0) {

        cc->html_out = "<h1>dt=0! stat unavilable.<br>";
        return;
    }
    {
        cc->html_out = "<link rel=stylesheet type=text/css href=/css/main.css>";
        cc->html_out += "<title>" + title + "</title><body>";
        cc->html_out += "<h1>" + title + "</h1><p>";


        cc->html_out += "Started: " + CTIME(inf_start_time) + "<br>\n";
        char s[200];
        snprintf(s, sizeof(s) - 1, "Uptime: %d days %02d:%02d:%02d hours (%d sec):<br>\n", (dt / 24) / 3600, dt / 3600, (dt % 3600) / 60,
                 dt % 60, dt);
        cc->html_out += s;
    }

    cc->html_out+=info_value("Total processed connections: %lld (%2.2f sec)<br>\n",tcp_total_accepted_connections.get(),dt);
    char s[200];
    cc->html_out+=info_value("Total data sent: %llu (%2.2f sec)<br>\n",tcp_total_send.get(),dt);
    cc->html_out+=info_value("Total data recv: %llu (%2.2f sec)<br>\n",tcp_total_recv.get(),dt);

    string mysock;
    {
        PTR_getter<c_socket > s=cc->socket;
        {
            PGLW( c_socket , ss,s);
            if (ss) {
                mysock = ss->get_socket_descr();
            }
        }


    }
    cc->html_out += "Socket: " + mysock + "<br>";
    cc->html_out += "IP: " + cc->peer_ipaddress + "<br>";


    cc->html_out += "Currently " + itostring(local_users.size()) + " users<br>\n";

#ifdef __linux__
    {
//        double twt = total_wtime();
//        twt /= 100;
//        snprintf(s, sizeof(s) - 1, "Total CPU time %2.2f ( %2.2f\% )<p>\n", twt, ((twt / dt) * 100));
    }
#endif
    {
        cc->html_out += s;

#ifndef _NO_PROXY
        cc->html_out += "<hr>\n";
        cc->html_out += "<h3>Proxy whole statistics</h3>\n";
        vector<string> pv=proxy_users.keys();
        cc->html_out += "Currently connected "+itostring(pv.size())+" proxies<p>\n";
        proxy_server_stat pst=__global_proxy_stats.get();

        cc->html_out+=info_value("Total data sent: %llu (%2.2f sec)<br>\n",pst._tcp_total_send,dt);
        cc->html_out+=info_value("Total data recv: %llu (%2.2f sec)<br>\n",pst._tcp_total_recv,dt);
        cc->html_out+=info_value("Total cached sent: %llu (%2.2f sec)<br>\n",pst._www_total_cached_send,dt);
        cc->html_out+=info_value("Total cached recv: %llu (%2.2f sec)<br>\n",pst._www_total_cached_recv,dt);
        cc->html_out+=info_value("Total head filtered: %llu (%2.2f sec)<br>\n",pst._www_total_head_filtered,dt);
        cc->html_out+=info_value("Total www recv: %llu (%2.2f sec)<br>\n",pst._www_total_recv,dt);
        vector<string> plist;
        for (int i=0;i<pv.size();i++) {
            PTR_getter<proxy_user> U=proxy_users.get(pv[i]);
            if (U)
            {
                PGLR(proxy_user, u,U);
                plist.push_back(u->nick);
            }
        }
        cc->html_out+="Proxy list: "+join(",",plist)+"<br>\n";

        cc->html_out += "<hr>\n";
#endif

        cc->html_out += "<h2>Params</h2>";
        {
            for (map< string, string >::iterator i = cc->params.begin(); i != cc->params.end(); i++) {
                cc->html_out += i->first + ": " + i->second + "<br>";
            }
        }
//        cc->html_out+=thread_info_html(pthread_2_url_map.get_container());

    }

}


