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
#include "chat_def.h"
#include "utils.h"
#include "web_tools.h"
#include "cm_container.h"
#include "irc_server_config.h"
#include "chat_globals.h"
#ifndef __CLAN
#endif
#include "chat_thread_event.h"


extern m_var<string> url_users_content;
void make_url_users_content(chat_thread_stuff &stuff)
{

    int users_cnt=0;
    map<CH_id, vector<string> > v;
    map<CH_id, string> name2;
    int csize=stuff.channels.size();
    for (map<CH_id,c_set> ::iterator i=stuff.channels.begin();i!=stuff.channels.end();i++)
    {
        vector<string> __v;
        v[i->first]=__v;
        for (map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > > ::iterator j=i->second.u_list.begin();j!=i->second.u_list.end();j++)
        {
            if (!j->second.first.___ptr) continue;
            chat_stuff_user &__z=j->second.first.___ptr->ud;

            if (__z.cstate.status.id!=st_invisible && __z.cstate.status.id!=st_offinvisible &&__z.cstate.status.id!=user_state::UNDEF)
            {
                v[i->first].push_back(__z.cstate.nick.name);
                users_cnt++;
            }
        }
        {
            name2[i->first]=i->second.cd.name2();
        }
    }

    map<string,string> m;
    string u;
    string s;

    if (csize==1) {
        str_sort(v.begin()->second);
        string q;
        vector<string> &vs=v.begin()->second;
        if (vs.size()==0) {
            q=_MSG("empty");
        }
        else {
            for (unsigned int j=0;j<vs.size();j++) {
                q+=vs[j]+"<br>";
            }
        }
        u=q;
    } else {
        for (map<CH_id, vector<string> > ::iterator i=v.begin();i!=v.end();i++) {
            vector<string> &vs=i->second;
            str_sort(vs);
            string q;
            if (vs.size()==0) {
                q=_MSG("empty");
            }
            else {
                for (unsigned int j=0;j<vs.size();j++) {
                    q+=vs[j]+"<br>";
                }
            }
            m["~num~"]=itostring(i->first.container);
            {
                m["~cn~"]=name2[i->first];
            }
            m["~cc~"]=itostring(vs.size());
            m["~users~"]=q;
            u+=RVfiles(m,"frame_user_channel");
        }
    }
    map<string,string> z;
    z["~users~"]=u;
    z["~cnt~"]=itostring(users_cnt);
    string ret;
    if (csize==1) {
        ret=RVfiles(z,"frame_user_single");
    } else {
        ret=RVfiles(z,"frame_user");
    }
    url_users_content=ret;

}



string LK_get_users_count_for_web(chat_thread_stuff& stuff)
{
    vector<string>m;
    for (map<CH_id,c_set> ::iterator  i=stuff.channels.begin();i!=stuff.channels.end();i++)
    {
        m.push_back(itostring(i->second.u_list.size()));
    }
    return "<script>parent.rc([" +join(",",m)+"]);</script>";
}

string get_irc_name(const CH_id& channel)
{
    string irc_name;
    {
        __CH_LOCK(chat_channels[channel]);
        irc_name="#"+CH->cd.irc_name;
    }
    return irc_name;
}
void set_user_state(const out_oscar_buffer &s)
{
    chat_event_SET_USER_STATE *e=new chat_event_SET_USER_STATE;
    e->msg=s.as_string();
    send_chat_event(e,true);
}

void send_join_msgs(chat_stuff_user &uu,chat_thread_stuff& stuff,set<CH_id>& join_msgs_channels)
{
    for (set<CH_id>::iterator _ch=join_msgs_channels.begin();_ch!=join_msgs_channels.end();_ch++)
    {
        CH_id ch;
        ch=*_ch;
        c_set &c=stuff.channels[ch];

        chat_msg_JOIN *ej=new chat_msg_JOIN;
        ej->gender=uu.gender;
        ej->nick=uu.cstate.nick.name;
        ej->channel=ch;
        ej->location=uu.city;
        ej->n_index=rand()%msgs_greeting.size();
        for (map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > > ::iterator i=c.u_list.begin();i!=c.u_list.end();i++)
        {

            chat_stuff_user &z=i->second.first.___ptr->ud;

            PTR_getter<chat_user> __Z=local_users.get(z.dbid);
            if (__Z)
            {
                if (z.user_type==TYPE_WWW)
                {
                    string s=ej->make(ch,i->first);
                    s+=SCROLL;
                    data_push_back(__Z,s);
                }
            }

        }
        send_chat_msg(ej,stuff);
    }

}

void send_quit_msgs(chat_stuff_user &uu,chat_thread_stuff& stuff,set<CH_id>& quit_msgs_channels)
{
    for (set<CH_id>::iterator _ch=quit_msgs_channels.begin();_ch!=quit_msgs_channels.end();_ch++)
    {
        CH_id ch;
        ch=*_ch;
        c_set &c=stuff.channels[ch];
        chat_msg_QUIT *eq=new chat_msg_QUIT;
        eq->channel=ch;
        eq->nick=uu.cstate.nick.name;
        eq->add_info=uu.city;
        eq->gender=uu.gender;
        eq->n_index=rand()%msgs_bye.size();
        for (map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > > ::iterator i=c.u_list.begin();i!=c.u_list.end();i++)
        {
            chat_stuff_user &u=i->second.first.___ptr->ud;
            PTR_getter<chat_user> __Z=local_users.get(u.dbid);

            if (__Z)
            {
                if (u.user_type==TYPE_WWW)
                {
//		    if(u.dbid.container==26)
//		    logErr2("if(u.dbid.container==26) %s %d",__FL__);
                    string s=eq->make(ch,i->first);
                    s+=SCROLL;
                    data_push_back(__Z,s);
                }
            }
        }
        send_chat_msg(eq,stuff);
    }
}

void send_chroom_msgs(chat_stuff_user &uu,chat_thread_stuff& stuff,const string &new_channel_name,const CH_id & chan)
{
    c_set &c=stuff.channels[chan];
    chat_msg_CHROOM *eq=new chat_msg_CHROOM;
    eq->channel=chan;
    eq->gender=uu.gender;
    eq->nick=uu.cstate.nick.name;
    eq->chroomname=new_channel_name;
    eq->n_index=rand()%msgs_changes.size();

    for (map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > > ::iterator i=c.u_list.begin();i!=c.u_list.end();i++)
    {

        chat_stuff_user &z=i->second.first.___ptr->ud;

        PTR_getter<chat_user> __Z=local_users.get(z.dbid);
        if (__Z)
        {
            if (z.user_type==TYPE_WWW)
            {
                string s=eq->make(chan,i->first);
                s+=SCROLL;
                data_push_back(__Z,s);
            }
        }
    }
    send_chat_msg(eq,stuff);
}
out_oscar_buffer & operator<<(out_oscar_buffer&b, const chat_stuff_user &n)
{
    b<<n.dbid;
    b<<n.ignores;
    b<<n.contacts;
    b<<n.gender;
    b<<n.ip;
    b<<n.pip;
    b<<n.invisibility;
    b<<n.bought_invisibility;
    b<<n.cstate;
    b<<n.nickstyle;
    b<<n.level;
    b<<n.clevel;
    b<<n.setting_show_eye;
    b<<n.city;
    b<<n.neye;
    b<<n.lpp;
    b<<n.b_day;
    b<<n.b_mon;
    b<<n.hide_bdate;
    b<<n.n_color_pack;
    b<<n.user_type;
    b<<n.login;
    b<<n.privileges;
    b<<n.db_privileges;
    b<<n.contact_options;
    b<<n.ul_mode_contacts_only;
    b<<n.ul_mode_hide_male;
    b<<n.ul_mode_hide_female;
    b<<n.str_nicks;
    b<<n.last_m_time;
    b<<n.last_message;
    b<<n.last_invite_time;
    b<<n.msg_cnt_per_time;
    return b;
}
oscar_buffer & operator>>(oscar_buffer&b, chat_stuff_user &n)
{
    b>>n.dbid;
    b>>n.ignores;
    b>>n.contacts;
    b>>n.gender;
    b>>n.ip;
    b>>n.pip;
    b>>n.invisibility;
    b>>n.bought_invisibility;
    b>>n.cstate;
    b>>n.nickstyle;
    b>>n.level;
    b>>n.clevel;
    b>>n.setting_show_eye;
    b>>n.city;
    b>>n.neye;
    b>>n.lpp;
    b>>n.b_day;
    b>>n.b_mon;
    b>>n.hide_bdate;
    b>>n.n_color_pack;
    b>>n.user_type;
    b>>n.login;
    b>>n.privileges;
    b>>n.db_privileges;
    b>>n.contact_options;
    b>>n.ul_mode_contacts_only;
    b>>n.ul_mode_hide_male;
    b>>n.ul_mode_hide_female;
    b>>n.str_nicks;
    b>>n.last_m_time;
    b>>n.last_message;
    b>>n.last_invite_time;
    b>>n.msg_cnt_per_time;
    return b;
}
#ifndef __CLAN
#endif

out_oscar_buffer & operator<<(out_oscar_buffer&b, const c_set &n)
{
    map<DB_id,set<DB_id> > u;
    for (map<DB_id /*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > >::const_iterator i=n.u_list.begin();i!=n.u_list.end();i++)
    {
        for (map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > ::const_iterator j=i->second.second.begin();j!=i->second.second.end();j++)
            u[i->first].insert(j->first);
    }
    b<<u<<n.cd;
    return b;
}
oscar_buffer & operator>>(oscar_buffer&b, c_set &n)
{
    map<DB_id,set<DB_id> > u;
    b>>u>>n.cd;
    for (map<DB_id,set<DB_id> > ::iterator i=u.begin();i!=u.end();i++)
    {
        map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > tt;
        for (set<DB_id> ::iterator j=i->second.begin();j!=i->second.end();j++)
        {
            PTR_getter_nm<chat_stuff_user_p> p(NULL);
            tt.insert(make_pair(*j,p));
        }
        PTR_getter_nm<chat_stuff_user_p> p(NULL);
        n.u_list.insert(make_pair(i->first,make_pair(p,tt)));
    }
    return b;
}


out_oscar_buffer & operator<<(out_oscar_buffer&b, const chat_thread_stuff &n)
{
    b<< n.channels<<n.to_all<<n.join_time<<n.trash;
    b<<n.users.size();
    for (map<DB_id,PTR_getter_nm<chat_stuff_user_p> >::const_iterator i=n.users.begin();i!=n.users.end();i++)
    {
        b<<i->first;
        b<<i->second.___ptr->ud;
    }
    return b;
}
oscar_buffer & operator>>(oscar_buffer&b, chat_thread_stuff &n)
{
    b>>n.channels>>n.to_all>>n.join_time>>n.trash;
    int nu;
    b>>nu;

    for (int i=0;i<nu;i++)
    {
        DB_id uid;
        PTR_getter_nm<chat_stuff_user_p> pu=new chat_stuff_user_p;
        b>>uid;
        b>>pu.___ptr->ud;
        n.users.insert(make_pair(uid,pu)) ;

    }
    for (map<CH_id,c_set>::iterator i=n.channels.begin();i!=n.channels.end();i++)
    {
        for (map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > >::iterator j=i->second.u_list.begin();j!=i->second.u_list.end();j++)
        {
            if (!j->second.first)
            {
                if (n.users.count(j->first))
                {
                    j->second.first=n.users.find(j->first)->second;
                }
                else
                {
                    logErr2("!n.users.count(j->first) %s","");
                }
            }
            for (map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > ::iterator k=j->second.second.begin();k!=j->second.second.end();k++)
            {
                if (!k->second)
                {
                    if (n.users.count(j->first))
                    {
                        k->second=n.users.find(j->first)->second;
                    }
                    else
                    {
                        logErr2("!n.users.count(j->first) %s","");
                    }

                }
            }
        }
    }
    return b;
}

void chat_event_UPDATE_DATA::pack(out_oscar_buffer &b)
{

    throw cError("invalid for chatevent "+itostring(type)+" ");
}
void chat_event_UPDATE_DATA::unpack(oscar_buffer &b)
{

    throw cError("invalid for chatevent "+itostring(type)+" ");
}

void chat_event_CHAT_MESSAGES::pack(out_oscar_buffer &b)
{

    throw cError("invalid for chatevent "+itostring(type)+" ");
}
void chat_event_CHAT_MESSAGES::unpack(oscar_buffer &b)
{

    throw cError("invalid for chatevent "+itostring(type)+" ");
}

void chat_event_UPDATE_USER_SESSION::pack(out_oscar_buffer &b)
{

    throw cError("invalid for chatevent "+itostring(type)+" ");
}
void chat_event_UPDATE_USER_SESSION::unpack(oscar_buffer &b)
{

    throw cError("invalid for chatevent "+itostring(type)+" ");
}

void chat_event_CHMODE::pack(out_oscar_buffer &b)
{
    b<<nick;
    b<<channel;
    b<<uid;
    b<<mode;
}
void chat_event_CHMODE::unpack(oscar_buffer &b)
{
    b>>nick;
    b>>channel;
    b>>uid;
    b>>mode;
}

void chat_event_SEND_MESSAGE::pack(out_oscar_buffer &b)
{
    b<<from_uid;
    b<<msg;
    b<<tonick;
    b<<priv;
    b<<sys;
    b<<makeit;
    b<<channel;
    b<<user_type;

}
void chat_event_SEND_MESSAGE::unpack(oscar_buffer &b)
{
    b>>from_uid;
    b>>msg;
    b>>tonick;
    b>>priv;
    b>>sys;
    b>>makeit;
    b>>channel;
    b>>user_type;

}
void chat_event_IGNORE::pack(out_oscar_buffer &b)
{
    b<<uid<<zid;

}
void chat_event_IGNORE::unpack(oscar_buffer &b)
{
    b>>uid>>zid;
}
void chat_event_INVITE::pack(out_oscar_buffer &b)
{
    b<<uid;
    b<<zid;
    b<<msg;
}
void chat_event_INVITE::unpack(oscar_buffer &b)
{
    b>>uid;
    b>>zid;
    b>>msg;

}

void chat_event_CHVOICE::pack(out_oscar_buffer &b)
{
    b<<nick;
    b<<channel;
    b<<uid;
    b<<voice;

}
void chat_event_CHVOICE::unpack(oscar_buffer &b)
{
    b>>nick;
    b>>channel;
    b>>uid;
    b>>voice;

}
void chat_event_SET_USER_STATE::pack(out_oscar_buffer &b)
{
    b<<msg;

}
void chat_event_SET_USER_STATE::unpack(oscar_buffer &b)
{
    b>>msg;

}
#ifndef __CLAN
#endif
void chat_event_SEND_DATA_TO_WWW_USERS::pack(out_oscar_buffer &b)
{

    throw cError("invalid for chatevent "+itostring(type)+" ");

}
void chat_event_SEND_DATA_TO_WWW_USERS::unpack(oscar_buffer &b)
{

    throw cError("invalid for chatevent "+itostring(type)+" ");

}

void chat_event_CHTOPIC::pack(out_oscar_buffer &b)
{
    b<<uid;
    b<<channel;
    b<<top;

}
void chat_event_CHTOPIC::unpack(oscar_buffer &b)
{
    b>>uid;
    b>>channel;
    b>>top;

}
void chat_event_irc_cmd_ISON::pack(out_oscar_buffer &b)
{

    throw cError("invalid for chatevent "+itostring(type)+" ");

}
void chat_event_irc_cmd_ISON::unpack(oscar_buffer &b)
{

    throw cError("invalid for chatevent "+itostring(type)+" ");

}
void chat_event_irc_cmd_WHOIS::pack(out_oscar_buffer &b)
{

    throw cError("invalid for chatevent "+itostring(type)+" ");

}
void chat_event_irc_cmd_WHOIS::unpack(oscar_buffer &b)
{

    throw cError("invalid for chatevent "+itostring(type)+" ");

}


string chat_event_INVITE::dump()
{
    return "uid "+itostring(uid.container)+" zid "+itostring(zid.container)+" msg "+msg;
}
string chat_event_CHVOICE::dump()
{
    return "uid "+itostring(uid.container)+" channel "+itostring(channel.container)+" voice "+itostring(voice);

}
string chat_event_CHMODE::dump()
{
    return "uid "+itostring(uid.container)+" channel "+itostring(channel.container)+" mode "+itostring(mode)+" nick "+nick;

}
string chat_event_CHAT_MESSAGES::dump()
{
    return "uid "+itostring(uid.container)+" channel "+c;

}
string chat_event_UPDATE_DATA::dump()
{
    return "";
}
string chat_event_SET_USER_STATE::dump()
{
    return "";
}
string chat_event_irc_cmd_WHOIS::dump()
{
    return "";
}
string chat_event_irc_cmd_ISON::dump()
{
    return "";
}
string chat_event_CHTOPIC::dump()
{
    return "";
}
string chat_event_SEND_DATA_TO_WWW_USERS::dump()
{
    return "";
}
string chat_event_IGNORE::dump()
{
    return "";
}
string chat_event_SEND_MESSAGE::dump()
{
    return "";
}
string chat_event_UPDATE_USER_SESSION::dump()
{
    return "";
}
