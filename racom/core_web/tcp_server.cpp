#include "stdafx.h"
#include <unistd.h>
#include "tcp_server_data.h"
#include "tcp_server.h"

#include <errno.h>
#include <sys/stat.h>
#ifndef WIN32
#include <arpa/inet.h>
#endif
#ifdef WIN32
#include <process.h>
#include <time.h>
#endif
#ifdef WIN32
#define snprintf _snprintf
#endif
#include "PTR.h"
#include "str_lib.h"
#include "tcp_stats.h"
#ifndef WIN32
#include <sys/time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#endif
#include <sys/types.h>

using namespace std;
void on_socket_create(int sock);
void on_socket_close(int sock);

void  log_start_thread(const std::string &n);
tcp_server_data::tcp_server_data(
)
        : asocket(-1)


{
    handlers_count=0;
    handlers_busy=0;
}
tcp_server_data::~tcp_server_data()
{
}

void tcp_server::start(const string& pn,const string& prefix,map<string,string>&m)
{
    ;
    load_config(pn,prefix,m);
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;

    sa.sin_port = htons(tcpdata->listen_port.get());

    {
        if (tcpdata->listen_ip=="INADDR_ANY") sa.sin_addr.s_addr = INADDR_ANY;
        else sa.sin_addr.s_addr = inet_addr(tcpdata->listen_ip.get().c_str());
    }

    int sock=::socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock==-1) {
        char s[200];
#ifdef DEBUG
        snprintf(s,sizeof(s)-1,"tcp_server::start() - socket() failed %s %s %d",strerror(errno),__FL__);
#else
        snprintf(s,sizeof(s)-1,"Server: socket() failed %s",strerror(errno));
#endif
        throw cError(cError::E_FATAL,s);
    }
    tcpdata->asocket=sock;
    {
        ;
        int i = 1;
        {
            ;
            i=setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char *)&i,sizeof(i));
            
        }
        while (bind (sock,(struct sockaddr *) &sa, sizeof (sa)) == -1)
        {
            ;

            char s[100];
            {
#ifdef DEBUG
                snprintf(s,sizeof(s)-1,"tcp_server::start() - bind() failed: %s %s %d",strerror(errno),__FL__);
#else
                snprintf(s,sizeof(s)-1,"Server: bind() failed: %s",strerror(errno));
#endif
            }
            logErr2("%s %s:%d", s,inet_ntoa(sa.sin_addr),htons(sa.sin_port));
            /*            if(bind_error_is_fatal)
                        {
                            exit(1);
                        }*/
            {
                sleep(1);
            }
            
        }
        logErr2("%s binded to %s:%d", server_name().c_str(),inet_ntoa(sa.sin_addr),htons(sa.sin_port));
        if (listen(sock,128)==-1) {
            char s[200];
#ifdef DEBUG
            snprintf(s,sizeof(s)-1,"tcp_server::start() - listen() failed: %s %s %d",strerror(errno),__FL__);
#else
            snprintf(s,sizeof(s)-1,"Server: listen() failed: %s",strerror(errno));
#endif
            //exit(1);
            throw cError(cError::E_FATAL,s);
        }
        
    }
    create_thread(listener,server_name()+"tcp listener");

    
}
tcp_server::tcp_server()
        :tcpdata(new tcp_server_data())
{
}
tcp_server::~tcp_server()
{
#ifdef WIN32
    ::closesocket(tcpdata->asocket);
#else
    ::shutdown(tcpdata->asocket,SHUT_RDWR);
    ::close(tcpdata->asocket);
#endif
    on_socket_close(tcpdata->asocket);
    delete tcpdata;
}


#ifdef WIN32
typedef int socklen_t;
#endif




class st_THREAD_BUSY
{
    /*
    stack based class to calculated currently runned handlers

    constructor: increment serv->tcpdata->handlers_busy
    destructor: decrement serv->tcpdata->handlers_busy
    */
    tcp_server *serv;
    pthread_t self;
public:
    st_THREAD_BUSY(tcp_server *s,pthread_t sf)
    {
        serv=s;
        self=sf;
        ++serv->tcpdata->handlers_busy;
    }
    ~st_THREAD_BUSY()
    {
        --serv->tcpdata->handlers_busy;
    }
};


void *tcp_server::handler(void *pr)
{

    tcp_server *srv=(tcp_server*)pr;
    string thread_name=((tcp_server *) pr)->server_name()+" tcp_server::handler";
    log_start_thread(thread_name);
    pthread_t self = pthread_self();
    while (1) {
        try {

            PTR_getter <c_socket> sok(NULL);
            /*
            what while not accepted connection available
            */
#ifdef WIN32
            while (!srv->tcpdata->conn_list.extract_first(sok)) {
                if (srv->USLEEP(srv->tcpdata->accept_handler_timeout_usec))
                    return NULL;
            }
#else
            while (!srv->tcpdata->conn_list.try_extract_first(sok)) {
                if (srv->USLEEP(srv->tcpdata->accept_handler_timeout_usec))return NULL;
            }
#endif




            if (sok) {

                sockaddr_in ip;
                string ips;
                {
                    PGLW(c_socket, s,sok);
                    ip=s->peer_address;
                    ips=s->peer_ipaddress;
                }
                {
                    if (!srv->validate_peer_ip_address(ip))
                    {
                        continue;
                    }

                }
                tcp_server_connection * connection=(tcp_server_connection *)srv->new_connection(sok);
                connection->peer_address=ip;
                connection->tcp_peer_ipaddress=ips;

                {
                    /*
                    mark thread as busy
                    */
                    st_THREAD_BUSY kall_mazafaka_AAAAAAA(srv, self);
                    try {
                        /*
                        call virtual inherited function
                        */
                        connection->process_tcp();
                    }
                    STDCATCHS("tcpserver handler STDCATCHS");
                }	// if(connection->connected())
                delete connection;
            }	// if(connection)
        }
        STDCATCHS("tcp server handler");
    }			// while(1)

}


static bool readable_fd(int fd)
{
    int iii;
    {


        if (fd==-1)return false;
        fd_set rdfs;	/*for select */
        FD_ZERO(&rdfs);
        FD_SET(fd, &rdfs);
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        iii = select(fd + 1, &rdfs, NULL, NULL, &tv);
        if (iii!=-1)
            return FD_ISSET(fd, &rdfs);
    }
    if (iii == -1) {
        return false;
    }
    return false;

}

void *tcp_server::listener(void *pr)
{

    tcp_server *srv=(tcp_server*)pr;

    string thread_name=srv->server_name()+" tcp_server::listener";
    log_start_thread(thread_name);

    while (1) {
//        if(srv->tcpdata->asocket==-1) return NULL;
        try {
            sockaddr_in sa;
            int len = sizeof(sa);
            PTR_getter<c_socket> __nsock(NULL);

            while (!readable_fd(srv->tcpdata->asocket))
            {
                if (srv->USLEEP(srv->tcpdata->listener_timeout_usec))return NULL;
            }

            int ns = accept(srv->tcpdata->asocket,(sockaddr *) &sa, (socklen_t *) &len);

            if (ns==-1)
            {
                logErr2("accept socket: %s",strerror(errno));
                return NULL;
            }

#ifdef WIN32
            u_long f = 1;
            int r=ioctlsocket(ns, FIONBIO, &f);
#else
            int f = 1;
            int r=ioctl(ns, FIONBIO, &f);
#endif
            if (r==-1)
            {
                logErr2("ioctl: %s",strerror(errno));
            }

            int val=0x8000;
            if (setsockopt(ns,SOL_SOCKET,SO_RCVBUF,(char*)&val,sizeof(val)))
            {
                DBG(logErr2("setsockopt failed %s %d (%s)",__FILE__,__LINE__,strerror(errno)));
            }
            val=0x8000;
            if (setsockopt(ns,SOL_SOCKET,SO_SNDBUF,(char*)&val,sizeof(val)))
            {
                DBG(logErr2("setsockopt failed %s %d (%s)",__FILE__,__LINE__,strerror(errno)));
            }
            on_socket_create(ns);

            if (ns!=-1)
            {
                c_socket *s=new c_socket(ns);
                memcpy(&s->peer_address,&sa,sizeof(s->peer_address));
                s->peer_ipaddress = sockaddr_to_string(s->peer_address.sin_addr.s_addr);

                __nsock=s;
                ++tcp_total_accepted_connections;
            }


            if (__nsock) {
                {
                    /*
                    add accepted connection into conn_list
                    */
                    srv->tcpdata->conn_list.push_back(__nsock);
                }
                /*
                if free handler available do nothing
                esle create additional handler
                */
                bool found_free = (srv->tcpdata->handlers_count.get()-srv->tcpdata->handlers_busy.get()>0);

                if (!found_free) {
                    if (srv->tcpdata->max_number_of_accept_handlers.get() == 0 || srv->tcpdata->handlers_count.get() < (int)srv->tcpdata->max_number_of_accept_handlers) {
                        srv->create_thread(handler,srv->server_name()+" tcp handler");
                        ++srv->tcpdata->handlers_count;
                    }
                }
            }
            else
            {

            }
        }
        STDCATCHS("tcp_server__listener STDCATCHS");
    }
    return NULL;
}

m_var<bool> TCP_enabled(true);

void tcp_server::load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{
    set_cfg_str(m,	prefix+"listen_ip", pn,tcpdata->listen_ip, "INADDR_ANY");
    set_cfg_ishort(m,	prefix+"listen_port", pn,tcpdata->listen_port, 80);
    set_cfg_i(m,	prefix+"accept_handler_timeout_usec", pn,tcpdata->accept_handler_timeout_usec,20000);
    set_cfg_i(m,	prefix+"listener_timeout_usec", pn,tcpdata->listener_timeout_usec,20000);
    set_cfg_i(m,	prefix+"max_number_of_accept_handlers", pn,tcpdata->max_number_of_accept_handlers,0);

}
