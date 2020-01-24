#include "stdafx.h"
#include <errno.h>
#include "c_conn.h"
#include "bos_server.h"
#include "udp_addr.h"
#include "udp_packet.h"
#include <unistd.h>
 
bool readable_abs(const PTR_getter<c_socket> &__S,int millsec, bool ckIntBuf);

void bos_server::udp_handler_worker()
{
	log_start_thread(server_name()+" udp_handler");
	while(1)
	{
		{
			MUTEX_INSPECTORS("SLEEP");
			sleep(udp_handler_time_usec);
		}
		try{
			if(!udp_socket.valid())
			{
				logErr2("!serv->udp_socket");
				continue;
			}
			{
				char buffer[1024];
				msockaddr_in sa;
				socklen_t len=sizeof(sa);
				if(!readable_abs(udp_socket,0,false)) continue;
				int res=0;
				{
					PGLW(c_socket,s,udp_socket);
					int fd=CONTAINER(s->get_socket_fd());
					if(fd==-1)
					{
						logErr2("bad socket");
						continue;
					}

#ifndef WIN32
					res=::recvfrom(fd,(void*)buffer,sizeof(buffer)-1,0,(sockaddr*)&sa,&len);
#else
					res=::recvfrom(fd,buffer,sizeof(buffer)-1,0,(sockaddr*)&sa,&len);
#endif
					if(res==-1)
					{
						logErr2("udp_fd: %s",strerror(errno));
					}
				}
				if(res==-1)
				{
					logErr2("res==-1");
					continue;
				}
				if (len > 0 && res>0)
				{
					oscar_buffer in_b((unsigned char*) buffer,res);
					std::deque<PTR_getter_nm<udp_packet> > dP(create_from_buffer(in_b,sa));

					while(dP.size())
					{
						PTR_getter_nm<udp_packet> P(*dP.begin());
						dP.pop_front();
						if(P.valid())
						{
							udp_packet *p=P.___ptr;
							switch(p->type)
							{
							case UDP_PING: 
								{
									MUTEX_INSPECTOR;
									pUDP_PING *pp=(pUDP_PING*)p;
									PTR_getter_nm<udp_packet> PS(new pUDP_SET_YOUR_EXTERNAL_SA(sa,pp->sender_gid));
									PS.___ptr->send_self(udp_socket,sa);
								}
							}
						}
						else
						{
							logErr2("error init udp packet");
						}
					}
				}


			}
		}STDCATCHS("udp handler");
	}

}
void* bos_server::udp_handler(void*pr)
{
	bos_server *serv=(bos_server*)pr;
	serv->udp_handler_worker();
	return NULL;
}
