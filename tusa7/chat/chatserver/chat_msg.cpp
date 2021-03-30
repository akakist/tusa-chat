#include "stdafx.h"
#include <string>
#include "PTR.h"
#include "oscar_buffer.h"
#include "DB_id.h"
#include "CH_id.h"
#include "chat_msg.h"
#include "chat_colors.h"
#include "str_lib.h"
#include "cm_container.h"
#include "utils.h"
#include "chat_config.h"
#include "M_DEQUE.h"
#include "chat_stuff.h"
using namespace std;

string _MSG(const string &n);

M_DEQUE<chat_msg$ *> chat_msgs_deque;
void send_chat_msg(chat_msg$ *e)
{
    chat_msgs_deque.push_back(e);
}

chat_msg_STDTO::~chat_msg_STDTO() {}
chat_msg_STDTO::chat_msg_STDTO():chat_msg$(STDTO) {}

chat_msg_PRIV::~chat_msg_PRIV() {}
chat_msg_PRIV::chat_msg_PRIV():chat_msg$(PRIV) {}

chat_msg_SYSPRIV::~chat_msg_SYSPRIV() {}
chat_msg_SYSPRIV::chat_msg_SYSPRIV():chat_msg$(SYSPRIV) {}

chat_msg_SYS::~chat_msg_SYS() {}
chat_msg_SYS::chat_msg_SYS():chat_msg$(SYS) {}

chat_msg_MAKEIT::chat_msg_MAKEIT():chat_msg$(MAKEIT) {}
chat_msg_MAKEIT::~chat_msg_MAKEIT() {}



chat_msg_QUIT::chat_msg_QUIT():chat_msg$(QUIT),n_index(-1) {}
chat_msg_QUIT::~chat_msg_QUIT() {}

chat_msg_KICK::~chat_msg_KICK() {}
chat_msg_KICK::chat_msg_KICK():chat_msg$(KICK),n_index(-1) {}

chat_msg_CHNICK::~chat_msg_CHNICK() {}
chat_msg_CHNICK::chat_msg_CHNICK():chat_msg$(CHNICK),n_index(-1) {}

chat_msg_KILLED::~chat_msg_KILLED() {}
chat_msg_KILLED::chat_msg_KILLED():chat_msg$(KILLED),n_index(-1) {}

chat_msg_JOIN::~chat_msg_JOIN() {}
chat_msg_JOIN::chat_msg_JOIN():chat_msg$(JOIN),n_index(-1) {}

chat_msg_CHTOPIC::~chat_msg_CHTOPIC() {}
chat_msg_CHTOPIC::chat_msg_CHTOPIC():chat_msg$(CHTOPIC),n_index(-1) {}

chat_msg_CHROOM::~chat_msg_CHROOM() {}
chat_msg_CHROOM::chat_msg_CHROOM():chat_msg$(CHROOM),n_index(-1) {}

chat_msg_MAT::chat_msg_MAT():chat_msg$(MAT),n_index(-1) {}
chat_msg_MAT::~chat_msg_MAT() {}


chat_msg_MODE::chat_msg_MODE():chat_msg$(MODE),n_index(-1) {}
chat_msg_MODE::~chat_msg_MODE() {}


string chat_msg_STDTO::make(const CH_id& chan,const DB_id &__id)
{
    if (chan!=channel)return "";
    if (from_id==__id)
    {
        if (prepf.size()) return prepf;
        PTR_getter<c_pack> cp=c_packs.get(n_color_pack);
        map<string,string>m;
        m["~fromnick~"]=_nick$(from_nick,false,cp);


        m["~msg~"]=msg;
        string ccc;
        {
            PGLR(c_pack, c,cp);
            ccc=c->stdto;
        }
        prepf=replace_vals(m,ccc);
        return prepf;
    }
    else if (to_id==__id)
    {
        if (prept.size()) return prept;
        PTR_getter<c_pack> cp=c_packs.get(n_color_pack);
        map<string,string>m;
        m["~fromnick~"]=_nick$(from_nick,false,cp);
        m["~msg~"]=msg;
        string ccc;
        {
            PGLR(c_pack, c,cp);
            ccc=c->stdfrom;
        }
        prept=replace_vals(m,ccc);
        return prept;

    }
    else
    {
        if (prepa.size()) return prepa;
        PTR_getter<c_pack> cp=c_packs.get(n_color_pack);
        map<string,string>m;
        {
            m["~fromnick~"]=_nick$(from_nick,false,cp);
        }
        m["~msg~"]=msg;
        string ccc;
        {
            PGLR(c_pack, c,cp);
            ccc=c->std;
        }
        prepa=replace_vals(m,ccc);
        return prepa;
    }
}

string chat_msg_PRIV::make(const CH_id& __ch,const DB_id &__id)
{
    if (channel!=__ch) return "";
    if (__id==from_id)
    {
        if (prepf.size()) return prepf;
        PTR_getter<c_pack> cp=c_packs.get(n_color_pack);
        map<string,string>m;
        m["~tonick~"]=_nick$(to_nick,true,cp);;
        m["~msg~"]=msg;
        string ccc;
        {
            PGLR(c_pack, c,cp);
            ccc=c->privto;
        }

        prepf=replace_vals(m,ccc);
        return prepf;

    }
    else if (__id==to_id)
    {
        if (prept.size()) return prept;
        PTR_getter<c_pack> cp=c_packs.get(n_color_pack);
        map<string,string>m;
        m["~fromnick~"]=_nick$(from_nick,true,cp);;
        m["~msg~"]=msg;
        string ccc;
        {
            PGLR(c_pack, c,cp);
            ccc=c->privfrom;
        }
        prept=replace_vals(m,ccc);
        return prept;

    }
    return "";
}


string chat_msg_MAKEIT::make(const CH_id& chan,const DB_id &)
{
    if (chan!=channel)return "";
    if (preparation.size()) return preparation;
    PTR_getter<c_pack> cp=c_packs.get(n_color_pack);
    map<string,string>m;
    string n;
    n=_nick$(from_nick,false,cp);
    m["~fromnick~"]=n;
    m["~msg~"]=msg;
    string ccc;
    {
        PGLR(c_pack, c,cp);
        ccc=c->makeit;
    }
    preparation=replace_vals(m,ccc);
    return preparation;

}
string chat_msg_SYS::make(const CH_id &chan,const DB_id &)
{

    if (chan!=channel)return "";
    if (preparation.size()) return preparation;
    PTR_getter<c_pack> cp=c_packs.get(0);
    map<string,string>m;
    m["~msg~"]=msg;
    string ccc;
    {
        PGLR(c_pack, c,cp);
        ccc=c->sys;
    }
    preparation=replace_vals(m,ccc);
    return preparation;

}
string chat_msg_SYSPRIV::make(const CH_id& __ch,const DB_id &__id)
{
    if (channel!=__ch) return "";
    if (__id==from_id)
    {
        map<DB_id,string>::iterator it=preparations.find(__id);
        if (it!=preparations.end())return it->second;
        PTR_getter<c_pack> cp=c_packs.get(0);
        map<string,string>m;
        if (to_nick.size())
            m["~fornick~"]=_MSG("for")+" "+to_nick;
        else
            m["~fornick~"]="";
        m["~msg~"]=msg;
        string ccc;
        {
            PGLR(c_pack, c,cp);
            ccc=c->syspriv;
        }
        string ret=replace_vals(m,ccc);
        preparations[__id]=ret;
        return ret;
    }
    else if (__id==to_id)
    {
        map<DB_id,string>::iterator it=preparations.find(__id);
        if (it!=preparations.end())return it->second;
        PTR_getter<c_pack> cp=c_packs.get(0);
        map<string,string>m;
        m["~msg~"]=msg;
        m["~fornick~"]="";
        string ccc;
        {
            PGLR(c_pack, c,cp);
            ccc=c->syspriv;
        }
        string ret=replace_vals(m,ccc);
        preparations[__id]=ret;
        return ret;

    }
    return "";
}
string chat_msg_JOIN::make(const CH_id &chan,const DB_id &)
{
    if (chan!=channel)return "";
    if (preparation.size()) return preparation;
    PTR_getter<c_pack> cp=c_packs.get(0);
    string s=msgs_greeting.get(gender,n_index);
    string n=_nick$(nick,false,cp);
    map<string,string> q;
    char ss[300];
    tm TM=LOCALTIME(time(NULL));
    int z=strftime(ss,sizeof(ss)-2,string(chat_config.time_format).c_str(),&TM);
    string t(ss,z);

    q["~who~"]=n;
    q["~time~"]=t;
    q["~location~"]=location;
    map<string,string> m;
    m["~msg~"]=replace_vals(q,s);
    string ccc;
    {
        PGLR(c_pack, c,cp);
        ccc=c->sys;
    }
    string ret=replace_vals(m,ccc);
    preparation=ret;
    return ret;
}

string chat_msg_KILLED::make(const CH_id &chan,const DB_id &)
{
    if (chan!=channel)return "";
    if (preparation.size()) return preparation;
    PTR_getter<c_pack> cp=c_packs.get(0);
    string s=msgs_killing.get(gender,n_index);
    string n=_badnick$(nick,cp);
    char ss[300];
    snprintf(ss,sizeof(ss)-1,s.c_str(),n.c_str());
    map<string,string>m;
    m["~msg~"]=ss;
    string ccc;
    {
        PGLR(c_pack, c,cp);
        ccc=c->sys;
    }
    string ret=replace_vals(m,ccc);
    preparation=ret;
    return ret;

}

string chat_msg_QUIT::make(const CH_id &chan,const DB_id &)
{
    if (chan!=channel)return "";
    if (preparation.size()) return preparation;
    PTR_getter<c_pack> cp=c_packs.get(0);
    string s=msgs_bye.get(gender,n_index);
    string n=_badnick$(nick,cp);
    map<string,string> q;
    char ss[300];
    tm TM=LOCALTIME(time(NULL));
    int z=strftime(ss,sizeof(ss)-2,string(chat_config.time_format).c_str(),&TM);
    string t(ss,z);
    q["~who~"]=n;
    q["~time~"]=t;
    q["~location~"]=add_info;
    map<string,string>m;
    m["~msg~"]=replace_vals(q,s);
    string ccc;
    {
        PGLR(c_pack,c,cp);
        ccc=c->sys;
    }
    string ret=replace_vals(m,ccc);
    preparation=ret;
    return ret;

}
string chat_msg_KICK::make(const CH_id &chan,const DB_id &)
{
    if (chan!=channel)return "";
    if (preparation.size()) return preparation;

    PTR_getter<c_pack> cp=c_packs.get(0);
    string s=msgs_kicking.get(gender,n_index);
    string n=_badnick$(nick,cp);
    string pr;
    if (zamsg.size()) {
        pr=_MSG("za")+" "+zamsg;
    }
    char ss[2000];
    snprintf(ss,sizeof(ss)-1,s.c_str(),n.c_str(),pr.c_str());
    map<string,string>m;
    m["~msg~"]=ss;
    string ccc;
    {
        PGLR(c_pack, c,cp);
        ccc=c->sys;
    }
    string ret=replace_vals(m,ccc);
    preparation=ret;
    return ret;

}
string chat_msg_CHROOM::make(const CH_id &chan,const DB_id &)
{
    if (chan!=channel)return "";
    if (preparation.size()) return preparation;
    PTR_getter<c_pack> cp=c_packs.get(0);
    string s=msgs_changes.get(gender,n_index);
    string n=_badnick$(nick,cp);
    char ss[300];
    snprintf(ss,sizeof(ss)-1,s.c_str(),n.c_str(),chroomname.c_str());
    map<string,string>m;
    m["~msg~"]=ss;
    string ccc;
    {
        PGLR(c_pack, c,cp);
        ccc=c->sys;
    }
    string ret=replace_vals(m,ccc);
    preparation=ret;
    return ret;

}
string chat_msg_CHNICK::make(const CH_id &chan,const DB_id &)
{
    if (chan!=channel)return "";
    if (preparation.size()) return preparation;

    PTR_getter<c_pack> cp=c_packs.get(0);
    string s=msgs_nickchanges.get(gender,n_index);
    string n=_badnick$(oldnick,cp);
    string n2=_nick$(newnick,false,cp);
    char ss[300];
    snprintf(ss,sizeof(ss)-1,s.c_str(),n.c_str(),n2.c_str());
    map<string,string>m;
    m["~msg~"]=ss;
    string ccc;
    {
        PGLR(c_pack, c,cp);
        ccc=c->sys;
    }
    string ret=replace_vals(m,ccc);
    preparation=ret;
    return ret;

}

string chat_msg_MAT::make(const CH_id &chan,const DB_id &)
{
    if (chan!=channel)return "";
    if (preparation.size()) return preparation;

    PTR_getter<c_pack> cp=c_packs.get(0);
    string s=msgs_maty.get(gender,n_index);

    string n2=_nick$(nick,false,cp);
    char ss[300];
    snprintf(ss,sizeof(ss)-1,s.c_str(),n2.c_str());
    map<string,string>m;
    m["~msg~"]=ss;
    string ccc;
    {
        PGLR(c_pack, c,cp);
        ccc=c->sys;
    }
    string ret=replace_vals(m,ccc);
    preparation=ret;
    return ret;

}
string chat_msg_CHTOPIC::make(const CH_id &chan,const DB_id &)
{
    if (chan!=channel)return "";
    if (preparation.size()) return preparation;

    PTR_getter<c_pack> cp=c_packs.get(0);

    string s=msgs_topicchanges.get(gender,n_index);
    string n;
    n=_nick$(nick,false,cp);

    char ss[300];
    snprintf(ss,sizeof(ss)-1,s.c_str(),n.c_str(),topic.c_str());
    map<string,string> m;
    m["~msg~"]=ss;
    string ccc;
    {
        PGLR(c_pack, c,cp);
        ccc=c->sys;
    }
    string ret=replace_vals(m,ccc);
    preparation=ret;
    return ret;

}
string chat_msg_MODE::make(const CH_id &chan,const DB_id &)
{
    if (chan!=channel)return "";
    if (preparation.size()) return preparation;

    PTR_getter<c_pack> cp=c_packs.get(0);

    string s=msgs_modechanges.get(gender,n_index);
    string n=_nick$(nick1,false,cp);

    char ss[300];
    if (msg=="+v" || msg=="-v") {
        string z=msg+" "+_badnick$(nick2,cp);
        snprintf(ss,sizeof(ss)-1,s.c_str(),n.c_str(),z.c_str());
    } else {
        snprintf(ss,sizeof(ss)-1,s.c_str(),n.c_str(),_MSG("channelmode"+msg).c_str());
    }
    map<string,string>m;
    m["~msg~"]=ss;
    string ccc;
    {
        PGLR(c_pack, c,cp);
        ccc=c->sys;
    }
    string ret=replace_vals(m,ccc);
    preparation=ret;
    return ret;
}

void chat_msg_CHNICK::pack(out_oscar_buffer&o) {
    o<<channel<<gender<<n_index<<oldnick<<newnick;
}
void chat_msg_CHNICK::unpack(oscar_buffer&o) {
    o>>channel>>gender>>n_index>>oldnick>>newnick;
}
void chat_msg_CHROOM::pack(out_oscar_buffer&o) {
    o<<channel<<gender<<n_index<<nick<<chroomname;
}
void chat_msg_CHROOM::unpack(oscar_buffer&o) {
    o>>channel>>gender>>n_index>>nick>>chroomname;
}
void chat_msg_CHTOPIC::pack(out_oscar_buffer&o) {
    o<<channel<<gender<<n_index<<nick<<topic;
}
void chat_msg_CHTOPIC::unpack(oscar_buffer&o) {
    o>>channel>>gender>>n_index>>nick>>topic;
}
void chat_msg_JOIN::pack(out_oscar_buffer&o) {
    o<<channel<<n_index<<location<<nick<<gender;
}
void chat_msg_JOIN::unpack(oscar_buffer&o) {
    o>>channel>>n_index>>location>>nick>>gender;
}
void chat_msg_KICK::pack(out_oscar_buffer&o) {
    o<<channel<<nick<<zamsg<<gender<<n_index;
}
void chat_msg_KICK::unpack(oscar_buffer&o) {
    o>>channel>>nick>>zamsg>>gender>>n_index;
}
void chat_msg_KILLED::pack(out_oscar_buffer&o) {
    o<<channel<<n_index<<gender<<nick;
}
void chat_msg_KILLED::unpack(oscar_buffer&o) {
    o>>channel>>n_index>>gender>>nick;
}
void chat_msg_MAKEIT::pack(out_oscar_buffer&o) {
    o<<channel<<from_id<<from_nick<<msg<<n_color_pack;
}
void chat_msg_MAKEIT::unpack(oscar_buffer&o) {
    o>>channel>>from_id>>from_nick>>msg>>n_color_pack;
}
void chat_msg_MAT::pack(out_oscar_buffer&o) {
    o<<channel<<gender<<n_index<<nick;
}
void chat_msg_MAT::unpack(oscar_buffer&o) {
    o>>channel>>gender>>n_index>>nick;
}
void chat_msg_PRIV::pack(out_oscar_buffer&o) {
    o<<channel<<from_id<<to_id<<from_nick<<to_nick<<msg<<n_color_pack;
}
void chat_msg_PRIV::unpack(oscar_buffer&o) {
    o>>channel>>from_id>>to_id>>from_nick>>to_nick>>msg>>n_color_pack;
}
void chat_msg_QUIT::pack(out_oscar_buffer&o) {
    o<<channel<<n_index<<nick<<add_info<<gender;
}
void chat_msg_QUIT::unpack(oscar_buffer&o) {
    o>>channel>>n_index>>nick>>add_info>>gender;
}
void chat_msg_STDTO::pack(out_oscar_buffer &o) {
    o<<from_id<<to_id<<channel<<from_nick<<msg<<n_color_pack;
}
void chat_msg_STDTO::unpack(oscar_buffer &o) {
    o>>from_id>>to_id>>channel>>from_nick>>msg>>n_color_pack;
}
void chat_msg_SYS::pack(out_oscar_buffer&o) {
    o<<channel<<from_id<<msg;
}
void chat_msg_SYS::unpack(oscar_buffer&o) {
    o>>channel>>from_id>>msg;
}
void chat_msg_SYSPRIV::pack(out_oscar_buffer&o) {
    o<<channel<<from_id<<to_id<<to_nick<<msg;
}
void chat_msg_SYSPRIV::unpack(oscar_buffer&o) {
    o>>channel>>from_id>>to_id>>to_nick>>msg;
}
void chat_msg_MODE::pack(out_oscar_buffer&o) {
    o<<channel<<from_id<<nick1<<nick2<<msg<<n_index<<gender;
}
void chat_msg_MODE::unpack(oscar_buffer&o) {
    o>>channel>>from_id>>nick1>>nick2>>msg>>n_index>>gender;
}




string chat_msg_MAT::make_backup(chat_thread_stuff& stuff)
{
    return ":MAT: n:+"+nick+"\n";
}
string chat_msg_STDTO::make_backup(chat_thread_stuff&)
{
    return ":STDTO: n:"+from_nick+" m:"+msg+"\n";
}
string chat_msg_PRIV::make_backup(chat_thread_stuff&)
{
    return ":PRIV: fn:"+from_nick+" tn:"+to_nick+" m:"+msg+"\n";
}
string chat_msg_MAKEIT::make_backup(chat_thread_stuff&)
{
    return ":MAKEIT: n:"+from_nick+" m:"+msg+"\n";
}
string chat_msg_MODE::make_backup(chat_thread_stuff&)
{
    return "";
}
string chat_msg_JOIN::make_backup(chat_thread_stuff&)
{
    return "";
}
string chat_msg_QUIT::make_backup(chat_thread_stuff&)
{
    return "";
}
string chat_msg_KILLED::make_backup(chat_thread_stuff&)
{
    return "";
}
string chat_msg_KICK::make_backup(chat_thread_stuff&)
{
    return "";
}
string chat_msg_CHTOPIC::make_backup(chat_thread_stuff&)
{
    return "";
}
string chat_msg_SYS::make_backup(chat_thread_stuff& stuff)
{
    map<DB_id,PTR_getter_nm<chat_stuff_user_p> > ::iterator it=stuff.users.find(from_id);
    if (it!=stuff.users.end())
    {
        return ":SYS: n:"+it->second.___ptr->ud.cstate.nick.name+" m:"+msg+"\n";
    }
    return "";
}
string chat_msg_SYSPRIV::make_backup(chat_thread_stuff& stuff)
{
    map<DB_id,PTR_getter_nm<chat_stuff_user_p> > ::iterator it=stuff.users.find(from_id);
    if (it!=stuff.users.end())
    {
        return ":SYS: fn:"+it->second.___ptr->ud.cstate.nick.name+" tn:"+to_nick+" m:"+msg+"\n";
    }
    return "";
}
string chat_msg_CHROOM::make_backup(chat_thread_stuff&)
{
    return "";
}
string chat_msg_CHNICK::make_backup(chat_thread_stuff&)
{
    return "";
}
