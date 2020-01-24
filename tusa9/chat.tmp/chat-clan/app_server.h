#ifndef APP_SERVER__H
#define APP_SERVER__H
#include "web_server.h"
#include "M_SET.h"
class app_server:public web_server
{
	void *new_connection(const PTR_getter<c_socket>&s);
	void on_inspector_iterate();
	static void *PTHR_users_handler(void *pr);
	static void *PTHR_clan_parser(void *pr);

public:
	const char* getclassname()const {return "app_server";}

	app_server();
	~app_server();
	void start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);
	void users_handler(void*);
	void messages_handler(void*);
	std::string server_name(){return "chatserver";}
	//CONF	
	m_var<string> document_root;
	M_SET<string> doc_urls;
	//ENDCONF
	bool validate_peer_ip_address(const sockaddr_in & sa){return true;};
	time_t get_socket_inactive_kill_timeout();


};

#endif
