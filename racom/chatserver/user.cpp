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
#include "web_tools.h"
#include "file_set.h"
#include "web_server_data.h"
#include "channels.h"
#include "levels.h"
#include "register.h"
#include "server_config.h"

#include "user_info.h"
//#include "app_con.h"
#include "chat_colors.h"
#include "chat_config.h"
#include "fotos.h"
#include "irc_server_config.h"
#include "oscar_buffer.h"
#include "irc_utils.h"
#include "tcp_sender.h"
#include "update_cmd.h"
#include "levels.h"
#include "CH_id.h"
#include "DB_id.h"
#include "chat_msg.h"
#include "cm_container.h"
#include "chat_thread_event.h"
#include "chat_stuff.h"
#include "ignore_vec.h"
#include "contact_vec.h"
#include "user_stat.h"
#include "chat_globals.h"
db_map<user_stat> user_stats("user_stats",DBMAP_MYSQL,DBMAP_REFID);
db_map<user_profile> user_profiles("user_profiles",DBMAP_MYSQL,DBMAP_REFID);
db_map<user_set> user_sets("user_sets",DBMAP_MYSQL,DBMAP_REFID);

db_map<nick_vec> nick_vecs("nick_vecs",DBMAP_MYSQL,DBMAP_REFID);
db_map<ignore_vec> ignore_vecs("ignore_vecs",DBMAP_MYSQL,DBMAP_REFID);
db_map<contact_vec> contact_vecs("contact_vecs",DBMAP_MYSQL,DBMAP_REFID);

chat_users_container local_users;
#ifndef __CLAN

M_MAP<DB_id,user_state> global_states;
#endif
cookie_2_session_id __cookie_2_session_id;
int do_ipban(const string &ip_orig,const string &proxy_orig,time_t t,const DB_id& id);

string homedir(unsigned int uid);
void get_notes_files(set<string> &files, unsigned int uid);

void get_irc_list(chat_thread_stuff &stuff);
void do_kick(chat_stuff_user &uu,chat_thread_stuff& stuff,const string &msg,set<CH_id>& chans) ;
void send_chnick_msgs(chat_stuff_user &uu,chat_thread_stuff& stuff, const string &from_nick,const string& new_nick, set<CH_id> &chans);
void send_chroom_msgs(chat_stuff_user &uu,chat_thread_stuff& stuff,const string &new_channel_name,const CH_id & chan);
void send_quit_msgs(chat_stuff_user &uu,chat_thread_stuff& stuff,set<CH_id>& quit_msgs_channels);
void send_join_msgs(chat_stuff_user &uu,chat_thread_stuff& stuff,set<CH_id>& join_msgs_channels);
string LK_get_users_count_for_web(chat_thread_stuff& stuff);
void make_url_users_content(chat_thread_stuff &stuff);

static inline int get_flags(chat_stuff_user &zz)
{
    int z=0;

    bool hide_bdate;

    if (zz.level/sub_levels>=am_admin && zz.setting_show_eye) {
        z|=f_admin;
    }
    if (zz.level/sub_levels==am_killer) {
        z|=f_leader;
    }


    time_t t;
    t=time(NULL);

    struct tm q=LOCALTIME(time(NULL));
    {
        int bd=atoi(zz.b_day);
        if (bd!=0 && zz.b_mon!=0 && !zz.hide_bdate) {
            if (q.tm_mday==bd && q.tm_mon+1==zz.b_mon) {
                z|=f_bday;
            }
        }
    }
    return z;
}
static inline string get_remove_string(const string& nick)
{
    string s="<SCRIPT>parent.DeleteUser('";
    s+=nick;
    s+="');</SCRIPT>\r\n";
    return s;
}
static inline string LK_chat_channel_get_n_messages(const CH_id &ch_id, const DB_id &uid,unsigned int n,chat_thread_stuff &stuff)
{
    int nm=0;

    deque<string> out;
    for (deque<PTR_getter_nm<chat_msg> >::reverse_iterator i=stuff.messages.rbegin();i!=stuff.messages.rend();i++)
    {
        string s=i->___ptr->data->make(ch_id,uid);
        if (s.size()) {
            out.push_front(s);
            nm++;
        }
        if (nm>n)break;

    }
    string o;
    for (unsigned i=0;i<out.size();i++)
        o+=out[i];
    return o;
}

static inline string get_add_string(const CH_id& channel,chat_stuff_user &uu,chat_stuff_user &zz,chat_thread_stuff& stuff)
{
    string s;


    s="<SCRIPT>parent.AddUser({n:'"+zz.cstate.nick.name+"',";
    s+="nu:'"+str_nick(nick_for_sort(zz.cstate.nick.name))+"',";
    s+="ipn:"+itostring(zz.cstate.status.pic)+",";
    s+="sd:'"+ES(zz.cstate.status.name)+"',";
    s+="id:"+itostring(zz.dbid.container)+",";
    s+="c:'"+zz.nickstyle+"',";
    s+="v:"+itostring(zz.cstate.voice.count(channel))+",";
    s+="l:"+itostring(zz.level/sub_levels)+",";
    if (zz.level/sub_levels>=am_admin) {
        s+="ap:"+itostring(zz.neye)+",";
    }
    s+="g:"+itostring(zz.gender)+",";
    s+="ign:"+itostring(uu.ignores.count(zz.dbid)!=0)+",";


    s+="f:"+itostring(get_flags(zz))+"});</SCRIPT>\r\n";

    return s;
}
static inline string LK_get_java_users(const CH_id& channel, chat_stuff_user &__u,chat_thread_stuff& stuff)
{

    map<CH_id,c_set> ::iterator it=stuff.channels.find(channel);
    if (it==stuff.channels.end())return "";

    c_set &cs=it->second;

    map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > >::iterator it2=cs.u_list.find(__u.dbid);
    if (it2==cs.u_list.end()) return "";

    map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > &cl=it2/*cs.u_list.find(__u.dbid)*/->second.second;
    vector<string> v;
    for ( map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> >::iterator i=cl.begin();i!=cl.end();i++)
    {
        chat_stuff_user &zz=i->second.___ptr->ud;
        string ret;
        ret+="{n:'"+zz.cstate.nick.name+"',"
             "nu:'"+str_nick(nick_for_sort(zz.cstate.nick.name))+"',"
             "ipn:"+itostring(zz.cstate.status.pic) + ","
             "sd:'" + ES(zz.cstate.status.name) + "',"
             "id:" + itostring(zz.dbid.container) + ","
             "l:" + itostring(zz.level/sub_levels) + ",";
        if (zz.level/sub_levels>=am_admin) {
            ret+="ap:"+itostring(zz.neye)+",";
        }
        ret+="g:"+itostring(zz.gender)+",";
        ret+="c:'"+zz.nickstyle+"',";
        ret+="v:"+itostring(zz.cstate.voice.count(channel))+",";
        ret+="ign:"+itostring(__u.ignores.count(i->first)!=0)+",";
        ret+="f:"+itostring(get_flags(zz))+"}";
        v.push_back(ret);
    }
    str_sort(v);
    string res=join(", ",v);
    return res;
}

static inline bool is_inv(const chat_stuff_user& __u)
{
    if (__u.cstate.status.id==st_invisible || __u.cstate.status.id==st_offinvisible ) return true;
    return false;
}
static inline void data_push_back(const DB_id& uid,chat_thread_stuff &stuff, const string& msg)
{
    PTR_getter<chat_user> __U=local_users.get(uid);
    if (__U)
        data_push_back(__U,msg);
}

static inline void preload_user(const DB_id& uid, chat_thread_stuff& stuff)
{
    if (uid.container==0) throw cError("--Error: preload user 0");

    chat_stuff_user_p *pu=new chat_stuff_user_p;
    chat_stuff_user &uu=pu->ud;

    uu.dbid=uid;
    {
        PGLR(contact_vec,c,contact_vecs.find_by_id(uid));
        uu.contacts=c->contact;

    }
    {
        PGLR(ignore_vec,c,ignore_vecs.find_by_id(uid));
        uu.ignores=c->ignore;
    }
    {
        PGLR(user_profile,u,user_profiles.find_by_id(uid));

        uu.gender=u->get_gender();
        uu.level=u->level;
        uu.city=u->city;
        uu.b_day=u->b_day;
        uu.b_mon=u->b_mon;
        uu.login=u->login;
        uu.db_privileges=u->db_privileges;

        const map<unsigned int,user_status> &st=u->status;
        if (st.count(st_online))
            uu.cstate.status=st.find(st_online)->second;

    }
    uu.clevel=LEVELS(uu.level);
    uu.privileges=uu.clevel.privileges| uu.db_privileges;
    {
        PGLR(user_set,u,user_sets.find_by_id(uid));
        uu.contact_options=u->contact_options;
        uu.setting_show_eye=u->setting_show_eye;
        uu.neye=u->neye;
        uu.lpp=u->lpp;
        uu.hide_bdate=u->hide_bdate;
        uu.n_color_pack=u->n_color_pack;
        uu.invisibility=u->bought_invisibility+uu.clevel.invisibility;
        uu.bought_invisibility=u->bought_invisibility;
        uu.cstate.nick.id=u->last_nick_id;
        uu.cstate.nick.name=u->last_nick;
        uu.ul_mode_contacts_only=u->ul_mode_contacts_only;
        uu.ul_mode_hide_male=u->ul_mode_hide_male;
        uu.ul_mode_hide_female=u->ul_mode_hide_female;

    }
    PTR_getter<c_pack> cp=c_packs.get(uu.n_color_pack);
    {
        PGLR(c_pack, c,cp);
        uu.nickstyle=c->nickstyle;
    }
    PTR_getter<chat_stuff_user_p> ppp(pu);
    stuff.users.insert(make_pair(uid,pu));
    PGLR(nick_vec,u,nick_vecs.find_by_id(uid));
    for (map<unsigned int,user_nick> ::const_iterator i=u->u_nicks.begin();i!=u->u_nicks.end();i++)
    {
        string sn=str_nick(i->second.name);
        stuff.strnick2__u.insert(make_pair(sn,pu));
        uu.str_nicks[i->first]=sn;
    }
    if (u->u_nicks.size())
    {
        map<unsigned int,user_nick> ::const_iterator it=u->u_nicks.find(uu.cstate.nick.id);


        if (it==u->u_nicks.end())
            uu.cstate.nick=u->u_nicks.begin()->second;
        else  uu.cstate.nick=it->second;
    }

    uu.last_m_time=0;
    uu.last_invite_time=0;
    uu.msg_cnt_per_time=0;
    uu.user_type=TYPE_UNKNOWN;

}
void unload_user(const DB_id &uid,chat_thread_stuff& stuff)
{
    map<DB_id,PTR_getter_nm<chat_stuff_user_p> > ::iterator it=stuff.users.find(uid);
    if (it==stuff.users.end()) return;
    chat_stuff_user &__uu=it->second.___ptr->ud;
    for (map<unsigned int,string>::iterator i=__uu.str_nicks.begin();i!=__uu.str_nicks.end();i++)
    {
        stuff.strnick2__u.erase(i->second);
    }
    stuff.users.erase(uid);
    for (map<CH_id,c_set> ::iterator i=stuff.channels.begin();i!=stuff.channels.end();i++)
    {
        i->second.u_list.erase(uid);
    }
}

void send_chat_msg(chat_msg$ *e,chat_thread_stuff& stuff)
{
    PTR_getter_nm<chat_msg> m(new chat_msg(e));
    stuff.messages.push_back(m);
    stuff.backup_messages.push_back(m);
}

static inline void rebuild_me(const user_state& oldstate, const user_state &state, bool &need_send_rc,chat_thread_stuff& stuff,DB_id &u_dbid, const PTR_getter_nm<chat_stuff_user_p>&__uu, chat_stuff_user& __u, const PTR_getter<chat_user>&__UU)
{

    for (set<CH_id>::const_iterator _ch=oldstate.channel.begin();_ch!=oldstate.channel.end();_ch++)
    {

        if (!state.channel.count(*_ch))
        {
            c_set &c=stuff.channels[*_ch];
            c.u_list.erase(u_dbid);
            need_send_rc=true;
        }
    }
    for (set<CH_id>::const_iterator  _ch=state.channel.begin();_ch!=state.channel.end();_ch++)
    {
        CH_id ch;
        ch=*_ch;
        c_set &c=stuff.channels[ch];
        if (!c.u_list.count(u_dbid))
        {
            map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> >  __m;
            __m.insert(make_pair(u_dbid,__uu));
            c.u_list.insert(make_pair(u_dbid,make_pair(__uu,__m)));

            map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> >  &ucit=c.u_list.find(u_dbid)->second.second;
            need_send_rc=true;
            for (map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > > ::iterator i=c.u_list.begin();i!=c.u_list.end();i++)
            {
                chat_stuff_user &__z=i->second.first.___ptr->ud;
                bool i_can_see=__u.I_can_see(__z);

                if (i_can_see)
                {
                    ucit.insert(make_pair(i->first,i->second.first));
                }
            }
            if (__u.user_type==TYPE_WWW && __UU)
            {
                string out="<SCRIPT>parent.UpdateUsers(["+LK_get_java_users(*_ch,__u,stuff)+"]);</SCRIPT>";
                data_push_back(__UU, out);
            }
            else if (__u.user_type==TYPE_IRC && __UU)
            {
                string s=":"+state.nick.name+"!"+state.nick.name+"@"+__u.ip+" JOIN :#"+c.cd.irc_name+"\r\n";
                data_push_back(__UU,s);

                if (c.cd.topic.size()) irc_send_reply(__UU,332,"#"+c.cd.irc_name,c.cd.topic);
                s=":"+string(irc_server_config.host)+" 333 "+state.nick.name+" #"+c.cd.irc_name+" "+c.cd.set_by+" "+itostring(c.cd.topic_time)+"\r\n";
                data_push_back(__UU,s);
                map<int, vector<string> > nks;
                int idx=0;
                for (map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> >  ::iterator i=ucit.begin();i!=ucit.end();i++)
                {
                    idx++;
                    nks[idx/20].push_back(i->second.___ptr->ud.cstate.nick.name);
                }
                for (map<int, vector<string> >::iterator i=nks.begin();i!=nks.end();i++)
                {
                    irc_send_reply(__UU,353,"= #"+c.cd.irc_name,join(" ",i->second));
                }
                irc_send_reply(__UU,366,"#"+c.cd.irc_name,"End of NAMES list.");
            }
        }
        else
        {
            map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> >  &ucit=c.u_list.find(u_dbid)->second.second;
            for (map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > > ::iterator i=c.u_list.begin();i!=c.u_list.end();i++)
            {
                chat_stuff_user &__z=i->second.first.___ptr->ud;
                bool i_can_see=__u.I_can_see(__z);
                bool in_list=ucit.count(i->first);
                if (!in_list && i_can_see)
                {
                    if (__u.user_type==TYPE_WWW && __UU)
                    {
                        string out=get_add_string(*_ch,__u,__z,stuff);
                        data_push_back(__UU, out);
                    }
                    else if (__u.user_type==TYPE_IRC && __UU)
                    {
                        string dt_join=":"+__z.cstate.nick.name+"!"+__z.cstate.nick.name+"@"+string(irc_server_config.host)+" JOIN #"+c.cd.irc_name+"\r\n";
                        if (__z.setting_show_eye && __z.level/sub_levels>=am_admin)
                        {
                            string mo=":System!System@"+string(irc_server_config.host)+" MODE #"+c.cd.irc_name+" +o "+__z.cstate.nick.name+"\r\n";
                            dt_join+=mo;
                        }
                        data_push_back(__UU,dt_join);

                    }
                    ucit.insert(make_pair(i->first,i->second.first));

                }
                else if (in_list && !i_can_see)
                {
                    if (__u.user_type==TYPE_WWW && __UU)
                    {
                        string out=get_remove_string(__z.cstate.nick.name);
                        data_push_back(__UU, out);
                    }
                    else if (__u.user_type==TYPE_IRC && __UU)
                    {
                        string out=":"+__z.cstate.nick.name+"!"+__z.cstate.nick.name+"@"+string(irc_server_config.host)+" PART #"+ c.cd.irc_name +" :\r\n";
                        data_push_back(__UU, out);
                    }
                    ucit.erase(i->first);

                }
            }
        }
    }
}
void do_set_user_state(const string &msg,chat_thread_stuff& stuff)
{
    try {
        oscar_buffer o(msg.data(),msg.size());
        int cmd;
        o>>cmd;
        DB_id u_dbid;
        o>>u_dbid;

        if (u_dbid.container==0)throw cError("--Error: do_set_user_state uid 0");

        if (!stuff.users.count(u_dbid)) preload_user(u_dbid, stuff);
        PTR_getter_nm<chat_stuff_user_p> &__uu=stuff.users.find(u_dbid)->second;
        chat_stuff_user &__u=__uu.___ptr->ud;
        user_state oldstate=__u.cstate;
        user_state newstate=oldstate;
        string kick_msg;
        bool CL_mode_changed=false;
        switch (cmd)
        {
        case user_state::PARTALL:
            newstate.channel.clear();
            break;
        case user_state::RECALC:
            break;
        case user_state::CHANGE_CONTACT_MODE:
        {
            unsigned char c;
            o>>c;
            if (c=='C')  o>>__u.ul_mode_contacts_only;
            else if (c=='F')  o>>__u.ul_mode_hide_female;
            else if (c=='M')  o>>__u.ul_mode_hide_male;
            CL_mode_changed=true;
        }
        break;
        case user_state::SET_NICK:
            o>>newstate.nick;
            stuff.trash.erase(u_dbid);
            break;
        case user_state::KICK:
            o>>kick_msg;
            newstate.channel.clear();
            break;
#ifdef __CLAN
        case user_state::SET_BIN_STATE2:
            stuff.trash.erase(u_dbid);
            o>>newstate;
            break;
#endif
        case user_state::SET_BIN_STATE:
            stuff.trash.erase(u_dbid);
            o>>newstate;
            break;
        case user_state::SET_STATUS:
            stuff.trash.erase(u_dbid);
            o>>newstate.status;
            break;
        case user_state::CHANGE_CHANNEL:
            stuff.trash.erase(u_dbid);

            {
                CH_id c;
                o>>c;
                newstate.channel.clear();
                newstate.channel.insert(c);
            }
            break;
        case user_state::PART:
        {
            CH_id c;
            o>>c;
            newstate.channel.erase(c);
        }
        break;
        case user_state::JOIN:
            stuff.trash.erase(u_dbid);
            {
                CH_id c;
                o>>c;
                newstate.channel.insert(c);
            }
            break;
        case user_state::CONTACT_ADD:
            stuff.trash.erase(u_dbid);
            {
                DB_id zid;
                o>>zid;
                __u.contacts.insert(zid);
            }
            break;
        case user_state::CONTACT_REMOVE:
            stuff.trash.erase(u_dbid);
            {
                DB_id zid;
                o>>zid;
                __u.contacts.erase(zid);

            }

            break;
        }
        const user_state &state=newstate;
#ifndef __CLAN
        global_states.set(u_dbid,newstate);
        if (newstate.channel.size()==0 && newstate.voice.size()==0) global_states.erase_key(u_dbid);
#endif
        if (state.channel.size() && !stuff.join_time.count(u_dbid))
        {
            stuff.join_time[u_dbid]=time(NULL);
        }
        if (state.channel.size()==0 && stuff.join_time.count(u_dbid))
        {
            //if(local_users.get(u_dbid))
#ifndef __CLAN
            send_update_g3(user_stat$add_t_count,u_dbid,time(NULL)-stuff.join_time[u_dbid]);
#endif
            stuff.join_time.erase(u_dbid);
        }
        PTR_getter<chat_user> __UU=local_users.get(u_dbid);
        if (__UU)
        {
            PGLW(chat_user,u,__UU);
            u->cstate=state;
        }

        __u.cstate=state;

        if (cmd==user_state::KICK)
        {
            do_kick(__u,stuff,kick_msg,oldstate.channel);
            unload_user(u_dbid,stuff);
            return;
        }

        bool old_inv=oldstate.status.id==st_invisible || oldstate.status.id==st_offinvisible;
        bool new_inv=state.status.id==st_invisible || state.status.id==st_offinvisible;

        // channels to send chnick message
        if (!old_inv && !new_inv && state.channel==oldstate.channel && state.nick.id!=oldstate.nick.id)
        {

            string from_nick=oldstate.nick.name;
            string  new_nick=state.nick.name;
            send_chnick_msgs(__u,stuff,from_nick,new_nick,oldstate.channel);
            return;
        }


        map<CH_id,set<DB_id> > added_me_now;

        // PRINT MESSAGES IN CHANNELS
        set<CH_id> join_msgs_channels;
        set<CH_id> quit_msgs_channels;

        set<CH_id> chroom_msgs_channels;


        set<CH_id> clean_channels;



        // CHROOM MSG
        if (state.channel.size()==1 && oldstate.channel.size()==1 && state.channel!=oldstate.channel && !old_inv && ! new_inv)
        {

            CH_id from=*oldstate.channel.begin();
            CH_id to=*state.channel.begin();
            string to_name=stuff.channels[to].cd.name();
            send_chroom_msgs(__u,stuff,to_name,from);
            chroom_msgs_channels.insert(from); // do not send QUIT to channel if chroom chan exists
            join_msgs_channels.insert(to);

        }



        //JOIN & QUIT MSGS CHANNELS IF VIS INVIS
        if (old_inv && !new_inv) 	join_msgs_channels=oldstate.channel;
        if ((!old_inv && new_inv) && oldstate.channel.size()) 	quit_msgs_channels=state.channel;


        // JOIN & QUIT MSGS IF CHANNEL CHANGE
        if (state.channel.size()!=oldstate.channel.size() && !old_inv && !new_inv)
        {


            for (set<CH_id>::const_iterator i=state.channel.begin();i!=state.channel.end();i++)
            {
                if (!oldstate.channel.count(*i))
                {
                    if (!old_inv && !new_inv)
                        join_msgs_channels.insert(*i);
                }
            }

            for (set<CH_id>::iterator i=oldstate.channel.begin();i!=oldstate.channel.end();i++)
            {
                if (!state.channel.count(*i))
                {
                    if (!old_inv && !new_inv && !chroom_msgs_channels.count(*i))
                        quit_msgs_channels.insert(*i);
                }
            }

        }


        // joins
        send_join_msgs(__u,stuff,join_msgs_channels);
        // quits
        /*	if(u_dbid.container==26)
        	{
        	    logErr2("send_quit_msgs(__u,stuff,quit_msgs_channels); cmd=%d",cmd);
        	}*/
        send_quit_msgs(__u,stuff,quit_msgs_channels);


        set<CH_id> all_chans;
        for (set<CH_id>::iterator  i=oldstate.channel.begin();i!=oldstate.channel.end();i++)
            all_chans.insert(*i);
        for (set<CH_id>::const_iterator  i=state.channel.begin();i!=state.channel.end();i++)
            all_chans.insert(*i);


        {
            string remove_string=get_remove_string(__u.cstate.nick.name);
            for (set<CH_id>::iterator ch=all_chans.begin();ch!=all_chans.end();ch++)
            {
                c_set &c=stuff.channels[*ch];

                string dt_part;
                if (state.channel.size())
                {
                    dt_part=":"+oldstate.nick.name+"!"+oldstate.nick.name+"@"+string(irc_server_config.host)+" PART #"+ c.cd.irc_name +" :\r\n";
                }
                else
                {
                    dt_part=":"+oldstate.nick.name+"!"+oldstate.nick.name+"@"+string(irc_server_config.host)+" QUIT :\r\n";
                }
                string dt_join=":"+state.nick.name+"!"+state.nick.name+"@"+string(irc_server_config.host)+" JOIN #"+c.cd.irc_name+"\r\n";
                if (__u.setting_show_eye && __u.level/sub_levels>=am_admin)
                {
                    string mo=":System!System@"+string(irc_server_config.host)+" MODE #"+c.cd.irc_name+" +o "+state.nick.name+"\r\n";
                    dt_join+=mo;
                }

                bool leave=oldstate.channel.count(*ch) && !state.channel.count(*ch);
                bool join=!oldstate.channel.count(*ch) && state.channel.count(*ch);
                {


                    for (map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > > ::iterator i=c.u_list.begin();i!=c.u_list.end();i++)
                    {

                        bool need_part=false;
                        bool need_join=false;
                        bool second_count_uid=i->second.second.count(__u.dbid);
                        if (leave && second_count_uid) need_part=true;
                        if (!leave)
                        {
                            bool i_can_see=i->second.first.___ptr->ud.I_can_see(__u);
                            if (i_can_see && !second_count_uid) need_join=true;
                            if (!i_can_see && second_count_uid) need_part=true;

                        }
                        if (need_part)
                        {
                            i->second.second.erase(__u.dbid);

                            chat_stuff_user &z=i->second.first.___ptr->ud;
                            PTR_getter<chat_user> __Z=local_users.get(z.dbid);
                            if (__Z)
                            {
                                if (z.user_type==TYPE_WWW)
                                {
                                    data_push_back(__Z,remove_string);
                                }
                                else if (z.user_type==TYPE_IRC)
                                {
                                    data_push_back(__Z,dt_part);
                                }
                            }
                        }
                        if (need_join)
                        {
                            i->second.second.insert(make_pair(__u.dbid,__uu));

                            chat_stuff_user  &z=i->second.first.___ptr->ud;

                            PTR_getter<chat_user> __Z=local_users.get(z.dbid);
                            if (__Z)
                            {
                                if (z.user_type==TYPE_WWW)
                                {
                                    string s=get_add_string(*ch,z,__u,stuff);
                                    data_push_back(__Z,s);
                                }
                                else if (z.user_type==TYPE_IRC)
                                {
                                    data_push_back(__Z,dt_join);

                                }
                            }
                        }
                    }
                }
            }
        }

        if (oldstate.status.id!=state.status.id && oldstate.channel==state.channel)
        {
            string status_string="<SCRIPT>parent.ChangeStatus("+itostring(u_dbid.container)+","+itostring(state.status.pic)+",'"+ES(state.status.name)+"');</SCRIPT>\r\n";
            for (set<CH_id>::const_iterator _ch=state.channel.begin();_ch!=state.channel.end();_ch++)
            {
                CH_id ch;
                ch=*_ch;
                c_set &c=stuff.channels[ch];

                for (map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > > ::iterator i=c.u_list.begin();i!=c.u_list.end();i++)
                {
                    if (i->second.second.count(u_dbid))
                    {
                        chat_stuff_user &z=i->second.first.___ptr->ud;

                        PTR_getter<chat_user> __Z=local_users.get(z.dbid);
                        if (__Z)
                        {
                            if (z.user_type==TYPE_WWW)
                            {
                                data_push_back(__Z,status_string);
                            }
                        }
                    }
                }

            }
        }
        // rebuild me
        bool need_send_rc=false;
        rebuild_me(oldstate, state, need_send_rc,stuff,u_dbid, __uu,  __u, __UU);
        //    .....................

        if (need_send_rc)
        {
            string rc=LK_get_users_count_for_web(stuff);
            for (map<CH_id,c_set> ::iterator ch=stuff.channels.begin();ch!=stuff.channels.end();ch++)
            {
                c_set &c=ch->second;
                for (map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > > ::iterator i=c.u_list.begin();i!=c.u_list.end();i++)
                {
                    chat_stuff_user &z=i->second.first.___ptr->ud;
                    PTR_getter<chat_user> __Z=local_users.get(z.dbid);
                    if (__Z)
                    {
                        if (z.user_type==TYPE_WWW)
                            data_push_back(__Z,rc);
                    }

                }
            }
        }
        if (oldstate.channel!=state.channel || old_inv!=new_inv)
        {
            make_url_users_content(stuff);
            get_irc_list(stuff);
        }
        if (state.channel.size()==0)
        {
            stuff.trash[u_dbid]=time(NULL);
        }
    } catch (cError e) {
        logErr2("catched %s (%s %d)",e.what(),__FILE__,__LINE__);
    } catch (...) {
        logErr2("ctched %s %d",__FILE__,__LINE__);
    }

}
void on_SET_USER_STATE(chat_event_SET_USER_STATE* e, chat_thread_stuff& stuff)
{
    do_set_user_state(e->msg,stuff);
}


void broadcast_chat_event(chat_event*e);



void on_CHAT_MESSAGES(chat_event_CHAT_MESSAGES*e,chat_thread_stuff &stuff)
{

    DB_id uid=e->uid;
    if (uid.container==0)throw cError("--Error: on_CHAT_MESSAGES uid 0"); ;
    map<string,string> m;
    bool moderated;
    string out;

    if (!stuff.users.count(uid)) preload_user(uid,stuff);
    chat_stuff_user &__u=stuff.users.find(uid)->second.___ptr->ud;

    set<CH_id> uchan=__u.cstate.channel;
    vector<CH_id> chs=chat_channels.keys();
    if (e->c!="") {
        int c;
        c=atoi(e->c);
        if (c>=chs.size() || c<0) {
            c=0;
        }

        if (!uchan.count(chs[c])) {

            out_oscar_buffer o;
            o<<user_state::CHANGE_CHANNEL<<e->uid<<chs[c];
            do_set_user_state(o.as_string(),stuff);
            __u.cstate.channel.clear();
            __u.cstate.channel.insert(chs[c]);
            chat_event_SET_USER_STATE ee;
            ee.msg=o.as_string();
            broadcast_chat_event(&ee);


            uchan=__u.cstate.channel;
            send_update_g3(user_set$last_channel,uid,chs[c].container);
        }
    }
    if (!uchan.size()) throw cError("!uchan.suze()");
    {
        __CH_LOCK(chat_channels[*uchan.begin()]);
        moderated=CH->cd.moderated;
        if (CH->cd.topic.size()) {
            m["~top~"]="";
            m["~etop~"]="";

            string tp=CH->cd.topic;
            m["~topic~"]=tp;
            m["~topic2~"]=tp;
            m["~who~"]=CH->cd.set_by;
            m["~time~"]=datetime2rus(CH->cd.topic_time);
        } else {
            m["~top~"]="<!--";
            m["~etop~"]="-->";
            m["~topic~"]="";
            m["~topic2~"]="";
            m["~who~"]="";
            m["~time~"]="";
        }
    }
    out="\r\n\r\n"+RVfiles(m,"chat/messages");
    if (uid.container /* && !is_unreg_id(uid)*/)

        out+="<SCRIPT>parent.ChangeStatus("+itostring(__u.dbid.container)+","+itostring(__u.cstate.status.pic)+",'"+ES(__u.cstate.status.name)+"');</SCRIPT>\r\n";

    int cidx=0;
    for (int i=0;i<chs.size();i++)
    {
        if (chs[i]==*uchan.begin()) cidx=i;
    }
    out+="<script>parent.chc("+itostring(cidx)+");</script>\n";
    out+=LK_chat_channel_get_n_messages(*uchan.begin(),uid,__u.lpp,stuff);
    out+=SCROLL;
    string LK="<SCRIPT>parent.UpdateUsers(["+LK_get_java_users(*uchan.begin(),__u,stuff)+"]);</SCRIPT>\n";
    out+=LK;
    out+="<script>parent.need_update=true; setTimeout('parent.OnTimerUpdate()',1000);</script>\n";
    out+=LK_get_users_count_for_web(stuff);
    out+="<script>parent.moderated="+itostring(moderated)
         +"; if(window.top.addmessage && window.top.addmessage.document && window.top.addmessage.document.StatusForm && window.top.addmessage.document.StatusForm.moderated) window.top.addmessage.document.StatusForm.moderated.checked="
         +itostring(moderated)+"; parent.set_topic(parent.topic); </script>\n";

    PTR_getter<chat_user> __U=local_users.get(e->uid);
    if (__U)
    {
        data_push_back(__U,out);
        {
            PGLW(chat_user,u,__U);
            u->www_offline_status_sent=false;
            u->www_inchat=true;
            u->www_offline_time=0;

        }
    }

}
void on_INVITE(chat_event_INVITE *e,chat_thread_stuff &stuff)
{
    map<string,string> m;
    if (e->zid.container==0 ||e->uid.container==0) throw cError("--Error: on_INVITE uid zid 0"); ;
    if (!stuff.users.count(e->zid)) preload_user(e->zid,stuff);
    if (!stuff.users.count(e->uid)) preload_user(e->uid,stuff);

    chat_stuff_user &__z=stuff.users.find(e->zid)->second.___ptr->ud;
    chat_stuff_user &__u=stuff.users.find(e->uid)->second.___ptr->ud;

    string data;

    string msg=e->msg;
    if (msg.size()>1024) msg=msg.substr(0,1024);
    {
        if (__z.user_type==TYPE_WWW) {
            if (!(__u.privileges&u_allow_tags)) msg=remove_tags(msg);
            msg=replace_links(msg);
        }
    }
    bool may_invite=true;
    bool timeok=true;
    if (__z.ignores.count(e->uid)) {
        may_invite=false;
    }
    if (time(NULL)-__z.last_invite_time<30) timeok=false;
    __z.last_invite_time=time(NULL);
    if (__z.user_type==TYPE_IRC) timeok=true;

    if (may_invite) {
        if (__z.cstate.status.disable_invite || !timeok) {
            if (msg.size()) {
                if (__z.user_type==TYPE_WWW) {

                    chat_msg_PRIV *cm=new chat_msg_PRIV;
                    cm->to_id=e->zid;
                    cm->from_id=e->uid;
                    cm->from_nick=__u.cstate.nick.name;
                    cm->to_nick=__z.cstate.nick.name;;
                    cm->msg=msg;
                    cm->n_color_pack=__u.n_color_pack;
                    CH_id cch;
                    if (__z.cstate.channel.size()) cch=*__z.cstate.channel.begin();
                    cm->channel=cch;
                    PTR_getter<chat_user> __ZZ=local_users.get(e->zid);
                    if (__ZZ)
                    {
                        data_push_back(__ZZ,cm->make(cch,e->zid));
                    }
                    send_chat_msg(cm,stuff);

                }
            }
            string mmsg;
            if (!timeok) {
                mmsg=_MSG("cantinvitewaitplz");
            } else {
                char ss[200];
                snprintf(ss,sizeof(ss)-1,_MSG("invitedisabled").c_str(),__z.cstate.nick.name.c_str());
                mmsg=ss;
            }
            PTR_getter<chat_user> __UU=local_users.get(e->uid);
            if (__UU)
            {

                send_syspriv_msg(__UU,mmsg);
            }

        }
        else {
            msg=str_replace("\'", "\\\'", msg);


            if (__z.user_type==TYPE_WWW) {
                PTR_getter<chat_user> __ZZ=local_users.get(e->zid);
                if (__ZZ)
                {
                    string str="<SCRIPT>parent.DoInvite('"+itostring(e->uid.container)+"','"+__u.cstate.nick.name+"','"+__z.cstate.nick.name+"','"+msg+"','"+strtime(time(NULL))+"'); </SCRIPT>";
                    data_push_back(__ZZ,str);
                }
            } else if (__z.user_type==TYPE_IRC) {
                PTR_getter<chat_user> __ZZ=local_users.get(e->zid);
                if (__ZZ)
                {

                    if (msg.size()) {
                        irc_send_notice(__ZZ,"Invites you: "+msg,__u.cstate.nick.name);
                    } else {
                        irc_send_notice(__ZZ,"Invites you!",__u.cstate.nick.name);
                    }
                }
            }


        }
    }


    if (data.size()) {
        PTR_getter<chat_user>__UU=local_users.get(e->uid);
        if (__UU)
            data_push_back(__UU,data);
    }

}

void kick_user(const PTR_getter<chat_user> &__UU,const string &msgs);
bool user_process_send_message_to_channel(const DB_id &uid, const CH_id& chan,const string &__ms,const string& tonick, bool makeit,bool usersys, chat_thread_stuff &stuff);
bool user_process_send_message_priv(const PTR_getter<chat_user>& __UU, const PTR_getter<chat_user>&__ZZ, string ms, string tonick, bool usersys, chat_thread_stuff &stuff);

bool user_process_send_message_priv(const DB_id &uid, const DB_id & zid, string ms, string tonick, bool usersys, chat_thread_stuff &stuff)
{
    if (zid.container==0 ||uid.container==0) throw cError("--Error: user_process_send_message_priv uid 0 || zid 0");

    char cc02[3] = {0x02,0x02,0x02};
    char cc1f[3] = {0x1f,0x1f,0x1f};
    string ms2=ms;
    if (!stuff.users.count(zid)) preload_user(zid,stuff);
    if (!stuff.users.count(uid)) preload_user(uid,stuff);

    chat_stuff_user &__z=stuff.users.find(zid)->second.___ptr->ud;
    chat_stuff_user &__u=stuff.users.find(uid)->second.___ptr->ud;

    if (__u.contact_options & user_set::CONTACT_ADD_OUT_PRIV)
    {
        if (!__u.contacts.count(zid))
        {
#ifndef __CLAN
            send_update_g3(contact$add,uid,zid.container);
#endif
            __u.contacts.insert(zid);
            out_oscar_buffer o;
            o<<user_state::RECALC<<__u.dbid;
            set_user_state(o);
        }
    }
    if (__z.contact_options & user_set::CONTACT_ADD_IN_PRIV)
    {
        if (!__z.contacts.count(uid))
        {
#ifndef __CLAN
            send_update_g3(contact$add,zid,uid.container);
#endif
            __z.contacts.insert(uid);
            out_oscar_buffer o;
            o<<user_state::RECALC<<__z.dbid;
            set_user_state(o);
        }
    }
    if (__u.cstate.channel.size()==0) return false; // !inchat

    if (ms.size()>__u.clevel.max_msg_len)return false;
    if (remove_spaces(ms) == "") return false;
    char c160 = 0xa0;
    if (ms.find(c160, 0) != -1) return false;

    string c02=string(cc02,1);
    string c1f=string(cc1f,1);

    if (__u.level/sub_levels < am_admin) usersys = false;

    if (ms == strupper(ms)) ms = strlower(ms);

    if (!(__u.privileges&u_allow_tags))    ms = remove_tags(ms);


    if (__u.level/sub_levels >= am_admin) {
        ms = str_replace("&lt;br&gt;", "<br>", ms);
        ms = str_replace("&lt;BR&gt;", "<BR>", ms);
        ms = str_replace("&lt;/br&gt;", "</br>", ms);
        ms = str_replace("&lt;/BR&gt;", "</BR>", ms);
        ms = str_replace("&lt;u&gt;", "<u>", ms);
        ms = str_replace("&lt;/u&gt;", "</u>", ms);
    }
    if (__u.level/sub_levels >= 3) {
        ms = str_replace("&lt;i&gt;", "<i>", ms);
        ms = str_replace("&lt;/i&gt;", "</i>", ms);
        ms = str_replace("&lt;I&gt;", "<i>", ms);
        ms = str_replace("&lt;/I&gt;", "</i>", ms);
    }
    {
        ms2=str_replace("<u>",c1f,ms2);
        ms2=str_replace("</u>",c1f,ms2);
        ms2=str_replace("<b>",c02,ms2);
        ms2=str_replace("</b>",c02,ms2);
    }
    ms = replace_links(ms);

    {

        if (time(NULL)-__u.last_m_time>1 && uid != zid/* && uid.container<UNREG_BASE*/)
        {
            //	    if(local_users.get(uid))
#ifndef __CLAN
            send_update_g2(user_stat$inc_m_count,uid);
#endif
        }
        __u.last_m_time = time(NULL);
    }
    if (__u.clevel.replacements.size())
    {
        ms = replace_re_vals(__u.clevel.replacements, ms);
    }

    if (usersys)
    {
        chat_msg_SYSPRIV *e=new chat_msg_SYSPRIV;
        try {
            e->from_id=uid;
            e->to_id= zid;
            e->to_nick=__z.cstate.nick.name;
            e->msg=ms;

            CH_id ch;

            if (__u.user_type==TYPE_WWW)
            {
                if (__u.cstate.channel.size()) ch=*__u.cstate.channel.begin();
            }
            else if (__z.user_type==TYPE_WWW)
            {
                if (__z.cstate.channel.size()) ch=*__z.cstate.channel.begin();
            }
            e->channel=ch;

            PTR_getter<chat_user> __U=local_users.get(uid);
            if (__U)
            {
                if (__u.user_type==TYPE_WWW) data_push_back(__U,e->make(ch,e->from_id)+SCROLL);
                else if (__u.user_type==TYPE_IRC)  irc_send_notice(__U,ms2,"System");
            }
            PTR_getter<chat_user> __Z=local_users.get(zid);
            if (__Z)
            {
                if (__z.user_type==TYPE_WWW) data_push_back(__Z,e->make(ch,e->to_id)+SCROLL);
                else if (__z.user_type==TYPE_IRC) irc_send_notice(__Z,ms2,"System");
            }
        }
        catch (cError e)
        {
            logErr2("catched %s %s %d",e.what(),__FILE__,__LINE__);
        }
        catch (...)
        {
            logErr2("catched %s %d",__FILE__,__LINE__);
        }
        send_chat_msg(e,stuff);
    }
    else
    {
        chat_msg_PRIV *e=new chat_msg_PRIV;
        try {
            e->from_id=uid;
            e->to_id= zid;
            e->from_nick=__u.cstate.nick.name;
            e->to_nick=__z.cstate.nick.name;
            e->msg=ms;
            e->n_color_pack=__u.n_color_pack;

            CH_id ch;
            if (__u.user_type==TYPE_WWW)
            {
                if (__u.cstate.channel.size()) ch=*__u.cstate.channel.begin();
            }
            else if (__z.user_type==TYPE_WWW)
            {
                if (__z.cstate.channel.size()) ch=*__z.cstate.channel.begin();
            }
            e->channel=ch;
            {
                PTR_getter<chat_user> __U=local_users.get(uid);
                if (__U)
                {
                    if (__u.user_type==TYPE_WWW) data_push_back(__U,e->make(ch,e->from_id)+SCROLL);
                }
            }
            {
                PTR_getter<chat_user> __Z=local_users.get(zid);
                {
                    if (!__z.ignores.count(uid) &&__Z)
                    {
                        if (__z.user_type==TYPE_WWW) data_push_back(__Z,e->make(ch,e->to_id)+SCROLL);
                        else irc_send_private_message(__Z,ms2,e->from_nick);

                    }
                }
            }
        }
        catch (cError e)
        {
            logErr2("catched %s %s %d",e.what(),__FILE__,__LINE__);
        }
        catch (...)
        {
            logErr2("catched %s %d",__FILE__,__LINE__);
        }
        send_chat_msg(e,stuff);
    }
    return true;

}
void push_back_channel_msg(chat_msg$* e,const CH_id& ch,const DB_id& from_id,const DB_id &to_id,chat_thread_stuff& stuff,const string& ircd,const string& ircdto)
{
    c_set &st=stuff.channels[ch];
    for (map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > > ::iterator i=st.u_list.begin();i!=st.u_list.end();i++)
    {

        chat_stuff_user &z=i->second.first.___ptr->ud;

        if (z.user_type==TYPE_WWW)
        {
            string ms=e->make(ch,i->first);
            ms+=SCROLL;
            PTR_getter<chat_user> _u=local_users.get(z.dbid);
            if (_u)data_push_back(_u,ms);
        }
        else if (z.user_type==TYPE_IRC)
        {
            if (i->first==from_id) continue;
            PTR_getter<chat_user> _u=local_users.get(z.dbid);
            if (to_id==i->first)
            {
                if (_u)data_push_back(_u,ircdto);
            }
            else
                if (_u)data_push_back(_u,ircd);

        }
    }

}

bool user_process_send_message_to_channel(const DB_id &uid, /*const PTR_getter<chat_channel> &__ML*/ const CH_id& __channel,const string &__ms,
        const string& tonick, bool makeit,bool usersys, chat_thread_stuff &stuff)
{
    string ms=__ms;
    CH_id channel=__channel;

    string nmsg = ms;
    string ms2;

    if (uid.container==0) throw cError("--Error: user_process_send_message_to_channel uid 0");
    if (!stuff.users.count(uid)) preload_user(uid,stuff);
    chat_stuff_user &__u=stuff.users.find(uid)->second.___ptr->ud;

    if (!stuff.channels.count(channel)) return false;

    char c160 = 0xa0;

    char cc02[3] = {0x02,0x02,0x02};
    char cc1f[3] = {0x1f,0x1f,0x1f};
    string c02;
    c02.assign(cc02,1);
    string c1f;
    c1f.assign(cc1f,1);
    bool _is_inv=is_inv(__u);
    if (__u.last_message==ms) return false;
    __u.last_message=ms;

    bool u_inchat=__u.cstate.channel.size();
    if (!u_inchat || remove_spaces(ms) == "" || ms.size() > __u.clevel.max_msg_len)
    {
        return false;
    }

    if (__u.level/sub_levels < am_admin) {
        usersys = false;
    }
    if (ms == strupper(ms))
        ms = strlower(ms);
    if (!makeit && !usersys && strupper(tonick) != stuff.to_all && tonick != "") {
        ms = tonick + ", " + ms;
    }
    ms2 = ms;
    if (!(__u.privileges&u_allow_tags)) {
        ms = remove_tags(ms);


    }
    if (__u.level/sub_levels >= am_admin) {
        ms = str_replace("&lt;br&gt;", "<br>", ms);
        ms = str_replace("&lt;BR&gt;", "<BR>", ms);
        ms = str_replace("&lt;/br&gt;", "</br>", ms);
        ms = str_replace("&lt;/BR&gt;", "</BR>", ms);
        ms = str_replace("&lt;u&gt;", "<u>", ms);
        ms = str_replace("&lt;/u&gt;", "</u>", ms);
    }
    if (__u.level/sub_levels >= 3) {
        ms = str_replace("&lt;i&gt;", "<i>", ms);
        ms = str_replace("&lt;/i&gt;", "</i>", ms);
        ms = str_replace("&lt;I&gt;", "<i>", ms);
        ms = str_replace("&lt;/I&gt;", "</i>", ms);
    }
    {
        ms2=str_replace("<u>",c1f,ms2);
        ms2=str_replace("</u>",c1f,ms2);
        ms2=str_replace("<b>",c02,ms2);
        ms2=str_replace("</b>",c02,ms2);
    }
    ms = replace_links(ms);
    c_set &__c=stuff.channels[channel];
    int voice=__u.cstate.voice.count(channel);

    if (__u.clevel.replacements.size())
    {
        ms = replace_re_vals(__u.clevel.replacements, ms);
    }

    {
        //check message for maty
        if (__c.cd.moderated && !voice) {
            PTR_getter<chat_user> __UU=local_users.get(uid);
            if (__UU)
            {

                send_syspriv_msg(__UU,_MSG("cantsendtochannel"));
            }
            return false;
        }
        if (__u.level<__c.cd.write_level)
        {
            PTR_getter<chat_user> __UU=local_users.get(uid);
            if (__UU)
            {

                send_syspriv_msg(__UU,_MSG("cantsendtochannelrdonly"));
            }
            return false;
        }

        if (__c.cd.censored) {
            if (!check_maty(ms))
            {
                if (__c.cd.move) {
                    channel.container=__c.cd.move_to_channel;
                    data_push_back(uid,stuff,"<script>parent.chc(" +
                                   itostring(__c.cd.move_to_channel) +
                                   "); window.top.messages.location='messages?r=" +
                                   itostring(rand()) + "';</script>");
                    if (__u.user_type==TYPE_WWW)
                    {

                        out_oscar_buffer o;
                        o<<user_state::CHANGE_CHANNEL<<__u.dbid<<__c.cd.move_to_channel;
                        set_user_state(o);
                    }

                }
                else {

                    chat_msg_MAT *e=new chat_msg_MAT;
                    try {
                        e->channel=channel;
                        e->gender=__u.gender;
                        e->nick=__u.cstate.nick.name;
                        e->n_index=msgs_maty.get_random_n(e->gender);
                        string s=msgs_maty.get(e->gender,e->n_index);
                        char ss[300];
                        snprintf(ss, sizeof(ss) - 1, s.c_str(), e->nick.c_str());
                        DB_id to_id;//empty
                        DB_id from_id;//empty
                        string ircd=s_irc_send_system_message_to_channel(ss,"#"+__c.cd.irc_name);
                        push_back_channel_msg(e,e->channel,from_id,to_id,stuff,ircd,"");

                    }
                    catch (cError e)
                    {
                        logErr2("catched %s %s %d",e.what(),__FILE__,__LINE__);
                    }
                    catch (...)
                    {
                        logErr2("catched %s %d",__FILE__,__LINE__);
                    }
                    {
                        send_chat_msg(e,stuff);
                    }
                    return false;
                }

            }
        }
        if ((_is_inv)  && !usersys) {

            PTR_getter<chat_user> __UU=local_users.get(uid);
            if (__UU)
            {

                send_syspriv_msg(__UU,_MSG("ininvisibleandcantwrite"));
            }
            return false;
        }

        if (makeit)
        {
            chat_msg_MAKEIT *e= new chat_msg_MAKEIT;
            try {
                e->from_id=uid;
                e->channel=channel;
                e->from_nick=__u.cstate.nick.name;
                e->msg=ms;
                e->n_color_pack=__u.n_color_pack;
                DB_id to_id;//empty
                string ircd=s_irc_send_action_to_channel(ms2,e->from_nick,"#"+__c.cd.irc_name);
                push_back_channel_msg(e,e->channel,e->from_id,to_id,stuff,ircd,"");
            }
            catch (...)
            {
                logErr2("catched %s %d",__FILE__,__LINE__);

            }
            send_chat_msg(e,stuff);
        }
        else if (usersys)
        {
            chat_msg_SYS *e=new chat_msg_SYS;
            try
            {
                e->from_id=uid;
                e->channel=channel;
                e->msg=ms;
                string ircd=s_irc_send_system_message_to_channel(ms2,"#"+__c.cd.irc_name);
                DB_id to_id;//empty
                push_back_channel_msg(e,e->channel,e->from_id,to_id,stuff,ircd,"");

            }
            catch (...)
            {
                logErr2("catched %s %d",__FILE__,__LINE__);

            }

            send_chat_msg(e,stuff);
        }
        else
        {
            chat_msg_STDTO *e =new chat_msg_STDTO;
            try {
                e->from_id=uid;
                e->from_nick=__u.cstate.nick.name;
                e->channel=channel;
                e->n_color_pack=__u.n_color_pack;
                e->msg=ms;
                char cc2=2;
                DB_id zid;
                string stonick = str_nick(tonick);
                if (stuff.strnick2__u.count(stonick))
                    zid = stuff.strnick2__u.find(stonick)->second.___ptr->ud.dbid;
                e->to_id=zid;


                string ircd=	s_irc_send_message_to_channel(ms2,e->from_nick,"#"+__c.cd.irc_name);
                string ircdto=	s_irc_send_message_to_channel(cc2+ms2+cc2,e->from_nick,"#"+__c.cd.irc_name);
                push_back_channel_msg(e,e->channel,e->from_id,e->to_id,stuff,ircd,ircdto);
            }
            catch (...)
            {
                logErr2("catched %s %d",__FILE__,__LINE__);
            }
            send_chat_msg(e,stuff);
        }
        bool decr = false;


        if (time(NULL)-__u.last_m_time>1 && !decr && !__c.cd.no_statistic)
        {
#ifndef __CLAN
            send_update_g2(user_stat$inc_m_count,uid);
#endif

        }
        __u.last_m_time=time(NULL);
    }
    return true;
}


void on_SEND_MESSAGE(chat_event_SEND_MESSAGE *e,chat_thread_stuff &stuff)
{
    DB_id uid=e->from_uid;
    if (uid.container==0)throw cError("on_SEND_MESSAGE uid 0 || zid 0");;

    if (!stuff.users.count(uid)) preload_user(uid,stuff);
    chat_stuff_user&__u=stuff.users.find(uid)->second.___ptr->ud;

    __u.user_type=e->user_type;
#ifndef __CLAN
    if (__u.level/sub_levels<am_admin)
    {// check for flood
        if (__u.last_m_time==time(NULL)) {//;
            __u.msg_cnt_per_time++;
            if (__u.msg_cnt_per_time>MAX_MSG_PER_SEC && !(__u.privileges&u_allow_tags)) {
                int r=do_ipban(__u.ip,__u.pip,600,uid);

                kick_user(e->from_uid,"");

                logErr2("User %s (%s) was kicked by System(antiflood protection)",__u.cstate.nick.name.c_str(),__u.login.c_str());
                return;
            }
        }
        else {
            __u.msg_cnt_per_time=0;
        }

    }
#endif

    if (e->priv)
    {
        map<string, PTR_getter_nm<chat_stuff_user_p> >::iterator it=stuff.strnick2__u.find(str_nick(e->tonick));
        if (it==stuff.strnick2__u.end())
        {
            PTR_getter<chat_user> __U=local_users.get(e->from_uid);
            if (__U)
            {

                send_syspriv_msg(__U,_MSG("receiver_not_found"));
            }
        }
        else
        {
            user_process_send_message_priv(e->from_uid,it->second.___ptr->ud.dbid,e->msg,e->tonick,e->sys,stuff);
        }
    }
    else
    {
        if (__u.cstate.channel.size())
        {
            if (e->user_type==TYPE_WWW)
                user_process_send_message_to_channel(e->from_uid,*__u.cstate.channel.begin(),e->msg,e->tonick,e->makeit,e->sys,stuff);
            else if (e->user_type==TYPE_IRC)
                user_process_send_message_to_channel(e->from_uid,e->channel,e->msg,e->tonick,e->makeit,e->sys,stuff);
        }

    }

}
m_var<map<string,pair<int,string> > > get_irc_list_container;
void get_irc_list(chat_thread_stuff &stuff)
{
    map<string,pair<int,string> > r;


    for (map<CH_id,c_set> ::iterator i=stuff.channels.begin();i!=stuff.channels.end();i++)
    {
        if (r.count(i->second.cd.irc_name)) r["#"+i->second.cd.irc_name].first+=i->second.u_list.size();
        else r["#"+i->second.cd.irc_name].first=i->second.u_list.size();
        r["#"+i->second.cd.irc_name].second=i->second.cd.topic;
    }

    get_irc_list_container=r;
}

void on_CHMODE(chat_event_CHMODE *e,chat_thread_stuff &stuff)
{
    if (e->uid.container==0) throw cError("on_CHMODE uid 0 || zid 0");
    chat_msg_MODE *m=new chat_msg_MODE;
    m->nick1=e->nick;
    m->channel=e->channel;
    m->from_id=e->uid;

    if (!stuff.users.count(e->uid)) preload_user(e->uid,stuff);
    chat_stuff_user &__u=stuff.users.find(e->uid)->second.___ptr->ud;



    c_set &c=stuff.channels[m->channel];
    if (e->mode==-1)
    {
        if (c.cd.moderated)
        {
            m->msg="-m";
            c.cd.moderated=false;
        }
        else
        {
            m->msg="+m";
            c.cd.moderated=true;
        }
    }
    else
    {
        if (e->mode)
        {
            m->msg="+m";
            c.cd.moderated=true;
        }
        else
        {
            m->msg="-m";
            c.cd.moderated=false;
        }
    }
    string cmm;
    if (c.cd.moderated) cmm="1";
    else cmm="0";

    {
        __CH_LOCKW(chat_channels[m->channel]);
        CH->cd.moderated=c.cd.moderated;
    }
    m->n_index=rand()%msgs_modechanges.size();;


    m->gender=__u.gender;
    string ircd=":"+e->nick+"!"+e->nick+"@"+string(irc_server_config.host)+" MODE #"+c.cd.irc_name+" "+m->msg+"\r\n";
    for (map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > >::iterator i=c.u_list.begin();i!=c.u_list.end();i++)
    {
        chat_stuff_user &z=i->second.first.___ptr->ud;

        PTR_getter<chat_user> __Z=local_users.get(i->first);
        if (__Z)
        {
            if (z.user_type==TYPE_WWW)
            {
                string s=m->make(e->channel,i->first);
                s+="<script>if(window.top.addmessage.document.StatusForm.moderated) window.top.addmessage.document.StatusForm.moderated.checked="+cmm+"; parent.moderated="+cmm+"; parent.set_topic(parent.topic);</script>";
                s+=SCROLL;
                data_push_back(__Z,s);
            }
            else if (z.user_type==TYPE_IRC)
            {
                data_push_back(__Z,ircd);
            }
        }
    }
    send_chat_msg(m);

}
void on_CHVOICE(chat_event_CHVOICE *e,chat_thread_stuff &stuff)
{
    if (e->uid.container==0) throw cError("on_CHVOICE uid 0");

    if (!stuff.users.count(e->uid))  preload_user(e->uid,stuff);
    chat_stuff_user &__u=stuff.users.find(e->uid)->second.___ptr->ud;


    if (__u.level/sub_levels<am_admin) {

        PTR_getter<chat_user> __U=local_users.get(e->uid);
        if (__U)
        {

            send_syspriv_msg(__U,_MSG("lowlevel"));
        }
        return;
    }

    if (!stuff.channels.count(e->channel))
    {
        return;
    }
    else
    {
        if (!stuff.channels[e->channel].cd.extended)
        {
            PTR_getter<chat_user> __U=local_users.get(e->uid);
            if (__U)
            {

                send_syspriv_msg(__U,_MSG("cantvoice"));
            }
            return;
        }
    }

    map<string, PTR_getter_nm<chat_stuff_user_p> > ::iterator it=stuff.strnick2__u.find(str_nick(e->nick));
    if (it==stuff.strnick2__u.end())
    {
        PTR_getter<chat_user> __U=local_users.get(e->uid);
        if (__U)
        {

            send_syspriv_msg(__U,_MSG("nicknotfound"));
        }
        return;
    }

    chat_stuff_user &__z=it->second.___ptr->ud;




    chat_msg_MODE *m=new chat_msg_MODE;
    {
        m->nick1=__u.cstate.nick.name;
    }
    {
        m->nick2=__z.cstate.nick.name;
    }
    m->channel=e->channel;
    m->from_id=e->uid;
    {
        m->n_index=rand()%msgs_modechanges.size();;
    }
    m->gender=__u.gender;

    if (e->voice==-1) {
        if (__z.cstate.voice.count(e->channel)) {
            __z.cstate.voice.erase(e->channel);
#ifndef __CLAN
            global_states.set(e->uid,__z.cstate);
#endif
            m->msg="-v";
        }
        else {
            __z.cstate.voice.insert(e->channel);
#ifndef __CLAN
            global_states.set(e->uid,__z.cstate);
#endif
            m->msg="+v";
        }

    } else {
        if (e->voice)
        {
            __z.cstate.voice.insert(e->channel);
#ifndef __CLAN
            global_states.set(e->uid,__z.cstate);
#endif
            m->msg="+v";

        }
        else {
            __z.cstate.voice.erase(e->channel);;
#ifndef __CLAN
            global_states.set(e->uid,__z.cstate);
#endif
            m->msg="-v";
        }
    }

    c_set &c=stuff.channels[e->channel];
    string ircd=(string)":"+__u.cstate.nick.name+"!"+__u.cstate.nick.name+"@"+string(irc_server_config.host)+" MODE #"+c.cd.irc_name+" "+m->msg+" "+m->nick2+"\r\n";
    for (map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > > ::iterator i=c.u_list.begin();i!=c.u_list.end();i++)
    {
        chat_stuff_user &z=i->second.first.___ptr->ud;
        PTR_getter<chat_user> __Z=local_users.get(z.dbid);
        if (__Z)
        {
            if (z.user_type==TYPE_WWW)
            {
                string s=m->make(e->channel,i->first);


                s+=SCROLL;
                string rs=get_remove_string(__z.cstate.nick.name)+get_add_string(e->channel,z,__z,stuff);
                s+=rs;
                data_push_back(__Z,s);
            }
            else if (z.user_type==TYPE_IRC)
            {
                data_push_back(__Z,ircd);
            }
        }
    }
    send_chat_msg(m);
}

void on_CHTOPIC(chat_event_CHTOPIC *e,chat_thread_stuff &stuff)
{
    if (e->uid.container==0) throw cError("on_CHTOPIC uid 0 ");

    if (!stuff.users.count(e->uid))  preload_user(e->uid,stuff);
    chat_stuff_user &__u=stuff.users.find(e->uid)->second.___ptr->ud;
    string cnick=__u.cstate.nick.name;
    string ircd=":"+cnick+"!"+cnick+"@"+string(irc_server_config.host)+" TOPIC #"+stuff.channels[e->channel].cd.irc_name+" :"+e->top+"\r\n";
    string webd="<script>parent.set_topic('"+e->top+"');</script>";
    c_set &c=stuff.channels[e->channel];
    chat_msg_CHTOPIC *m=new chat_msg_CHTOPIC;
    m->channel=e->channel;
    m->gender=__u.gender;
    m->n_index=rand()%msgs_topicchanges.size();
    m->nick=__u.cstate.nick.name;
    m->topic=e->top;
    for (map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > > ::iterator i=c.u_list.begin();i!=c.u_list.end();i++)
    {
        chat_stuff_user &__z=i->second.first.___ptr->ud;
        PTR_getter<chat_user> __Z=local_users.get(__z.dbid);
        if (__Z)
        {
            if (__z.user_type==TYPE_WWW)
            {
                string s=m->make(e->channel,i->first);
                s+=SCROLL;
                s+=webd;
                data_push_back(__Z,s);
            }
            else if (__z.user_type==TYPE_IRC)
            {
                data_push_back(__Z,ircd);
            }
        }
    }
    send_chat_msg(m);

}


void on_SEND_DATA_TO_WWW_USERS(chat_event_SEND_DATA_TO_WWW_USERS*e,chat_thread_stuff &stuff)
{
    for (map<CH_id,c_set> ::iterator i=stuff.channels.begin();i!=stuff.channels.end();i++)
    {
        for (map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > > ::iterator j=i->second.u_list.begin();j!=i->second.u_list.end();j++)
        {
            chat_stuff_user &__z=j->second.first.___ptr->ud;
            PTR_getter<chat_user> __Z=local_users.get(__z.dbid);
            if (__Z)
            {
                if (__z.user_type==TYPE_WWW)
                {
                    data_push_back(__Z,e->msg);
                }
            }

        }

    }

}

void on_UPDATE_USER_SESSION(chat_event_UPDATE_USER_SESSION *e,chat_thread_stuff &stuff)
{
    if (e->uid.container==0) throw cError("--Error: on_UPDATE_USER_SESSION uid 0");
    if (!stuff.users.count(e->uid)) preload_user(e->uid,stuff);
    chat_stuff_user &__u=stuff.users.find(e->uid)->second.___ptr->ud;
    __u.user_type=e->user_type;
    __u.ip=e->ip;
    __u.pip=e->pip;
}
void on_IGNORE(chat_event_IGNORE *e,chat_thread_stuff &stuff)
{
    if (e->uid.container==0) throw cError("--Error: on_IGNORE uid 0");
    if (!stuff.users.count(e->uid)) preload_user(e->uid,stuff);
    if (!stuff.users.count(e->zid))
        if (!stuff.users.count(e->zid)) preload_user(e->zid,stuff);

    chat_stuff_user &__u=stuff.users.find(e->uid)->second.___ptr->ud;
    chat_stuff_user &__z=stuff.users.find(e->zid)->second.___ptr->ud;



    if (__u.ignores.count(e->zid))
    {
        __u.ignores.erase(e->zid);
    }
    else
    {
        __u.ignores.insert(e->zid);
    }
}
void send_chnick_msgs(chat_stuff_user &__u,chat_thread_stuff& stuff, const string &from_nick,const string& new_nick, set<CH_id> &chans)
{
    string ircd=":"+from_nick+"!"+from_nick+"@"+string(irc_server_config.host)+" NICK :"+new_nick+"\r\n";
    string remove_string=get_remove_string(from_nick);
    for (set<CH_id>::iterator _ch=chans.begin();_ch!=chans.end();_ch++)
    {
        chat_msg_CHNICK *e=new chat_msg_CHNICK;

        e->channel=*_ch;
        e->gender=__u.gender;
        e->n_index=rand()%msgs_nickchanges.size();
        e->oldnick=from_nick;
        e->newnick=new_nick;
        c_set &c=stuff.channels[*_ch];
        for (map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > > ::iterator i=c.u_list.begin();i!=c.u_list.end();i++)
        {
            chat_stuff_user &__z=i->second.first.___ptr->ud;
            string rs=remove_string+get_add_string(*_ch,__z,__u,stuff);
            PTR_getter<chat_user> __Z=local_users.get(__z.dbid);
            if (__Z)
            {
                if (__z.user_type==TYPE_WWW)
                {
                    string s=e->make(*_ch,i->first);
                    s+=SCROLL;
                    data_push_back(__Z,s);
                }
                if (i->second.second.count(__u.dbid))
                {
                    if (__z.user_type==TYPE_WWW)
                    {
                        data_push_back(__Z,rs);
                    }
                    else if (__z.user_type==TYPE_IRC)
                    {
                        data_push_back(__Z,ircd);

                    }
                }

            }
        }

    }

}
void do_kick(chat_stuff_user &__u,chat_thread_stuff& stuff,const string &msg,set<CH_id>& chans)
{
    //    PTR_getter<chat_user> __U=local_users.get(__u.dbid);
    //    if(!__U) return;
    for (set<CH_id>::iterator _ch=chans.begin();_ch!=chans.end();_ch++)
    {
        stuff.channels[*_ch].u_list.erase(__u.dbid);
    }
    string rc=LK_get_users_count_for_web(stuff);
    string remove_string=get_remove_string(__u.cstate.nick.name)+rc;
    for (set<CH_id>::iterator _ch=chans.begin();_ch!=chans.end();_ch++)
    {
        c_set &c=stuff.channels[*_ch];
        string dt_part=":System!system@"+string(irc_server_config.host)+" KICK #"+c.cd.irc_name+" "+__u.cstate.nick.name+" :"+msg+"\r\n"; //KALLLLL
        chat_msg_KICK *eq=new chat_msg_KICK;
        eq->channel=*_ch;
        eq->gender=__u.gender;
        eq->nick=__u.cstate.nick.name;
        eq->zamsg=msg;
        eq->n_index=rand()%msgs_kicking.size();
        for (map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > > ::iterator i=c.u_list.begin();i!=c.u_list.end();i++)
        {
            chat_stuff_user &__z=i->second.first.___ptr->ud;
            {
                PTR_getter<chat_user> __Z=local_users.get(__z.dbid);

                if (__Z)
                {
                    if (__z.user_type==TYPE_WWW)
                    {
                        string s=eq->make(*_ch,i->first);
                        s+=SCROLL;
                        data_push_back(__Z,s);
                    }
                    if (i->second.second.count(__u.dbid))
                    {
                        if (__z.user_type==TYPE_WWW)
                        {
                            data_push_back(__Z,remove_string);
                        }
                        else if (__z.user_type==TYPE_IRC)
                        {
                            data_push_back(__Z,dt_part);

                        }
                        i->second.second.erase(__u.dbid);
                    }

                }
            }
        }
        c.u_list.erase(__u.dbid);

        send_chat_msg(eq,stuff);
    }
    PTR_getter<chat_user> __U=local_users.get(__u.dbid);
    if (__U) {
        if (__u.user_type==TYPE_WWW) {
            map<string,string> m;
            if (msg.size()) {
                m["~msg~"]=msg;
                data_push_back(__U,RVfiles(m,"kick_user_for"));
            } else {
                data_push_back(__U,RVfiles(m,"kick_user"));
            }
        }

        {
            PGLW(chat_user,u,__U);
            u->erased=true;
        }
    }

}
bool u_has_console(const user_pair& __U)
{
    unsigned int c_priv=u_allow_view_logs | u_is_settings_admin | u_is_funny_admin | u_is_vote_admin | u_is_privs_admin | u_is_accounts_admin | u_is_hints_admin | u_is_news_admin |  u_is_advertizer_admin;
    unsigned int level;
    {
        PGLR(user_profile,u,__U.up);
        if (u->db_privileges&c_priv) return true;
        level=u->level;

    }
    c_level lv=LEVELS(level);
    if (lv.privileges&c_priv) return true;
    if (lv.levelup_ability) return true;
    if (lv.leveldown_ability) return true;

    return false;
}

#include "RTYPES_CLAN.h"
#ifndef __CLAN
#endif

void send_packet_to_cs(bool immed,CLAN_MSG,const out_oscar_buffer & b);
void broadcast_user_logged_in(const DB_id&uid)
{
    out_oscar_buffer bbb;
    bbb<<uid;
#ifdef __CLAN
    send_packet_to_cs(true,__TYPE_NOTIFY_USER_LOGGED_IN,bbb);
#else
#endif
}
void broadcast_user_logged_out(const DB_id& uid)
{

}
static M_MAP<string,DB_id> all_user_nick_2_id;
DB_id  all_user_nick_2_DB_id(const string & nick)
{
    string s_nick=str_nick(nick);
    if (all_user_nick_2_id.count(s_nick))
    {
        DB_id sess=all_user_nick_2_id[s_nick];
        return sess;
    }
    DB_id a;
    return a;

}
void user_unregister_1_nick(const string & nick, bool broadcast)
{
    string strn=str_nick(nick);
    all_user_nick_2_id.erase_key(strn);
    if (broadcast)
    {

        out_oscar_buffer bbb;
        bbb<<nick;
#ifdef __CLAN
#else
#endif

    }


}
void user_register_all_nicks(const DB_id& id, bool broadcast)
{

    map<unsigned int,user_nick> n;

    {
        PGLR(nick_vec, u,nick_vecs.find_by_id(id));
        n=u->u_nicks;

    }

    for (map<unsigned int,user_nick>::iterator i=n.begin();i!=n.end();i++) {
        string strn=str_nick(i->second.name);
        all_user_nick_2_id.set(strn,id);
    }
    if (broadcast)
    {

#ifdef __CLAN
#else
#endif

    }
}

void user_unregister_all_nicks(const DB_id& id, bool broadcast)
{

    map<unsigned int,user_nick> n;
    {
        PGLR(nick_vec, u,nick_vecs.find_by_id(id));
        n=u->u_nicks;
    }

    for (map<unsigned int,user_nick>::iterator i=n.begin();i!=n.end();i++) {
        string strn=str_nick(i->second.name);
        all_user_nick_2_id.erase_key(strn);
    }

}

bool I_can_see(const PTR_getter<chat_user>__U,const PTR_getter<chat_user>__Z)
{
    DB_id uid=user$id(__U);
    DB_id zid=user$id(__Z);
    if (uid==zid) return true;
    bool i_can_see=true;
    int uinvisibility;
    unsigned int ulevel;
    int zinvisibility;
    unsigned int zlevel;
    {
        PGLR(user_profile,u,user_profiles.find_by_id(uid))
        ulevel=u->level;
    }
    {
        PGLR(user_profile,z,user_profiles.find_by_id(zid));
        zlevel=z->level;
    }
    uinvisibility=LEVELS(ulevel).invisibility;
    zinvisibility=LEVELS(zlevel).invisibility;
    {
        PGLR(user_set,u,user_sets.find_by_id(uid));
        uinvisibility+=u->bought_invisibility;
    }
    {
        PGLR(user_set,z,user_sets.find_by_id(zid));
        zinvisibility+=z->bought_invisibility;
    }
    user_state ustate,zstate;
    {
        PGLR(chat_user,u,__U);
        ustate=u->cstate;
    }
    {
        PGLR(chat_user,z,__Z);
        zstate=z->cstate;
    }

    if (zstate.status.id==st_offinvisible ||zstate.status.id==st_invisible)
    {
        if (zinvisibility>uinvisibility) return false;
    }
    return true;
}
