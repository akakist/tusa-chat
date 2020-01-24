#ifndef command_server__H
#define command_server__H
/*#include "web_server.h"
#include "M_SET.h"
class command_server:public web_server
{
	void *new_connection(const PTR_getter<c_socket>&s);
//	void on_inspector_iterate();
public:
	const char* getclassname()const {return "command_server";}

	command_server();
	~command_server();
	virtual void start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);
	//static void* users_handler(void*);
//	void messages_handler(void*);
	std::string server_name(){return "commandserver";}
	bool validate_peer_ip_address(const sockaddr_in & sa){return true;};
    private:

	void load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);
	time_t get_socket_inactive_kill_timeout();
	
};
*/
#endif
