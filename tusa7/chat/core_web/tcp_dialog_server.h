/*
core_dialog
(c) belialov.com
*/
#ifndef TCP_DIALOG_SERVER__H
#define TCP_DIALOG_SERVER__H

#include <map>
#include <time.h>
#include "_mutex.h"
#include <vector>
#include "tcp_server.h"
#include "tcp_server_connection.h"
#include "PTR.h"
#include "M_SET.h"
class out_oscar_buffer;
class tcp_dialog_server;
class tcp_second_data: public base_container
{
    /*
    	second_data used as data mapped to socket
    */
public:
    /*	extra_user_id - any additional data allocated in inherited classes,
    used to store f.e. user data
    object can be constructed at any time
    but destructed using call virtual server::delete__U
    ----------------
    changed unsigned int means user_id;
    */
    std::string extra_user_id;

    /*	recv_0 - method fix linux bug 'crazy sockets'. I.e. recv() return OK but without data
    	and process drops to infinitive loop. */
    unsigned int recv_0;

    //	Command buffer
    //std::string buffer;
    std::string buffer;

    // pointer to server
    tcp_dialog_server *server;

    //	Operating socket
    PTR_getter<c_socket> socket;

    // client ip
    std::string peer_ipaddress;
    sockaddr_in peer_sockaddr;

    // gets line if available in buffer, else return empty string
//		std::string get_line();

    // time of creation
    time_t create_time;
    time_t last_io_time;

    // flag marks do not destroy in validate_second_data
    bool keep_alive;
    bool kick_on_ping_timeout;
//		bool secure;
//		std::string rsa_key;
    tcp_second_data(tcp_dialog_server* serv);
    virtual ~tcp_second_data();
};

class tcp_dialog_server: public tcp_server
{
public:

    class  __tcpdial_read_stuff
    {
        _mutex MutexZZ;
        /*container of all sockets first element used to handle objects only*/
        std::map<int/*sock fd*/,PTR_getter<c_socket> > __Mx_sockets;

        /* readable sockets, if any socket is readable in sockets
        	it copied to sockets_to_process and removed from sockets.
        	After processing, if no error,
        	socket will moved to sockets again from sockets_to_process
        	for next processing.
        */
        std::map <int,PTR_getter<c_socket> > __Mx_sockets_to_process;
        tcp_dialog_server *server;
    public:
        /*mutexed accessors*/
        unsigned int sockets_size();
        unsigned int sockets_to_process_size();
//#ifdef DEBUG
        void dump_state();
//#endif

        __tcpdial_read_stuff(tcp_dialog_server *_server);
        PTR_getter<c_socket> get_socket();
        /*add to sockets*/
        void add(const PTR_getter<c_socket> &s);

        /*scan for sockets for readable and prepare sockets_to_process*/
        void do_select(time_t & last_full_select);
        void erase(int);

//		void on_iterate();
    };

    /*
    second_data container
    */
    std::map<PTR_getter<c_socket>,PTR_getter<tcp_second_data> > __mx_tcpdial_socket_user_map;
    _mutex tcpdial_socket_user_mapMX;
    m_var<time_t> last_tcpdial_socket_user_map_cleanup;

    __tcpdial_read_stuff tcpdial_read_stuff;

    tcp_dialog_server();
    virtual void start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);

    ~tcp_dialog_server();
private:
    void load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);
    static void *handler(void*);
    static void *iterator(void*);
    static void *socket_selector(void*);
public:
    //void start_threads(unsigned int NHandlers);
//#ifdef DEBUG
    void dump_state();
//#endif
    void on_iterate();
    // process buffer by derived calls
    virtual void process_buffer(const PTR_getter<tcp_second_data>& __SD)=0;

    // call inherited to do something like log output etc..
    virtual void on_delete(const PTR_getter<tcp_second_data>& __SD,const std::string& msg)=0;

    // virtual destructor to delete second_data.extra_user_id (means user data)


    // virtual second_data validator.  Called in inherited classes
    // return 0 if user invalid
    // 1 - if valid
    virtual bool validate_second_data(const PTR_getter<tcp_second_data>&,std::string& errstr)=0;

    // call to do something when connections accepted.
    // f.e. FTPD case - print "220 FTP server is ready."
    virtual void on_accept_dialog_socket(const PTR_getter<c_socket>&s,tcp_second_data * __sd)=0;

    // thread timeouts
    // CONF
    m_var<unsigned int> dialog_handler_timeout_usec;
    m_var<unsigned int> dialog_iterator_timeout_sec;
    m_var<unsigned int> selector_timeout_sec;
    m_var<unsigned int> dialog_handler_cnt;
    // stuff to prevent hacker attack.
    // is is possible to establish many connection and take all system sockets.
    // to prevent we limited number of connections in time_period
    // ex: 20,5 means per 20 sec max accepted connections will be 5.
    //
    m_var<unsigned int> antiflood_period;
    m_var<unsigned int> antiflood_period_cnt;
    m_var<unsigned int> client_kill_ping_timeout_sec; // kill in __mx_tcpdial_socket_user_map if no IO at timeout
    //ENDCONF

    m_var<time_t> last_antiflood_period_start;
    m_var<int>connects_in_period;
    virtual void delete_extra_user_id(const std::string&)=0;

private:


};
class tcp_dialog_connection:public tcp_server_connection
{
public:
    tcp_dialog_server *server;
    tcp_dialog_connection(const PTR_getter<c_socket> &sk, tcp_dialog_server* serv):
            tcp_server_connection(sk),server(serv) {}

    // virtual inherited from tcp_server_connection
    void process_tcp();
    virtual tcp_second_data* new_tcp_second_data(tcp_dialog_server* serv)=0;

};
class tcp_linedialog_server: public tcp_dialog_server
{
public:
    tcp_linedialog_server();
    virtual void start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);
    void load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);

    // derived call to process buffer
    void process_buffer(const PTR_getter<tcp_second_data>& __SD);

    // process command in inherited class
    virtual void process_command(const std::string& cmd,const PTR_getter<tcp_second_data>& __SD)=0;
    static std::string extract_command(std::string& buffer);

};
void disconnect(const PTR_getter<tcp_second_data>& __SD);
void reply_second_data(const PTR_getter<tcp_second_data>& __SD, const std::string & _data);
void reply_second_data(const PTR_getter<tcp_second_data>& __SD, const OCALC & _data);

#endif
