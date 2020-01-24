#include "stdafx.h"
#include "errs.h"
#include "str_lib.h"
#ifndef WIN32
#include <sys/timeb.h>
#include <netdb.h>
#endif
#include "PTR.h"

#include "oscar_client.h"
#include "c_conn.h"
#ifndef WIN32
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include <errno.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void  log_start_thread(const std::string &n);


int S_recv(const PTR_getter<c_socket>&__S,void *buf, size_t len, int flags);
void dump_traf_incoming(const string& bb);
void dump_traf_outgoing(const string& bb);

struct oscar_client_data
{
    oscar_client_data();
    string in_buffer;
    bool isConnected();
    PTR_getter<c_socket> sock$;



};
oscar_client_data::oscar_client_data():sock$(NULL)
{
}

void *oscar_client::parse_handler(void *pr)
{
    log_start_thread("oscar_client parser");
    oscar_client *bcid=(oscar_client*)pr;
    if (!bcid) {
        logErr2("KALLsrall %s %d",__FILE__,__LINE__);
        return NULL;
    }
    while (1)
    {
        try {
            if (bcid->Parse())
            {
                logErr2("parse_handler exiting");
                return NULL;
            }
        }
        catch (cError e)
        {
            logErr2("%s",e.what());
            logErr2("catched %s %d",__FILE__,__LINE__);
        }
        catch (...)
        {
            logErr2("catched %s %d",__FILE__,__LINE__);
            logErr2("unknow exception");
        }
    }


    return NULL;
}
bool oscar_client::Recv()
{
    char recv_buf[4096];

    PTR_getter<c_socket> __SK(ocd->sock$);
    if (__SK)
    {
        int rret=0;
        rret=S_recv(__SK,recv_buf,sizeof(recv_buf),0);
        if (rret==-1)
        {
            ocd->sock$=NULL;
            on_disconnect("recv");
            return false;
        }

        if (rret>0)
        {
            {
                M_LOCK(ocdmx);
                ocd->in_buffer+=string(recv_buf,rret);
            }
#ifdef DUMP_TRAF
            dump_traf_incoming(string(recv_buf,rret));
#endif

        }
    }
    {
        if (USLEEP(recv_handler_timeout_usec))return true;
    }
    return false;

}
void *oscar_client::recv_handler(void *pr)
{

    oscar_client *bcid=(oscar_client*)pr;
    if (!bcid) {
        logErr2("KALLsrall %s %d",__FILE__,__LINE__);
        return NULL;
    }
    while (1)
    {
        try {
            if (bcid->Recv())
            {
                logErr2("recv_handler exiting");
                return NULL;
            }

        }
        catch (cError e)
        {
            logErr2("%s",e.what());
            logErr2("catched %s %d",__FILE__,__LINE__);
        }
        catch (...)
        {
            logErr2("catched %s %d",__FILE__,__LINE__);
            logErr2("unknow exception");
        }
    }


    return NULL;
}

void oscar_client::do_parse()
{
    try {
        while (1)
        {

            unsigned char start_byte, channel;
            string command;
            bool need_disconnect=false;
            {
                {
                    M_LOCK(ocdmx);
                    if (ocd->in_buffer.size()==0)return;
                    start_byte=ocd->in_buffer[0];
                }

                if (start_byte == OSCAR2_START_BYTE)
                {
                    M_LOCK(ocdmx);
                    if (ocd->in_buffer.size()<FLAP2_HEADER_SIZE)
                        return;
                    OSCAR2_DATA_LEN_T data_len;
                    memcpy(&data_len,ocd->in_buffer.data()+FLAP2_DATA_SIZE_OFFSET,sizeof(data_len));
                    memcpy(&channel,ocd->in_buffer.data()+FLAP2_CHANNEL_OFFSET,sizeof(channel));
                    int tl=FLAP2_HEADER_SIZE+data_len;
                    if (ocd->in_buffer.size()>=tl)
                    {
                        command=ocd->in_buffer.substr(FLAP2_HEADER_SIZE,data_len);
                        int bsz=ocd->in_buffer.size();
                        ocd->in_buffer=ocd->in_buffer.substr(tl,bsz-tl);
                    }
                    else return;
                }
                else  {
                    need_disconnect=true;
                }
                if (need_disconnect)
                {
                    DBG(logErr2("Invalid Start Byte on FLAP %d  %s %d",start_byte,__FILE__,__LINE__));
                    M_LOCK(ocdmx);
                    ocd->in_buffer.clear();
                }
                if (start_byte==OSCAR2_START_BYTE)
                {

                    oscar_buffer in_b(command.data(),command.size());
                    switch (channel) {
                    case 1:
                        parse_ch1(in_b);
                        break;
                    case 2:
                        parse_ch2(in_b);
                        break;
                    case 3:
                        parse_ch3(in_b);
                        break;
                    case 4:
                        parse_ch4(in_b);
                        break;
                    case 5:
                        parse_ch5(in_b);
                        break;
                    case 6:
                        parse_ch6(in_b);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
    STDCATCHS("Parse()");

}

bool oscar_client::Parse()
{
    do_parse();

    {
        if (USLEEP(parse_handler_timeout_usec))
            return true;
    }
    return false;
}
void oscar_client::client_connect( const char *host, unsigned short port)
{
    int __sock = ::socket(AF_INET, SOCK_STREAM, 0);
    if (__sock <= 0)
        throw cError("Couldn't create socket");
    struct sockaddr_in remoteAddr;
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(port);
    remoteAddr.sin_addr.s_addr = gethostname(host);


    while (1)
    {
        int res;
        {
            res=::connect(__sock,(const struct sockaddr *)&remoteAddr, sizeof(struct sockaddr));
        }
        if (res==-1)
        {
            logErr2("cant connect %s %d",host,port);
            break_connect("connect_failed");

            {
                sleep(1);
            }

            return;
        }
        else
        {
            logErr2("connected %s %d",host,port);
            {
                ocd->sock$=new c_socket(__sock);
            }
            break;
        }
        {
        }
    }

#ifdef WIN32
    u_long f = 1;
    int r=ioctlsocket(__sock, FIONBIO, &f);
#else
    int f = 1;
    int r=ioctl(__sock, FIONBIO, &f);
#endif
    if (r==-1)
    {
        logErr2("ioctl: %s",strerror(errno));
    }

    int val=0x8000;
    if (setsockopt(__sock,SOL_SOCKET,SO_RCVBUF,(char*)&val,sizeof(val)))
    {
        DBG(logErr2("setsockopt failed %s %d (%s)",__FILE__,__LINE__,strerror(errno)));
    }
    val=0x8000;
    if (setsockopt(__sock,SOL_SOCKET,SO_SNDBUF,(char*)&val,sizeof(val)))
    {
        DBG(logErr2("setsockopt failed %s %d (%s)",__FILE__,__LINE__,strerror(errno)));
    }
    on_socket_create(__sock);

}

void oscar_client::break_connect(const string& reason)
{
    PTR_getter<c_socket> __S(ocd->sock$);
    ocd->sock$=NULL;
    if (__S) {
        disconnect(__S);
    }
    on_disconnect(reason);


}
oscar_client::oscar_client(bool __start_parser):ocd(new oscar_client_data),start_parser(__start_parser) {}
oscar_client::~oscar_client() {
    delete ocd;
}


void oscar_client::reply(const string& buf)
{
    reply_socket(ocd->sock$,buf);
}
void oscar_client::start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{
    load_config(pn,prefix,m);

    if (start_parser)
        create_thread(parse_handler,"parse_handler");

    create_thread(recv_handler,"recv_handler");

}
void oscar_client::load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{
    set_cfg_i(m,	prefix+"parse_handler_timeout_usec", pn,parse_handler_timeout_usec, 10000);
    set_cfg_i(m,	prefix+"recv_handler_timeout_usec", pn,recv_handler_timeout_usec, 20);
    set_cfg_str(m,	prefix+"bind_ip", pn,bind_ip, "INADDR_ANY");

}
void oscar_client::do_disconnect()
{
    PTR_getter<c_socket> __S(ocd->sock$);
    ocd->sock$=NULL;
    if (__S) {
        disconnect(__S);
    }

}
