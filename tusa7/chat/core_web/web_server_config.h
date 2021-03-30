#ifndef WEBSERVER_CONFIGH
#define WEBSERVER_CONFIGH
using namespace std;
#include "M_MAP.h"
#include "M_SET.h"
#include "m_var.h"
#include "file_set.h"
#ifdef __KALL
struct __web_server_config
{
    m_var<string> listen_ip;
    m_var<unsigned short>listen_port;
    m_var<unsigned int>accept_handler_timeout_usec;
    m_var<unsigned int>max_number_of_accept_handlers;
    m_var<unsigned int>max_multipart;
    m_var<unsigned int>max_post;
    M_MAP<string,string>mime_types;
    m_var<string> document_root;
    M_SET<string> doc_urls;
    m_var<unsigned int>inspector_time_usec;

    m_var<string>adminfo_url;

    params_map replacement_conf;
    map<string,vector<string> > replacements;
    _mutex replacementsMX;
    map<string,string> get_replacements();
    void init_replacements();
    void load_config(const string&pn);
    __web_server_config();
};
extern __web_server_config web_server_config;

#endif
#endif
