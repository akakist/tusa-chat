#include "stdafx.h"
#include <string>
#include <set>
using namespace std;
#include "oscar_buffer.h"
#include "PTR.h"
#include "DB_id.h"
#include "CH_id.h"
#include "S_id.h"
#include "chat_msg.h"
#include "M_DEQUE.h"
#include "user_status.h"
#include "user_nick.h"
#include "user_state.h"
#include "levels.h"
#include "chat_stuff.h"
#include "message.h"
#include "channels.h"
#include "update_cmd.h"
#include "chat_colors.h"
#include "utils.h"
#include "chat_def.h"
#include "server_config.h"
#include "RTYPES_CLAN.h"
#ifndef __CLAN
//#include "bos_client.h"
#else
#endif
#include "chat_thread_event.h"
#include "irc_utils.h"
#include "irc_server_config.h"
#include "chat_globals.h"
#include "user_stat.h"
#include "html_out.h"
#include "chat_config.h"
void  log_start_thread(const std::string &n);
M_DEQUE<chat_event*> __chat_events;
extern M_DEQUE<chat_msg$ *> chat_msgs_deque;

M_DEQUE<pair<string,string> > messages_to_backup;

void on_INVITE(chat_event_INVITE *e,chat_thread_stuff &stuff);
void on_CHAT_MESSAGES(chat_event_CHAT_MESSAGES*e,chat_thread_stuff &stuff);
void on_SEND_MESSAGE(chat_event_SEND_MESSAGE*e,chat_thread_stuff &stuff);
void on_SET_USER_STATE(chat_event_SET_USER_STATE*e,chat_thread_stuff &stuff);
void on_SEND_DATA_TO_WWW_USERS(chat_event_SEND_DATA_TO_WWW_USERS*e,chat_thread_stuff &stuff);
void on_CHMODE(chat_event_CHMODE *e,chat_thread_stuff &stuff);
void on_CHVOICE(chat_event_CHVOICE *e,chat_thread_stuff &stuff);
void on_CHTOPIC(chat_event_CHTOPIC *e,chat_thread_stuff &stuff);
void on_UPDATE_DATA(chat_event_UPDATE_DATA *e,chat_thread_stuff &stuff);
void on_UPDATE_USER_SESSION(chat_event_UPDATE_USER_SESSION *e,chat_thread_stuff &stuff);
void on_IGNORE(chat_event_IGNORE *e,chat_thread_stuff &stuff);
void on_irc_cmd_ISON(chat_event_irc_cmd_ISON *e,chat_thread_stuff &stuff);
void on_irc_cmd_WHOIS(chat_event_irc_cmd_WHOIS *e,chat_thread_stuff &stuff);

void make_url_users_content(chat_thread_stuff &stuff);
void get_irc_list(chat_thread_stuff &stuff);
void pack_backup_messages(chat_thread_stuff& stuff);
void unload_user(const DB_id &uid,chat_thread_stuff& stuff);
#ifdef __CLAN
void send_packet_to_cs(bool immed,int family,int subtype,const out_oscar_buffer & b);
void send_packet_to_cs(bool immed,CLAN_MSG,const out_oscar_buffer & b);
#endif

void broadcast_chat_event(chat_event*e)
{
    out_oscar_buffer b;
    b<<e->type;
    e->pack(b);
#ifdef __CLAN
    send_packet_to_cs(true,__TYPE_SEND_CHAT_EVENT,b);
#endif

}
void send_chat_event(chat_event*e, bool broadcast)
{
    if (broadcast)
    {
        broadcast_chat_event(e);
    }
    __chat_events.push_back(e);
}



void *chat_processor(void *pr)
{
    log_start_thread("chat processor");
    chat_thread_stuff stuff;
    time_t last_t_cnt_recalc=time(NULL);
    vector<CH_id> chs=chat_channels.keys();
    for (unsigned i=0;i<chs.size();i++)
    {
        __CH_LOCK(chat_channels[chs[i]]);
        chat_channel_data cd=CH->cd;
        stuff.channels[cd.chid].cd=cd;
    }
    stuff.to_all=chat_config.to_all;
    make_url_users_content(stuff);
    get_irc_list(stuff);

    while (1) {
        try {

            deque<chat_event*> de=__chat_events.extract_all();
            for (unsigned int i=0;i<de.size();i++)
            {
                try {
                    switch (de[i]->type)
                    {
                    case chat_event::INVITE:
                        on_INVITE((chat_event_INVITE*)de[i],stuff);
                        break;
                    case chat_event::CHAT_MESSAGES:
                        on_CHAT_MESSAGES((chat_event_CHAT_MESSAGES*)de[i],stuff);
                        break;
                    case chat_event::SEND_MESSAGE:
                        on_SEND_MESSAGE((chat_event_SEND_MESSAGE*)de[i],stuff);
                        break;
                    case chat_event::SET_USER_STATE:
                        on_SET_USER_STATE((chat_event_SET_USER_STATE*)de[i],stuff);
                        break;
                    case chat_event::SEND_DATA_TO_WWW_USERS:
                        on_SEND_DATA_TO_WWW_USERS((chat_event_SEND_DATA_TO_WWW_USERS*)de[i],stuff);
                        break;
                    case chat_event::CHMODE:
                        on_CHMODE((chat_event_CHMODE*)de[i],stuff);
                        break;
                    case chat_event::CHVOICE:
                        on_CHVOICE((chat_event_CHVOICE*)de[i],stuff);
                        break;
                    case chat_event::CHTOPIC:
                        on_CHTOPIC((chat_event_CHTOPIC*)de[i],stuff);
                        break;
                    case chat_event::UPDATE_DATA:
                        on_UPDATE_DATA((chat_event_UPDATE_DATA*)de[i],stuff);
                        break;
                    case chat_event::UPDATE_USER_SESSION:
                        on_UPDATE_USER_SESSION((chat_event_UPDATE_USER_SESSION*)de[i],stuff);
                        break;
                    case chat_event::__IGNORE:
                        on_IGNORE((chat_event_IGNORE*)de[i],stuff);
                        break;
#ifndef __CLAN
#endif
                    case chat_event::irc_cmd_ISON:
                        on_irc_cmd_ISON((chat_event_irc_cmd_ISON*)de[i],stuff);
                        break;
                    case chat_event::irc_cmd_WHOIS:
                        on_irc_cmd_WHOIS((chat_event_irc_cmd_WHOIS*)de[i],stuff);
                        break;

                    default:
                        logErr2("Undefined chat_event %d",de[i]->type)    ;
                    }
                }
                catch (cError e)
                {
                    logErr2("catched in chat_processor %s",e.what());

                }
                catch (...)
                {
                    logErr2("catched in chat_processor");
                }
                delete de[i];
            }
            deque<chat_msg$*> dm=chat_msgs_deque.extract_all();
            for (unsigned i=0;i<dm.size();i++)
            {
                PTR_getter_nm<chat_msg> m(new chat_msg(dm[i]));
                stuff.messages.push_back(m);
                stuff.backup_messages.push_back(m);
            }
            pack_backup_messages(stuff);
            if (stuff.messages.size()>15000)
            {
                while (stuff.messages.size()>10000)
                    stuff.messages.pop_front();
            }
            if (time(NULL)-last_t_cnt_recalc>600)
            {
                time_t tt=time(NULL);
                last_t_cnt_recalc=tt;
                for (map<DB_id,time_t> ::iterator i=stuff.join_time.begin();i!=stuff.join_time.end();i++)
                {
                    if (tt-i->second>100)
                    {
#ifndef __CLAN
                        send_update_g3(user_stat$add_t_count,i->first,tt-i->second);
#endif
                        i->second=tt;
                    }
                }
                vector<DB_id> todel;
                for (map<DB_id,time_t> ::iterator i=stuff.trash.begin();i!=stuff.trash.end();i++)
                {
                    if (tt-i->second>3600) todel.push_back(i->first);
                }
                for (unsigned i=0;i<todel.size();i++)
                {
                    stuff.trash.erase(todel[i]);
                    unload_user(todel[i],stuff);
                }
            }
            {
                usleep(10000);
            }
        }
        catch (cError e)
        {
            logErr2("--Error: cha_processor: error! %s %d %s",__FILE__,__LINE__,e.what());

        }
        catch (...)
        {
            logErr2("--Error: cha_processor: unknow error! %s %d",__FILE__,__LINE__);
        }
    }
    return NULL;
}
void pack_backup_messages(chat_thread_stuff& stuff)
{
    if (stuff.backup_messages.size())
    {
        out_oscar_buffer o;
        string o2;
        for (deque<PTR_getter_nm<chat_msg> > ::iterator i=stuff.backup_messages.begin();i!=stuff.backup_messages.end();i++)
        {
            chat_msg$ *m=i->___ptr->data;
            o<<m->msgtype;
            m->pack(o);
            o2+=m->make_backup(stuff);
        }
        messages_to_backup.push_back(make_pair(o.as_string(),o2));
        stuff.backup_messages.clear();
    }
}
void start_chat_processor()
{
    pthread_t t;
    int r=pthread_create(&t,NULL,chat_processor,NULL);
    if (r!=0) {
        logErr2("--Error while creating pthread_ceate: %d",r);
        return;
    }
}
bool chat_stuff_user::I_can_see(const chat_stuff_user&__z)
{
    if (dbid==__z.dbid) return true;
    bool i_can_see=true;
    if (__z.cstate.status.id==st_offinvisible ||__z.cstate.status.id==st_invisible)
    {
        if (__z.invisibility>invisibility) return false;
    }
    if (user_type==TYPE_IRC) return true;
    if (ul_mode_contacts_only)
    {
        if (contacts.count(__z.dbid)) return true;
    }
    if (ul_mode_hide_male)
    {
        if (__z.gender!=2)return false;
    }
    if (ul_mode_hide_female)
    {
        if (__z.gender!=1)return false;
    }

    return true;
}
void on_UPDATE_DATA(chat_event_UPDATE_DATA *e,chat_thread_stuff &stuff)
{

    oscar_buffer o(e->buf.data(),e->buf.size());
    int cmd;
    o>>cmd;
    DB_id uid;
    o>>uid;
    map<DB_id,PTR_getter_nm<chat_stuff_user_p> > ::iterator it=stuff.users.find(uid);
    if (it==stuff.users.end()) return;
    chat_stuff_user &__u=it->second.___ptr->ud;

    switch (cmd)
    {
    case user_stat$last_ip:
        o>>__u.ip;
        break;
    case user_stat$last_pip:
        o>>__u.pip;
        break;
    case user_set$ul_mode_contacts_only:
        o>>__u.ul_mode_contacts_only;
        break;
    case user_set$ul_mode_hide_male:
        o>>__u.ul_mode_hide_male;
        break;
    case user_set$ul_mode_hide_female:
        o>>__u.ul_mode_hide_female;
        break;

    case user_set$contact_options:
        o>>__u.contact_options;
        break;
    case ignore$add: {
        DB_id zid;
        o>>zid;
        __u.ignores.insert(zid);
    } break;
    case ignore$remove: {
        DB_id zid;
        o>>zid;
        __u.ignores.erase(zid);
    } break;
    case contact$add: {
        DB_id zid;
        o>>zid;
        __u.contacts.insert(zid);
    } break;
    case contact$remove: {
        DB_id zid;
        o>>zid;
        __u.contacts.erase(zid);
    } break;
    case user_profile$gender:
        o>>__u.gender;
        break;
    case user_set$setting_show_eye:
        o>>__u.setting_show_eye;
        break;
    case user_profile$city:
        o>>__u.city;
        break;
    case user_set$neye:
        o>>__u.neye;
        break;
    case user_set$lpp:
        o>>__u.lpp;
        break;
    case user_profile$b_day:
        o>>__u.b_day;
        break;
    case user_profile$b_mon:
        o>>__u.b_mon;
        break;
    case user_set$hide_bdate:
        o>>__u.hide_bdate;
        break;
    case user_profile$db_privileges:
    {
        o>>__u.db_privileges;
        __u.privileges=__u.db_privileges|__u.clevel.privileges;
    }
    break;
    case user_set$bought_invisibility:
    {
        o>>__u.bought_invisibility;
        __u.invisibility=__u.bought_invisibility+__u.clevel.invisibility;
    }
    break;
    case user_profile$level:
    {
        o>>__u.level;
        __u.clevel=LEVELS(__u.level);
        __u.invisibility=__u.clevel.invisibility+__u.bought_invisibility;
        __u.privileges=__u.db_privileges+__u.clevel.privileges;
    } break;
    case user_profile$login:
        o>>__u.login;
        break;
    case user_set$n_color_pack:
    {
        o>>__u.n_color_pack;
        PTR_getter<c_pack> cp=c_packs.get(__u.n_color_pack);
        {
            PGLR(c_pack, c,cp);
            __u.nickstyle=c->nickstyle;
        }
    }break;
    case nick$add:
    {

        user_nick n;
        o>>n;

        map<DB_id,PTR_getter_nm<chat_stuff_user_p> > ::iterator it=stuff.users.find(uid);
        string sn=str_nick(n.name);
        if (it!=stuff.users.end())
        {
            stuff.strnick2__u.insert(make_pair(sn,stuff.users.find(uid)->second));
            __u.str_nicks[n.id]=sn;
        }
    }
    case nick$remove:
    {
        unsigned int nid;
        o>>nid;
        if (__u.str_nicks.count(nid))
        {
            string sn=__u.str_nicks[nid];//(n.name);

            stuff.strnick2__u.erase(sn);
            __u.str_nicks.erase(nid);
        }
    }
    case nick$change_nick:
    {


    }break;

    }

}
void on_irc_cmd_ISON(chat_event_irc_cmd_ISON *e,chat_thread_stuff &stuff)
{
    vector<string> onus;
    DB_id uid=user$id(e->__U);
    for (unsigned int i=0;i<e->nicks.size();i++) {
        string strn=str_nick(e->nicks[i]);
        if (stuff.strnick2__u.count(strn) && stuff.users.count(uid))
        {
            chat_stuff_user &__z=stuff.strnick2__u.find(strn)->second.___ptr->ud;
            chat_stuff_user &__u=stuff.users.find(uid)->second.___ptr->ud;
            if (__u.I_can_see(__z))
                onus.push_back(e->nicks[i]);
        }
    }

    irc_send_reply(e->__U,303,join(" ",onus));

}
void on_irc_cmd_WHOIS(chat_event_irc_cmd_WHOIS *e,chat_thread_stuff &stuff)
{
    string strn=str_nick(e->nick);
    DB_id uid=user$id(e->__U);
    if (stuff.strnick2__u.count(strn) && stuff.users.count(uid))
    {
        chat_stuff_user &__z=stuff.strnick2__u.find(strn)->second.___ptr->ud;
        chat_stuff_user &__u=stuff.users.find(uid)->second.___ptr->ud;
        unsigned int levelsub_levels;
        bool admin;
        bool found=false;
        string cnick;
        string irc_host=string(irc_server_config.host);
        string r;
        {
            PGLR(user_profile,u,user_profiles.find_by_id(uid));
            levelsub_levels=u->level/sub_levels;
        }
        admin=levelsub_levels>=am_admin;
        {
            PGLR(user_set,u,user_sets.find_by_id(uid));
            cnick=u->last_nick;
        }
        {
            string host;
            string zfname;
            string zlname;
            string zlogin;
            {
                PGLR(user_profile,z,user_profiles.find_by_id(__z.dbid));
                zfname=z->fname;
                zlname=z->lname;
                zlogin=z->login;
            }
            if (levelsub_levels>=am_spy) {
                PGLR(user_stat,z,user_stats.find_by_id(__z.dbid))
                host=z->last_ip;
            } else {
                host=irc_host;
            }
            {
                PGLR(user_set,u,user_sets.find_by_id(__z.dbid));
                if (u->hide_lname) {
                    if (!admin) {
                        zfname="";
                    } else {
                        zfname << " " << _MSG("hidden");
                    }
                }
                if (u->hide_fname) {
                    if (!admin) {
                        zlname="";
                    } else {
                        zlname << " " << _MSG("hidden");
                    }
                }
            }
            string nnk=e->nick;
            if (levelsub_levels>=am_spy) {
                nnk=zlogin;
            }
            r+=irc_gen_reply2(311,e->nick+" "+nnk+" "+host+" *",zfname+" "+zlname,irc_host,cnick);
            r+=irc_gen_reply2(312,e->nick+" "+irc_host,irc_server_config.location,irc_host,cnick);
            if (admin)r+=irc_gen_reply2(317,e->nick+" "+itostring(time(NULL)-__z.last_m_time),"seconds idle",irc_host,cnick);
            r+=make_user_info(__z.dbid,uid,admin,true,irc_host,cnick,true).as_string();
            r+=irc_gen_reply2(318,e->nick,"End of WHOIS list.",irc_host,cnick);

            if (__u.I_can_see(__z)) {
                data_push_back(e->__U,r);
            }
            else {
                irc_send_reply(e->__U,401,"No such nick/channel");
            }
        }

    }
    else {
        irc_send_reply(e->__U,401,"No such nick/channel");
    }

}

#ifndef __CLAN

#else

#endif
