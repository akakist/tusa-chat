#ifndef ooscar___cli__H
#define ooscar___cli__H
#include "threadable.h"
struct oscar_client_data;
class oscar_client:public threadable
{
private:
    oscar_client_data* ocd;
    _mutex ocdmx;
    bool Parse(); // true if stop thread
    bool Recv(); // true if stop thread
    bool start_parser;
public:
    oscar_client(bool __start_parser);
    virtual ~oscar_client();
    virtual void parse_ch1(oscar_buffer & b)=0;
    virtual void parse_ch2(oscar_buffer & b)=0;
    virtual void parse_ch3(oscar_buffer & b)=0;
    virtual void parse_ch4(oscar_buffer & b)=0;
    virtual void parse_ch5(oscar_buffer & b)=0;
    virtual void parse_ch6(oscar_buffer & b)=0;
    void client_connect( const char *host, unsigned short port);
    void reply(const string& buf);
    virtual void on_socket_create(int sock)=0;
    void do_parse();
private:
    pthread_t parse_thread;
    pthread_t recv_thread;
    static void *parse_handler(void *pr);
    static void *recv_handler(void *pr);
public:
//    void start_parse_handler();
//    void start_recv_handler();
    void do_disconnect();


    void break_connect(const string &reason);
    virtual void on_disconnect(const string& reason)=0;
    virtual void start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);

private:
    void load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);
    m_var<unsigned int> parse_handler_timeout_usec;
    m_var<unsigned int> recv_handler_timeout_usec;
    m_var<string> bind_ip;

};

#endif
