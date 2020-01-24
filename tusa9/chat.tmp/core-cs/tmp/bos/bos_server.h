#ifndef BOS_SERVER__H
#define BOS_SERVER__H
#include "tcp_oscar_dialog_server.h"
#include "M_SET.h"
#include "oscar_buffer.h"
#include "bs_user.h"
#include "oscar_client.h"

#define BOS_UDP
class cs_client;
class bos_server;

    enum State
    { NOT_CONNECTED=0,
      AUTH_AWAITING_CONN_ACK=2,
      AUTH_AWAITING_AUTH_REPLY=3,
      CS_LOGGED_IN=6,
      LOGIN_FAILED=11
    };
    enum Target
    { __LOGIN=0, SLEEPING=2 };

struct cc_data
{
    const char* getclassname()const{return "cc_data";}

    State m_state;
    Target m_target;
    PTR_getter<c_socket> socket;
    time_t last_ping_time;
    time_t last_pong_time;
    time_t auth_time;
    cc_data();
};

class _cs_client:public oscar_client
{
    public:
    const char* getclassname()const {return "_cs_client";}
    bos_server *server;
    cc_data *ccd;
    Mutex ccdmx;
    _cs_client(bos_server *_server);
    ~_cs_client();
    void parse_ch1(oscar_buffer & b);
    void parse_ch2(oscar_buffer & b);
    void parse_ch3(oscar_buffer & b);
    void parse_ch4(oscar_buffer & b);
    void parse_ch5(oscar_buffer & b);
    void parse_ch6(oscar_buffer & b);
    void on_disconnect(const std::string& reason);
    void on_socket_create(int sock);
    void start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);
    void do_auth();
    void load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);
    void Poll();
    static void *T_run_poll_handler(void *pr);

    m_var<std::string> authorizer_server_ip;
    m_var<unsigned int> authorizer_server_port;
    //m_var<unsigned int> listener_timeout_usec;
    m_var<std::string>	auth_nick;
    m_var<std::string>	auth_password;              
    m_var<unsigned int> poll_timeout_usec;
    m_var<unsigned int> ping_timeout_sec;
    m_var<unsigned int> pong_kill_timeout_sec;
    m_var<unsigned int> login_timeout_sec;
	time_t get_socket_inactive_kill_timeout(){return  pong_kill_timeout_sec.get();}
	


    void send_bos_cs_auth_req();
    void on_TYPE_BOS_LOGIN_RESULT_01(oscar_buffer & in_b);
};

class bos_server:public TCPOscarDialogServer
{
    //void load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);
public:
    const char* getclassname()const {return "bos_server";}

    bos_server();
    ~bos_server();
    _cs_client *client;
    void finishCreate(configObj* conf);


    void on_delete(const PTR_getter<c_socket>& __SD,const std::string& msg);

//    bool validate_second_data(const PTR_getter<c_socket>&,std::string& errstr);
    std::string server_name(){return "bos_server";}

    void parse_ch1(const PTR_getter<c_socket>& __SD,oscar_buffer & in_b);
    void parse_ch2(const PTR_getter<c_socket>& __SD,oscar_buffer & in_b);
    void parse_ch3(const PTR_getter<c_socket>& __SD,oscar_buffer & in_b);
    void parse_ch4(const PTR_getter<c_socket>& __SD,oscar_buffer & in_b);
    void parse_ch5(const PTR_getter<c_socket>& __SD,oscar_buffer & in_b);
    void parse_ch6(const PTR_getter<c_socket>& __SD,oscar_buffer & in_b){}

//    void start_sub_tcp();
    void *new_connection(const PTR_getter<c_socket>&s);
    void on_accept_dialog_socket(const PTR_getter<c_socket>&s);

    void parse_ch1_CLI2BOS_CONNECT_SSL(const PTR_getter<c_socket>& __SD,oscar_buffer &bzz);

    bool validate_peer_ip_address(const sockaddr_in & sa);

    void delete_extra_user_id(const std::string &);
	void inspector_worker();
    static void *inspector(void *pr);
    ___bs_users __bs_users;
    std::string do_adminfo_bos();

    // UDP
#ifdef BOS_UDP    
    PTR_getter<c_socket> udp_socket;
	void udp_handler_worker();
    static void* udp_handler(void*pr);
#endif

    
    
    unsigned int	client_max_users;
    std::string	bos_name;
//    m_var<string>	authorizer_server_ip;
//    m_var<unsigned int> authorizer_server_port;
//    m_var<unsigned int> client_logoff_cache_timeout_sec;
    
    unsigned int user_login_timeout_sec;
    unsigned int inspector_timeout_sec;
    unsigned int adminfo_log_timeout_sec;
    unsigned int cs_ping_timeout_sec;
    unsigned int rsa_client_io_size;
    unsigned int client_linger_sec;
    // udp
#ifdef BOS_UDP    
    unsigned int udp_handlers_count;
//    unsigned int udp_listen_port;
  //  std::string 	udp_listen_ip;
    unsigned int udp_handler_time_usec;
#endif    
};

/*class bos_server_connection:public tcp_dialog_connection
{
public:
    bos_server_connection(const PTR_getter<c_socket> &sk, tcp_dialog_server* s);
    ~bos_server_connection();
};
*/

//class bs_user;

#endif
