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
#include "server_config.h"
#include "tcp_server_data.h"
#include "chat_colors.h"
#include "irc_server_config.h"

#include "irc_utils.h"
#include "irc_session.h"
#include "chat_thread_event.h"
#include "update_cmd.h"
#include "tcp_stats.h"

void user_process_irc_command(const PTR_getter<chat_user> &__UU,irc_command &c);
void user_process_irc_command2(const PTR_getter<chat_user> &__UU,irc_command &c);
__irc_sessions irc_sessions;
void irc_cmd_EYE(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_EYEN(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_JOIN(const PTR_getter<chat_user> &__UU,const PTR_getter<irc_session> &__IS,irc_command &cmd);
void irc_cmd_KICK(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_LIST(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_MODE(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_PRIVMSG(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_WHOIS(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_USERHOST(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_ISON(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_CTTU(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_UTTC(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_EUI(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_PART(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_SYS(const PTR_getter<chat_user> &__UU,irc_command &cmd);

void irc_change_nick(const PTR_getter<chat_user> &__UU,const string &nick);
pair<string,DB_id> get_pass_by_nick(const string &nick);
vector<string> get_uid_time_cnt_descr_from_banned_login_by_uid(const DB_id &uid);

S_id next_session_id();

void irc_server::start(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{
    tcp_linedialog_server::start(pn,prefix,m);
    load_config(pn,prefix,m);
}

irc_server::irc_server()
{

}

void *irc_server::new_connection(const PTR_getter<c_socket>&s)
{
    int fd;
    {
        PGLR(c_socket,S,s);
        fd=S->get_socket_fd();
    }

    return new irc_connection(s,this);
}

irc_connection::~irc_connection()
{
}

irc_command irc_parse_command(const string &s)
{
    irc_command c;
    size_t pz=s.find(" ",0);
    if (pz!=-1) {
        c.command=strupper(s.substr(0,pz));
        c.data=s.substr(pz+1,s.size()-pz-1);
        c.data=str_replace("\r","",c.data);
        c.data=str_replace("\n","",c.data);
    } else {
        c.command=strupper(s);
        c.command=str_replace("\r","",c.command);
        c.command=str_replace("\n","",c.command);
    }
    return c;
}


void irc_iterate()
{
    irc_sessions.iterate();
}
void __irc_sessions::add(const S_id &sid,const PTR_getter<irc_session> &__IS)
{
    M_LOCK(Mutex);
    container.insert(make_pair(sid,__IS));
}
PTR_getter<irc_session> __irc_sessions::get(const S_id &s)
{
    M_LOCK(Mutex);
    if (container.count(s)) return container.find(s)->second;
    return NULL;
}
void __irc_sessions::iterate()
{
    set<S_id> rm;
    map<S_id,PTR_getter<irc_session> > V;
    {
        M_LOCK(Mutex);
        V=container;

    }
    for (map<S_id,PTR_getter<irc_session> > ::iterator i=V.begin();i!=V.end();i++)
    {
        PTR_getter<c_socket> __S(NULL);
        PTR_getter<chat_user> __U(NULL);
        if (i->second)
        {
            PGLR(irc_session,u,i->second);
            if (time(NULL)-u->last_pong>irc_server_config.ping_kill_timeout) rm.insert(i->first);
            if (!u->__U && time(NULL)-u->create_time > irc_server_config.login_timeout) rm.insert(i->first);
            __S=u->__S;
            __U=u->__U;
        }

        if (__S)
        {
            PGLW(c_socket,s,__S);
            if (!s->connected())rm.insert(i->first);
        }
        else rm.insert(i->first);
        if (__U)
        {
            PGLR(chat_user,u,__U);
            if (u->erased) rm.insert(i->first);
        }

        // PING PONG
        string spb;
        {
            PGLW(irc_session,u,i->second);

            if (time(NULL)>=u->last_ping+irc_server_config.ping_time.get()) {
                u->last_ping=time(NULL);
                spb="PING ";
                spb+=string(irc_server_config.host);
                spb+="\r\n";
            }
        }
        if (spb.size())reply_socket(__S,spb);
    }
    for (set<S_id> ::iterator i=rm.begin();i!=rm.end();i++)
    {
        erase(*i);
    }
}
void __irc_sessions::erase(const S_id &sid)
{
    PTR_getter<irc_session> __IS(NULL);
    {
        M_LOCK(Mutex);
        if (container.count(sid)) __IS=container.find(sid)->second;
        container.erase(sid);
    }
    if (!__IS) return;
    PTR_getter<chat_user> __U(NULL);
    PTR_getter<c_socket> __S(NULL);

    {
        PGLR(irc_session,u,__IS);
        __U=u->__U;
        __S=u->__S;
    }
    if (__U)
    {
        DB_id uid;
        {
            PGLR(chat_user,u,__U);
            uid=u->db_id;
        }
        out_oscar_buffer o;
        o<<user_state::PARTALL<<uid;
        set_user_state(o);
        local_users.erase(uid);
        broadcast_user_logged_out(uid);

    }

}
PTR_getter<irc_session> __irc_sessions::get_by_dbid(const DB_id &s)
{
    map<S_id,PTR_getter<irc_session> > m;

    {
        M_LOCK(Mutex);
        m=container;
    }
    for (map<S_id,PTR_getter<irc_session> > ::iterator i=m.begin();i!=m.end();i++)
    {
        if (i->second)
        {
            PTR_getter<chat_user> __U(NULL);
            {
                PGLR(irc_session,u,i->second);
                __U=u->__U;
            }
            if (__U)
            {


                PGLR(chat_user,u,__U);
                if (u->db_id==s) return i->second;
            }
        }
    }
    return NULL;
}




void irc_server::process_command(const string & command, const PTR_getter<tcp_second_data > &__SD)
{
    string u_key;
    ++tcp_total_accepted_connections;

    {
        PGLR( tcp_second_data , sd,__SD);
        u_key=sd->extra_user_id;
    }
    S_id st;
    st.container=atoi(u_key);
    PTR_getter<chat_user> __UU(NULL);
    PTR_getter<irc_session> __IS=irc_sessions.get(st);
    string ip;
    {
        PGLR( tcp_second_data , sd,__SD);
        ip=sd->peer_ipaddress;
    }
    PTR_getter<c_socket>sock(NULL);
    if (!__IS)
    {

        {
            PGLR( tcp_second_data , sd,__SD);
            sock=sd->socket;
        }

        irc_session* sess=new irc_session;
        sess->ip=ip;
        sess->__S=sock;
        st=sess->session;
        __IS=sess;
        irc_sessions.add(st,__IS);

        {
            PGLW( tcp_second_data , sd,__SD);
            sd->extra_user_id=itostring(st.container);
        }

    }
    else
    {
        PGLW(irc_session,s,__IS);
        __UU=s->__U;
        s->last_pong=time(NULL);
        sock=s->__S;
    }
    try {

        if (__UU) {
            PGLW(chat_user, u,__UU);
            u->last_access_time=time(NULL);
        }
        irc_command cmd = irc_parse_command(command);
        if (cmd.command=="") {
            return;
        }
        if (cmd.command=="PONG")
        {
            PGLW(irc_session, u,__IS);
            u->last_pong=time(NULL);
            return;
        }
        if (cmd.command=="QUIT") {
            if (!__UU)
            {
                string nick;
                {
                    PGLW(irc_session,s,__IS);
                    nick=s->nick;
                }
                if (!nick.size())nick="tipok";
                logErr2("User not logged from [%s] logout from IRC",ip.c_str());
                data_push_back(__IS,"ERROR :Closing Link "+nick+"~1@"+string(irc_server_config.host)+"] ("+cmd.data+")\r\n");
            }
            else
            {
                user_pair __U(__UU);
                string cnick=GET_CNICK(__U);
                logErr2("User %s (%s) logout from IRC [%s] {%d}",cnick.c_str(),user$login(__U).c_str(),user$ip(__U).c_str(),user$get_spent_time(__U));
                data_push_back(__U.cu,"ERROR :Closing Link "+cnick+"[~1@"+string(irc_server_config.host)+"] ("+cmd.data+")\r\n");
                PTR_getter<c_socket> s(NULL);
                {
                    __UC_LOCK;
                    u->erased=true;
                }
            }
            irc_sessions.erase(st);
            return;
        }
        else if (cmd.command=="NICK")
        {
            string nick=cmd.data;
            bool too_fast=false;
            bool unregistered=false;
            bool irc_registered=false;

            if (nick.size()>2 && nick.substr(0,1)==":") nick=nick.substr(1,nick.size()-1);
            if (nick.size()>16 || nick.size()<0) {
                irc_send_reply(__IS,432,nick+": Nick is too long");
                return;
            }
            if (!check_nick(nick)) {
                irc_send_reply(__IS,432,nick+" is incorrect Nick");
                return;
            }
            if (__UU)
            {
                irc_change_nick(__UU,nick);
                {
                    PGLW(irc_session,u,__IS);
                    u->nick=nick;
                }

                return;
            }
            else
            {
                {
                    PGLW(irc_session,u,__IS);
                    u->nick=nick;
                }
                irc_send_reply(__IS,512,"Authorization requried to use Registered nick "+nick);
                irc_send_notice(__IS,"If this is your nickname, type /PASS <password>","System");
            }
            return;

        }
        else if (cmd.command=="PASS")
        {
            if (__UU)
            {
                irc_send_notice(__IS,"Already logged, please log off first","System");
                return;
            }
            string nick;
            {
                PGLW(irc_session, u,__IS);
                nick=u->nick;

            }
            if (nick=="") {
                irc_send_reply(__IS,431,"No nickname given.");
                return;
            }

            pair<string,DB_id> r=get_pass_by_nick(nick);
            if (r.second.container==0)
            {
                irc_send_reply(__IS,465,"Invalid nick, or nick banned.");
                return;
            }
            if (bin2hex(MD5(cmd.data),0)!=r.first) {
                irc_send_reply(__IS,464,"Password incorrect.");
                return;
            }
            DB_id uid=r.second;


            PTR_getter<chat_user> __Z=local_users.get(uid);
            if (__Z)
            {
                unsigned char ztype;
                {
                    PGLR(chat_user,z,__Z);
                    ztype=z->user_type;
                }
                if (ztype==TYPE_WWW)
                {
                    irc_send_reply(__IS,433,nick+": Nick is already in use from WEB. Logout from WEB first or login/logout to/from WEB to kill WEB session.");
                    return;
                }
                else if (ztype==TYPE_IRC)
                {
                    PTR_getter<irc_session> __ZI=irc_sessions.get_by_dbid(uid);
                    if (__ZI)
                        disconnect(__ZI);
                }

            }

            vector<string> bb=get_uid_time_cnt_descr_from_banned_login_by_uid(uid);
            if (bb.size()==3) {
                irc_send_reply(__IS,465,"You are banned from this server by login. Time: "+bb[1]+". "+bb[2]);
                disconnect(__IS);
                return;
            }
            PTR_getter<user_profile>__UP(user_profiles.find_by_id(uid));
            unsigned int level;
            {
                PGLR(user_profile,u,__UP);
                level=u->level;
            }

            if (level<am_admin*sub_levels) {
                if (!check_for_ipban(ip,"")) {
                    irc_send_reply(__IS,465,"You are banned from this server by IP.");
                    disconnect(__IS);
                    return;
                }
            }


            chat_user *cu=new chat_user(TYPE_IRC);
            {
                cu->db_id=uid;
                cu->__user_profile=user_profiles.find_by_id(uid);
                cu->__user_set=user_sets.find_by_id(uid);
                cu->login_date=time(NULL);
                cu->last_access_time=time(NULL);
                cu->erased=false;
                cu->cu_ip=ip;
                cu->psocket=sock;
                cu->ua="IRC user";

            }
            __UU=cu;
            {
                PGLW(irc_session,u,__IS);
                u->__U=__UU;
                u->__S=sock;
            }

            user_pair __U(__UU);
            user_register_all_nicks(uid,true);



            {
                PGLW(irc_session,u,__IS);
                u->__U=__UU;
            }


            local_users.insert(__UU);
            broadcast_user_logged_in(uid);

            {
                chat_event_UPDATE_USER_SESSION *ce=new chat_event_UPDATE_USER_SESSION;
                {
                    __UC_LOCK;
                    ce->uid=u->db_id;
                    ce->user_type=TYPE_IRC;
                }
                send_chat_event(ce,false);
            }


            user_nick nn;
            {
                PGLW(nick_vec, n,nick_vecs.find_by_id(uid));
                for (map<unsigned int,user_nick> ::iterator i=n->u_nicks.begin();i!=n->u_nicks.end();i++)
                {
                    if (str_nick(i->second.name)==str_nick(nick))
                    {
                        nn=i->second;
                    }

                }
            }

            bool allok=false;
            if (nn.id!=user_state::UNDEF)
            {
                PGLW(user_set, u,__U.us);
                u->last_nick=nn.name;
                u->last_nick_id=nn.id;
            }
            send_update_g3(user_set$last_nick,uid,nn.name);
            send_update_g3(user_set$last_nick_id,uid,nn.id);
            {
                PGLW(chat_user, u,__UU);
                u->cu_ip=ip;
                u->cstate.nick=nn;
            }
            {
                out_oscar_buffer o;
                o<<user_state::SET_NICK<<user$id(__U)<<nn;
                set_user_state(o);

            }
            send_update_g3(user_stat$last_ip,uid,ip);
            send_update_g3(user_stat$last_pip,uid,"");
            send_update_g2(user_stat$inc_v_count,uid);
            send_update_g3(user_stat$last_date,uid,time(NULL));
            irc_send_welcome(__U);
            return;

        }
        else if (cmd.command=="USER")
        {
            string rn;
            size_t pz=cmd.data.find(":",0);
            if (pz!=-1) {
                rn=cmd.data.substr(pz+1,cmd.data.size()-pz-1);
            }
            if (!rn.size()) {
                irc_send_reply(__IS,461,"USER: Not enought parameters");
                return;
            }
            {
                PGLW(irc_session, u,__IS);
                u->user=rn;
            }
            return;


        }
        else if (__UU)
        {

            if (cmd.command=="USERHOST") {
                irc_cmd_USERHOST(__UU,cmd);
                return;
            }
            else if (cmd.command=="MODE") {
                irc_cmd_MODE(__UU,cmd);
                return;
            }
            else if (cmd.command=="EYE") {
                irc_cmd_EYE(__UU,cmd);
                return;
            }
            else if (cmd.command=="EYEN") {
                irc_cmd_EYEN(__UU,cmd);
                return;
            }
            else if (cmd.command=="KICK") {
                irc_cmd_KICK(__UU,cmd);
                return;
            }
            else if (cmd.command=="ISON") {
                irc_cmd_ISON(__UU,cmd);
                return;
            }
            else if (cmd.command=="EUI") {
                irc_cmd_EUI(__UU,cmd);
                return;
            }
#ifndef __CLAN
            else if (cmd.command=="CTTU") {
                irc_cmd_CTTU(__UU,cmd);
                return;
            }
            else if (cmd.command=="UTTC") {
                irc_cmd_UTTC(__UU,cmd);
                return;
            }
#endif
            else if (cmd.command=="PART" || cmd.command=="PARTALL") {
                irc_cmd_PART(__UU,cmd);
                return;
            }
            else if (cmd.command=="JOIN") {
                irc_cmd_JOIN(__UU,__IS,cmd);
                return;
            }
            else if (cmd.command=="SYS") {
                irc_cmd_SYS(__UU,cmd);
                return;
            }
            else if (cmd.command=="PRIVMSG") {
                irc_cmd_PRIVMSG(__UU,cmd);
                return;
            }
            else if (cmd.command=="LIST") {
                irc_cmd_LIST(__UU,cmd);
                return;
            }
            else if (cmd.command=="WHOIS") {
                irc_cmd_WHOIS(__UU,cmd);
                return;
            }
            else irc_send_reply(__UU,421,cmd.command+": Unknown command");

        }
        else
        {
            disconnect(__IS);
        }
    }
    catch (cError e)
    {
        {
            PTR_getter<irc_session> __ZZ=irc_sessions.get(st);
            if (__ZZ)
            {
                irc_send_reply(__ZZ,421, (string)"Command syntax error: "+e.error_string);
            }
        }

    }
    catch (...) {
        {
            PTR_getter<irc_session> __ZZ=irc_sessions.get(st);
            if (__ZZ)
            {
                irc_send_reply(__ZZ,421, "Command syntax error");
            }
        }
    }
}
void irc_server::on_delete(const PTR_getter<tcp_second_data > &__SD,const string& err_msg)
{
    if (!__SD) return;
    string u_key;
    {
        PGLR( tcp_second_data , sd,__SD);
        u_key=sd->extra_user_id;
    }
    S_id st;
    st.container=atoi(u_key);
    PTR_getter<irc_session> __IS=irc_sessions.get(st);
    PTR_getter<chat_user>__UU(NULL);
    if (__IS)
    {
        PGLR(irc_session,is,__IS);
        __UU=is->__U;
    }
    if (__UU)
    {
        user_pair __U(__UU);
        logErr2("User %s (%s) killed due irc connection lost [%s] {%d}.", GET_CNICK(__U).c_str(),
                user$login(__U).c_str(), user$ip(__U).c_str(), user$get_spent_time(__U));
    }
    irc_sessions.erase(st);
}
bool irc_server::validate_second_data(const PTR_getter<tcp_second_data>& __SD,string& errstr)
{
    string u_key;
    {
        PGLR( tcp_second_data, sd,__SD);
        u_key=sd->extra_user_id;
    }
    return true;
}
void irc_server::delete_extra_user_id(const string& kk) {
}
void irc_server::load_config(const std::string& pn,const std::string& prefix,std::map<std::string,std::string>&m)
{

}
