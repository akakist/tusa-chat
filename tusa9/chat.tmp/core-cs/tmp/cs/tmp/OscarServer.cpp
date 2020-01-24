#include "stdafx.h"
#include "OscarServer.h"
#include "utils.h"
#include "globals.h"
#ifndef _WIN32
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#endif
#include <errno.h>

void OscarService::Server::finishCreate(configObj* config)
{
	CFG_PUSH("OscarServer",config);
	OscarServiceImpl::finishCreate(config);

	std::string strBind;
	config->set_cfg_str("bind",strBind,"INADDR_ANY:5556,INADDR_ANY:5555");
	int listen_backlog;
	config->set_cfg_i("listen_backlog",listen_backlog,128);
	std::vector<std::string> v=utils::splitString(",;",strBind);
	for (size_t i=0;i<v.size();i++)
	{
		std::vector<std::string> _vv=utils::splitString(":",v[i]);
		if (_vv.size()!=2) throw CommonError("error in config %s",strBind.c_str());
		std::string serviceAddr=_vv[0];
		std::string servicePort=_vv[1];
		SOCKET_fd sock=::socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (CONTAINER(sock)==-1) {
			throw CommonError("Server: socket()  failed %s %s %d",strerror(errno),__FILE__,__LINE__);
		}
		struct sockaddr_in sa;
		sa.sin_family = AF_INET;
		sa.sin_port = htons(atoi(servicePort.c_str()));
		{
			if (serviceAddr=="INADDR_ANY") sa.sin_addr.s_addr = INADDR_ANY;
			else sa.sin_addr.s_addr = inet_addr(serviceAddr.c_str());
		}
		{
			int i = 1;
			i=setsockopt(CONTAINER(sock),SOL_SOCKET,SO_REUSEADDR,(char *)&i,sizeof(i));
		}
		logErr2("binding OscarServer sock to %s:%s",serviceAddr.c_str(),servicePort.c_str());
		while (bind (CONTAINER(sock),(struct sockaddr *) &sa, sizeof (sa)) == -1)
		{
			logErr2("Server: bind()  failed: %s %s:%d %s %d", strerror(errno),inet_ntoa(sa.sin_addr),htons(sa.sin_port),__FILE__,__LINE__);
			sleep(1);
			if (globals::g_bAppIsTerminating) return;
			logErr2("binded to %s:%d",inet_ntoa(sa.sin_addr),htons(sa.sin_port));
		}
		if (listen(CONTAINER(sock),listen_backlog)==-1) {
			throw CommonError("listen() '%s' failed: %s %s %d",strerror(errno),__FILE__,__LINE__);
		}
		sendEvent(ServiceList::SocketIO,new SocketIO::Event::SOCKET_ADD(sock,true));
	}

}
OscarService::Server::Server(Service::Manager* m):OscarService::OscarServiceImpl(m,ServiceList::OscarServer){}
