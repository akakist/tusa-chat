#include "stdafx.h"
#include "oscar_buffer.h"
#include "G_session.h"
//#include "c_conn.h"
#include "RTYPES_CORE.h"
#include "commonError.h"
#include "oscarService.h"
/*
void Oscar::ServiceImpl::user_session_data::clean()
{
    bos=NULL;

}
*/
/*
void reply_session(const PTR_getter<Oscar::ServiceImpl::user_session_data>& __SD,int fam,int subt,const out_oscar_buffer & _data)
{
	MUTEX_INSPECTOR;
	PTR_getter<Oscar::User> __BOS(NULL);
    BU_session sid;
    {
		PGLR(Oscar::ServiceImpl::user_session_data,s,__SD);
        __BOS=s->bos;
        sid=s->session;
    }
    REF_getter<epoll_socket_info> __S(NULL);
    if(__BOS.valid()){
		MUTEX_INSPECTOR;
		PGLR(Oscar::User, b,__BOS);
        __S=b->esi;

    }
    F_outV2 o(CHANNEL_5);
    o<<sid<<fam<<subt<<_data.as_string();
    o.calc_size();
    reply(__S,o);
}
*/