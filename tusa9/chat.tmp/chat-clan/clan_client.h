#ifndef CLAN_CLIENT____H
#define CLAN_CLIENT____H
#include "bos_client.h"
#include "RTYPES_CLAN.h"
#include "bos_client_interface.h"
    class clan_client: public bos_client_interface
    {
	public:
	clan_client();
	const char* getclassname()const {return "clan_client";}

	void on_data_event(int cmd,oscar_buffer & in_b);
	void on_redirector_connected();
	void on_bos_connected();
	void on_login_ok(const map<string,string> &m);
	void on_login_failed(const map<string,string> &m);
	void on_disconnect(const string& reason);
	void on_socket_create(SOCKET sock);
	void start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);
	m_var<string> auth_login;
	m_var<string> auth_password;
    
    };
    
#endif
