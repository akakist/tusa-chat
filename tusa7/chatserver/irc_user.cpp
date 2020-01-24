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
#include "server_config.h"
#include "irc_server_config.h"

#include "user_credits.h"
#include "thread_descr.h"
#include "irc_utils.h"
#include "tcp_stats.h"
#include "chat_thread_event.h"
#include "irc_session.h"
#include "chat_globals.h"
#include "html_out.h"
#include "user_stat.h"
vector<string> LK_get_irc_users(bool get_inv,unsigned int channel);

void irc_cmd_EYE(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_EYEN(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_JOIN(const PTR_getter<chat_user> &__UU,const PTR_getter<irc_session> &__IS,irc_command &cmd);
void irc_cmd_KICK(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_LIST(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_MODE(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_PRIVMSG(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_WHOIS(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_SYS(const PTR_getter<chat_user> &__UU,irc_command &cmd)
{		//system message

    user_pair __U(__UU);
    vector<string> v=splitTOK(" ",cmd.data);
    if (!v.size())
    {
        irc_send_reply(__U,403,"Not in channel");
        return;
    }
    string irc_name=v[0];
    PTR_getter<chat_channel> ML=chat_channels.by_irc(irc_name);
    if (!ML)
    {
        irc_send_reply(__U,403,"Bad channel");
        return;
    }
    CH_id ch;
    {
        __CH_LOCK(ML);
        ch=CH->cd.chid;
    }

    if (!inchat$(__U.cu)) {
        irc_send_reply(__U,403,"Not in channel");
        return;
    }
    if (user$level(__U)/sub_levels<am_admin) {
        irc_send_reply(__U,481,"You are not an IRC operator");
        return;
    }
    chat_event_SEND_MESSAGE *e=new chat_event_SEND_MESSAGE;
    e->from_uid=user$id(__U);
    e->msg=cmd.data;
    e->tonick="";
    e->priv=false;
    e->sys=true;
    e->makeit=false;
    e->channel=ch;
    e->user_type=TYPE_IRC;
    send_chat_event(e,true);
    {
        __UC_LOCK;
        u->last_m_time = time(NULL);
    }
    return;
}

void irc_cmd_PART(const PTR_getter<chat_user> &__UU,irc_command &cmd)
{
    user_pair __U(__UU);
    if (!inchat$(__U.cu)) {
        irc_send_reply(__U,403,"Not in channel");
        return;
    }
    vector<string> v=splitTOK(" ,",cmd.data);
    if (!v.size())
    {
        irc_send_reply(__U,403,"Bad syntax");
        return;

    }
    for (unsigned i=0;i<v.size();i++)
    {

        CH_id ch;
        PTR_getter<chat_channel> ML=chat_channels.by_irc(v[i]);
        if (!ML)
        {
            irc_send_reply(__U,403,"Invalid channel "+v[i]);
            continue;

        }
        {
            __CH_LOCK(ML);
            ch=CH->cd.chid;
        }
        out_oscar_buffer o;
        DB_id uid=user$id(__U);
        o<<user_state::PART<<uid<<ch;
        set_user_state(o);
    }
}



void irc_cmd_EUI(const PTR_getter<chat_user> &__UU,irc_command &cmd)
{
    DB_id uid;
    user_pair __U(__UU);
    if (user$level(__U)/sub_levels<am_admin) return;


    string rp;
    DB_id zid=all_user_nick_2_DB_id(cmd.data);
    string IP;
    if (zid.container)
    {

        string znick;
        {
            PGLR(user_set,z,user_sets.find_by_id(zid));
            znick=z->last_nick;
        }
        {
            PGLR(user_stat,z,user_stats.find_by_id(zid));
            IP=z->last_ip;
        }
        string zlogin;
        unsigned char zgender;
        unsigned int zlevel;
        {
            PGLR(user_profile,z,user_profiles.find_by_id(zid));
            zlogin=z->login;
            zgender=z->get_gender();
            zlevel=z->level;

        }
        rp=
            znick+
            ":"+zlogin+
            ":"+itostring(zgender)+
            ":"+itostring(0)+
            ":"+itostring(zlevel);

    } else
        return;

    double sm=credit_reminder(zid);
    rp+=":"+ftostring(sm)+
        ":"+IP;
    string s="EUI_REPLY "+rp+"\r\n";
    data_push_back(__U.cu,s);
    return;
}

void irc_cmd_ISON(const PTR_getter<chat_user> &__UU,irc_command &cmd)
{

    chat_event_irc_cmd_ISON *e=new chat_event_irc_cmd_ISON;
    e->__U=__UU;
    e->nicks=splitTOK(" ",cmd.data);
    send_chat_event(e, false);
}
void irc_cmd_USERHOST(const PTR_getter<chat_user> &__UU,irc_command &cmd)
{

    user_pair __U(__UU);

    string sss;
    irc_send_reply(__U,302,sss<<GET_CNICK(__U)<<"=+~"<<GET_CNICK(__U)<<"@"<<user$ip(__U));
    return;


}

void irc_cmd_JOIN(const PTR_getter<chat_user> &__UU,const PTR_getter<irc_session> &__IS,irc_command &cmd)
{
    user_pair __U(__UU);

    string irc_channel=cmd.data;
    time_t last_join;

    {
        PGLR(irc_session,u,__IS);
        last_join=u->last_join;
    }
    if (time(NULL)<last_join+5) {
        irc_send_reply(__U,405,irc_channel+": Too fast join");
        return;
    }
    {
        PGLW(irc_session,u,__IS);
        u->last_join=time(NULL);
    }
    PTR_getter<chat_channel> ML=chat_channels.by_irc(irc_channel);

    if (!ML) {
        irc_send_reply(__U,403,irc_channel+": No such channel");
        return;
    }
    CH_id ch_id;
    {
        __CH_LOCK(ML);
        ch_id=CH->cd.chid;
    }
    {
        out_oscar_buffer o;
        DB_id uid;
        uid=user$id(__U);
        o<<user_state::JOIN<<uid<<ch_id;
        set_user_state(o);
    }
}
void irc_cmd_WHOIS(const PTR_getter<chat_user> &__UU,irc_command &cmd)
{

    chat_event_irc_cmd_WHOIS *e=new chat_event_irc_cmd_WHOIS;
    e->__U=__UU;
    e->nick=cmd.data;
    send_chat_event(e, false);
}
void irc_cmd_PRIVMSG(const PTR_getter<chat_user> &__UU,irc_command &cmd)
{
    user_pair __U(__UU);
    string irc_channel;
    bool is_admin;
    string to;
    string ms;
    int pz=cmd.data.find(":");
    if (pz!=-1) {
        to=cmd.data.substr(0,pz);
        to=remove_spaces(to);
    }
    if (!inchat$(__U.cu)) {
        irc_send_reply(__U,403,"Not in channel");
        return;
    }

    ms=cmd.data.substr(pz+1,cmd.data.size()-pz-1);

    if (!to.size() || !ms.size()) {
        irc_send_reply(__U,401,to,"No such nick/channel.");
        return;
    }	//anti flood protection

    if (!to.size())
    {
        irc_send_reply(__U,411,to,"No recipient given.");
        return;
    }

    PTR_getter<chat_channel> ML(NULL);
    {
        ML=chat_channels.by_irc(to);
    }
    DB_id zid=all_user_nick_2_DB_id(to);
    bool to_channel=true;
    if (!ML) to_channel=false;
    if (!ML)
    {
        if (!zid.container)
        {
            string s="No recipient found. '"+to+"'";
            irc_send_reply(__U,411,to,s);
            return;
        }
    }

    if (ML)
    {
        bool makeit=false;
        if (ms.size()>=7) {	//may be action message
            char cc1=1;
            string act(cc1,1);
            act+="ACTION";
            if (ms.substr(0,7)==act) {
                makeit=true;
                ms=ms.substr(8,ms.size()-9);
            }
        }

        string ton;
        if (!makeit)
        {
            pz=ms.find(",",0);
            if (pz!=-1) {
                ton=ms.substr(0,pz);
                ms=ms.substr(pz+1,ms.size()-1-pz);
            }

        }
        CH_id channel;

        {
            __CH_LOCK(ML);
            channel=CH->cd.chid;
        }
        chat_event_SEND_MESSAGE *e=new chat_event_SEND_MESSAGE;
        e->from_uid=user$id(__U);
        e->msg=ms;
        e->tonick=ton;
        e->priv=false;
        e->sys=false;
        e->makeit=makeit;
        e->channel=channel;
        e->user_type=TYPE_IRC;

        send_chat_event(e,true);
        {
            __UC_LOCK;
            u->last_m_time = time(NULL);
        }
        return;
    }
    if (to.size()>16) {
        irc_send_reply(__U,404,to,"Cant send to channel");
        return;
    }
    if (zid.container)
    {
        chat_event_SEND_MESSAGE *e=new chat_event_SEND_MESSAGE;
        e->from_uid=user$id(__U);
        e->msg=ms;
        e->tonick=to;
        e->priv=true;
        e->sys=false;
        e->makeit=false;
        e->user_type=TYPE_IRC;
        send_chat_event(e,true);
        {
            __UC_LOCK;
            u->last_m_time = time(NULL);
        }
        return;
    }

    irc_send_reply(__U,411,to,"No recipient given.");

}

extern m_var<map<string,pair<int,string> > > get_irc_list_container;
void irc_cmd_LIST(const PTR_getter<chat_user> &__UU,irc_command &cmd)
{
    user_pair __U(__UU);

    map<string,pair<int,string> >r= get_irc_list_container.get();
    string cnick=GET_CNICK(__U);
    for (map<string,pair<int,string> >::iterator i=r.begin();i!=r.end();i++) {
        string ss;
        ss+=":"+string(irc_server_config.host)+" 322 "+cnick+" "+i->first+" "+itostring(i->second.first)+" :"+i->second.second+"\r\n";
        data_push_back(__U.cu,ss);
    }
    irc_send_reply(__U,323,"End of list");
}

