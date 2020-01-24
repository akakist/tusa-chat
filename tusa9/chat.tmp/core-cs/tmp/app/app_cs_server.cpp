#include "stdafx.h"
#include "mutexable.h"
#include <stdio.h>
#include "commonError.h"
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "m_var.h"
#include "str_lib.h"
#include "tcp_stats.h"
#include "oscarService.h"
#include "app_cs_server.h"
#include "app_cs_server_iface.h"
#ifdef DEBUG
//#pragma comment(lib, "lib_win32d.lib")
#else
//#pragma comment(lib, "lib_win32r.lib")
#endif

static m_var<time_t> __inf_start_time(time(NULL));
time_t total_wtime();

void app_cs_server::start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{
	logErr2("app_cs_server::start");
//	OscarService::start(pn,prefix,m);
	load_config(pn,prefix,m);
}
/*app_cs_server::app_cs_server(Service::Manager *m): Oscar::ServiceImpl(m)
{
}*/




Mutex FUNCTIONS_MX;
std::map<int,app_interface *> interfaces;

void add_handler(app_interface* iface)
{
	MUTEX_INSPECTOR;
    M_LOCK(FUNCTIONS_MX);
    while(iface->client_type!=-1)
    {
        interfaces[iface->client_type]=iface;
        iface++;
    }
}
void __get_interfaces(std::map<int,app_interface *> &m)
{
	MUTEX_INSPECTOR;
    M_LOCK(FUNCTIONS_MX);
    m=interfaces;

}


bool app_cs_server::do_application_login(const G_session& app_data,int client_type, const PTR_getter<user_session_data> &__SD,const std::string& ip,std::map<std::string,std::string> &m)
{
	MUTEX_INSPECTOR;
    DO_APPLICATION_LOGIN_FUNCTION f=NULL;
    {
        M_LOCK(FUNCTIONS_MX);
		std::map<int,app_interface *>::const_iterator it;
        it=interfaces.find(client_type);
        if(it!=interfaces.end())
        {
            f=it->second->_DO_APPLICATION_LOGIN_FUNCTION;
        }
    }
    if(f!=NULL)return f(app_data, __SD,ip,m);
    else{ 
	logErr2("DO_APPLICATION_LOGIN_FUNCTION not found for client_type %d",client_type);
	std::map<std::string,std::string> mm;
	mm["result"]="invalid_client_type";
	Oscar::ServiceImpl::reply_login_failed(__SD,mm);
	return false;
    }



}
void app_cs_server::on_delete_session(int client_type,const G_session& app_data,const PTR_getter<user_session_data>&SD)
{
	MUTEX_INSPECTOR;
    ONDELETE_SESSION_FUNCTION f=NULL;
    {
        M_LOCK(FUNCTIONS_MX);

		std::map<int,app_interface *>::const_iterator it;
        it=interfaces.find(client_type);
        if(it!=interfaces.end())
        {
            f=it->second->_ONDELETE_SESSION_FUNCTION;
        }

    }
    if(f!=NULL)return f(app_data,SD);
    else logErr2("ONDELETE_SESSION_FUNCTION not found for client_type %d",client_type);


}

void app_cs_server::process_data_event(int client_type,const G_session& app_data, const PTR_getter<user_session_data> &__SD, oscar_buffer& b,int subtype)
{
	MUTEX_INSPECTOR;
    PROCESS_DATA_EVENT_FUNCTION f=NULL;
    {
        M_LOCK(FUNCTIONS_MX);

        std::map<int,app_interface *>::const_iterator it;
        it=interfaces.find(client_type);
        if(it!=interfaces.end())
        {
            f=it->second->_PROCESS_DATA_EVENT_FUNCTION;
        }

    }
    if(f!=NULL)return f(app_data,__SD,b, subtype);
    else logErr2("PROCESS_PACKET_FUNCTION not found for client_type %d",client_type);

}

bool app_cs_server::process_request(int client_type,const G_session& app_data, const PTR_getter<user_session_data> &__SD, oscar_buffer& b,int subtype, int req_id, out_oscar_buffer& out)
{
	MUTEX_INSPECTOR;
    PROCESS_REQUEST_FUNCTION f=NULL;
    {
        M_LOCK(FUNCTIONS_MX);

        std::map<int,app_interface *>::const_iterator it;
        it=interfaces.find(client_type);
        if(it!=interfaces.end())
        {
            f=it->second->_PROCESS_REQUEST_FUNCTION;
        }

    }
    if(f!=NULL)return f(app_data,__SD,b, subtype, req_id,out);
    else logErr2("PROCESS_PACKET_FUNCTION not found for client_type %d",client_type);
    return "";
}

/*void app_cs_server::on_iterate(std::map<std::string,std::string>&m)
{
	MUTEX_INSPECTOR;
    OscarService::on_iterate(m);
    std::map<int,app_interface *> mm;
	__get_interfaces(mm);
	for(std::map<int,app_interface *>::const_iterator i=mm.begin();i!=mm.end();i++)
    {
        i->second->_ON_ITERATE_FUNCTION(m);
    }
}*/
std::string app_cs_server::do_adminfo()
{
	MUTEX_INSPECTOR;
    time_t dt = time(NULL) - __inf_start_time.get();
    std::string out;
    out+="SERVER statistics on "+CTIME(time(NULL))+"\n";
    if (dt == 0) {

        out = "dt=0! stat unavilable.";
        return out;
    }
    {
        out += "Started: " + CTIME(__inf_start_time) + "\n";
        char s[200];
        snprintf(s, sizeof(s) - 1, "Uptime: %d days %02d:%02d:%02d hours (%d sec)\n", (dt / 24) / 3600, dt / 3600, (dt % 3600) / 60,
                 dt % 60, dt);
        out += s;
    }
    //double p1 = tcp_total_accepted_connections.get();
    char s[200];
    /*{

        p1 /= dt;
        snprintf(s, sizeof(s) - 1, "Total accepted connections: %llu (%2.2f/sec)\n", tcp_total_accepted_connections.get(),p1);
        out += s;
    }*/

/*    {
        p1 = (double)tcp_oscar_dialog_server_total_processed_requests.get();
        p1 /= dt;
        snprintf(s, sizeof(s) - 1, "Total processed requests: %llu (%2.2f/sec)\n", tcp_oscar_dialog_server_total_processed_requests.get(),p1);
        out += s;
    }*/
    /*{
        p1 = (double)tcp_total_send.get();
        p1 /= dt;
        snprintf(s, sizeof(s) - 1, "Total data sent: %llu (%2.2f/sec)\n", tcp_total_send.get(),p1);
        out += s;
    }
    {
        p1 = (double)tcp_total_recv.get();
        p1 /= dt;
        snprintf(s, sizeof(s) - 1, "Total data recv: %llu (%2.2f/sec)\n", tcp_total_recv.get(),p1);
        out += s;
    }*/


#ifdef __linux__
    {

        double twt = total_wtime();
        twt /= 100;
        snprintf(s, sizeof(s) - 1, "Total CPU time %2.2f ( %2.2f\% )\n", twt, ((twt / dt) * 100));
        out += s;
    }
#endif

    std::map<int,app_interface *> mm;
	__get_interfaces(mm);
	for(std::map<int,app_interface *>::const_iterator i=mm.begin();i!=mm.end();i++)
    {
        out+=i->second->_DO_ADMINFO_FUNCTION();
    }
    return out;
}
void app_cs_server::load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{

}
