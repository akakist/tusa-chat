#ifndef APP_CON__H
#define APP_CON__H
#include "web_connection.h"
#include "PTR.h"
#include "c_conn.h"
#include <string>
#include <map>
class app_connection: public web_connection
{
public:
    void process_web();
    app_connection(
        app_server *p,
        const PTR_getter<c_socket>&s
#ifdef __MCASSA
        ,bool _is_cassa
#endif
    );
    app_server *server;

    void postinit_rvmap(map<string,string> &m);

    void redirect(const string &url);
    void init_temp_vars(const PTR_getter<chat_user> &__ZZ );

    ////////////// COPY from CHATUSER
    bool user_unregistered;
    DB_id user_id;
    unsigned int sub_level;
#ifdef __MCASSA
    bool is_cassa;
#endif
    vector<string>vurl;
};


#endif
