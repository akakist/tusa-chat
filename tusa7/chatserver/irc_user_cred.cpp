#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <stdio.h>
#include <map>
#include "user.h"
#include "str_lib.h"
#include "st_stuff.h"
#include "errs.h"
#include "message.h"
#include "chat_def.h"
#include "utils.h"
#include "irc_server.h"
#include "register.h"
#include "file_set.h"
#include "web_server_data.h"
#include "register.h"
#include "channels.h"
#include "server_config.h"
#include "irc_server_config.h"

#include "user_credits.h"
#include "thread_descr.h"
#include "irc_utils.h"
#include "tcp_stats.h"
#include "chat_thread_event.h"
#include "irc_session.h"
#include "chat_globals.h"
void irc_cmd_UTTC(const PTR_getter<chat_user> &__UU,irc_command &cmd)
{
    user_pair __U(__UU);
    if (!user$privileges(__U)& u_is_credit_operator)
    {
        irc_send_reply(__UU,421,cmd.command+": Unauthorized command");
        return;

    }
    vector<string> vV=splitTOK(" ",cmd.data);
    if (vV.size()==4) {

        string nick=vV[0];
        string summa=vV[1];
        string type=vV[2];
        string cookie=vV[3];

        DB_id to;
        DB_id from=all_user_nick_2_DB_id(nick);

        if (from.container==0) {
            st_dbh d;
            from.container=atoi(d.dbh->select_1Q((QUERY)"select uid from nicks where str_nick='?'"<<str_nick(nick)));
        }
        if (from.container==0) {
            irc_send_reply(__U,401,"No such nick/channel.");
            return;
        }
        if (!(user$privileges(__U)&u_allow_tags)) {
            irc_send_reply(__U,401,"Bad command");
            return;
        }

        to=user$id(__U);

        double tot_cost=atof(summa.c_str());
        bool OK = false;
        if (tot_cost>0 )
        {
            if (buy_thing(from,to,tot_cost, type)) // true if success
            {
                data_push_back(__U.cu,"UTTC_REPLY "+nick+":OK:"+ftostring(tot_cost)+":"+cookie+":"+ftostring(credit_reminder(from))+":"+ftostring(credit_reminder(to))+"\n");
            } else {
                data_push_back(__U.cu,"UTTC_REPLY "+nick+":FAIL:Not_enough_credits:"+cookie+":0:0"+"\n");
            }
        }
        else
            data_push_back(__U.cu,"UTTC_REPLY "+nick+":FAIL:Not_enough_credits:"+cookie+":0:0"+"\n");
        return;
    }
    else
        data_push_back(__U.cu,"UTTC_REPLY invalid_format\n");
}

void irc_cmd_CTTU(const PTR_getter<chat_user> &__UU,irc_command &cmd)
{
    user_pair __U(__UU);
    if (!user$privileges(__U)& u_is_credit_operator)
    {
        irc_send_reply(__UU,421,cmd.command+": Unauthorized command");
        return;

    }
    vector<string> vV=splitTOK(" ",cmd.data);

    if (vV.size()==4) {
        string nick=vV[0];
        string summa=vV[1];
        string type=vV[2];
        string cookie=vV[3];
        DB_id to, from;
        to=all_user_nick_2_DB_id(nick);

        if (to.container==0)
        {
            st_dbh d;
            to.container=atoi(d.dbh->select_1Q((QUERY)"select uid from nicks where str_nick='?'"<<str_nick(nick)));
        }
        if (to.container==0) {
            irc_send_reply(__U,401,"No such nick/channel.");
            return;
        }
        from=user$id(__U);

        double tot_cost=atof(summa.c_str());

        if (tot_cost>0)
        {
            if (buy_thing(from,to,tot_cost, type)) // true if success
            {
                data_push_back(__U.cu,"CTTU_REPLY "+nick+":OK:"+ftostring(tot_cost)+":"+cookie+":"+ftostring(credit_reminder(from))+":"+ftostring(credit_reminder(to))+"\n");
            }
            else
            {
                data_push_back(__U.cu,"CTTU_REPLY "+nick+":FAIL:Not_enough_credits:"+cookie+":0:0"+"\n");
            }
        } else data_push_back(__U.cu,"CTTU_REPLY "+nick+":FAIL:Not_enough_credits:"+cookie+":0:0"+"\n");

        return;
    }
    else
        data_push_back(__U.cu,"CTTU_REPLY invalid_format\n");

}
