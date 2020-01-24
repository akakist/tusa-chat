#include "stdafx.h"
#include "OscarClient.h"
#include "OscarServer.h"
#include "utils.h"
#ifndef _WIN32
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#endif
#include <errno.h>

void OscarService::Client::finishCreate(configObj* config)
{
	CFG_PUSH("OscarClient",config);
	OscarServiceImpl::finishCreate(config);
	std::string strConnect;
	config->set_cfg_str("connect",strConnect,"127.0.0.1:5556");
	std::vector<std::string> v=utils::splitString(":",strConnect);
	if(v.size()==2)
	{
		std::string ip=v[0];
		unsigned short port=atoi(v[1].c_str());
		int fd=socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(fd==-1) 
		{
			throw CommonError("socket failed");
		}
		{
			int i = 1;
			if(setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,(char *)&i,sizeof(i)))
			{
#ifdef _WIN32
				closesocket(fd);
#else
				close(fd);
#endif
				throw CommonError("setsockopt failed %s %d",__FILE__,__LINE__);
			}
		}
		{

			struct linger l;
			l.l_onoff=1;
			l.l_linger=(u_short)0;
			if (::setsockopt(fd,SOL_SOCKET,SO_LINGER,(char*)&l, sizeof(l))!=0)
			{
#ifdef _WIN32
				closesocket(fd);
#else
				close(fd);
#endif
				throw CommonError("setsockopt failed %s %d",__FILE__,__LINE__);
			}

		}

		sockaddr_in ra;
		ra.sin_family=AF_INET;
		ra.sin_port=htons(port);
		ra.sin_addr.s_addr=inet_addr(ip.c_str());
		if (connect(fd,(sockaddr*)&ra,sizeof(ra))==-1) {
#ifdef _WIN32
				closesocket(fd);
#else
				close(fd);
#endif
			throw CommonError("connect failed %s %d",__FILE__,__LINE__);
		}
		sendEvent(ServiceList::SocketIO,new SocketIO::Event::SOCKET_ADD(fd,false));
	}



}
OscarService::Client::Client(Service::Manager* m):OscarService::OscarServiceImpl(m,ServiceList::OscarClient){}
