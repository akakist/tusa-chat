#ifdef __GNUC__
#pragma implementation
#endif

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
#include "levels.h"
#include "irc_server_config.h"

#include "irc_utils.h"
#include "update_cmd.h"
#include "contact_vec.h"
#include "chat_thread_event.h"

static _mutex _login_MX("static _login_MX");
void reload(const PTR_getter<nick_vec> &N);
pair<string,DB_id> get_pass_by_nick(const string &nick);


void irc_change_nick(const PTR_getter<chat_user> &__UU,const string &nick)
{
    user_pair __U(__UU);

    bool too_fast=false;
    DB_id uid=user$id(__U);
    {
        __UC_LOCK;
        too_fast=(time(NULL)-u->last_change_nick)<11;
    }

    if (too_fast) {
        irc_send_reply(__U,401,"Too fast nick change. Wait some seconds...");
        return;
    }
    if (!NICK_EXISTS(user$id(__U),nick)) {
        irc_send_reply(__U,432,nick+": You dont have this nick. To use other nick, register it from WEB.");
        return;
    }
    DB_id zzzz;
    user_nick nn("",user_state::UNDEF,zzzz,false,0);
    {
        PGLR(nick_vec, u,nick_vecs.find_by_id(uid));
        for (map<unsigned int,user_nick> ::const_iterator i=u->u_nicks.begin();i!=u->u_nicks.end();i++) {
            if (str_nick(nick)==str_nick(i->second.name)) {
                nn=i->second;
                break;
            }
        }
    }
    if (nn.id==user_state::UNDEF) {
        irc_send_reply(__U,432,nick+": You dont have this nick. To use other nick, register it from WEB.");
        return;
    }
    if (nn.id==GET_CNICK_ID(__U)) {
        irc_send_reply(__U,432,nick+": You already use this nick.");
        return;
    }
    if (!inchat$(__U.cu)) {
        string cnick=GET_CNICK(__U);
        string s=":"+cnick+"!"+cnick+"@"+string(irc_server_config.host)+" NICK :"+nick+"\r\n";
        data_push_back(__U.cu,s);
    }
    user_nick old_nick;
    {
        __UC_LOCKW;
        u->last_change_nick=time(NULL);
        old_nick=u->cstate.nick;
        u->cstate.nick=nn;
    }

    if (nn.id!=user_state::UNDEF)
    {
        PGLW(user_set, u,__U.us);
        u->last_nick=nn.name;
        u->last_nick_id=nn.id;
        send_update_g3(user_set$last_nick,uid,u->last_nick);
        send_update_g3(user_set$last_nick_id,uid,u->last_nick_id);
    }
    {
        out_oscar_buffer o;
        DB_id uid=user$id(__U);
        o<<user_state::SET_NICK<<uid<<nn;
        set_user_state(o);
        send_update_g3(user_set$last_nick,uid,nn.name);
        send_update_g3(user_set$last_nick_id,uid,nn.id);

    }
    return;
}
void disconnect_irc_user(const PTR_getter<chat_user> &__UU)
{
    PTR_getter<c_socket>__S(NULL);
    {
        PGLW(chat_user, u,__UU);
        __S=u->psocket;
        u->psocket=NULL;
        u->erased=true;
    }
    if (__S)
    {
        disconnect(__S);
    }

}
