#include "stdafx.h"
#include "commonError.h"
#include "str_lib.h"
#include "bos_client.h"

#ifndef WIN32
#include <sys/timeb.h>
#include <netdb.h> 
#endif
#include "RTYPES_CORE.h"
#ifdef WIN32
#include <malloc.h>
#endif
#include "RTYPES_CORE.h"
#include <errno.h>
#include "RTYPES_CORE.h"
#include "rijndael.h"
#include "st_rsa.h"
#include "c_conn.h"
#include "M_DEQUE.h"
#include "oscar_client.h"
#include "bos_client_interface.h"

m_var <std::string> g_bosHostname;
m_var <int> g_bosPort;



void dump_traf_incoming(const std::string& bb);
void dump_traf_outgoing(const std::string& bb);



enum State
{ NOT_CONNECTED=0,

  AUTH_AWAITING_CONN_ACK=2,
  AUTH_AWAITING_AUTH_REPLY=3,
  BOS_AWAITING_CONN_ACK=4,
  BOS_LOGGED_IN=6,
  AUTH_CONNECTED=12
};
enum Target
{
    __LOGIN=0,
    SLEEPING=2,
};
struct __packet_F2
{
	const char* getclassname()const {return "__packet_F2";}
    __packet_F2():immed(false),family(0),subtype(0){}
    bool immed;
    int family;
    int subtype;
    std::string data;
};
out_oscar_buffer & operator<< (out_oscar_buffer& b,const __packet_F2 &s);
oscar_buffer & operator>> (oscar_buffer& b,  __packet_F2 &s);

out_oscar_buffer & operator<< (out_oscar_buffer& b,const enc_string &s);
oscar_buffer & operator>> (oscar_buffer& b,  enc_string &s);




class bos_client_interface;



struct bc_data
{
	const char* getclassname()const {return "bc_data";}

    bc_data(m_var<std::string>&ip,unsigned int &port);
    State m_state;
    Target m_target;
    void set_state(const State &s);
    void set_target(const Target &s);
    State get_state()const {return m_state;}
    Target get_target()const {return m_target;}
    std::map<std::string,std::string> login_data;
    std::deque<__packet_F2*> _sio_out_packets;
    std::map<int,std::pair<int/*subtype*/,std::string/*buffer*/> > req_responses;
    std::map<int, time_t> unhandled_reqs;
    std::string out_buffer;
    st_rsa server_rsa;
    time_t last_ping_time;
    time_t last_pong_time;
    unsigned int bos_session_id;
    m_var<std::string>& m_authorizerHostname;
    unsigned int& m_authorizerPort;
    std::string m_bosHostname;
    unsigned short m_bosPort;
    unsigned char rjKey[RIJNDAEL_KEYSIZE];
    unsigned char rjIV_in[RIJNDAEL_BLOCKSIZE];
    unsigned char rjIV_out[RIJNDAEL_BLOCKSIZE];
    RIJNDAEL_context rjctx_in;
    RIJNDAEL_context rjctx_out;
    std::string rjDecode(const enc_string & in);
    enc_string  rjEncode(const std::string &in);
    time_t auth_time;
    void cleanup();

};

void bc_data::cleanup()
{
    login_data.clear();
    _sio_out_packets.clear();
    req_responses.clear();
    unhandled_reqs.clear();
    out_buffer.clear();
    
    last_pong_time=time(NULL);
    last_ping_time=time(NULL);
    memset(rjKey,0,sizeof(rjKey));
    memset(&rjctx_in,0,sizeof(rjctx_in));
    memset(&rjctx_out,0,sizeof(rjctx_out));
    memset(rjIV_in,0,sizeof(rjIV_in));
    memset(rjIV_out,0,sizeof(rjIV_out));
    m_state = NOT_CONNECTED;
    m_target=SLEEPING;
    bos_session_id=0;
    auth_time=time(NULL);

}

bc_data::bc_data(m_var<std::string>&ip,unsigned int &port):m_authorizerHostname(ip),m_authorizerPort(port)
{
    cleanup();
}
void bos_client::on_socket_create(int sock)
{
    api->on_socket_create(sock);
}
bos_client::~bos_client()
{
    delete bcd;
}

void bc_data::set_state(const State &s)
{
    m_state=s;
    if(s==NOT_CONNECTED){
        bos_session_id=0;
    }
}
void bc_data::set_target(const Target &s)
{
    m_target=s;
}

std::string bc_data::rjDecode(const enc_string & in)
{
    if(in.buf.size()%RIJNDAEL_BLOCKSIZE){ DBG(logErr2("invalid buffer size %s %d",__FILE__,__LINE__));
        throw CommonError("invalid buffer size");
    }
    unsigned char *out=(unsigned char *)malloc(in.buf.size()+1);
    std::string r;
    try{
        block_decrypt(&rjctx_in, (const unsigned char*)in.buf.data(), in.buf.size(),out, rjIV_in);
        r=std::string((char*)out,in.original_size);
        free(out);
    }catch(...){logErr2("catchd %s %d",__FILE__,__LINE__);}
    return r;
}
enc_string  bc_data::rjEncode(const std::string &in)
{
    enc_string r;
    size_t len=in.size();
    if(len%RIJNDAEL_BLOCKSIZE) len+=RIJNDAEL_BLOCKSIZE-(len%RIJNDAEL_BLOCKSIZE);
    if(len%RIJNDAEL_BLOCKSIZE) throw CommonError("if(len%16) ");
    unsigned char *b=(unsigned char *)malloc(in.size()+RIJNDAEL_BLOCKSIZE);
    unsigned char *out=(unsigned char *)malloc(len);
    try{
        memcpy(b,in.data(),in.size());
        for(size_t ii=in.size();ii<len;ii++)
            b[ii]=rand();
        block_encrypt(&rjctx_out, b, len,out, rjIV_out);
        r.buf=std::string((char*)out,len);
        r.original_size=in.size();
    }catch(...)
	{
	logErr2("catchd %s %d",__FILE__,__LINE__);
	}
    if(b) free(b);
    if(out) free(out);
    return r;
}
out_oscar_buffer & operator<< (out_oscar_buffer& b,const __packet_F2 &s)
{
    b<<s.family<<s.subtype<<s.data;  return b;
}
oscar_buffer & operator>> (oscar_buffer& b,  __packet_F2 &s)
{
    b>>s.family>>s.subtype>>s.data;  return b;
}

enc_string bos_client::encode_cs(const std::string&s)
{
    enc_string es;
    {
        M_LOCK(bcdmx);
        es=bcd->server_rsa.public_encrypt(s);
    }
    return es;

}
std::string bos_client::gen_des_key()
{

#ifdef WIN32
    srand(time(NULL));
#else
    timeb tb;
    ftime(&tb);
    srand(tb.time*tb.millitm);
#endif
    char b[RIJNDAEL_KEYSIZE];
    for(unsigned i=0;i<RIJNDAEL_KEYSIZE;i++)
    {
        unsigned n=rand()%10;
        for(unsigned j=0;j<n;j++) rand();
        b[i]=rand();
    }
    return std::string(b,RIJNDAEL_KEYSIZE);
}
void bos_client::sio()
{

    MUTEX_INSPECTOR;
    while(1)
    {
        try{
            std::string send_buf;
            { 
                M_LOCK(bcdmx);
                send_buf+=bcd->out_buffer;
                bcd->out_buffer.clear();
            }
            if(!send_buf.size())
            {
                prepare_send_buffer_from_packets();

            }
            int ret=0;
            if(send_buf.size())
            {
                reply(send_buf);
#ifdef DUMP_TRAF
                dump_traf_outgoing(send_buf);
#endif
            }
		}
		STDCATCHS("sio_handler");
		{
			MUTEX_INSPECTORS("SLEEP");
			if(USLEEP(sio_handler_timeout_usec))return;
		}
    }
}
void *bos_client::T_run_sio_handler(void *pr)
{
	//MUTEX_INSPECTOR;
    bos_client *bcid=(bos_client*)pr;
    if(!bcid){logErr2("KA LLsrall %s %d",__FILE__,__LINE__);return NULL;}
    log_start_thread("bos client io");
    {
        try{
	    bcid->sio();
	    logErr2("sio_handler exiting");
        }
        catch(CommonError e)
        {
            logErr2("%s",e.what());
            logErr2("catched %s %d",__FILE__,__LINE__);
        }
        catch(...)
        {
			logErr2("catchd %s %d",__FILE__,__LINE__);
          //  logErr2("catched %s %d",__FILE__,__LINE__);
          //  logErr2("unknow exception");
        }
    }


    return NULL;
}

void *bos_client::T_run_poll_handler(void *pr)
{
	//MUTEX_INSPECTOR;
    log_start_thread("bos client poller");
    bos_client *bcid=(bos_client*)pr;
    if(!bcid){logErr2("KA LLsrall %s %d",__FILE__,__LINE__);return NULL;}

    {
        try{

            bcid->Poll();
	    logErr2("poll_handler exiting");
        }
        catch(CommonError e)
        {
            logErr2("%s",e.what());
            logErr2("catched %s %d",__FILE__,__LINE__);
        }
        catch(...)
        {
#ifndef WIN32
            logErr2("catched %s %d",__FILE__,__LINE__);
            logErr2("unknow exception");
#endif
        }
    }


    return NULL;
}
void bos_client::prepare_send_buffer_from_packets()
{
    MUTEX_INSPECTOR;
    std::deque <__packet_F2*> dp;
    unsigned int bos_session_id;
    {
        
        M_LOCK(bcdmx);
        bos_session_id=bcd->bos_session_id;

    }
    if(bos_session_id!=0)
    {
        bool immed=false;
        M_LOCK(bcdmx);
        std::deque <__packet_F2*> &d=bcd->_sio_out_packets;
        for(unsigned i=0;i<d.size();i++)
        {
            if(d[i]->immed) immed=true;
        }
        if(!immed && d.size()<120) return;
        dp=bcd->_sio_out_packets;
        bcd->_sio_out_packets.clear();

    }
    if(dp.size())
    {
        
        out_oscar_buffer bs;
        bs<<dp.size();
        for(unsigned i=0;i<dp.size();i++)
        {
            bs<<*dp[i];
			delete dp[i];
        }
        F_outV2 o(CHANNEL_5);

        enc_string es;
        
        {
            M_LOCK(bcdmx);
            es=bcd->rjEncode(bs.as_string());
        }
        o<<es;
        o.calc_size();
        client_send(o);
    }
}

void bos_client::send_request_to_redirector()
{
	MUTEX_INSPECTOR;
    F_outV2 b(CHANNEL_1);
    b<<5;
    b.calc_size();
    client_send(b);
}


void bos_client::send_login_LK()
{
	MUTEX_INSPECTOR;
    out_oscar_buffer b;
    {
        M_LOCK(bcdmx);
        b<<bcd->login_data;
    }
    send_packet_to_cs2(true,FAM_LOGIN,TYPE_LOGIN_SEND_AUTH2_02,b);
}

void bos_client::send_to_bos_des_key()
{
	MUTEX_INSPECTOR;
    F_outV2 b(CHANNEL_1);
    b<<3;
    std::string key=gen_des_key();
    {
        M_LOCK(bcdmx);
        memcpy(bcd->rjKey,key.data(),key.size());
        memset(bcd->rjIV_in,0,sizeof(bcd->rjIV_in));
        memset(bcd->rjIV_out,0,sizeof(bcd->rjIV_out));
        bcd->rjctx_in.mode=MODE_CFB;
        bcd->rjctx_out.mode=MODE_CFB;
        rijndael_setup(&bcd->rjctx_in, RIJNDAEL_KEYSIZE, bcd->rjKey);
        rijndael_setup(&bcd->rjctx_out, RIJNDAEL_KEYSIZE, bcd->rjKey);


    }
    enc_string es=encode_cs(key);
    b<<es.original_size;
    b<<es.buf;
    b.calc_size();
    client_send(b);
}

void bos_client::parse_ch1(oscar_buffer & b)
{
MUTEX_INSPECTOR;
    
    Target xxm_target;
    State xxm_state;
    {
        M_LOCK(bcdmx);
        xxm_target=bcd->get_target();
        xxm_state=bcd->get_state();
    }
    if((xxm_target == __LOGIN) && (xxm_state == AUTH_AWAITING_CONN_ACK||xxm_state == AUTH_CONNECTED))
    {
        unsigned int unknown;
        b>>unknown;

        {
            M_LOCK(bcdmx);
            bcd->set_state(AUTH_AWAITING_AUTH_REPLY);
        }
        send_request_to_redirector();
        return;
    }
    else if((xxm_target == __LOGIN) && xxm_state == BOS_AWAITING_CONN_ACK )
    {
//		unsigned int unknown;
//		b>>unknown;
        std::string server_rsa_pub_key;
        b>>server_rsa_pub_key;
		//logErr2("server_rsa_pub_key %s", bin2hex(server_rsa_pub_key).c_str());

        {
            M_LOCK(bcdmx);
            bcd->server_rsa.pub_key_set(server_rsa_pub_key);
            bcd->server_rsa.init_from_pub_key();

        }
		//logErr2("send_to_bos_des_key();");
        send_to_bos_des_key();
        if(xxm_target == __LOGIN) send_login_LK();
        return;

    }
    else {
        DBG(logErr2("--Error: Unknown packet received on channel 0x01 %s", bin2hex(std::string((char*)b._data(),b.size()),10).c_str()));
    }

}
void bos_client::parse_ch4(oscar_buffer & b)
{
	MUTEX_INSPECTOR;

    Target xxm_target;
    State xxm_state;
    {
        M_LOCK(bcdmx);
        xxm_target=bcd->get_target();
        xxm_state=bcd->get_state();
    }
    if (xxm_state == AUTH_AWAITING_AUTH_REPLY) {

        std::map<std::string,std::string> m;
        b>>m;
        if(m.count("bos"))
        {
			MUTEX_INSPECTOR;
            std::string bos=m["bos"];
			
            size_t d = bos.find(':');
            if (d != -1) {
                {
					MUTEX_INSPECTOR;
                    M_LOCK(bcdmx);
                    bcd->m_bosHostname = bos.substr(0, d);
                    bcd->m_bosPort = atoi(bos.substr(d + 1).c_str());
					g_bosHostname=bcd->m_bosHostname;
					g_bosPort=bcd->m_bosPort;
                }
            }
            else
                throw CommonError("return str " + bos);

        }
        std::string host;unsigned short port;
        {
			MUTEX_INSPECTOR;
            M_LOCK(bcdmx);
            host=bcd->m_bosHostname;
            port=bcd->m_bosPort;
            bcd->set_state(BOS_AWAITING_CONN_ACK);
        }
        try{
			MUTEX_INSPECTOR;
            client_connect(host.c_str(),port);
        }
		catch(CommonError e)
		{
			logErr2("catched %s  %s %d",e.what(),__FILE__,__LINE__);
		}
		catch(...)
        {
            logErr2("catched %s %d",__FILE__,__LINE__);
        }
        return;
    }
}
void bos_client::parse_ch5(oscar_buffer & b)
{
	MUTEX_INSPECTOR;
	//logErr2("bos_client::parse_ch5");

    enc_string s_enc;
    std::string decbuf;
    b>>s_enc;
    {
        M_LOCK(bcdmx);
        decbuf=bcd->rjDecode(s_enc);
    }

    oscar_buffer nb(decbuf.data(),decbuf.size());
    int fam,subt;
    std::string pkt;
    int N;
    nb>>N;
    for(int i=0;i<N;i++)
    {
        nb>>fam>>subt>>pkt;
        oscar_buffer in_b(pkt.data(),pkt.size());
        if(fam==FAM_LOGIN)
        {
            if(subt==TYPE_AUTH_OK_06)
            {
				//logErr2("subt==TYPE_AUTH_OK_06");
                {
                    M_LOCK(bcdmx);
                    bcd->set_state(BOS_LOGGED_IN);
                }


                std::map<std::string,std::string> m;
                in_b>>m;
                api->on_login_ok(m);
                return;
            }
            else if(subt==TYPE_AUTH_FAILED_07)
            {
				//logErr2("subt==TYPE_AUTH_FAILED_07");
                std::map<std::string,std::string> m;
                in_b>>m;
                api->on_login_failed(m);
                return;
            }
        }
        else if(fam==FAM_REQUEST_2)
        {
			//logErr2("fam==FAM_REQUEST_2");
            int id;
            std::string data;
            in_b>>id;
            in_b.Unpack(data,in_b.remains());
            {
                M_LOCK(bcdmx);
                bcd->req_responses[id]=std::make_pair(subt,data);
            }
            return;

        }
        else if(fam==FAM_DATA_EVENT_0)
		{
			//logErr2("fam==FAM_DATA_EVENT_0");
            api->on_data_event(subt,in_b);
		}
        else logErr2("Undefined FAM 0x%02x",fam);
    }
}

void bos_client::parse_ch6(oscar_buffer & b)
{
MUTEX_INSPECTOR;

    DBG(logErr2("inbval pkt %s %d",__FILE__,__LINE__));

}
void bos_client::parse_ch3(oscar_buffer & b)
{
MUTEX_INSPECTOR;

    DBG(logErr2("Error void parse_ch3(oscar_buffer & b)"));
}

void bos_client::Poll()
{
	MUTEX_INSPECTOR;
	while(1)
	{
		{
			MUTEX_INSPECTORS("SLEEP");
			if(USLEEP(poll_handler_timeout_usec))return;
		}

		try {

			Target xxm_target;
			State xxm_state;
			bool need_ping=false;
			bool need_pong_kill=false;
			bool need_auth_timeout_kill=false;
			{
				M_LOCK(bcdmx);
				xxm_target = bcd->get_target();
				xxm_state = bcd->get_state();
				if(time(NULL)-bcd->last_ping_time>ping_timeout_sec && xxm_state==BOS_LOGGED_IN)
				{
					need_ping=true;
					bcd->last_ping_time=time(NULL);
				}
				if(time(NULL)-bcd->last_pong_time>pong_kill_timeout_sec && xxm_state==BOS_LOGGED_IN)
				{
					need_pong_kill=true;
					bcd->last_pong_time=time(NULL);
					logErr2("Killed due PONG timeout");


				}
				if(xxm_state==BOS_LOGGED_IN && __LOGIN==xxm_target)
				{
					//logErr2("set bos_client auth time");
					bcd->auth_time=time(NULL);
				}
				if(xxm_state!=BOS_LOGGED_IN && __LOGIN==xxm_target&&time(NULL)-bcd->auth_time>login_timeout_sec)
				{
					logErr2("set need_auth_timeout_kill true");
					need_auth_timeout_kill=true;
					bcd->auth_time=time(NULL);

				}    
			}
			if(need_pong_kill)
			{
				logErr2("call pong_kill");
				break_connect("pong_kill");
				continue;
			}
			if(need_auth_timeout_kill)
			{
				logErr2("call login_timeout_kill");
				break_connect("login_timeout_kill");
				continue;
			}
			if(need_ping && xxm_state==BOS_LOGGED_IN)
			{
				FS_outV2 o(CHANNEL_2,FAM_OTHER,TYPE_PING_09);
				o.calc_size();
				client_send(o);
			}
			if ((xxm_target == __LOGIN) && (xxm_state == NOT_CONNECTED))
			{
				//logErr2("make connection to authorizer");
				{
					std::string host;
					unsigned short __port;
					{
						M_LOCK(bcdmx);
						host = bcd->m_authorizerHostname.get();
						__port = bcd->m_authorizerPort;
						int n=0;
					}
					if(xxm_state==NOT_CONNECTED)
					{
						try{

							client_connect( host.c_str(), __port);
						}catch(...)
						{
							DBG(logErr2("catched here %s %d",__FILE__,__LINE__));
							logErr2("catched %s %d",__FILE__,__LINE__);
						}
						{
							//logErr2("set_state(AUTH_CONNECTED)");
							M_LOCK(bcdmx);
							bcd->set_state(AUTH_CONNECTED);
							xxm_state = AUTH_CONNECTED;
						}
					}
					srand(time(0));
					{
						//logErr2("set_state (AUTH_AWAITING_CONN_ACK)");
						M_LOCK(bcdmx);
						bcd->set_state (AUTH_AWAITING_CONN_ACK);
						xxm_state = AUTH_AWAITING_CONN_ACK;

					}
				}
			}


		}
		catch(socketError e){
			MUTEX_INSPECTOR;
			logErr2("catched %s %d",__FILE__,__LINE__);
			on_disconnect((std::string)"catch "+e.what());
		}
		catch(CommonError e){
			MUTEX_INSPECTOR;
			DBG(logErr2("catched CommonError %s %d %s",__FILE__,__LINE__,e.what()));
			on_disconnect((std::string)"catch "+e.what());
		}
		catch(...) {
			MUTEX_INSPECTOR;
			logErr2("catched %s %d",__FILE__,__LINE__);
			int n=0;
			on_disconnect("catch ...");
		}
	}
}



void bos_client::parse_ch2(oscar_buffer& in_b)
{
MUTEX_INSPECTOR;

    
    unsigned int family;
    unsigned int subtype;
    in_b>>family>>subtype;

    if(family==FAM_LOGIN && subtype==TYPE_LOGIN_SET_SESSION_ID_05)
    {
		unsigned int s;
		in_b>>s;
		{
			M_LOCK(bcdmx);
			bcd->bos_session_id=s;

		}
		//logErr2("family==FAM_LOGIN && subtype==TYPE_LOGIN_SET_SESSION_ID_05 bos_session_id %d",s);
    }
    if(family==FAM_OTHER && subtype==TYPE_PONG_0A)
    {
		//logErr2("family==FAM_OTHER && subtype==TYPE_PONG_0A");
        M_LOCK(bcdmx);
        bcd->last_pong_time=time(NULL);
    }
}


void bos_client::client_send( out_oscar_buffer & b)
{
	MUTEX_INSPECTOR;
    
        M_LOCK(bcdmx);
        bcd->out_buffer+=b.as_string();
    
}




void bos_client::on_disconnect(const std::string& reason)
{
	MUTEX_INSPECTOR;

	logErr2("bos_client::on_disconnect");
    State state;
    Target target;
    {
        M_LOCK(bcdmx);
        state=bcd->get_state();
        target=bcd->get_target();
    }
    if(target==__LOGIN && (state==BOS_LOGGED_IN || state==BOS_AWAITING_CONN_ACK))
    {
            M_LOCK(bcdmx);
            bcd->set_state(NOT_CONNECTED);
            bcd->set_target(SLEEPING);
        
    }

    api->on_disconnect(reason);
}
void bos_client::send_packet_to_cs(bool immed,int msg,const out_oscar_buffer & b)
{
    __packet_F2 *p=new __packet_F2;
    p->family=0;
    p->subtype=msg;
    p->data=b.as_string();
    p->immed=immed;
    {
        M_LOCK(bcdmx);
        bcd->_sio_out_packets.push_back(p);
    }
}
void bos_client::send_packet_to_cs(bool immed,int msg)
{
	__packet_F2 *p=new __packet_F2;
	p->family=0;
	p->subtype=msg;
	std::string ss;
	p->data=ss;
	p->immed=immed;
	{
		M_LOCK(bcdmx);
		bcd->_sio_out_packets.push_back(p);
	}
}
void bos_client::send_packet_to_cs(bool immed,int msg,const std::string & b)
{
    __packet_F2 *p=new __packet_F2;
    p->family=0;
    p->subtype=msg;
    p->data=b;
    p->immed=immed;
    {
        M_LOCK(bcdmx);
        bcd->_sio_out_packets.push_back(p);
    }
}
void bos_client::send_packet_to_cs2(bool immed,int family,int subtype,const out_oscar_buffer & b)
{
    __packet_F2 *p=new __packet_F2;
    p->family=family;
    p->subtype=subtype;
    p->data=b.as_string();
    p->immed=immed;
    {
        M_LOCK(bcdmx);
        bcd->_sio_out_packets.push_back(p);
    }
}
void bos_client::send_packet_to_cs2(bool immed,int family,int subtype,const std::string & b)
{
    __packet_F2 *p=new __packet_F2;
    p->family=family;
    p->subtype=subtype;
    p->data=b;
    p->immed=immed;
    {
	M_LOCK(bcdmx);
        bcd->_sio_out_packets.push_back(p);
    }
}



static m_var<int> req_id;



bool bos_client::send_request(int cmd_code,std::string &in,const std::string & out, time_t timeout)
{
    out_oscar_buffer b;
    int id=++req_id;
    b<<id;

    b.Pack(out);

    __packet_F2 *p=new __packet_F2;
    p->family=FAM_REQUEST_2;
    p->subtype=cmd_code;
    p->data=b.as_string();
    p->immed=true;
    {
        M_LOCK(bcdmx);
        bcd->_sio_out_packets.push_back(p);
    }

    time_t t=time(NULL);
    while(1)
    {
		MUTEX_INSPECTOR;
        if(time(NULL)-t>timeout){
            return false;
        }
        {
			MUTEX_INSPECTORS("SLEEP");
            if(USLEEP(10000)) return false;
        }
        {
            M_LOCK(bcdmx);
            if(bcd->req_responses.count(id))
            {
                std::pair<int,std::string> pin=bcd->req_responses[id];
  
				if(pin.first!=cmd_code)
                {
                    logErr2("pin.first!=cmd_cod");
                    return false;
                }
                in=pin.second;
                {
                    bcd->req_responses.erase(id);
                }
                return true;
            }
        }
    }
    return false;

}

bos_client::bos_client(bos_client_interface *_api):api(_api),bcd(new bc_data(authorizer_server_ip, authorizer_server_port)){}
void bos_client::do_auth(const std::map<std::string,std::string> &login_params)
{
	//logErr2("bos_client::do_auth");
	MUTEX_INSPECTOR;

	M_LOCK(bcdmx);
	bcd->auth_time=time(NULL);
	bcd->login_data=login_params;
	bcd->set_target(__LOGIN);
	bcd->set_state(NOT_CONNECTED);

}
void bos_client::start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{
    oscar_client::start(pn,prefix,m);
    load_config(pn,prefix,m);
    create_thread(T_run_sio_handler,"T_run_sio_handler");
    create_thread(T_run_poll_handler,"T_run_poll_handler");
    
}
void bos_client::load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{
    set_cfg_i(m,	prefix+"authorizer_server_port", pn,authorizer_server_port, 10000);
    set_cfg_i(m,	prefix+"sio_handler_timeout_usec", pn,sio_handler_timeout_usec, 10000);
    set_cfg_i(m,	prefix+"poll_handler_timeout_usec", pn,poll_handler_timeout_usec, 10000);
    set_cfg_i(m,	prefix+"ping_timeout_sec", pn,ping_timeout_sec, 10);
    set_cfg_i(m,	prefix+"pong_kill_timeout_sec", pn,pong_kill_timeout_sec, 60);
    set_cfg_i(m,	prefix+"login_timeout_sec", pn,login_timeout_sec, 5);
    set_cfg_str(m,	prefix+"authorizer_server_ip", pn,authorizer_server_ip, "tusovka.tomsk.ru");
    set_cfg_i(m,	prefix+"request_timeout_sec", pn,request_timeout_sec, 30);

}
void bos_client::do_disconnect()
{
	logErr2("bos_client::do_disconnect");
    oscar_client::do_disconnect();
    {
        M_LOCK(bcdmx);
        bcd->set_target(SLEEPING);
        bcd->set_state(NOT_CONNECTED);
    }	
        
}
std::string bos_client::get_bos_addr()
{
	M_LOCK(bcdmx);
	return bcd->m_bosHostname;
}
int bos_client::get_bos_port()
{
	M_LOCK(bcdmx);
	return bcd->m_bosPort;
}
void bos_client::cleanup()
{
    oscar_client::cleanup();
    {
        M_LOCK(bcdmx);
		bcd->cleanup();
    }
}
