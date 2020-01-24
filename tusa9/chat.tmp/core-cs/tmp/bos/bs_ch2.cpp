#include "stdafx.h"
#include "bos_server.h"
#include "str_lib.h"
#include "RTYPES_CORE.h"

void bos_server::parse_ch2(const PTR_getter<c_socket>& __SD,oscar_buffer &in_b)
{
    MUTEX_INSPECTOR;
    unsigned int family;//=in_b.get_8();
    unsigned int subtype;//=in_b.get_8();
    in_b>>family>>subtype;
    PTR_getter<bs_user> __U(NULL);
    std::string sid;
    std::string ip;
    if (__SD.valid()) {
        PGLR(c_socket,sd,__SD);
        ip=sd->peer_ipaddress;
        if (sd->extra_user_id!="")
        {
            sid=sd->extra_user_id;
        }
    }
    NOTPTR(__SD);
    if (sid!="") {
        BU_session bid;
        CONTAINER(bid)=atoi(sid);
        __U=__bs_users._BS_find(bid);
    }
    if (!__U.valid()) {//MUTEX_INSPECTOR;
        logErr2("--Warning: Parse ch2 on non existent user kill socket");
        PTR_getter<c_socket>__S(NULL);
        if (__SD.valid()) {//MUTEX_INSPECTOR;

            disconnect(__SD);

            logErr2("--Report: socket closed on non existent user");
            return;
        }
        else
        {
            logErr2("--Warning: socket not valid on channel 2\n%s",_DMI().c_str());
        }

        throw CommonError("!PU"+_DMI());
    }




    if (!__U.valid()) {//MUTEX_INSPECTOR;
        throw CommonError("!U"+_DMI());
    }

    BU_session session_id;
    if (__U.valid()) {//MUTEX_INSPECTOR;
        {
            PGLW(bs_user,u,__U);
            u->last_access_time=time(NULL);

            session_id=u->session_id;

        }
    }
    NOTPTR(__U);

    if (family==FAM_OTHER && subtype==TYPE_PING_09) // ping
    {//MUTEX_INSPECTOR;
        FS_outV2 b(CHANNEL_2,FAM_OTHER,TYPE_PONG_0A);

        bs_user::reply(__U,b); //pong


        return;
    }

}
