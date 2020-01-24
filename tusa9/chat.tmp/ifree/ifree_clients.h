#ifndef CHAT_CLASS___H
#define CHAT_CLASS___H
#include "G_session.h"
#include "session_data.h"
#include "DB_id.h"
#include "RTYPES_CLAN.h"
class ifree_client: public base_container
{
    public:
	const char* getclassname()const {return "ifree_client";}

	G_session session_id;
	PTR_getter<session_data> session;
	string ip;
	time_t login_time;
	ifree_client();
};
class __ifree_clients
{
	_mutex Mutex;
	map<G_session, PTR_getter<ifree_client> > container;
	public:
	void insert(const G_session& sid,const PTR_getter<ifree_client>& __U);
	void erase(const G_session &);
	int size();
	vector<G_session> keys();
	PTR_getter<ifree_client> find(const G_session &);
	map<G_session, PTR_getter<ifree_client> >  get_container();
	void on_iterate();
	__ifree_clients():Mutex("__ifree_clients"){}
	
};
extern __ifree_clients ifree_clients;

void reply_ifree_client(const PTR_getter <ifree_client> &__U, int msg, const out_oscar_buffer & _data);
void reply_ifree_client_f(const PTR_getter <ifree_client> &__U, int fam, int stype, const out_oscar_buffer & _data);
#endif
