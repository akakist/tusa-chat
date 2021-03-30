#ifndef WEB_SERVER_H__
#define WEB_SERVER_H__
#include "PTR.h"
#include "tcp_server.h"
#include "M_MAP.h"
#include "M_SET.h"
#include "file_set.h"
using namespace std;
//class web_server_data;
class  params_map;
class web_server : public tcp_server
{

private:
    void load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);
    void load_mime_types();

protected:

public:
    void *new_connection(const PTR_getter<c_socket>&s);
    virtual ~web_server();
    web_server();
    virtual void start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);

    //	{CONF
    m_var<unsigned int> max_multipart;
    m_var<unsigned int> max_post;
    M_MAP<string,string> mime_types;
    m_var<string> document_root;
    M_SET<string> doc_urls;
    m_var<unsigned int>inspector_time_usec;
    m_var<string>adminfo_url;
    params_map replacement_conf;
    map<string,vector<string> > replacements;
    _mutex replacementsMX;
    map<string,string> get_replacements();
    //	}
};



#endif
