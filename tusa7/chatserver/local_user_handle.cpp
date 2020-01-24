#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include <list>
#include "_mutex.h"
#include <stdio.h>
#include "web_server.h"
#include "errs.h"
#include <signal.h>
#include "st_stuff.h"
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include "_mutex.h"
#include <time.h>

#include "utils.h"
#include <algorithm>
#include "user.h"
#include "message.h"
#include "web_server_data.h"
#include "file_set.h"
#include "register.h"
#include "tcp_stats.h"
#include "server_config.h"
#include "app_def.h"
#include "tcp_sender.h"
#include "web_tools.h"
#include "version.h"
#include "user_credits.h"
#include "chat_def.h"
#include "irc_server_config.h"

#include "chat_config.h"
#include "fotos.h"
#include "channels.h"
#include "irc_utils.h"
#include "update_cmd.h"
#include "ignore_vec.h"
#include "user_stat.h"
#include "contact_vec.h"
#include "notes.h"
class ignore_vec;
class contact_vec;
string update_to_db(const PTR_getter<contact_vec>&__P,const string &tblname);
string update_to_db(const PTR_getter<ignore_vec>&__P,const string &tblname);
string update_to_db(const PTR_getter<nick_vec>&__P,const string &tblname);
string update_to_db(const PTR_getter<note_text>&__P,const string &tblname);
string update_to_db(const PTR_getter<u_notes>&__P,const string &tblname);
string update_to_db(const PTR_getter<user_credit>&__P,const string &tblname);
string update_to_db(const PTR_getter<user_fotos>&__P,const string &tblname);
string update_to_db(const PTR_getter<user_profile>&__P,const string &tblname);
string update_to_db(const PTR_getter<user_set>&__P,const string &tblname);
string update_to_db(const PTR_getter<user_stat>&__P,const string &tblname);

void www_local_user_handle_rn(const PTR_getter<chat_user> &__ZZ)
{
    bool need_rn=false;
    {
        PGLW(chat_user,   z,__ZZ);
        if (z->user_type==TYPE_WWW)
        {
            if (time(NULL) - z->www_last_send_time > 60) {
                z->www_last_send_time = time(NULL);
                z->www_data_send_count++;
                need_rn=true;
            }
        }
    }
    if (need_rn)
        data_push_back(__ZZ,"\r\n");
}
void www_local_user_handle_max_inactive_time(const PTR_getter<chat_user> &__ZZ)
{

    bool psock_connected = false;
    time_t last_access_time = 0;
    PTR_getter<c_socket > pusock(NULL);
    {
        PGLW(chat_user,   z,__ZZ);
        last_access_time = z->last_access_time;
        pusock = z->psocket;
    }

    if (pusock) {
        PGLR(c_socket, ps,pusock);
        psock_connected = ps->connected();
    }
    else psock_connected=false;
    if (time(NULL) - last_access_time > chat_config.user_max_inactive_time && !psock_connected)
    {
        {
            user_pair __Z(__ZZ);
            logErr2("%s (%s) killed due timeout [%s - %s] {%d}",GET_CNICK(__Z).c_str(),
                    user$login(__Z).c_str(),user$ip(__Z).c_str(),user$proxy_ip(__Z).c_str(),user$get_spent_time(__Z));
        }
        {
            PGLW(chat_user, z,__ZZ);
            z->erased=true;
        }
    }

}
void www_local_user_handle_offline_status(const PTR_getter<chat_user> &__ZZ)
{
    if (!__ZZ) throw cError("!ZZ");
    bool conn_active=false;
    PTR_getter<c_socket> __S(NULL);
    unsigned int zstatus;
    DB_id db_id;
    {
        PGLR(chat_user,z,__ZZ);
        if (z->user_type!=TYPE_WWW) return;
        __S=z->psocket;
        db_id=z->db_id;
        zstatus=z->cstate.status.id;
    }
    if (__S)
    {
        PGLW(c_socket,s,__S);
        conn_active=s->connected();
    }

    bool cond;

    {
        PGLW(chat_user,z,__ZZ);

        if (conn_active) z->www_offline_time=0;

        cond=!z->www_offline_status_sent &&
             z->www_offline_time&&
             time(NULL)-z->www_offline_time>10 &&
             z->www_inchat &&
             !conn_active;
        if (!conn_active && z->www_offline_time==0)
        {
            z->www_offline_time=time(NULL);
        }
        if (cond)
        {
            z->www_offline_status_sent=true;
            z->last_access_time=time(NULL);

        }
    }

    user_pair __Z(__ZZ);
    bool isinv=is_inv(__Z);


    if (cond) {

        if (isinv) {
            user_status st=get_user_status_by_id(__Z, st_offinvisible);
            out_oscar_buffer o;
            o<<user_state::SET_STATUS<<user$id(__Z)<<st;
            set_user_state(o);
            {
                __ZC_LOCK;
                z->cstate.status=st;
            }
        } else {
            user_status st=get_user_status_by_id(__Z, st_offline);
            out_oscar_buffer o;
            o<<user_state::SET_STATUS<<user$id(__Z)<<st;
            set_user_state(o);
            {
                __ZC_LOCK;
                z->cstate.status=st;
            }
        }
    }
    if (conn_active && (zstatus==st_offinvisible || zstatus==st_offline))
    {
        unsigned int lstatus;
        {
            PGLR(user_set,z,__Z.us);
            lstatus=z->last_status_id;
        }
        user_status st=get_user_status_by_id(__Z, lstatus);
        out_oscar_buffer o;
        o<<user_state::SET_STATUS<<user$id(__Z)<<st;
        set_user_state(o);
        {
            __ZC_LOCK;
            z->cstate.status=st;
        }

    }

}
void www_local_user_check_for_channel_cleanup(const PTR_getter<chat_user>&__ZZ )
{

    if (!__ZZ)  return;
    const user_pair __Z(__ZZ);
    bool conn_active=user__connection_is_active(__Z);

    bool cond;
    {
        __ZC_LOCK;
        if (z->user_type!=TYPE_WWW) return;
        cond=z->cstate.channel.size() && !conn_active && time(NULL)-z->www_offline_time > chat_config.chat_offline_timeout && z->www_offline_time!=0;
        if (!cond)
        {
            if (z->erased && z->cstate.channel.size())
                cond=true;
        }
        if (cond)
        {
            z->cstate.channel.clear();
        }
    }
    if (cond) {
        out_oscar_buffer o;
        o<<user_state::PARTALL<<user$id(__Z);
        set_user_state(o);
        {
            __ZC_LOCK;
            z->last_access_time=time(NULL);
        }
    }


}
void local_users_iterate()
{
    vector < PTR_getter<chat_user> > v=local_users.values();
    time_t t=time(NULL);
    for (unsigned i=0;i<v.size();i++)
    {
        try {
            if (!v[i])continue;
            www_local_user_handle_offline_status(v[i]);
            www_local_user_handle_rn(v[i]);
            www_local_user_handle_max_inactive_time(v[i]);
            www_local_user_check_for_channel_cleanup(v[i]);



        }STDCATCHS("local_users_iterate");

    }
    local_users.clean();
    __cookie_2_session_id.clean();

}
#ifndef __CLAN
void update_db_cache()
{

    time_t update_timeout = chat_config.data_update_timeout;
    time_t drop_timeout=chat_config.data_drop_timeout;
    try {
        user_credits.purge(update_timeout, drop_timeout);
    }
    catch (cError e) {
        logErr2("catched ... %s %d '%s'",__FL__,e.what());
    }
    catch (...) {
        logErr2("catched ... %s %d",__FL__);
    }
    try {
        __notes.purge(update_timeout, drop_timeout);
    }
    catch (cError e)    {
        logErr2("catched ... %s %d '%s'",__FL__,e.what());
    }
    catch (...) {
        logErr2("catched ... %s %d",__FL__);
    }

    try {
        note_texts.purge(update_timeout, drop_timeout);
    }
    catch (cError e)    {
        logErr2("catched ... %s %d '%s'",__FL__,e.what());
    }
    catch (...) {
        logErr2("catched ... %s %d",__FL__);
    }

    try {
        user_stats.purge(update_timeout, drop_timeout);
    }
    catch (cError e)    {
        logErr2("catched ... %s %d '%s'",__FL__,e.what());
    }
    catch (...) {
        logErr2("catched ... %s %d",__FL__);
    }

    try {
        user_profiles.purge(update_timeout, drop_timeout);
    }
    catch (cError e)    {
        logErr2("catched ... %s %d '%s'",__FL__,e.what());
    }
    catch (...) {
        logErr2("catched ... %s %d",__FL__);
    }

    try {
        user_sets.purge(update_timeout, drop_timeout);
    }
    catch (cError e)    {
        logErr2("catched ... %s %d '%s'",__FL__,e.what());
    }
    catch (...) {
        logErr2("catched ... %s %d",__FL__);
    }


    try {
        nick_vecs.purge(update_timeout, drop_timeout);
    }
    catch (cError e)    {
        logErr2("catched ... %s %d '%s'",__FL__,e.what());
    }
    catch (...) {
        logErr2("catched ... %s %d",__FL__);
    }

    try {
        contact_vecs.purge(update_timeout, drop_timeout);
    }
    catch (cError e)    {
        logErr2("catched ... %s %d '%s'",__FL__,e.what());
    }
    catch (...) {
        logErr2("catched ... %s %d",__FL__);
    }

    try {
        users_fotos.purge(update_timeout, drop_timeout);
    }
    catch (cError e)    {
        logErr2("catched ... %s %d '%s'",__FL__,e.what());
    }
    catch (...) {
        logErr2("catched ... %s %d",__FL__);
    }

    try {
        ignore_vecs.purge(update_timeout, drop_timeout);
    }
    catch (cError e)    {
        logErr2("catched ... %s %d '%s'",__FL__,e.what());
    }
    catch (...) {
        logErr2("catched ... %s %d",__FL__);
    }

    try {
        dump_credits_log();
    }
    catch (cError e)    {
        logErr2("catched ... %s %d '%s'",__FL__,e.what());
    }
    catch (...) {
        logErr2("catched ... %s %d",__FL__);
    }

}
#endif
