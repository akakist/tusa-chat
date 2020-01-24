#include "stdafx.h"
#include <string>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <errno.h>
#include "oscar_buffer.h"
#include "st_rsa.h"
#include "m_var.h"
#include "bos_server.h"
#include "RTYPES_CORE.h"
#include "str_lib.h"
#include "tcp_stats.h"
#ifndef _WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include "utils.h"
using namespace std;

string thread_info_txt();
out_oscar_buffer & operator<< (out_oscar_buffer& b,const enc_string &s);
oscar_buffer & operator>> (oscar_buffer& b,  enc_string &s);
namespace globals{
extern m_var<string>__PORT;
};

void bos_server::finishCreate(configObj* config)
{
    MUTEX_INSPECTOR;
//    TCPOscarDialogServer::start(config);
/*    load_config(pn,prefix,m);
    create_thread(inspector,server_name()+" inspector");
    client->start(pn,"client_",m);
*/
	config->set_cfg_i("client_max_users", client_max_users, 900);
	config->set_cfg_str("bos_name", bos_name, "www.bos.com");

	config->set_cfg_i("user_login_timeout_sec", user_login_timeout_sec, 10);
	config->set_cfg_i("inspector_timeout_sec", inspector_timeout_sec, 3);
	config->set_cfg_i("adminfo_log_timeout_sec", adminfo_log_timeout_sec, 3600);
	config->set_cfg_i("cs_ping_timeout_sec", cs_ping_timeout_sec, 20);
	config->set_cfg_i("rsa_client_io_size", rsa_client_io_size, 512);
	config->set_cfg_i("client_linger_sec", client_linger_sec, 3);

#ifdef BOS_UDP
	config->set_cfg_i("udp_handlers_count", udp_handlers_count, 3);
	//config->set_cfg_i("udp_listen_port", udp_listen_port, 2000);
	config->set_cfg_i("udp_handler_time_usec", udp_handler_time_usec, 2000);
	//config.set_cfg_str("udp_listen_ip", udp_listen_ip, "INADDR_ANY");
#endif

	
	//int udp_listen_port;
	 std::string udp_bind;
	//config->set_cfg_i("udp_listen_port",udp_listen_port,5454);
	 config->set_cfg_str("udp_bind",udp_bind,"INADDR_ANY:5454,INADDR_ANY:7777");
	 vector<pair<string,int> > binds;
	 vector<string> v=utils::splitString("|,;",udp_bind);
	 for(size_t i=0;i<v.size();i++)
	 {
		 vector<string> vz=utils::splitString(":",v[i]);
		 if(vz.size()==2)
		 {
			binds.push_back(make_pair(vz[0],atoi(vz[1])));
		 }
	 }

/*	 for(size_t i=0;i<binds.size();i++)
	 {
		 struct sockaddr_in sa;
		 sa.sin_family = AF_INET;
		 sa.sin_port = htons(udp_listen_port);

		 if (udp_listen_ip.get()=="INADDR_ANY") sa.sin_addr.s_addr = INADDR_ANY;
		 else sa.sin_addr.s_addr = inet_addr(udp_listen_ip.get().c_str());

		 int sock=::socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		 if (sock==-1) {
			 char s[200];
			 snprintf(s,sizeof(s)-1,"udp_listener: socket() failed %s",strerror(errno));
			 throw CommonError(s);
		 }
		 while (bind (sock,(struct sockaddr *) &sa, sizeof (sa)) == -1) {
			 char s[200];
			 snprintf(s,sizeof(s)-1,"udp_listener: bind() failed: %s",strerror(errno));
			 logErr2("%s %s:%d", s,inet_ntoa(sa.sin_addr),htons(sa.sin_port));
			 {
				 MUTEX_INSPECTORS("SLEEP");
				 sleep(1);
			 }
		 }
		 logErr2("udp_listener: binded to %s:%d", inet_ntoa(sa.sin_addr),htons(sa.sin_port));
		 c_socket *s=new c_socket(sock,"udp sock");
		 udp_socket=PTR_getter<c_socket> (s);
	 }*/
#ifdef BOS_UDP
    try {//MUTEX_INSPECTOR;
    }
    STDCATCHS("udp_listener");
#endif
#ifdef BOS_UDP
    /*for (unsigned int i=0; i<udp_handlers_count.get(); i++)
    {
        create_thread(udp_handler,server_name()+" udp_handler");
    }*/
#endif

}

bos_server::bos_server(): __bs_users(this),
#ifdef BOS_UDP
        udp_socket(NULL),
#endif
        client(new _cs_client(this)) 
{
}


/*void bos_server::on_delete(const PTR_getter<c_socket>& __SD,const std::string& msg)
{//MUTEX_INSPECTOR;
}

bool bos_server::validate_peer_ip_address(const sockaddr_in & sa)
{//MUTEX_INSPECTOR;
    return true;
}


void *bos_server::new_connection(const PTR_getter<c_socket>&s)
{
    bos_server_connection *p=new bos_server_connection(s, this);
    
    return p;

}
*/
void bos_server::on_accept_dialog_socket(const PTR_getter<c_socket>&_s)
{
    MUTEX_INSPECTOR;
    //logErr2("bos_server::on_accept_dialog_socket");
    F_outV2 o(CHANNEL_1);
    string rsa_pubkey;
    {
        PGLW(c_socket,s,_s);
        if (!s->rsa)
        {
            s->rsa=new st_rsa;
            s->rsa->generate_key(rsa_client_io_size);
        }
        if (s->rsa)
            rsa_pubkey=s->rsa->pub_key_get();
    }
    o<<rsa_pubkey;
    //logErr2("s->rsa->pub_key_get %s", bin2hex(rsa_pubkey).c_str());
    reply_socket(_s,OCALC(o).as_string());
}

/*bos_server_connection::bos_server_connection(const PTR_getter<c_socket> &sk, tcp_dialog_server* s)
        :tcp_dialog_connection(sk,s) {
}*/
/*bos_server_connection::~bos_server_connection() {
}*/
bos_server::~bos_server()
{
    
    delete client;
}

void bos_server::parse_ch3(const PTR_getter<c_socket>& __SD,oscar_buffer & in_b)
{//MUTEX_INSPECTOR;
    logErr2("bos_server::parse_ch3v2");

}

void bos_server::parse_ch4(const PTR_getter<c_socket>& __SD,oscar_buffer & in_b)
{//MUTEX_INSPECTOR;
    logErr2("bos_server::parse_ch4");

}

void bos_server::inspector_worker()
{
	log_start_thread("bos_server_inspector");
	time_t last_adminfo=time(NULL);
	while (1) {
		try {
			{//MUTEX_INSPECTOR;
				__bs_users.on_iterate();

			}
			{
				MUTEX_INSPECTORS("SLEEP");
				//if (SLEEP(inspector_timeout_sec.get()))return ;
				sleep(111);
			}

			if (time(NULL)-last_adminfo>adminfo_log_timeout_sec)
			{
				last_adminfo=time(NULL);
				logErr2("%s",do_adminfo_bos().c_str());
				logErr2("%s",thread_info_txt().c_str());

			}

			bool need_ping=false;
			
		}
		STDCATCHS("bos_server::inspector");
		{
			MUTEX_INSPECTORS("SLEEP");
			sleep(1);
			//if (SLEEP(inspector_timeout_sec.get()))return ;
		}
	}
	logErr2("--Error: T_run_cf_inspector: handler - exited. ??? %s %d",__FILE__,__LINE__);

}

/*void *bos_server::inspector(void *pr)
{
    MUTEX_INSPECTOR;
    
    bos_server *svr=(bos_server*)pr;
	svr->inspector_worker();

    return NULL;
}*/





time_t total_wtime();
static m_var<time_t> __inf_start_time(time(NULL));

string bos_server::do_adminfo_bos()
{//MUTEX_INSPECTOR;


    time_t dt = time(NULL) - __inf_start_time.get();
    string out;
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
    double p1 = tcp_total_accepted_connections.get();
    char s[200];
    {

        p1 /= dt;
        snprintf(s, sizeof(s) - 1, "Total accepted connections: %llu (%2.2f/sec)\n", tcp_total_accepted_connections.get(),p1);
        out += s;
    }

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
    }*/
    {

        p1 = (double)tcp_total_recv.get();
        p1 /= dt;
        snprintf(s, sizeof(s) - 1, "Total data recv: %llu (%2.2f/sec)\n", tcp_total_recv.get(),p1);
        out += s;
    }

    out += "Currently " + itostring(__bs_users._BS_size()) + " online users\n";

#ifdef __linux__
    {

        double twt = total_wtime();
        twt /= 100;
        snprintf(s, sizeof(s) - 1, "Total CPU time %2.2f ( %2.2f\% )\n", twt, ((twt / dt) * 100));
        out += s;
    }
#endif
    return out;
}

void bos_server::delete_extra_user_id(const string & id)
{
    MUTEX_INSPECTOR;
    logErr2("bos_server::delete_extra_user_id %s",id.c_str());
    if (id=="")return;
    BU_session sid;
    CONTAINER(sid)=atoi(id);
    __bs_users._BS_erase(sid);
}


void bos_server::parse_ch5(const PTR_getter<c_socket>& __SD,oscar_buffer & in_b)
{
    MUTEX_INSPECTOR;
    enc_string es;
    string pkt;
    in_b>>es;
    BU_session sid;
    string ip;
        {
            PGLR(c_socket, sd,__SD);
            CONTAINER(sid)=atoi(sd->extra_user_id);
        }
    if (__SD.valid())
    {
        PGLR(c_socket, s,__SD);
        ip=s->peer_ipaddress;
    }
    PTR_getter<bs_user> __B=__bs_users._BS_find(sid);
    if (__B.valid()) {
        {
            PGLW(bs_user, u,__B);
            pkt=u->rjDecode(es);
        }

        F_outV2 o(CHANNEL_5);
        o<<ip<<sid<<pkt;
        client->reply(OCALC(o).as_string());
    }
    else logErr2("__B not found %s %d",__FILE__,__LINE__);

}
/*void bos_server::load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{
    MUTEX_INSPECTOR;
}*/
_cs_client::_cs_client(bos_server*s):server(s),ccd(new cc_data) {}
void _cs_client::Poll()
{
    MUTEX_INSPECTOR;
    try {
        while (1)
        {
            MUTEX_INSPECTOR;
            Target m_target;
            State m_state;
            PTR_getter<c_socket> __S(NULL);
            bool connected=false;
            {
                MUTEX_INSPECTOR;
                M_LOCK(ccdmx);
                m_target = ccd->m_target;
                m_state = ccd->m_state;
                __S=ccd->socket;
            }
            bool need_ping=false;
            bool need_pong_kill=false;
            bool need_auth_timeout_kill=false;
            {
                MUTEX_INSPECTOR;
                M_LOCK(ccdmx);
                if (time(NULL)-ccd->last_ping_time>ping_timeout_sec && m_state==CS_LOGGED_IN)
                {
                    MUTEX_INSPECTOR;
                    need_ping=true;
                    ccd->last_ping_time=time(NULL);
                }
                if (time(NULL)-ccd->last_pong_time>pong_kill_timeout_sec && m_state==CS_LOGGED_IN)
                {
                    MUTEX_INSPECTOR;
                    need_pong_kill=true;
                    ccd->last_pong_time=time(NULL);
//                    logErr2("Killed due PONG timeout");


                }
                if (m_state==CS_LOGGED_IN && __LOGIN==m_target)
                {
                    MUTEX_INSPECTOR;
                    ccd->auth_time=time(NULL);
                }
                if (m_state!=CS_LOGGED_IN && __LOGIN==m_target&&time(NULL)-ccd->auth_time>login_timeout_sec)
                {
                    MUTEX_INSPECTOR;
                    need_auth_timeout_kill=true;
                    ccd->auth_time=time(NULL);
                    //		    logErr2("time %d auth %d",time(NULL),bcd->auth_time);
                }
            }
            if (need_pong_kill)
            {
                MUTEX_INSPECTOR;
                break_connect("pong_kill");
                continue;
            }
            if (need_auth_timeout_kill)
            {
                MUTEX_INSPECTOR;
                break_connect("login_timeout_kill");
                continue;
                //return;
            }
            if (need_ping && m_state==CS_LOGGED_IN)
            {
                MUTEX_INSPECTOR;
//                logErr2("send ping");
                FS_outV2 o(CHANNEL_2,FAM_OTHER,TYPE_PING_09);
                reply(OCALC(o).as_string());
            }
            if (m_target == __LOGIN) {
                MUTEX_INSPECTOR;

                if (m_state == NOT_CONNECTED) {
                    MUTEX_INSPECTOR;

                    client_connect(authorizer_server_ip.get().c_str(), authorizer_server_port.get());
                    srand(time(0));
                    {
                        MUTEX_INSPECTOR;
                        //                    PGLW(cs_client,u,__U);
                        M_LOCK(ccdmx);
                        ccd->m_state = AUTH_AWAITING_CONN_ACK;
                        m_state== AUTH_AWAITING_CONN_ACK;
                    }
                }
            }
            //        cs_clientRecv(__U);
            usleep(poll_timeout_usec.get());
            {
                MUTEX_INSPECTOR;
                M_LOCK(ccdmx);
                m_target = ccd->m_target;
                m_state = ccd->m_state;
            }

        }
    }
    catch(socketError e) {
        MUTEX_INSPECTOR;
        logErr2("catched socketError %s %d",__FILE__,__LINE__);
        on_disconnect((string)"catch "+e.what());
    }
    catch(CommonError e) {
        MUTEX_INSPECTOR;
        logErr2("catched CommonError %s %d %s",__FILE__,__LINE__,e.what());
        on_disconnect((string)"catch "+e.what());
    }
    catch(...) {
        MUTEX_INSPECTOR;
        logErr2("catched %s %d",__FILE__,__LINE__);
        on_disconnect("catch ...");

#ifdef _DEBUG
        logErr2("catched %s %d",__FILE__,__LINE__);
#endif
    }
}

void *_cs_client::T_run_poll_handler(void *pr)
{
    MUTEX_INSPECTOR;
    log_start_thread("_cs_client poller");
    _cs_client *bcid=(_cs_client*)pr;
    if (!bcid) {
        logErr2("KA LLsrall %s %d",__FILE__,__LINE__);
        return NULL;
    }
    //    while(1)
    {
        try {
            //            if(sio_handler_exit_flag)return NULL;
            bcid->Poll();
			//if(USLEEP())
//	    uslepp(10000);
            logErr2("poll_handler exiting");
        }
        catch(CommonError e)
        {
            logErr2("%s",e.what());
            logErr2("catched %s %d",__FILE__,__LINE__);
        }
        catch(...)
        {
            logErr2("catched %s %d",__FILE__,__LINE__);
            logErr2("unknow exception");
        }
    }


    return NULL;
}
void _cs_client::parse_ch1(oscar_buffer & b)
{
    //    oscar_buffer b(bs.data(),bs.size());
//logErr2("parse_ch1");
    Target m_target;
    State m_state;
    {//MUTEX_INSPECTOR;
        M_LOCK(ccdmx);//PGLR(cs_client,u,__U);
        m_target=ccd->m_target;
        m_state=ccd->m_state;
    }
    //    logErr2("b.remains() %d",b.remains());
    if (m_target == __LOGIN) {//MUTEX_INSPECTOR;
        if (b.remains() && m_state == AUTH_AWAITING_CONN_ACK) {//MUTEX_INSPECTOR;
            // Connection Acknowledge - first packet from server on connection
            unsigned int unknown;
            b>>unknown;
            {//MUTEX_INSPECTOR;
                M_LOCK(ccdmx);//PGLW(cs_client,u,__U);
                ccd->m_state = AUTH_AWAITING_AUTH_REPLY;
            }
            send_bos_cs_auth_req();

        }
        else {
            logErr2("Unknown packet received on channel 0x01");
        }
    }
    else if (m_target==SLEEPING)
    {
    }
    else logErr2("unknown target");


}
void _cs_client::send_bos_cs_auth_req()
{
    MUTEX_INSPECTOR;
//	logErr2("send_bos_cs_auth_req");
    F_outV2 b(CHANNEL_1);
    {
        b<<(0x00000004); // type of login to auth server
        map<string,string> m;
        m["nick"]=auth_nick;
        m["password"]=auth_password;
        m["max_users"]=itostring(server->client_max_users);
//	deque<>
		m["bos_address"]=server->bos_name+":"+=globals::__PORT;

        logErr2("bos_address %s",m["bos_address"].c_str());
        b<<m;
    }
    reply(OCALC(b).as_string());
}
void _cs_client::on_TYPE_BOS_LOGIN_RESULT_01(oscar_buffer & in_b)
{
    MUTEX_INSPECTOR;


    logErr2("Logged in");
    {
        M_LOCK(ccdmx);
        ccd->m_state=CS_LOGGED_IN;
    }

}

void _cs_client::parse_ch2(oscar_buffer & in_b)
{

    int family,subtype;
    in_b>>family>>subtype;

    switch (family)
    {
    case FAM_LOGIN:
    {
        switch (subtype)
        {
        case TYPE_BOS_LOGIN_RESULT_01: // BOS log in notification
            on_TYPE_BOS_LOGIN_RESULT_01(in_b);
            break;
        case TYPE_NOTIFY_BOS_TO_DELETE_USER_03: // delete user
        {
            //                    logErr2("TYPE_NOTIFY_BOS_TO_DELETE_USER_03");
            BU_session sid;
            in_b>>CONTAINER(sid);//=id;
            server->__bs_users._BS_erase(sid);

        }
        break;
        default:
            logErr2("--Error: unrecognized SNAC %02x,%02x %s %d",family,subtype,__FILE__,__LINE__);
        }

    }
    return;
    case FAM_OTHER:
        if (subtype==TYPE_PONG_0A)
        {
//            logErr2("acceptd TYPE_PONG_0A");
            M_LOCK(ccdmx);
            ccd->last_pong_time=time(NULL);
        }
        else  logErr2("--Error: unrecognized SNAC %02x,%02x %s %d",family,subtype,__FILE__,__LINE__);

        return;
    default:
        logErr2("--Error: unrecognized SNAC %02x,%02x %s %d",family,subtype,__FILE__,__LINE__);

        break;
    }


}
void _cs_client::parse_ch3(oscar_buffer & b)
{
    logErr2("inval recv %s %d",__FILE__,__LINE__);
}
void _cs_client::parse_ch4(oscar_buffer & b)
{
    logErr2("inval recv %s %d",__FILE__,__LINE__);

}
void _cs_client::parse_ch5(oscar_buffer & b)
{
    out_oscar_buffer outpk;
    BU_session sid;
    {
        string pkt;
        int fam,subt;
        b>>sid>>fam>>subt>>pkt;
        outpk<<1<<fam<<subt<<pkt;

    }
    PTR_getter<bs_user> __B=server->__bs_users._BS_find(sid);
    if (__B.valid()) {
        enc_string cbuf;
        {
            PGLW(bs_user,b,__B);
            cbuf=b->rjEncode(outpk.as_string());
        }
        F_outV2 bc(CHANNEL_5);
        bc<<cbuf;
        bs_user::reply(__B,bc);

    }
    else
    {
        FS_outV2 b(CHANNEL_2,FAM_B2CS_USER_MANAGE_10,TYPE_B2CS_USER_MANAGE_DELETE_USER_02);
        b<<sid;
        reply(OCALC(b).as_string()); // delete user
    }

}
void _cs_client::parse_ch6(oscar_buffer & b)
{
    logErr2("inval recv %s %d",__FILE__,__LINE__);
}
cc_data::cc_data(): socket(NULL)
{
    m_target=SLEEPING;
    m_state=NOT_CONNECTED;
    last_ping_time=time(NULL);
    last_pong_time=time(NULL);
    auth_time=time(NULL);

}
void _cs_client::start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{
    oscar_client::start(pn,prefix,m);
    load_config(pn,prefix,m);
    create_thread(T_run_poll_handler,"client_poll_handler");
    do_auth();

}
void _cs_client::load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{
    set_cfg_i(m,	prefix+"authorizer_server_port", pn,authorizer_server_port, 2771);
    set_cfg_str(m,      prefix+"authorizer_server_ip", pn, authorizer_server_ip, "tusovka.tomsk.ru");
    set_cfg_str(m,      prefix+"auth_nick", pn,auth_nick, "BOS");
    set_cfg_str(m,      prefix+"auth_password", pn,auth_password, "kall");

    set_cfg_i(m,	prefix+"poll_timeout_usec", pn,poll_timeout_usec, 20000);

    set_cfg_i(m,	prefix+"ping_timeout_sec", pn,ping_timeout_sec, 10);
    set_cfg_i(m,	prefix+"pong_kill_timeout_sec", pn,pong_kill_timeout_sec, 10);
    set_cfg_i(m,	prefix+"login_timeout_sec", pn,login_timeout_sec, 20);

}
void _cs_client::do_auth()
{
    M_LOCK(ccdmx);//PGLR(cs_client,u,__U);
    ccd->m_target=__LOGIN;
    ccd->m_state=NOT_CONNECTED;
    ccd->auth_time=time(NULL);
}
_cs_client::~_cs_client()
{
    delete ccd;
}
void _cs_client::on_disconnect(const string& reason)
{
    MUTEX_INSPECTOR;
    logErr2("on_disconnect '%s'  %s",reason.c_str(),_DMI().c_str());
    do_auth();
}
void _cs_client::on_socket_create(int sock)
{

}
