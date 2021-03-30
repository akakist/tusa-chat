#ifndef APP_SERVER__H
#define APP_SERVER__H
#include "web_server.h"
#include "M_SET.h"
class app_server:public web_server
{
    void *new_connection(const PTR_getter<c_socket>&s);
    void on_inspector_iterate();
public:
    app_server(
#ifdef __MCASSA
        bool _is_cassa
#endif
    );
    ~app_server();
    virtual void start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);
    static void* users_handler(void*);
    m_var<pthread_t> pth_users_handler;
    void messages_handler(void*);
    std::string server_name() {
        return "chatserver";
    }
#ifdef __MCASSA
    bool is_cassa;
#endif
    bool validate_peer_ip_address(const sockaddr_in & sa) {
        return true;
    };
private:

    void load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);

};

#endif
