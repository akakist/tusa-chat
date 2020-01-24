#include "stdafx.h"
#ifdef _DEBUG
#define New DEBUG_NEW
#endif

#include "PTR.h"
#include "oscar_buffer.h"
#include "G_session.h"
#include "session_data.h"
#include "ifree_clients.h"
#include "central_server.h"
#include "RTYPES_CORE.h"
PTR_getter<ifree_client>  __ifree_clients::find(const G_session &id)
{MUTEX_INSPECTOR;
    {
        MUTEX_LOCK kall(Mutex);
		map<G_session, PTR_getter<ifree_client> >::const_iterator j=container.find(id);
        if(j!=container.end())
        {
            return j->second;
        }
    }
    return NULL;

}
void __ifree_clients::insert(const G_session& sid,const PTR_getter<ifree_client>& __U)
{
    MUTEX_LOCK kall(Mutex);
    container.insert(make_pair(sid,__U));
}
map<G_session, PTR_getter<ifree_client> >  __ifree_clients::get_container()
{
    MUTEX_LOCK kall(Mutex);
    return container;

}
vector<G_session> __ifree_clients::keys()
{
    MUTEX_LOCK kall(Mutex);
    vector<G_session> ret;
    for(map<G_session, PTR_getter<ifree_client> >::const_iterator i=container.begin();i!=container.end();i++)
    {
	ret.push_back(i->first);
    }
    return ret;

}
void __ifree_clients::erase(const G_session &s)
{
    MUTEX_LOCK kall(Mutex);
    container.erase(s);
}
void reply_ifree_client(const PTR_getter <ifree_client> &__U, int msg, const out_oscar_buffer & _data)
{MUTEX_INSPECTOR;
    PTR_getter<session_data> __SD(NULL);
    {
        PGLR(ifree_client,u,__U);
        __SD=u->session;
    }
    if(!__SD) return;

    reply_session(__SD,FAM_DATA_EVENT,msg,_data);


}
void reply_ifree_client_f(const PTR_getter <ifree_client> &__U, int fam,int subt, const out_oscar_buffer & _data)
{MUTEX_INSPECTOR;
    PTR_getter<session_data> __SD(NULL);
    {
        PGLR(ifree_client,u,__U);
        __SD=u->session;
    }
    if(!__SD) return;

    reply_session(__SD,fam,subt,_data);


}
