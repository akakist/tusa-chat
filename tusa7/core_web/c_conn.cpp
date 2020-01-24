#ifdef __GNUC__
#pragma implementation				// gcc: implement sql_udf.h
#endif

#include "stdafx.h"
#ifndef WIN32
#include <unistd.h>
#endif
#include <sys/types.h>
#ifndef WIN32
#include <sys/time.h>
#endif
#include "c_conn.h"
#include <stdio.h>
#include "tcp_stats.h"

#ifndef WIN32
#include <arpa/inet.h>
#endif
#include <set>
#include "str_lib.h"
using namespace std;

#include <map>
#include "st_stuff.h"
#include "tcp_sender.h"
#include "oscar_buffer.h"
#ifndef WIN32
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include <errno.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;


bool readable_abs(const PTR_getter<c_socket> &__S,int sec, int usec);
void on_socket_close(int sock);

void disconnect(const PTR_getter <c_socket> &__S)
{
    _mutex *m=NULL;
    int fd=-1;
    {
        PGLW(c_socket,s,__S);
        fd=s->get_socket_fd();
        on_socket_close(fd);
        if (fd!=-1)
        {
#ifdef WIN32
            ::closesocket(fd);
#else
//            ::shutdown(fd,SHUT_RDWR);
            ::close(fd);
#endif
        }
        s->set_socket_descr(-1);
    }
}

void c_socket::set_socket_descr(int s)
{
    m__sock=s;
}
void c_conn_cpp() {}
m_var<long long> uniq_id_gen(0);
c_socket::c_socket(int s): m__sock(s),timeout_sec(20),timeout_usec(0),base_container("c_socket"),recv0(0)
{
}
c_socket::~c_socket()
{
    try {
        if (m__sock!=-1)
        {
            //on_socket_close(m__sock);
#ifdef WIN32
            ::closesocket(m__sock);
#else
//            ::shutdown(m__sock,SHUT_RDWR);
            ::close(m__sock);
#endif
            m__sock=-1;
        }
    }
    catch (...) {}
}

bool c_socket::connected() const
{
    if (m__sock != -1) {
        return true;
    }
    return false;
}


int S_recv(const PTR_getter<c_socket>&__S,void *buf, size_t len, int flags)
{

    if (!readable(__S,0,0))return 0;
    if (!__S)
    {
        logErr2("if(!__S)");
        return -1;
    }


    {
        PGLW(c_socket,s,__S);

        int rds=s->rd_buf.size();
        if (rds)
        {
            if (len>=rds)
            {
                memcpy(buf,s->rd_buf.data(),rds);
                s->rd_buf.clear();
                return rds;
            }
            else
            {
                memcpy(buf,s->rd_buf.data(),len);
                s->rd_buf=s->rd_buf.substr(len,s->rd_buf.size()-len);
                return len;

            }
        }
    }
    char b[4096];
    int ret;
    bool need_disconnect=false;
    {
        {
            int __errno=0;
            {
                PGLW(c_socket,s,__S);
                int fd=s->get_socket_fd();
                if (fd==-1)
                {
                    //logErr2("if(fd==-1)");
                    return -1;
                }
                ret=::recv(fd,b, sizeof(b), flags);
                if (ret==-1)
                {
                    __errno=errno;
                    //logErr2("errno %d",__errno);
                }
                if (ret==0)
                {
                    s->recv0++;
                    if (s->recv0>100)need_disconnect=true;

                }
                else
                {
                    s->recv0=0;
                }

            }
            if (need_disconnect)
            {
                disconnect(__S);
                return -1;

            }
            bool need_close=false;
            if (ret==-1)
            {
                switch (__errno)
                {
                case EAGAIN:
                    break;
                default:
                    need_close=true;
                }

            }
            if (need_close)
            {
                //logErr2("disconnect(__S)");
                disconnect(__S);
                return -1;
            }
            {


                if (ret!=-1 && ret!=0)tcp_total_recv+=ret;
                if (__S)
                {
                    if (ret!=0 && ret!=-1)
                    {
                        PGLW(c_socket,s,__S);

                        s->rd_buf+=string(b,ret);
                    }
                }
            }

        }
    }
    {
        PGLW(c_socket,s,__S);
        int rds=s->rd_buf.size();
        if (rds)
        {
            if (len>=rds)
            {
                memcpy(buf,s->rd_buf.data(),rds);
                s->rd_buf="";
                return rds;
            }
            else
            {
                memcpy(buf,s->rd_buf.data(),len);
                s->rd_buf=s->rd_buf.substr(len,s->rd_buf.size()-len);
                return len;

            }
        }
    }
    return 0;
    //}
}

int c_socket::get_socket_fd() const
{
    return m__sock;
}
void c_socket::sock_linger(int sec)
{
    if (m__sock>FD_SETSIZE) return;

    struct linger l;
    l.l_onoff=1;
    l.l_linger=sec;
    if (::setsockopt(m__sock,SOL_SOCKET,SO_LINGER,
#ifndef WIN32
                     &l
#else
                     (const char*)&l
#endif
                     , sizeof(l))!=0)
    {
        throw cError("linger failed");
    }
}
std::string c_socket::get_socket_descr() const
{
    return itostring(m__sock);
}
c_socket * c_socket::__get_this__()
{
    return this;
}
void reply_socket(const PTR_getter <c_socket> &__S, const OCALC & _data)
{
    return reply_socket(__S,  _data.as_string());

}
void reply_socket(const PTR_getter <c_socket> &__S, const std::string & _data)
{
    write_sender_data(__S,_data);
}
std::string __gets(const PTR_getter <c_socket> &__S, const string &delim)
{
    {
        PGLW(c_socket,s,__S);
        int pos=s->rd_buf.find(delim);
        if (pos!=-1)
        {
            string o=s->rd_buf.substr(0,pos);
            int delimsz=delim.size();
            s->rd_buf=s->rd_buf.substr(pos+delimsz,s->rd_buf.size()-(pos+delimsz));
            return o;
        }
    }


    int fd;
    {
        PGLW(c_socket,s,__S);
        fd=s->get_socket_fd();
    }
    if (fd==-1) {
        return "";
    }


    time_t start_t=time(NULL);
    time_t __start_t=time(NULL);
    while (1)
    {
        if (time(NULL)-start_t>60) {
            throw cError("break loop");
            return "";
        }
        if (time(NULL)-__start_t>3) {
            throw cError("break loop");
            return "";
        }
        if (readable_abs(__S,0,0))
        {
            char b[4096];
            int res;
            int __errno;
            int fd;
            {
                PGLW(c_socket,s,__S);
                fd=s->get_socket_fd();
                if (fd==-1)return "";
                res=::recv(fd,b,sizeof(b),0);
                if (res==-1)
                {
                    __errno=errno;
                }
            }
            if (res==-1)
            {
                if (__errno==EAGAIN)
                {

                    usleep(10000);
                    continue;
                }
                else
                {
                    disconnect(__S);
                    return "";
                }
            }
            if (res)
            {
                PGLW(c_socket,s,__S);
                s->rd_buf+=string(b,res);
                //                    s->recv0=0;
                tcp_total_recv+=res;
                __start_t=time(NULL);


            }
        }
        else
        {
            usleep(10000);
        }
        {
            PGLW(c_socket,s,__S);
            int pos=s->rd_buf.find(delim);
            if (pos!=-1)
            {
                string o=s->rd_buf.substr(0,pos);
                int delimsz=delim.size();
                s->rd_buf=s->rd_buf.substr(pos+delimsz,s->rd_buf.size()-(pos+delimsz));
                return o;
            }
        }
    }
    return "";
}

bool readable(const PTR_getter<c_socket> &__S,int sec, int usec)
{

    {
        PGLW(c_socket,s,__S);
        if (s->rd_buf.size()) return true;
    }



    int iii;
    {
        int fd;
        {
            PGLR(c_socket,s,__S);
            fd=s->get_socket_fd();
        }


        if (fd==-1)
        {
            //logErr2(" if(fd==-1)");
            return false;
        }
        fd_set rdfs;	/*for select */
        FD_ZERO(&rdfs);
        FD_SET(fd, &rdfs);
        struct timeval tv;
        tv.tv_sec = sec;
        tv.tv_usec = usec;
        iii = select(fd + 1, &rdfs, NULL, NULL, &tv);
        if (iii!=-1)
            return FD_ISSET(fd, &rdfs);
    }
    if (iii == -1) {
        disconnect(__S);
        return false;
    }
    return false;
}
bool readable_abs(const PTR_getter<c_socket> &__S,int sec, int usec)
{

    int iii;
    {
        int fd;
        {
            PGLR(c_socket,s,__S);
            fd=s->get_socket_fd();
        }

        if (fd==-1)
        {
            return false;
        }
        fd_set rdfs;	/*for select */
        FD_ZERO(&rdfs);
        FD_SET(fd, &rdfs);
        struct timeval tv;
        tv.tv_sec = sec;
        tv.tv_usec = usec;

        iii = select(fd + 1, &rdfs, NULL, NULL, &tv);
        if (iii!=-1)
            return FD_ISSET(fd, &rdfs);
    }
    if (iii == -1) {
        disconnect(__S);
        return false;
    }
    return false;

}
bool writeable(const PTR_getter<c_socket>& __S, int timeout_sec, int timeout_usec)
{
    int iii=0;
    {
        int fd;
        {
            PGLR(c_socket,s,__S);
            fd=s->get_socket_fd();
        }

        if (fd==-1)
        {
            return false;
        }
        fd_set  wrfs;
        FD_ZERO(&wrfs);
        FD_SET(fd, &wrfs);
        struct timeval tv;
        tv.tv_sec = timeout_sec;
        tv.tv_usec = timeout_usec;

        iii = select(fd + 1, NULL, &wrfs, NULL, &tv);
        if (iii!=-1)
            return FD_ISSET(fd, &wrfs);
    }
    if (iii == -1) {
        disconnect(__S);
        return false;
    }
    return false;


}


bool readable(const PTR_getter<c_socket>&__S)
{
    int timeout_sec,timeout_usec;
    {
        PGLR(c_socket,s,__S);
        timeout_sec=s->timeout_sec;
        timeout_usec=s->timeout_usec;
    }
    return readable(__S,timeout_sec,timeout_usec);
}
bool readable_abs(const PTR_getter<c_socket>&__S)
{
    int timeout_sec,timeout_usec;
    {
        PGLR(c_socket,s,__S);

        timeout_sec=s->timeout_sec;
        timeout_usec=s->timeout_usec;
    }
    return readable_abs(__S,timeout_sec,timeout_usec);
}
bool writeable(const PTR_getter<c_socket>&__S)
{
    int timeout_sec,timeout_usec;
    {
        PGLR(c_socket,s,__S);

        timeout_sec=s->timeout_sec;
        timeout_usec=s->timeout_usec;
    }
    return writeable(__S,timeout_sec,timeout_usec);
}
unsigned long gethostname(const char *hostname)
{

    // try and resolve hostname
    struct hostent *hostEnt;
    if ((hostEnt = gethostbyname(hostname)) == NULL || hostEnt->h_addrtype != AF_INET) {
        throw cError("DNS lookup failed");
    } else {
        return *((unsigned long *)(hostEnt->h_addr));
    }
}
