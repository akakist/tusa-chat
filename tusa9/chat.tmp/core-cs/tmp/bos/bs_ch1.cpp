#include "stdafx.h"
#include <list>
#include "mutexable.h"
#include <stdio.h>
#include "commonError.h"
#include <signal.h>

#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>
#include <algorithm>
#include "file_set.h"
#include "tcp_stats.h"
#include "server_config.h"
#include "lockctl.h"
#include "bos_server.h"

#include "oscar_buffer.h"
#include "RTYPES_CORE.h"
#include "BU_session.h"
#include "globals.h"
#include "utils.h"
#include "SOCKET_fd.h"
namespace globals{
static Mutex session_id_MX;
static unsigned int session_generator=1;
};
static BU_session next_session_id()
{
	MUTEX_INSPECTOR;
	M_LOCK(globals::session_id_MX);
    BU_session b;
    while(1)
    {
        CONTAINER(b)=globals::session_generator++;
        if(CONTAINER(b)!=0) return b;
    }
    return b;
}

void bos_server::parse_ch1_CLI2BOS_CONNECT_SSL(const PTR_getter<c_socket>& __SD,oscar_buffer &bzz)
{
	MUTEX_INSPECTOR;
    std::string ip;
    if(!__SD.valid()) return;
	{
		PGLR(c_socket,s,__SD);
        ip=s->peer_ipaddress;
	}

    enc_string es;
    bzz>>es.original_size>>es.buf;
    std::string key;
    {
        PGLW(c_socket,sd,__SD);
		if(sd->rsa)
		{
			key=sd->rsa->private_decrypt(es);
		}
    }
    if(key.size()!=RIJNDAEL_KEYSIZE){
        logErr2("key suze!=RIJNDAEL_KEYSIZE (%d)", key.size());
        disconnect(__SD);return;

    }

    bs_user *bu=NULL;
    PTR_getter<bs_user> BU(NULL);
    BU_session session_id;
    {
        bu=new bs_user;
		bu->__socket=__SD;
        bu->session_id=next_session_id();
        session_id=bu->session_id;
        bu->authorized=false;
        bu->last_access_time=time(NULL);
        bu->peer_ipaddress=ip;
        memcpy(bu->rjKey,key.data(),key.size());
        memset(bu->rjIV_in,0,sizeof(bu->rjIV_in));
        memset(bu->rjIV_out,0,sizeof(bu->rjIV_out));
        bu->rjctx_in.mode=MODE_CFB;
        bu->rjctx_out.mode=MODE_CFB;
        rijndael_setup(&bu->rjctx_in, RIJNDAEL_KEYSIZE, bu->rjKey);
        rijndael_setup(&bu->rjctx_out, RIJNDAEL_KEYSIZE, bu->rjKey);


        BU=PTR_getter<bs_user> (bu);
    }
    unsigned int uid=0;
    if(__SD.valid()){
	{
        PGLW(c_socket,sd,__SD);
        sd->extra_user_id=utils::itostring(CONTAINER(session_id));

	}
        __bs_users._BS_insert(session_id,BU);
    }NOTPTR(__SD);



  
    {
        int l_sec=client_linger_sec;
        if(__SD.valid()){
            PGLW(c_socket,s,__SD);
            SOCKET_fd fd;CONTAINER(fd)=-1;
            try{
                fd=s->get_socket_fd();
                s->sock_linger(l_sec);
            }
            catch(...)
            {
                logErr2("linger failed %d",CONTAINER(fd));
            }
        }NOTPTR(__SD);
    }
    if(BU.valid())
    {
        FS_outV2 bb(CHANNEL_2,FAM_LOGIN,TYPE_LOGIN_SET_SESSION_ID_05);
        bb<<session_id;
        bs_user::reply(BU,bb);
    }NOTPTR(BU);

}

void bos_server::parse_ch1(const PTR_getter<c_socket>& __SD,oscar_buffer& b)
{
	MUTEX_INSPECTOR;
    unsigned int first;
    b>>first;
    if(first==3)
    {
        parse_ch1_CLI2BOS_CONNECT_SSL(__SD,b);

    }
    else logErr2("--Error: Undefined client type '%d' %s %s %d",first,_DMI().c_str(),__FILE__,__LINE__);
}


