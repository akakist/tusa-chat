#ifndef ________OSCAR_CLIENT____H
#define ________OSCAR_CLIENT____H
#include "OscarService.h"
namespace OscarService
{
	class Client: public OscarServiceImpl
	{
	public:
		static I::Unknown* __neu_(Service::Manager* m){return new Client(m);}
		std::string getObjectName(void){return "OscarService::Client";}
		Client(Service::Manager* m);
		void finishCreate(configObj* config);

		// dummy
//		bool do_application_login(const G_session & app_data,int client_type, const PTR_getter<user_session_data> &__SD,const std::string& ip,std::map<std::string,std::string>& m){return true;}
//		void process_data_event(int client_type, const G_session& app_data, const PTR_getter<user_session_data> &__SD, oscar_buffer& in_b,int subtype){return ;}

	};
}
#endif
