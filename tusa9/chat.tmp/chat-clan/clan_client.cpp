#include "stdafx.h"
#ifdef _DEBUG
#define New DEBUG_NEW
#endif

#include "m_var.h"
#include "mutex_inspector.h"
#include "clan_client.h"
#include "version.h"
#include "str_lib.h"
#include "user.h"


extern unsigned int clan_id;
void clan_client::on_redirector_connected()
{
//    logErr2("void clan_client::on_redirector_connectedUNDEF %s %d",__FILE__,__LINE__);
}
void clan_client::on_bos_connected()
{
//    logErr2("clan_client::on_bos_connected UNDEF %s %d",__FILE__,__LINE__);
}
bool check_versions(const string &a,const string &b)
{
	vector<string> v1=splitTOK(".",a);
	vector<string> v2=splitTOK(".",b);
	if(v1.size()!=4 || v2.size()!=4)
		return false;
	if(		v1[0]==v2[0]
		&&	v1[1]==v2[1]
		&&	v1[2]==v2[2]
	)
		return true;
	return false;
}
void clan_client::on_login_ok(const map<string,string> &m)
{

//    logErr2("clan_client::on_login_ok %s %d",__FILE__,__LINE__);

	if(m.count("SV"))
	{
		MUTEX_INSPECTOR;
		if(!check_versions(m.find("SV")->second,SERVER_VERSION_INT))
		{
			MUTEX_INSPECTOR;
			logErr2("Incompatible version. Please download version %s",m.find("SV")->second.c_str());
			sleep(1);
			exit(1);
		}
		if(m.find("SV")->second!=SERVER_VERSION_INT)
			logErr2("New version released %s, please use newest version",m.find("SV")->second.c_str());


	}

	    logErr2("CLAN logged in");
#ifdef DEBUG	    
	    for(map<string,string>::const_iterator i=m.begin();i!=m.end();i++)
	    {MUTEX_INSPECTOR;
		logErr2("%s=%s",i->first.c_str(),i->second.c_str());
	    }
#endif	    
	    if(m.count("clan_id"))
		clan_id=atoi(m.find("clan_id")->second);
    
}
void clan_client::on_login_failed(const map<string,string> &m)
{
//    logErr2("UNDEF clan_client::on_login_failed %s %d",__FILE__,__LINE__);
	string res;
	if(m.count("result")) res=m.find("result")->second;
	logErr2("failed login: %s", res.c_str());
    logErr2("fatal error: login failed...");exit(1);
}
void clan_client::on_disconnect(const string& reason)
{

#ifdef DEBUG
	logErr2("%s UNDEF clan_client::on_disconnect %s %d",reason.c_str(),__FILE__,__LINE__);
#endif	

	map<string,string> mm;
	mm["login"]=auth_login;
	mm["pass"]=auth_password;
	mm["client_type"]="2";
	mm["SV"]=SERVER_VERSION_INT;
	mm["clan_id"]=itostring(CONTAINER(g_clan_id.get()));
	do_auth(mm);
    
}
void clan_client::on_socket_create(SOCKET sock)
{
//    logErr2("clan_client::on_socket_create %s %d",__FILE__,__LINE__);
}
clan_client::clan_client(): bos_client_interface()
{
//    logErr2("clan_client::clan_client() UNDEF %s %d",__FILE__,__LINE__);
}
void clan_client::start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{
    bos_client_interface::start(pn,prefix,m);
    set_cfg_str(m,	prefix+"auth_login", pn,auth_login, "login");
    set_cfg_str(m,	prefix+"auth_password", pn,auth_password, "password");
    
    
}
