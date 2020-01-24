#ifndef appm_centarl_server__H
#define appm_centarl_server__H


#include "oscarService.h"

class app_cs_server : public Oscar::ServiceImpl
{
    void load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);
public:
	const char* getclassname()const {return "app_cs_server";}

    virtual void start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);
    
    app_cs_server(Service::Manager *m);
				   




    void on_iterate(std::map<std::string,std::string> &m);
    std::string do_adminfo();
    bool do_application_login(const G_session& gsess, int client_type, const PTR_getter<user_session_data> &__SD,const std::string& ip,std::map<std::string,std::string>& m);
    void process_data_event(int client_type, const G_session& app_data, const PTR_getter<user_session_data> &__SD, oscar_buffer& in_b,int subtype);
    bool process_request(int client_type, const G_session& app_data, const PTR_getter<user_session_data> &__SD, oscar_buffer& in_b,int subtype, int req_id, out_oscar_buffer& out);

private:
public:
    void on_delete_session(int client_type,const G_session& app_data,const PTR_getter<user_session_data>&SD);
	

};


#endif
