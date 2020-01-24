#ifdef __GNUC__
#pragma implementation				// gcc: implement sql_udf.h
#endif

#include "stdafx.h"
#include <sys/stat.h>

#include "tcp_server_data.h"
#include "file_set.h"
#include <set>
#include "str_lib.h"
#include "tcp_sender.h"
#include "tcp_stats.h"
#include "M_SET.h"
#include "threadable.h"
#include <cerrno>
#include "errs.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SENDER2

void  log_start_thread(const std::string &n);


class sender2:public threadable
{
    _mutex MutexX;
public:

    map<int, PTR_getter<c_socket> > container;
    sender2();
    void on_socket_create(int fd);
    void on_socket_close(int fd);
    void start(const string& pn,const string& prefix,map<string,string>&m);

    void write_data(const PTR_getter<c_socket> &socket, const string& buf);
    void load_config(const string& pn,const string& prefix,map<string,string>&m);
    static void *sender_proc(void *pr);
    m_var<unsigned int>timeout_usec;

};
sender2 *__sender2=NULL;

#ifdef WIN32
__declspec(dllexport)
#endif
void init_senders(const string& pn,const string& prefix,map<string,string>&m)
{
#ifdef SENDER2
    __sender2=new sender2();
    __sender2->start(pn,prefix,m);
#else
    __sender=new sender();
    __sender->start(pn,prefix,m);
#endif
}
void hup_senders(const string& pn,const string& prefix,map<string,string>&m)
{
#ifdef SENDER2
    if (__sender2)__sender2->load_config(pn,prefix,m);
#else
    if (__sender)__sender->load_config(pn,prefix,m);
#endif
}
void destroy_senders()
{
#ifdef SENDER2
    sender2 *s=__sender2;
    __sender2=NULL;
    delete s;
#else
    sender *s=__sender;
    __sender=NULL;
    delete s;
#endif
}
void write_sender_data(const PTR_getter<c_socket> &socket, const string& buf)
{
#ifdef SENDER2
    if (__sender2)
    {
        __sender2->write_data(socket, buf);
    }
#else
    if (!__sender) throw cError("!__sender");
    PTR_getter<sender::sender_datum > sd(new sender::sender_datum(/*0,*/ sender::SENDER_TYPE_DATA, socket, buf));
    {
        M_LOCK(__sender->sender_dataMX);
        __sender->sender_data.push_back(sd);
    }
#endif
}

void on_socket_create(int sock)
{
    if (__sender2) __sender2->on_socket_create(sock);
}
void on_socket_close(int sock)
{
    if (__sender2) __sender2->on_socket_close(sock);
}
void sender2::start(const string& pn,const string& prefix,map<string,string>&m)
{
    load_config(pn,prefix,m);
    create_thread(sender_proc,"sender_proc");
}
void sender2::write_data(const PTR_getter<c_socket> &socket, const string& _buf)
{
    string buf=_buf;
    int res=0;
    bool need_disconnect=false;
    bool need_add=false;
    //{
    int fd;
    {
        PGLW(c_socket,s,socket);
        fd=s->get_socket_fd();
        if (fd==-1) return;
        if (s->send_buf.size())
        {
            buf=s->send_buf+buf;
            s->send_buf.clear();
        }
        if (buf.size()==0) return;

#ifdef WIN32
        res=::send(fd,(char*)buf.data(), buf.size(),0);
#else
        res=::send(fd,(char*)buf.data(), buf.size(),MSG_NOSIGNAL | MSG_DONTWAIT);
#endif
        if (res!=-1)
        {
            tcp_total_send += res;
            if (res!=buf.size())
            {
                buf=buf.substr(res,buf.size()-res);
                s->send_buf=buf;
                need_add=true;
            }
        }
        else
        {
            switch (errno)
            {
            case EAGAIN:
            {
                s->send_buf=buf;
                need_add=true;
//		    logErr2("__errno==EAGAIN");
            }break;
            default:
                need_disconnect=true;
            }

        }
    }
    if (need_disconnect)
    {
        disconnect(socket);
        return;
    }
    if (need_add)
    {
        MUTEX_LOCK kall(MutexX);
        container.insert(make_pair(fd,socket));
    }
    //}
}
sender2::sender2()
{
    /*    for(unsigned i=0;i<FD_SETSIZE+1;i++)
        {
            sds[i]=NULL;
        }*/
}
void sender2::on_socket_create(int fd)
{
    MUTEX_LOCK kall(MutexX);
    container.erase(fd);
}
void sender2::on_socket_close(int fd)
{
    MUTEX_LOCK kall(MutexX);
    container.erase(fd);
}
void sender2::load_config(const string& pn,const string& prefix,map<string,string>&m)
{

    set_cfg_i(m,prefix+"timeout_usec", pn,timeout_usec, 30000);
}
void *sender2::sender_proc(void *pr)
{

    sender2 *snd=(sender2*)pr;
    string thread_name="sender2::sender_proc";
    log_start_thread(thread_name);
    while (1) {
        try {

            while (1) {
                map<int,PTR_getter<c_socket> > m;
                {
                    MUTEX_LOCK kall(snd->MutexX);
                    m=snd->container;
                    snd->container.clear();
                }
                for (map<int,PTR_getter<c_socket> >::iterator i=m.begin();i!=m.end();i++)
                {
                    snd->write_data(i->second,"");
                }
                if (snd->USLEEP(snd->timeout_usec))return NULL;
            }
       }
        STDCATCHS("sender while(1) STDCATCHS");
        {
            if (snd->USLEEP(snd->timeout_usec))return NULL;
        }
    }
    return NULL;
}
