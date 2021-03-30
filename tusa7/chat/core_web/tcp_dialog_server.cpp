#include "stdafx.h"
#include "_mutex.h"
#include <list>

#include <stdio.h>
#include <map>
#include <set>

#include "tcp_dialog_server.h"
#ifndef WIN32
#include <sys/poll.h>
#endif
#include "tcp_server_data.h"
#ifdef WIN32
#endif
#include "str_lib.h"
using namespace std;
#ifdef THREAD_NAME_DBUG
#endif
void  log_start_thread(const std::string &n);
int S_recv(const PTR_getter<c_socket>&__S,void *buf, size_t len, int flags);

void tcp_dialog_server::start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{
    tcp_server::start(pn,prefix,m);
    load_config(pn,prefix,m);

    pthread_t pt;
    for (unsigned int i=0;i<dialog_handler_cnt.get();i++)
    {
        create_thread(handler,server_name()+" tcp_dialog_server::handler");
    }


    create_thread(socket_selector, server_name()+" tcp_dialog_server::socket_selector");
    create_thread(iterator, server_name()+" tcp_dialog_server::iterator");

}
tcp_dialog_server::tcp_dialog_server()
        :tcpdial_read_stuff(this)
{

    /*
    	constructor
    	parameters - config m_vars refs
    */
}
tcp_dialog_server::~tcp_dialog_server()
{


}


class tcpdial_socket_getter
{/*
        	stack object
        	constructor: do nothing
        	destructor: if socket assigned
        	add it into tcpdial_read_stuff
        */
    PTR_getter<c_socket> sock;
    tcp_dialog_server::__tcpdial_read_stuff& tcpdial_read_stuff;
public:
    tcpdial_socket_getter(tcp_dialog_server::__tcpdial_read_stuff &irs);
    void assign(const PTR_getter<c_socket> &s) {

        sock=s;
    }
    ~tcpdial_socket_getter();
};
tcpdial_socket_getter::tcpdial_socket_getter(tcp_dialog_server::__tcpdial_read_stuff &irs):sock(NULL),tcpdial_read_stuff(irs) {}
tcpdial_socket_getter::~tcpdial_socket_getter()
{
    /*
    	if sock is valid and alive push it into tcpdial_read_stuff on destroy
    	this object
    */

    if (sock) {
        bool need_kill = false;
        {
            PGLR(c_socket, ss,sock);
            if (!ss->connected())
                need_kill = true;
        }
        if (!need_kill) {
            tcpdial_read_stuff.add(sock);
        }
    }
}
void *tcp_dialog_server::iterator(void* pr)
{
    tcp_dialog_server *srv=(tcp_dialog_server*)pr;
    string thread_name=srv->server_name()+" tcp_dialog_server::iterator";
    log_start_thread(thread_name);

    while (1)
    {
        {
            if (srv->SLEEP(srv->dialog_iterator_timeout_sec))return NULL;
        }
        try {
            srv->on_iterate();
        }
        STDCATCHS("tcpdial_socket_iterator");

    }
}

void *tcp_dialog_server::handler(void* pr)
{
    tcp_dialog_server *srv=(tcp_dialog_server*)pr;
    string thread_name=srv->server_name()+" tcp_dialog_server::handler";
    log_start_thread(thread_name);

    while (1) {
        char buf[1024 + 100];
        {
            if (srv->USLEEP(srv->dialog_handler_timeout_usec.get()))return NULL;
        }
        try {


            while (1) {
                /*
                construct empty getter
                */
                tcpdial_socket_getter _tcpdial_socket_getter(srv->tcpdial_read_stuff);

                {
                    /*
                    find socket to process
                    */
                    PTR_getter <c_socket> sock(NULL);
                    {
                        sock=srv->tcpdial_read_stuff.get_socket();
                        if (!sock) break;
                    }

                    /*
                    	Select second data for this socket
                    */
                    PTR_getter<tcp_second_data> __SD(NULL);
                    {
                        M_LOCK(srv->tcpdial_socket_user_mapMX);
                        std::map<PTR_getter<c_socket>,PTR_getter<tcp_second_data> >::iterator iz = srv->__mx_tcpdial_socket_user_map.find(sock);
                        if (iz != srv->__mx_tcpdial_socket_user_map.end())
                        {
                            __SD = iz->second;
                        }
                        else
                        {
                            logErr2("second_data for socket not found");
                            continue;
                        }
                    }
                    /*
                    	assign to getter to be sure that socket will be returned
                    	into tcpdial_read_stuff on getter destroy
                    */
                    _tcpdial_socket_getter.assign(sock);

                    bool need_disconnect = false;
                    //                string data;
                    int cnt=0;
                    {
                        /*
                        	Receive portion from socket
                        */
                        {
                            //if (readable(sock,0,0))
                            {
                                cnt = S_recv(sock,buf, 1024, 0);
                                if (cnt == -1) {

                                    string ip;
                                    {
                                        PGLR(c_socket,s,sock);
                                        ip=s->peer_ipaddress;
                                    }
                                    need_disconnect = true;
                                }
                            }
                        }
                    }
                    if (__SD && (!need_disconnect)) {
                        /*
                        	handle possible linux bug
                        	socket like alive but really dead
                        */
                        PGLW(tcp_second_data, sd, __SD);
                        if (cnt == 0) {
                            sd->recv_0++;
                            if (sd->recv_0 > 10) {
                                need_disconnect = true;
                            }
                        }
                        else {
                            sd->recv_0 = 0;
                            sd->last_io_time=time(NULL);
#ifdef MSG_DBUG
                            logErr2("sd->last_io_time=time(NULL);");
#endif
                        }
                        if (time(NULL)-sd->last_io_time>srv->client_kill_ping_timeout_sec.get() && (!need_disconnect)) {


                            logErr2(" need_disconnect=true due client_kill_ping_timeout_sec %s %d",__FILE__,__LINE__);
                            need_disconnect=true;
                        }
                        if (!need_disconnect)
                        {
                            /*
                            	check if command line is too long
                            */
                            if (cnt>0)
                                sd->buffer+=std::string(buf,cnt);
                        }
                    }
                    if (need_disconnect) {
                        /*
                        	call virtual to notify inherited class about user deleted
                        */
                        {
                            if (__SD)
                            {
                                srv->on_delete(__SD,"connection broken by recv0");
                            }
                        }
                        {
                            /*
                            	Delete pair and automatically delete user
                            */
                            M_LOCK(srv->tcpdial_socket_user_mapMX);
                            srv->__mx_tcpdial_socket_user_map.erase(sock);
                        }
                        /*
                        	really disconnect socket
                        */
                        {
                            disconnect(sock);
                            continue;
                        }
                    }
                    {
                        srv->process_buffer(__SD);
                    }
                }
            }//while

            /*
            	Containers cleanup
            */
            if (time(NULL) - srv->last_tcpdial_socket_user_map_cleanup > 1) {
                srv->last_tcpdial_socket_user_map_cleanup = time(NULL);
                /*get keys*/
                map < PTR_getter <c_socket>, PTR_getter<tcp_second_data> >tmp_v;
                {

                    M_LOCK(srv->tcpdial_socket_user_mapMX);
                    tmp_v = srv->__mx_tcpdial_socket_user_map;
                }
                /*iterate over keys*/
                for (map < PTR_getter <c_socket>, PTR_getter<tcp_second_data> >::iterator i = tmp_v.begin(); i != tmp_v.end(); i++) {


                    bool lost = false;
                    {
                        /*
                        	Check for socket destroyed
                        */
                        if (i->first)
                        {
                            PGLR(c_socket, s,i->first);
                            if (!s->connected()) {
                                lost = true;
                            }
                        }
                    }
                    if (lost)
                    {
                        /*
                        	Notify inherited and cleanup
                        */
                        if (i->second)
                        {
                            PTR_getter<c_socket> ___S(NULL);
                            {
                                PGLR(tcp_second_data, sd,i->second);
                                ___S=sd->socket;
                            }
                            if (___S)
                            {
                                disconnect(___S);
                            }
                        }
                        if (i->second)
                        {
                            srv->on_delete(i->second,"connection lost");
                        }
                        {
                            M_LOCK(srv->tcpdial_socket_user_mapMX);
                            srv->__mx_tcpdial_socket_user_map.erase(i->first);
                        }
                    }
                    else
                    {
                        string errstr;
                        /*
                        Chack inherited validate
                        */
                        bool val_res;
                        {

                            val_res=srv->validate_second_data(i->second,errstr);
                        }
                        if (!val_res)
                        {
                            /*
                            	Notify inherited and cleanup
                            */
                            if (i->second)
                            {
                                PTR_getter<c_socket> ___S(NULL);
                                {
                                    PGLR(tcp_second_data, sd,i->second);
                                    ___S=sd->socket;
                                }
                                int fd=-1;
                                if (___S)
                                {
                                    disconnect(___S);
                                }
                            }

                            if (i->second)
                            {
                                srv->on_delete(i->second,errstr);
                            }
                            {
                                M_LOCK(srv->tcpdial_socket_user_mapMX);
                                srv->__mx_tcpdial_socket_user_map.erase(i->first);
                            }
                        }
                    }
                }
            }

        }STDCATCHS("tcp_dialog handler");
    }			//while
}

void* tcp_dialog_server::socket_selector(void*pr)
{
    tcp_dialog_server *srv=(tcp_dialog_server*)pr;
    string thread_name=srv->server_name()+" tcp_dialog_server::socket_selector";
    log_start_thread(thread_name);

    time_t last_full_select=time(NULL);
    while (1) {
        try {
            while (1)
            {
                {
                    ((tcp_dialog_server *) pr)->tcpdial_read_stuff.do_select(last_full_select);
                }
                {
                    if (srv->USLEEP(srv->selector_timeout_sec))return NULL;
                }
            }
        }
        STDCATCHS("tcpdial_socket_selector");
    }
    return NULL;
}

void tcp_dialog_server::dump_state()
{
    int __mx_tcpdial_socket_user_map_CNT;
    {
        M_LOCK(tcpdial_socket_user_mapMX);
        __mx_tcpdial_socket_user_map_CNT=__mx_tcpdial_socket_user_map.size();
    }

    tcpdial_read_stuff.dump_state();
}

void tcp_dialog_server::__tcpdial_read_stuff::dump_state()
{
}
void tcp_dialog_server::on_iterate()
{
    //clean users

    vector<PTR_getter<c_socket> > v;
    {
        M_LOCK(tcpdial_socket_user_mapMX);
        for (std::map<PTR_getter<c_socket>,PTR_getter<tcp_second_data> >::iterator i=__mx_tcpdial_socket_user_map.begin();i!=__mx_tcpdial_socket_user_map.end();i++)
        {
            v.push_back(i->first);
        }
    }
    time_t now=time(NULL);
    for (unsigned i=0;i<v.size();i++)
    {
        PTR_getter<tcp_second_data> __SD(NULL);
        {
            M_LOCK(tcpdial_socket_user_mapMX);
            std::map<PTR_getter<c_socket>,PTR_getter<tcp_second_data> >::iterator it=__mx_tcpdial_socket_user_map.find(v[i]);
            if (it!=__mx_tcpdial_socket_user_map.end()) __SD= it->second;
        }
        bool need_erase=false;
        PTR_getter<c_socket> __S(NULL);
        if (__SD)
        {
            PGLR(tcp_second_data, sd,__SD);
            if (now-sd->last_io_time> client_kill_ping_timeout_sec) need_erase=true;
            __S=sd->socket;
        }
        if (need_erase)
        {
            if (0) {
                {
                    M_LOCK(tcpdial_socket_user_mapMX);
                    __mx_tcpdial_socket_user_map.erase(v[i]);
                }
                if (__S) {

                    disconnect(__S);
                }
                logErr2("Disconnected client due ping timeout");
            }
        }
    }

}

void tcp_dialog_server::__tcpdial_read_stuff::do_select(time_t &last_full_select)
{
    /*
    	scan sockets for readable
    	if found then socket copied into sockets_to_process
    	and erased from sockets_to_process
    	to prevent multiple access
    */

    {
        /*
        	Return if no sockets
        */
        M_LOCK(MutexZZ);
        if (!__Mx_sockets.size())
            return;
    }

    map < int, PTR_getter <c_socket> >tmp;
#ifdef WIN32
    {
        M_LOCK(MutexZZ);
        map<int, PTR_getter <c_socket> > broken;
        for (std::map<int,PTR_getter<c_socket> >::iterator i=__Mx_sockets.begin();i!=__Mx_sockets.end();i++)
        {

            int iii;
            {
                int fd;
                {
                    PGLR(c_socket,s,i->second);
                    fd=s->get_socket_fd();
                }

                if (fd==-1) {
                    broken.insert(*i);
                    continue;
                }
                fd_set rdfs;	/*for select */
                FD_ZERO(&rdfs);
                FD_SET(fd, &rdfs);
                struct timeval tv;
                tv.tv_sec = 0;
                tv.tv_usec = 0;

                iii = select(fd + 1, &rdfs, NULL, NULL, &tv);
                if (iii!=-1)
                {
                    if (FD_ISSET(fd, &rdfs))tmp.insert(*i);
                }
            }
            if (iii == -1) {
                broken.insert(*i);
            }

        }
        for (map<int, PTR_getter <c_socket> >::iterator i=broken.begin();i!=broken.end();i++)
        {
            __Mx_sockets.erase(i->first);
        }


    }
#else
    {
        {
            pollfd pollfds[FD_SETSIZE];
            int nfds_poll;
            int idx=0;
            M_LOCK(MutexZZ);
            set<int> fds_readable;
            set<int> fds_broken;
            for (typeof(__Mx_sockets.begin()) i=__Mx_sockets.begin();i!=__Mx_sockets.end();i++)
            {
                bool cond=true;
                {
                    PGLR(c_socket,s,i->second);
                    if (s->rd_buf.size())
                    {
                        fds_readable.insert(i->first);
                        cond=false;
                    }
                }

                {
                    if (cond) {
                        pollfds[idx].fd=i->first;
                        pollfds[idx].events=POLLIN|POLLPRI;
                        pollfds[idx].revents=0;
                        idx++;
                    }
                }
            }
            if (idx)
            {
                int ret=poll(pollfds,idx,0);
                if (ret==-1)
                {
                    logErr2("poll returned -1",__FILE__,__LINE__);
                }
                else
                {


                    if (ret)
                    {

                        for (int ii=0;ii<idx;ii++)
                        {

                            if (pollfds[ii].revents & (POLLIN|POLLPRI))
                            {

                                fds_readable.insert(pollfds[ii].fd);
                            }
                            if (pollfds[ii].revents & (POLLERR|POLLHUP|POLLNVAL))
                            {

                                fds_broken.insert(pollfds[ii].fd);
                            }
                        }
                    }
                }
            }

            {
                for (typeof(fds_broken.begin()) i = fds_broken.begin();i!=fds_broken.end(); i++)
                {
                    typeof(__Mx_sockets.begin()) iter=__Mx_sockets.find(*i);
                    if (iter!=__Mx_sockets.end())
                    {
                        if (iter->second)
                        {


                            disconnect(iter->second);


                        }
                        __Mx_sockets.erase(iter);
                    }
                }
            }

            {
                for (typeof(fds_readable.begin()) i = fds_readable.begin();i!=fds_readable.end(); i++)
                {

                    typeof(__Mx_sockets.begin()) iter=__Mx_sockets.find(*i);
                    if (iter!=__Mx_sockets.end())
                    {
                        tmp.insert(*iter);
                    }
                }
            }
        }

    }
#endif

    {
        if (time(NULL)-last_full_select>2)
        {
            last_full_select=time(NULL);
            M_LOCK(MutexZZ);
            tmp = __Mx_sockets;
        }
    }
    //    {
    /*
    	copy to tmp container
    */
    vector < int >moved;
    vector<pair<int,PTR_getter <c_socket> > > local_sockets_to_process;
    for (map < int, PTR_getter <c_socket> >::iterator i = tmp.begin(); i != tmp.end(); i++) {
        bool __readable = false;
        bool closed = false;
        bool __moved = false;
        {
            {
                PGLW(c_socket, s,i->second);
                if (!s->connected()) {
                    closed = true;
                }
            }
            if (!closed)
            {
                if (readable(i->second,0,0)) {
                    __readable = true;
                }
            }

        }
        if (closed) {
            __moved = true;
            moved.push_back(i->first);
        }
        else if (__readable) {
            __moved = true;
            moved.push_back(i->first);
            {
                {
                    local_sockets_to_process.push_back(*i);
                }
            }
        }
        if (!__moved) {
            M_LOCK(server->tcpdial_socket_user_mapMX);
            if (!server->__mx_tcpdial_socket_user_map.count(i->second))
            {
                moved.push_back(i->first);
            }
        }
    }
    {
        M_LOCK(MutexZZ);
        for (unsigned int i = 0; i < moved.size(); i++) {
            __Mx_sockets.erase(moved[i]);
        }
    }
    {

        M_LOCK(MutexZZ);
        for (unsigned i=0;i<local_sockets_to_process.size();i++)
        {
            __Mx_sockets_to_process.insert(local_sockets_to_process[i]);
        }
    }
}
unsigned int tcp_dialog_server::__tcpdial_read_stuff::sockets_size()
{
    /*
    protected acessor
    */
    M_LOCK(MutexZZ);
    return __Mx_sockets.size();
}
unsigned int tcp_dialog_server::__tcpdial_read_stuff::sockets_to_process_size()
{
    /*
    protected acessor
    */
    M_LOCK(MutexZZ);
    return __Mx_sockets_to_process.size();
}
PTR_getter <c_socket> tcp_dialog_server::__tcpdial_read_stuff::get_socket()
{
    /*
    extracts 1st socket from sockets_to_process
    */


    M_LOCK(MutexZZ);
    if (!__Mx_sockets_to_process.size())
        return NULL;

    PTR_getter <c_socket> s=__Mx_sockets_to_process.begin()->second;
    __Mx_sockets_to_process.erase(__Mx_sockets_to_process.begin());
    return s;
}
void tcp_dialog_server::__tcpdial_read_stuff::erase(int fd)
{
    {
        M_LOCK(MutexZZ);
        __Mx_sockets.erase(fd);
        __Mx_sockets_to_process.erase(fd);
    }
}
void tcp_dialog_server::__tcpdial_read_stuff::add(const PTR_getter <c_socket> &s)
{
    /*
    	add socket to sockets
    */
    int sock;
    {
        PGLR(c_socket, ss,s);
        sock = ss->get_socket_fd();
    }
    if (sock != -1) {
        M_LOCK(MutexZZ);
        __Mx_sockets.insert(pair < int, PTR_getter <c_socket> >(sock, s));
    }
    else
    {
    }
}

void tcp_dialog_connection::process_tcp()
{
    /*
    	inherit call from tcp_server
    	called on accept connection to read and process it
    */

    // antiflood check
    if (time(NULL)-server->last_antiflood_period_start>server->antiflood_period) {
        server->last_antiflood_period_start=time(NULL);
        server->connects_in_period=0;
    }
    ++server->connects_in_period;
    if (server->connects_in_period.get()>server->antiflood_period_cnt.get())
        return;

    /*
    	store socket and user data into container
    	to process by other threads
    */
    tcp_second_data *dt=new_tcp_second_data(server);
    dt->socket=socket;
    dt->peer_ipaddress=tcp_peer_ipaddress;
    dt->peer_sockaddr=peer_address;

    server->on_accept_dialog_socket(socket,dt);
    PTR_getter<tcp_second_data> __SD(dt);
    {
        M_LOCK(server->tcpdial_socket_user_mapMX);
        server->__mx_tcpdial_socket_user_map.insert(pair<PTR_getter<c_socket>,PTR_getter<tcp_second_data> >(socket,__SD));
    }
    server->tcpdial_read_stuff.add(socket);
    /*
    do something on accept connecctioen
    ex: send 220 FTP server is ready
    */
}

static _mutex extra_Mutex("extra_Mutex");
tcp_second_data::~tcp_second_data()
{
    /*
    	In destructor call inherited virtual destructor for extra_data
    */
    if (extra_user_id!="") {
        server->delete_extra_user_id(extra_user_id);
        extra_user_id="";
    }
}
tcp_second_data::tcp_second_data(tcp_dialog_server* serv)
        :extra_user_id(""),recv_0(0),server(serv),socket(NULL),create_time(time(NULL)),
        last_io_time(time(NULL)),
        keep_alive(false),kick_on_ping_timeout(true),/*secure(false),*/
        base_container("tcp_second_data::") {
}


string tcp_linedialog_server::extract_command(std::string& buffer)
{
    /*
    	get line if available
    */

    if (!buffer.size())return "";
    int pz = buffer.find("\n");
    if (pz == -1)
    {
        return "";
    }
    
    string command= buffer.substr(0,pz);
    buffer=buffer.substr(pz+1,buffer.size()-1-pz);
/*    if (pz-buffer.data()<buffer.size())
    {
        memcpy(buffer.data(),pz+1,buffer.size()-1-(pz-buffer.data()));
        buffer.cur_pos=buffer.size()-1-(pz-buffer.data());
    }
    else buffer.cur_pos=0;
*/
    return command;

}


void tcp_linedialog_server::process_buffer(const PTR_getter<tcp_second_data>& __SD)
{
    while (1)
    {

        std::string command;
        {
            /*
            	try to receive line
            */
            PGLW(tcp_second_data, sd, __SD);
            if (sd->buffer.size()) {
                command=extract_command(sd->buffer);
            }
        }
        /*
        if OK process command
        */
        if (command.size()) {
            process_command(command,__SD);
        }
        else
            break;
    }
}
void disconnect(const PTR_getter<tcp_second_data>& __SD)
{
    PTR_getter<c_socket> __S(NULL);
    if (__SD) {
        PGLW(tcp_second_data,sd,__SD);
        __S=sd->socket;
    }
    if (__S) {
        disconnect(__S);
    }
}
void reply_second_data(const PTR_getter<tcp_second_data>& __SD, const OCALC&  _data)
{
    PTR_getter<c_socket> __S(NULL);
    if (__SD) {
        PGLR(tcp_second_data, sd,__SD);
        __S=sd->socket;
    }
    if (__S)
        reply_socket(__S,_data);

}
void reply_second_data(const PTR_getter<tcp_second_data>& __SD, const std::string & _data)
{
    PTR_getter<c_socket> __S(NULL);
    if (__SD) {
        PGLR(tcp_second_data, sd,__SD);
        __S=sd->socket;
    }
    if (__S)
        reply_socket(__S,_data);
}

tcp_dialog_server::__tcpdial_read_stuff::__tcpdial_read_stuff(tcp_dialog_server *_server):server(_server),MutexZZ("tcp_dialog_server") {}

void tcp_dialog_server::load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{

    set_cfg_i(m,prefix+"dialog_handler_timeout_usec", pn,dialog_handler_timeout_usec,11111);
    set_cfg_i(m,prefix+"dialog_iterator_timeout_sec", pn,dialog_iterator_timeout_sec,11);
    set_cfg_i(m,prefix+"dialog_handler_cnt", pn,dialog_handler_cnt,7);
    set_cfg_i(m,prefix+"selector_timeout_sec", pn,selector_timeout_sec,1000);

    set_cfg_i(m,prefix+"antiflood_period", pn,antiflood_period,20);
    set_cfg_i(m,prefix+"antiflood_period_cnt", pn,antiflood_period_cnt,5);
    set_cfg_i(m,prefix+"client_kill_ping_timeout_sec", pn,client_kill_ping_timeout_sec,200);


}
void tcp_linedialog_server::start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{
    tcp_dialog_server::start(pn,prefix,m);
    load_config(pn,prefix,m);
}
void tcp_linedialog_server::load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{

}
tcp_linedialog_server::tcp_linedialog_server()
{
}
