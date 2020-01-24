#ifndef ________OSCAR_SERVER_____H
#define ________OSCAR_SERVER_____H
#include "OscarService.h"
namespace OscarService
{
	class Server: public OscarServiceImpl
	{
	public:
		static I::Unknown* __neu_(Service::Manager* m){return new Server(m);}
		std::string getObjectName(void){return "OscarService::Server";}
		Server(Service::Manager* m);
		void finishCreate(configObj* config);

	};
}

#endif
