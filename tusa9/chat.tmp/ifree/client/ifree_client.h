#ifndef CLAN_CLIENT____H
#define CLAN_CLIENT____H
#include "bos_client_interface.h"
//#include "RTYPES_CLAN.h"
    class ifree_client: public bos_client_interface
    {
	public:
	ifree_client();
//	protected:
	void on_data_event(int cmd,oscar_buffer & in_b);
	void on_redirector_connected();
	void on_bos_connected();
	void on_login_ok(const map<string,string> &m);
	void on_login_failed(const map<string,string> &m);
	void on_disconnect(const string& reason);
	void on_socket_create(int sock);
    
    };
    
#endif
