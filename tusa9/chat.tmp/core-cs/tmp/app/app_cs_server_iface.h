#ifndef app_cs_server_iface__h
#define app_cs_server_iface__h
#include "G_session.h"
#include "oscarService.h"

typedef void (*ONDELETE_SESSION_FUNCTION)(const G_session& app_data,const PTR_getter<Oscar::ServiceImpl::user_session_data>&SD);
typedef bool (*DO_APPLICATION_LOGIN_FUNCTION)(const G_session& sess,const PTR_getter<Oscar::ServiceImpl::user_session_data> &__SD,const std::string& ip,std::map<std::string,std::string>& m);
typedef std::string (*DO_ADMINFO_FUNCTION)();
typedef void (*ON_ITERATE_FUNCTION)(std::map<std::string,std::string> &m);
typedef void (*LOAD_CONFIG_FUNCTION)(const std::string&);
typedef void (*INIT_FUNCTION)();
typedef void (*DEINIT_FUNCTION)();
typedef void (*PROCESS_DATA_EVENT_FUNCTION)(const G_session& app_data, const PTR_getter<Oscar::ServiceImpl::user_session_data> &__SD, oscar_buffer& in_b,int subtype);
typedef bool (*PROCESS_REQUEST_FUNCTION)(const G_session& app_data, const PTR_getter<Oscar::ServiceImpl::user_session_data> &__SD, oscar_buffer& in_b,int subtype, int req_id, out_oscar_buffer& out);


struct app_interface
{
    int client_type;
    ONDELETE_SESSION_FUNCTION _ONDELETE_SESSION_FUNCTION;
    DO_APPLICATION_LOGIN_FUNCTION _DO_APPLICATION_LOGIN_FUNCTION;
    DO_ADMINFO_FUNCTION _DO_ADMINFO_FUNCTION;
    ON_ITERATE_FUNCTION _ON_ITERATE_FUNCTION;
    LOAD_CONFIG_FUNCTION _LOAD_CONFIG_FUNCTION;
    INIT_FUNCTION _INIT_FUNCTION;
    DEINIT_FUNCTION _DEINIT_FUNCTION;
    PROCESS_DATA_EVENT_FUNCTION _PROCESS_DATA_EVENT_FUNCTION;
    PROCESS_REQUEST_FUNCTION _PROCESS_REQUEST_FUNCTION;
};
#endif
