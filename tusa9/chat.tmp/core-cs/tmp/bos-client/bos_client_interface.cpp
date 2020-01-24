#include "stdafx.h"
#include "m_var.h"
#include "bos_client.h"
#include "bos_client_interface.h"

void bos_client_interface::send_packet_to_cs(bool immediately,int cmd_code,const std::string & b)
{
    data->send_packet_to_cs(immediately,cmd_code, b);
}
void bos_client_interface::send_packet_to_cs(bool immediately,int cmd_code,const out_oscar_buffer & b)
{
	data->send_packet_to_cs(immediately,cmd_code, b);
}
void bos_client_interface::send_packet_to_cs(bool immediately,int cmd_code)
{
	data->send_packet_to_cs(immediately,cmd_code);
}
bool bos_client_interface::send_request(int cmd_code,std::string &in,const std::string & out, time_t timeout)
{
    return data->send_request(cmd_code,in,out,timeout);
}
void bos_client_interface::handle_packets()
{
    data->handle_packets();
}
bos_client_interface::~bos_client_interface()
{
	delete data;
}
bos_client_interface::bos_client_interface(): data(new bos_client(this)){}
void bos_client_interface::do_auth(const std::map<std::string,std::string> &login_params)
{
	MUTEX_INSPECTOR;
    data->do_auth(login_params);
}
void bos_client_interface::start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{
    data->start(pn,prefix,m);
}
void bos_client_interface::do_disconnect()
{
    data->do_disconnect();
}
std::string bos_client_interface::get_bos_addr()
{
	return data->get_bos_addr();
}
int bos_client_interface::get_bos_port()
{
	return data->get_bos_port();
}
