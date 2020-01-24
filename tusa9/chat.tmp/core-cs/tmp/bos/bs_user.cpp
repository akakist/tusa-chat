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
#include "c_conn.h"
#include "oscar_buffer.h"
#include "bs_user.h"

#include "rijndael.h"
#include "RTYPES_CORE.h"
#include "bos_server.h"

bs_user::bs_user(): __socket(NULL),base_container("bs_user"), authorized(false),create_time(time(NULL))
{
    memset(rjKey,0,sizeof(rjKey));
    memset(&rjctx_in,0,sizeof(rjctx_in));
    memset(&rjctx_out,0,sizeof(rjctx_out));
    memset(rjIV_in,0,sizeof(rjIV_in));
    memset(rjIV_out,0,sizeof(rjIV_out));
}
bs_user::~bs_user(){
	try
	{
		//logErr2("bs_user::~bs_user() %s",_DMI().c_str());
	}
	catch(...)
	{
	logErr2("catchd %s %d",__FILE__,__LINE__);
	}
}
size_t ___bs_users::_BS_size()
{
    M_LOCK(this);
    return container.size();
}

void ___bs_users::_BS_insert(const BU_session& id, const PTR_getter<bs_user>& __U)
{
	MUTEX_INSPECTOR;
    std::string ip;
    if(__U.valid()){
        PGLR(bs_user,b,__U);
        ip=b->peer_ipaddress;
    }
    size_t uc;
    {
        M_LOCK(this);
        container.insert(std::pair<BU_session, PTR_getter<bs_user> >(id,__U));
        uc=container.size();
    }
    logErr2("USER_LOGIN SID=%d CIP='%s' BUC=%d",CONTAINER(id),ip.c_str(),uc);
}
PTR_getter<bs_user> ___bs_users::_BS_find(const BU_session& id)
{
	MUTEX_INSPECTOR;
    M_LOCK(this);
    PTR_getter<bs_user> ret(NULL);
	std::map<BU_session, PTR_getter<bs_user> >::iterator i=container.find(id);
    if(i!=container.end()) ret=i->second;

    return ret;
}

static void reply_bs_user(const PTR_getter<bs_user> &__U, const std::string & _data)
{
	MUTEX_INSPECTOR;
    PTR_getter<c_socket> __S(NULL);
    if(__U.valid()){//MUTEX_INSPECTOR;
        PGLW(bs_user,u,__U);
        __S=u->__socket;
    }NOTPTR(__U);
    if(__S.valid())
    {//MUTEX_INSPECTOR;
        reply_socket(__S,_data);
    }NOTPTR(__S);
}
void bs_user::reply(const PTR_getter<bs_user> &__U, const OCALC & _data)
{
	MUTEX_INSPECTOR;
    PTR_getter<c_socket> __S(NULL);
    if(__U.valid()){//MUTEX_INSPECTOR;
        PGLW(bs_user,u,__U);
        __S=u->__socket;
    }NOTPTR(__U);
    if(__S.valid())
    {//MUTEX_INSPECTOR;
        reply_socket(__S,_data);
    }NOTPTR(__S);
}

size_t ___bs_users::_BS_count(const BU_session& id)
{
    M_LOCK(this);
    return container.count(id);
}
void ___bs_users::_BS_erase(const BU_session& id)
{
	MUTEX_INSPECTOR;

    PTR_getter<bs_user> __BU(_BS_find(id));
    std::string ip;
    if(__BU.valid()){
        PGLR(bs_user,b,__BU);
        ip=b->peer_ipaddress;
    }NOTPTR(__BU);
    size_t uc;
    {
        {
            M_LOCK(this);
            container.erase(id);
            uc=container.size();
        }

        FS_outV2 b(CHANNEL_2,FAM_B2CS_USER_MANAGE_10,TYPE_B2CS_USER_MANAGE_DELETE_USER_02);
        b<<id;
        server->client->reply(OCALC(b).as_string()); // delete user
    }
    if(ip.size())
    {
        logErr2("USER_LOGOFF SID=%d CIP='%s' BUC=%d",CONTAINER(id),ip.c_str(),uc);
    }

}
void ___bs_users::on_iterate()
{
	MUTEX_INSPECTOR;

    std::map<BU_session, PTR_getter<bs_user> > cc;
    {
        M_LOCK(this);
        cc=container;
    }
    for(std::map<BU_session, PTR_getter<bs_user> >::iterator i=cc.begin();i!=cc.end();i++)
    {
        PTR_getter<c_socket> __S(NULL);
        if(i->second.valid()){
            PGLR(bs_user,b,i->second);
            __S=b->__socket;
        }
        bool need_erase=false;
        if(__S.valid())
        {
            PGLR(c_socket,s,__S);
            if(!s->connected())
                need_erase=true;
        }NOTPTR(__S);
        if(!need_erase)
        {//MUTEX_INSPECTOR;
            if(i->second.valid()){//MUTEX_INSPECTOR;
                PGLR(bs_user, b,i->second);
				/*
                if(time(NULL)-b->last_access_time>server->client_kill_ping_timeout_sec)
                {
                    need_erase=true;
                    logErr2("user (%d) (%s) disconnected due ping timeout",CONTAINER(b->session_id) , b->peer_ipaddress.c_str());

                }
				*/
            }NOTPTR(i_second);
        }
        if(need_erase)
        {//MUTEX_INSPECTOR;
            if(__S.valid())
            {
                disconnect(__S);
            }NOTPTR(__S);
            _BS_erase(i->first);
        }
    }

}
std::vector<BU_session> ___bs_users::_BS_keys()
{
	MUTEX_INSPECTOR;

    std::vector<BU_session> r;
    {
        M_LOCK(this);
        for(std::map<BU_session, PTR_getter<bs_user> >::iterator i=container.begin();i!=container.end();i++)
            r.push_back(i->first);

    }
    return r;
}
std::string bs_user::rjDecode(const enc_string & in)
{
	MUTEX_INSPECTOR;
    if(in.buf.size()%RIJNDAEL_BLOCKSIZE){ logErr2("invalid buffer size %s %d",__FILE__,__LINE__);
        throw CommonError("invalid buffer size");
    }
    unsigned char *out=(unsigned char *)malloc(in.buf.size()+16);
    if(out)
    {
        block_decrypt(&rjctx_in, (const unsigned char*)in.buf.data(), in.buf.size(),out, rjIV_in);
        std::string o=std::string((char*)out,in.original_size);
        free(out);
        return o;
    }


    return "";
}
enc_string  bs_user::rjEncode(const std::string &in)
{
	MUTEX_INSPECTOR;
    enc_string r;
    unsigned char *b=(unsigned char *)malloc(in.size()+RIJNDAEL_BLOCKSIZE);
    memcpy(b,in.data(),in.size());
    size_t len=in.size();
    if(len%RIJNDAEL_BLOCKSIZE){ len+=RIJNDAEL_BLOCKSIZE-(len%RIJNDAEL_BLOCKSIZE);}
    for(size_t ii=in.size();ii<len;ii++)
        b[ii]=rand();
    if(len%RIJNDAEL_BLOCKSIZE)
    {
	if(b){ free(b); b=NULL;}
	 throw CommonError("if(len%16) ");
    }	 
    unsigned char *out=(unsigned char *)malloc(len);
    block_encrypt(&rjctx_out, b, len,out, rjIV_out);
    r.buf=std::string((char*)out,len);
    r.original_size=in.size();
    if(b){ free(b);b=NULL;}
    if(out){ free(out);out=NULL;}
    return r;
}
void ___bs_users::_BS_clear()
{
//    logErr2("void ___bs_users::_BS_clear()");
    std::map<BU_session, PTR_getter<bs_user> > c;
    {
	M_LOCK(this);
	c=container;
	container.clear();
    }    
    for(std::map<BU_session, PTR_getter<bs_user> >::iterator i=c.begin();i!=c.end();i++)
    {
	PTR_getter<c_socket>s(NULL);
	{
	    PGLW(bs_user,u,i->second);
	    s=u->__socket;
	}
	if(s.valid())disconnect(s);
    }
    

}

