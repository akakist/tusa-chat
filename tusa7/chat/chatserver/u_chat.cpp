#ifdef __GNUC__
#pragma implementation				// gcc: implement sql_udf.h
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
#include "web_tools.h"
#include "file_set.h"
#include "web_server_data.h"
#include "tcp_sender.h"
#include "channels.h"
#include "levels.h"
#include "register.h"
#include "server_config.h"
#include "chat_colors.h"



#include "irc_server_config.h"
#include "irc_utils.h"

#include "update_cmd.h"
#include "cm_container.h"
#include "ignore_vec.h"

#include "contact_vec.h"
#include "user_stat.h"

#include "notes.h"
#include "fotos.h"



bool user__connection_is_active(const user_pair&__U)
{
    PTR_getter<c_socket>sok(NULL);
    {
        __UC_LOCK;
        sok=u->psocket;
    }
    if (!sok) return false;
    PGLW(c_socket,s,sok);
    return s->connected();
}
void user_destroy(const PTR_getter<chat_user>&__UU)
{//;
    user_pair __U(__UU);
    DB_id session_id;
    {
        __UC_LOCK;
        session_id=u->db_id;
        u->erased=true;

    }
    bool _inchat=inchat$(__U.cu);
    if (_inchat) {

        user_exit_chat(__UU,false);
    }
    {
        user_unregister_all_nicks(session_id,true);
    }
    {

        __UC_LOCK;
        u->psocket=NULL;
        u->erased=true;
    }

}



void user_exit_chat(const PTR_getter<chat_user> &__UU,bool killed)
{
    user_pair __U(__UU);
//    if(is_www_user(__U))
    {
        out_oscar_buffer o;
        o<<user_state::PARTALL<<user$id(__U);
        set_user_state(o);
    }
    {
        __UC_LOCKW;
        u->cstate.channel.clear();
    }
}



extern map<string,time_t> ip_spent_time;
extern _mutex ip_spent_time_MX;
string get_full_name(const user_pair &__U)
{

    string a;
    string fname=user$fname(__U);
    string lname=user$lname(__U);
    if (fname!="") {
        a+=fname;
    }
    if (lname!="") {
        a+=" "+lname;
    }
    return a;

    return "";
}

int has_inv(const user_pair& __U)
{
    {
        PGLR(user_set, u,__U.us);
        if (u->bought_invisibility)return true;
    }
    if (LEVELS(user$level(__U)).invisibility) return true;
    return false;
}
chat_user$::~chat_user$()
{

}
chat_user$::chat_user$():erased(false),last_change_nick(0),last_m_time(0),last_pincode_entered(0),create_time(time(NULL))
{

}
chat_user::chat_user(int t):base_container("chat_user"),psocket(NULL),
        __user_profile(NULL), __user_set(NULL)
{
    user_type=t;
}

string user$login(const DB_id& uid)
{

    {
        PGLR(user_profile, u,user_profiles.find_by_id(uid));
        return u->login;
    }
}
string user$login(const user_pair& __U)
{
    {
        PGLR(user_profile, u,__U.up);
        return u->login;
    }
}
string user$pass(const user_pair& __U)
{
    {
        PGLR(user_profile, u,__U.up);
        return u->pass;
    }

}
int user$gender(const user_pair& __U)
{
    {
        PGLR(user_profile, u,__U.up);
        return u->get_gender();
    }

}

unsigned int user$n_color_pack(const user_pair&__U)
{
    {
        PGLR(user_set, u,__U.us);
        return u->n_color_pack;
    }

}
string user$ip(const user_pair& __U)
{
    {
        __UC_LOCK;
        return u->cu_ip;
    }
}

int user$privileges(const user_pair& __U)
{
    unsigned int privs=LEVELS(user$level(__U)).privileges;

    {
        PGLR(user_profile, u,__U.up);
        privs|=u->db_privileges;
    }
    return privs;
}
string user$proxy_ip(const user_pair& __U)
{
    {
        __UC_LOCK;
        return u->www_proxy_ip;
    }
    return "";
}
int user$get_spent_time(const user_pair& __U)
{
    {
        __UC_LOCK;
        return time(NULL)-u->create_time;
    }
    return 0;

}
DB_id user$id(const user_pair& __U)
{
    {
        PGLR(chat_user,u,__U.cu);
        return u->db_id;
    }

}
set<CH_id> user$channel(const user_pair& __U)
{
    {
        __UC_LOCK;
        return u->cstate.channel;
    }

}
bool inchat$(const PTR_getter<chat_user> &__U)
{

    {
        PGLR(chat_user, u,__U);
        return u->cstate.channel.size();
    }
}
unsigned int user$level(const user_pair& __U)
{
    {
        PGLR(user_profile, u,__U.up);
        return u->level;
    }

}
bool is_inv(const user_pair& __U)
{
    {
        __UC_LOCK;
        if (u->cstate.status.id==st_invisible || u->cstate.status.id==st_offinvisible ) return true;
    }
    return false;
}

void data_push_back(const user_pair& __U, const string& s)
{
    data_push_back(__U.cu,s);
}
void data_push_back(const PTR_getter<chat_user>& __U, const string& s)
{
    if (!__U) return;
    int utype;
    PTR_getter<c_socket> psocket(NULL);
    {
        PGLR(chat_user,u,__U);
        psocket=u->psocket;
        utype=u->user_type;
    }
    if (!psocket) {
        return;
    }
    if (utype==TYPE_IRC)
    {
        write_sender_data(psocket,s);

    }
    if (utype==TYPE_WWW)
    {
        PTR_getter<c_socket> psocket(NULL);
        {
            PGLR(chat_user,u,__U);
            psocket=u->psocket;
        }
        string push_buffer;
        if (!psocket) {//;
            PGLW(chat_user,u,__U);
            u->www_push_buffer+=s;
            return;
        }
        else
        {//;
            PGLR(chat_user,u,__U);
            push_buffer=u->www_push_buffer;

        }
        string ss;
        if (push_buffer.size() )
        {//;
            ss+=push_buffer;
            PGLW(chat_user,u,__U);
            u->www_push_buffer="";
        }
        ss += s;
        {//;
            PGLW(chat_user,u,__U);
            if (u->www_data_send_count > 1000) {
                u->www_data_send_count = 0;
                ss += "<script>document.location.reload();</script>";
            }
            u->www_data_send_count++;
            u->www_last_send_time=time(NULL);
        }
        write_sender_data(psocket,ss);

    }


}




bool can_add_nick(const user_pair &__U)
{
    if (LEVELS(user$level(__U))._max_nicks_count>user$nicks_size(__U)) return true;
    return false;
}

user_pair::user_pair(const PTR_getter<chat_user> &CU): cu(CU),up(NULL),us(NULL)
{//;
    {
        if (!CU) throw cError("if(!CU)");
        PGLR(chat_user, c,CU);
        if (!c->__user_profile) throw cError("!c->__user_profile");
        if (!c->__user_set) throw cError("!c->__user_set");
        up=c->__user_profile;
        us=c->__user_set;
    }

}

www_chat_user$::www_chat_user$():www_unregistered(true),www_offline_status_sent(false),www_inchat(false)
{
    www_last_send_time=time(NULL);
    www_data_send_count=0;
}

chat_user::~chat_user()
{
}

bool user$ignored(const user_pair& __Z,const DB_id& uid)
{
    {
        PGLR(ignore_vec, z,ignore_vecs.find_by_id(user$id(__Z)));
        return z->ignore.count(uid);
    }
}
bool user$erased(const user_pair& __U)
{
    {
        __UC_LOCK;
        return u->erased;
    }
}

void chat_users_container::clean()
{

    vector<DB_id> keys;
    {
        M_LOCK(Mutex);
        for (map<DB_id,PTR_getter<chat_user> > ::iterator i=container.begin();i!=container.end();i++)
        {
            keys.push_back(i->first);
        }
    }
    for (unsigned i=0;i<keys.size();i++)
    {//;
        bool need_clean=false;
        PTR_getter<chat_user> __Z=get(keys[i]);
        DB_id db_id;
        if (__Z)
        {
            PGLR(chat_user, z,__Z);
            db_id=z->db_id;
            if (z->erased)
                need_clean=true;


        }

        if (need_clean) {//;

            user_exit_chat(__Z,false);

            out_oscar_buffer o;
            o<<user_state::PARTALL<<db_id;
            set_user_state(o);

        }

        if (need_clean) {//;

            erase(keys[i]);
            PTR_getter<c_socket> S(NULL);
            {//;
                PGLR(chat_user, z,__Z);
                S=z->psocket;
            }
            {//;
                PGLW(chat_user, z,__Z);
                z->psocket=NULL;
            }

        }
    }
}
void cookie_2_session_id::erase(const string &s)
{
    M_LOCK(Mutex);
    container.erase(s);
}
DB_id cookie_2_session_id::get(const string &s)
{//;
    M_LOCK(Mutex);
    DB_id st;

    map<string,pair<DB_id, time_t> > ::iterator i=container.find(s);
    if (i==container.end()) return st;
    i->second.second=time(NULL);
    return i->second.first;
}
void cookie_2_session_id::set(const string& s,const DB_id& sid)
{//;
    M_LOCK(Mutex);
    container[s]=pair<DB_id, time_t>(sid,time(NULL));

}
void cookie_2_session_id::clean()
{//;
    map<string,pair<DB_id, time_t> > m;
    {
        M_LOCK(Mutex);
        vector<string> rm;
        time_t t=time(NULL);
        for (map<string,pair<DB_id, time_t> >::iterator i=container.begin();i!=container.end();i++)
        {
            if (i->second.second-t>3600) rm.push_back(i->first);
        }
        for (unsigned i=0;i<rm.size();i++)
        {
            container.erase(rm[i]);
        }
        m=container;
    }
}


int user$lpp(const user_pair&__U)
{
    {
        PGLR(user_set, u,__U.us);
        return u->lpp;
    }

}

int user$neye(const user_pair&__U)
{
    {
        PGLR(user_set, u,__U.us);
        return u->neye;
    }

}

int user$vote_balls(const user_pair&__U)
{

    {
        PGLR(user_profile, u,__U.up);
        return u->vote_balls;
    }

}
string user$fname(const user_pair&__U)
{
    {
        PGLR(user_profile, u,__U.up);
        return u->fname;
    }
}
string user$lname(const user_pair&__U)
{
    {
        PGLR(user_profile, u,__U.up);
        return u->lname;
    }
}


void SET_PASS(const user_pair&__U,const string& s)
{
    DB_id id=user$id(__U);
    {
        PGLW(user_profile, u,__U.up);
        u->pass=bin2hex(MD5(s),0);
        send_update_g3(user_profile$pass,id,u->pass);
    }
}
size_t chat_users_container::size()
{

    M_LOCK(Mutex);
    return container.size();
}

vector<PTR_getter<chat_user> > chat_users_container::values()
{

    M_LOCK(Mutex);
    vector<PTR_getter<chat_user> > r;
    for (map<DB_id,PTR_getter<chat_user> > ::iterator i=container.begin();i!=container.end();i++)
    {

        r.push_back(i->second);
    }
    return r;
}
void chat_users_container::insert(const PTR_getter<chat_user> &__UU)
{


    DB_id uid;
    {
        PGLR(chat_user, u,__UU);
        uid=u->db_id;
    }
    {
        M_LOCK(Mutex);
        container.erase(uid);
        container.insert(make_pair(uid,__UU));
    }



}
size_t chat_users_container::count(const DB_id& id)
{

    M_LOCK(Mutex);
    return container.count(id);
}
size_t chat_users_container::count(const PTR_getter<chat_user> &__U)
{
    DB_id s;
    if (!__U) return 0;
    {
        PGLR(chat_user, u,__U);
        s=u->db_id;
    }
    M_LOCK(Mutex);
    return container.count(s);
}

PTR_getter<chat_user> chat_users_container::get_throw(const DB_id& id)
{

    M_LOCK(Mutex);
    if (!container.count(id)) throw cError("!container.count(id)");
    return container.find(id)->second;
}
PTR_getter<chat_user>  chat_users_container::get(const DB_id& id)
{

    M_LOCK(Mutex);
    if (container.find(id)!=container.end())return container.find(id)->second;
    PTR_getter<chat_user> r(NULL);
    return r;
}

void chat_users_container::erase(const DB_id& id)
{//;
    PTR_getter<chat_user> __U(get(id));
    if (__U)
    {

        DB_id dbid;
        {
            PGLR(chat_user,u,__U);
            dbid=u->db_id;
        }
        {
            M_LOCK(Mutex);
            container.erase(dbid);
        }

    }

}



unsigned int user$nicks_size(const user_pair&__U)
{
    {
        PGLR(nick_vec, u,nick_vecs.find_by_id(user$id(__U)));
        return u->u_nicks.size();
    }
}

unsigned int user$nicks_size(unsigned int uid)
{

    PGLR(nick_vec, u,nick_vecs.find_by_id(uid));
    return u->u_nicks.size();
}


user_status get_user_status_by_id(const user_pair&__U, int id)
{

    user_status s;

    {
        PGLW(user_profile, u,__U.up);
        map<unsigned int,user_status>  &st=u->status;
        if (st.count(id))
            return st.find(id)->second;
        throw cError("Error: cannot find status by id "+itostring(id)+" ");
    }
    return s;
}

user_state get_user_state(const user_pair &__U)
{
    {
        PGLR(chat_user, u,__U.cu);
        return u->cstate;
    }
}
bool is_inv(const user_state & s)
{
    if (s.status.id==st_invisible|| s.status.id==st_offinvisible) return true;
    return false;
}
int get_used_space(const user_pair& __U)
{
    int us=0;
    DB_id uid=user$id(__U);
    {
        __NOTE_LOCK(uid);
        for (map<unsigned int,__note_head>::const_iterator i=u->map_msgs.begin();i!=u->map_msgs.end();i++)
        {
            us+=i->second.nfh.content_length;
            us+=i->second.nfh.attachment_content_length;
        }
    }
    {
        PGLR(user_fotos,u,users_fotos.find_by_id(uid));
        us+=u->getsize();
    }
    return us;
}
bool can_write_diskspace(const user_pair& __U, int space)
{

    unsigned int used_space=get_used_space(__U);
    int quota=LEVELS(user$level(__U)).quota;
    {
        PGLR(user_set, u,__U.us);
        quota+=u->bought_quota;
    }
    if (used_space+space<quota) return true;

    return false;

}
DB_id user$id(const PTR_getter<chat_user> &__U)
{
    {
        PGLR(chat_user,u,__U);
        return u->db_id;
    }
    DB_id d;
    return d;
}
