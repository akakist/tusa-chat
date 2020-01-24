#ifndef __SERVER___IO____H
#define __SERVER___IO____H

#include <string>
#include <map>
#include "oscar_buffer.h"
#include "oscar_client.h"
#include "st_rsa.h"
//using namespace std;

struct bc_data;
class bos_client_interface;
class bos_client: public oscar_client
{
    friend class bos_client_interface;

private:
    bc_data *bcd;
    Mutex bcdmx;
    static void *T_run_sio_handler(void *pr);
    static void *T_run_poll_handler(void *pr);
public:
	const char* getclassname()const {return "bos_client";}

    bos_client(bos_client_interface* __api);
    ~bos_client();
    bos_client_interface *api;
    enc_string encode_cs(const std::string&s);
    void sio();

    virtual void cleanup();
    
    void prepare_send_buffer_from_packets();
    void send_login_LK();
    void send_to_bos_des_key();
    void parse_ch1(oscar_buffer & b);
    void parse_ch2(oscar_buffer & b);
    void parse_ch4(oscar_buffer & b);
    void parse_ch5(oscar_buffer & b);
    void parse_ch6(oscar_buffer & b);
    void parse_ch3(oscar_buffer & b);

    void Poll();
    //void on_TYPE_LOGIN_SET_SESSION_ID_05_05( oscar_buffer & in_b);
    void client_send( out_oscar_buffer & b);
    void on_disconnect(const std::string& reason);
    bool send_request(int cmd_code,std::string &in,const std::string & out, time_t timeout);

    void send_request_to_redirector();

    void send_packet_to_cs2(bool immed,int family,int subtype,const out_oscar_buffer & b);
    void send_packet_to_cs2(bool immed,int family,int subtype,const std::string & b);
    void send_packet_to_cs(bool immed,int msg);
	void send_packet_to_cs(bool immed,int msg,const std::string & b);
    void send_packet_to_cs(bool immed,int msg,const out_oscar_buffer & b);
    void on_socket_create(int sock);
    void do_auth(const std::map<std::string,std::string> &login_params);
    void start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);
    void do_disconnect();
	std::string get_bos_addr();
	int get_bos_port();
    

    private:
    m_var<std::string> authorizer_server_ip;
    unsigned int authorizer_server_port;
    unsigned int sio_handler_timeout_usec;
    unsigned int poll_handler_timeout_usec;
    unsigned int ping_timeout_sec;
    unsigned int pong_kill_timeout_sec;
    unsigned int login_timeout_sec;
    unsigned int request_timeout_sec;

    void load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);
	static std::string gen_des_key();

};
#endif
