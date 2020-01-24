#ifndef bos_client_interface__h
#define bos_client_interface__h

#include <string>
#include <map>
#include "oscar_buffer.h"

//using namespace std;

class bos_client;
class 
bos_client_interface
{
	
    friend class bos_client;
    public:
	bos_client *data;
	bos_client_interface();	
	~bos_client_interface();
        void send_packet_to_cs(bool immediately,int cmd_code,const std::string & b);
		void send_packet_to_cs(bool immediately,int cmd_code,const out_oscar_buffer & b);
		void send_packet_to_cs(bool immediately,int cmd_code);

	
	// true if request successed
	bool send_request(int cmd_code,std::string &in,const std::string & out, time_t timeout);

	// функция для обработки пакетов вызывается из потока виндового гуи либо из созданного треда
	void handle_packets();
	
//	// встроенный тред - хендлер входящих пакетов используется как альтернатива handle_packets()
	
	// login_params мап из типа user=kkk pass=uuu все че надо на сервере для логина
    	void do_auth(const std::map<std::string,std::string> &login_params);
		void do_logout();
	void do_disconnect();
	virtual void start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m);
	std::string get_bos_addr();
	int get_bos_port();
    protected:
	virtual void on_data_event(int cmd,oscar_buffer & in_b)=0;
	virtual void on_redirector_connected()=0;
	virtual void on_bos_connected()=0;
	virtual void on_login_ok(const std::map<std::string,std::string> &m)=0;
	virtual void on_login_failed(const std::map<std::string,std::string> &m)=0;
	virtual void on_disconnect(const std::string& reason)=0;
	virtual void on_socket_create(int sock)=0;
	
};

#endif
