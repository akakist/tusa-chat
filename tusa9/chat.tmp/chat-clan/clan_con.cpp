#include "stdafx.h"
#ifdef _DEBUG
#define New DEBUG_NEW
#endif

using namespace std;
#include "PTR.h"
#include <deque>
#include "html_out.h"
#include "web_connection.h"

#include "clan_con.h"
#include "app_con.h"
__clan_cons clan_cons;

m_var<int> clan_con_id_gen;
clan_con::clan_con() : base_container("clan_con"),create_time(time(NULL)),wc(NULL)
{
    luid=++clan_con_id_gen;
}
clan_con::~clan_con()
{
	if(wc) {

		LEAKCTL_REMOVE(wc);delete wc;
	}

}
__clan_cons::__clan_cons():Mutex("clan_cons"){}
PTR_getter<clan_con> __clan_cons::find(int luid)
{
    MUTEX_LOCK kall(Mutex);
    if(container.count(luid)) return container.find(luid)->second;
    return NULL;
}

void __clan_cons::insert(const PTR_getter<clan_con> &__CLU)
{
    int luid;
    {
	PGLR(clan_con,u,__CLU);
	luid=u->luid;
    }
    {
	MUTEX_LOCK kall(Mutex);
	container.insert(make_pair(luid,__CLU));
    }
}
PTR_getter<clan_con> __clan_cons::extract(int luid)
{
    MUTEX_LOCK kall(Mutex);
    PTR_getter<clan_con> ret(NULL);
    if(container.count(luid))
    {
	 ret=container.find(luid)->second;
	 container.erase(luid);
    }
    return ret;
    
}
