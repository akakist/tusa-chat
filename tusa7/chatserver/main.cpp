#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include <sys/stat.h>
#include <map>

#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include "message.h"
#include "app_con.h"
#include "chat_def.h"
#include "file_set.h"
#include "web_server_data.h"
#include "web_tools.h"

#include "chat_funny.h"
#include "channels.h"
#include "levels.h"
#include "server_config.h"
#include "app_def.h"
#include "chat_colors.h"
#include "chat_config.h"
#include "register.h"
#include "irc_server_config.h"

#include "update_cmd.h"
#include "oscar_buffer.h"
#include "CH_id.h"
#include "DB_id.h"
#include "chat_thread_event.h"
#include "user_credits.h"
#include "cs_conn_data.h"
#include "chat_globals.h"
#include "ignore_vec.h"

string as_string(const hstring& h,  web_connection * cc);

void url_change_nick(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void url_invite_user(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void url_ignore_user(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void url_kick_user(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void url_change_mode(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void url_change_voice(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void url_user_info(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void url_chat(const PTR_getter<chat_user>&__U, cs_conn_data*);		// /chat
void url_chat_enter(const PTR_getter<chat_user>&__U, cs_conn_data*);		// /chat/enter
void url_chat_exit(const PTR_getter<chat_user>&__U, cs_conn_data*);		// /chat/enter
void url_chat_users(cs_conn_data*);		// /chat/users
void url_chat_buttons(const PTR_getter<chat_user>&__U, cs_conn_data*);	// /chat/buttons
void url_chat_messages(const PTR_getter<chat_user>&__U, cs_conn_data*);	// /chat/messages
void url_chat_addmessage(const PTR_getter<chat_user>&__U, cs_conn_data*);	// /chat/add_message
void url_chat_status(const PTR_getter<chat_user>&__U, cs_conn_data*);		// /chat/status
void url_chat_sendmessage(const PTR_getter<chat_user>&__U, cs_conn_data*);	// /chat/send_message
void url_chat_command(const PTR_getter<chat_user>&__U, cs_conn_data*);	// /chat/command
void url_chat_topic(const PTR_getter<chat_user> &__UU,cs_conn_data *cc);
void reload(const PTR_getter<nick_vec> &N);


hstring get_news_for_index(cs_conn_data * cc);
void url_index(const PTR_getter<chat_user>&__UU, cs_conn_data * cc)
{
    bool need_reload_statuses = false;
//    logErr2("url_index");

    if (cc->params["s"] == "1") {

        logErr2("--Info: Set home page from %s", cc->peer_ipaddress.c_str());
    }
    map<string, hstring > m;
    m["~news~"] = get_news_for_index(cc) ;//news;
    m["~login~"] = cc->params["login"];
    cc->html_out = make_pair(m,"index");
}

void url_relogin(cs_conn_data *cc)
{
    map<string,hstring> m;
    m["~login~"]=cc->params["login"];
    cc->html_out+=make_pair(m,"relogin");
}




void url_st_pic(cs_conn_data *cc)
{
    map<string,hstring> m;
    m["~imgn~"]=cc->params["n"];
    cc->html_out=make_pair(m,"st_pics");
}

void url_picz(cs_conn_data *cc)
{
    map<string,hstring> m;
    string u="/pics/"+cc->url.substr(6,cc->url.size()-6);
    m["~img~"]=u;
    m["~descr~"]=cc->params["d"];
    cc->html_out=make_pair(m,"picz");
}

void url_chat_users(cs_conn_data *cc)
{
    cc->html_out=global_config.files_get("chat/users");
}

void url_logout(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    bool ok=false;
    if (__UU) {
        user_pair __U(__UU);
        user_destroy(__UU);
        map<string,hstring> op;

        unsigned int spent=user$get_spent_time(__U);

        logErr2("%s logout. [%s - %s] {%d}",string(user$login(__U)).c_str(),cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str(),spent);

        op["~name~"]=get_full_name(__U);

        cc->user_id.container=0;
        cc->cookies["cid"]="0";
        cc->html_out=make_pair(op,"logout");
        ok=true;
    }
    if (!ok) {
        url_index(__UU,cc);
        return;
    }
}




void url_chat_buttons(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    if (!__UU)
        return;
    if (!inchat$(__UU))
        return;
    user_pair __U(__UU);
    map<string,hstring> m;
    map<string,string> c;
    string rm;
    vector<CH_id>chs=chat_channels.keys();
    for (unsigned int i=0;i<chs.size();i++) {
        __CH_LOCK(chat_channels[chs[i]]);
        c[itostring(i)]=CH->cd.name()+" (  )";
        rm+="rooms["+itostring(i)+"]=\""+CH->cd.name()+"\";\r\n";
    }
    m["~rooms~"]=rm;
    m["~level~"]=LEVEL_NAME(user$level(__U),user$gender(__U));
    m["~nick~"]=build_nicks_select(__U,"nick",GET_CNICK_ID(__U)," onchange='ch_nick();' class=bsel");

    CH_id lchan;
    {
        PGLR(user_set, u,__U.us);
        lchan.container=u->last_channel;
    }
    int chidx=0;
    for (int i=0;i<chs.size();i++)
    {
        if (chs[i]==lchan) chidx=i;
    }
    m["~channel~"]=make_select("channel",c,itostring(chidx)," onchange='ch_room();' class=bsel");
    if (chs.size()==1) {
        m["~schannel~"]="<!--";
        m["~eschannel~"]="-->";
    } else {
        m["~schannel~"]="";
        m["~eschannel~"]="";
    }
    if (user$level(__U)/sub_levels>=am_killer ||  u_has_console(__U)) {
        m["~adm~"]="";
        m["~eadm~"]="";
    } else {
        m["~adm~"]="<!--";
        m["~eadm~"]="-->";
        m["panel_adm.gif"]="panel.gif";
    }
    if (chat_config.use_advert_in_chat) {
        cc->html_out=make_pair(m,"chat/buttonsframe_adv");
    } else {
        cc->html_out=make_pair(m,"chat/buttonsframe");
    }
}



void url_chat_exit(const PTR_getter<chat_user> &__U,cs_conn_data *cc)
{
    if (!__U) {
        return;
    }
    if (inchat$(__U)) {
        user_pair __UU(__U);
        out_oscar_buffer o;
        o<<user_state::PARTALL<<user$id(__UU);
        set_user_state(o);
        user_exit_chat(__U,false);
    }
    if (cc->user_unregistered) {
        cc->redirect("/logout");
    } else {
        cc->redirect("/login");
    }
}




void url_change_contact_mode(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    user_pair __U(__UU);
    bool is_on;
    {
        PGLW(user_set,u,__U.us);
        u->ul_mode_contacts_only=!u->ul_mode_contacts_only;
        is_on=u->ul_mode_contacts_only;
    }
    out_oscar_buffer o;
    o<<user_state::CHANGE_CONTACT_MODE<<user$id(__U)<<'C'<<is_on;
    set_user_state(o);
    send_update_g3(user_set$ul_mode_contacts_only,user$id(__U),is_on);

    if (is_on)
    {
        send_syspriv_msg(__U,_MSG("contact_mode_enabled"));
        data_push_back(__U,"<SCRIPT>parent.set_state_contact_mode(1);</SCRIPT>\n");

    }
    else
    {
        send_syspriv_msg(__U,_MSG("contact_mode_disabled"));
        data_push_back(__U,"<SCRIPT>parent.set_state_contact_mode(0);</SCRIPT>\n");
    }

    cc->html_out="POSRALL";
}

void url_change_female_mode(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    user_pair __U(__UU);
    bool is_on;
    {
        PGLW(user_set,u,__U.us);
        u->ul_mode_hide_female=!u->ul_mode_hide_female;
        is_on=u->ul_mode_hide_female;
    }
    out_oscar_buffer o;
    o<<user_state::CHANGE_CONTACT_MODE<<user$id(__U)<<'F'<<is_on;
    set_user_state(o);
    send_update_g3(user_set$ul_mode_hide_female,user$id(__U),is_on);

    if (is_on)
    {
        send_syspriv_msg(__U,_MSG("hide_female_enabled"));
        data_push_back(__U,"<SCRIPT>parent.set_state_hide_female(1);</SCRIPT>\n");

    }
    else
    {
        send_syspriv_msg(__U,_MSG("hide_female_disabled"));
        data_push_back(__U,"<SCRIPT>parent.set_state_hide_female(0);</SCRIPT>\n");
    }

    cc->html_out="POSRALL";
}
void url_change_male_mode(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    user_pair __U(__UU);
    bool is_on;
    {
        PGLW(user_set,u,__U.us);
        u->ul_mode_hide_male=!u->ul_mode_hide_male;
        is_on=u->ul_mode_hide_male;
    }
    out_oscar_buffer o;
    o<<user_state::CHANGE_CONTACT_MODE<<user$id(__U)<<'M'<<is_on;
    set_user_state(o);
    send_update_g3(user_set$ul_mode_hide_male,user$id(__U),is_on);

    if (is_on)
    {
        send_syspriv_msg(__U,_MSG("hide_male_enabled"));
        data_push_back(__U,"<SCRIPT>parent.set_state_hide_male(1);</SCRIPT>\n");

    }
    else
    {
        send_syspriv_msg(__U,_MSG("hide_male_disabled"));
        data_push_back(__U,"<SCRIPT>parent.set_state_hide_male(0);</SCRIPT>\n");
    }

    cc->html_out="POSRALL";
}




void url_change_voice(const PTR_getter<chat_user>&__UU,cs_conn_data *cc)
{

    if (!__UU || cc->user_unregistered) return;

    user_pair __U(__UU);

    set<CH_id> uchan=user$channel(__U);

    if (uchan.size())
    {
        do_change_voice(*uchan.begin(),user$id(__U),cc->params["msg"],-1);
    }
}

bool do_change_mode(PTR_getter<chat_channel> &ML,const PTR_getter<chat_user> &__UU,int mode)
{
    if (!__UU) return false;
    user_pair __U(__UU);

    CH_id uch;
    bool ext;
    int ulvl;
    {
        __CH_LOCK(ML);
        uch=CH->cd.chid;
        ext=CH->cd.extended;
    }
    DB_id uid=user$id(__U);
    ulvl=user$level(__U);
    if (ulvl/sub_levels<am_admin) {
        send_syspriv_msg(__U,_MSG("lowlevel"));
        return false;
    }
    if (!ext) {
        send_syspriv_msg(__U,_MSG("cantchangechannelmode"));
        return false;
    }
    chat_event_CHMODE *ev=new chat_event_CHMODE;
    ev->nick=GET_CNICK(__U);
    ev->channel=uch;
    ev->uid=uid;
    ev->mode=mode;
    send_chat_event(ev,true);
    return true;
}

void url_change_mode(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);

    set<CH_id> chs=user$channel(__U);
    if (chs.size())
    {
        PTR_getter<chat_channel> ML(chat_channels[*chs.begin()]);
        do_change_mode(ML,__UU,-1);
    }
}
map<CH_id,pair<int,string> > get_web_clist();

m_var<string> url_users_content;

void url_users(const PTR_getter<chat_user>&__UU,cs_conn_data *cc)
{
    cc->html_out=url_users_content;
}



bool do_change_voice(const CH_id& channel,const DB_id& uid,string nick, int nvoice)
{
    chat_event_CHVOICE *ev=new chat_event_CHVOICE;
    ev->nick=nick;
    ev->channel=channel;
    ev->uid=uid;
    ev->voice=nvoice;
    send_chat_event(ev,true);
    return true;
}

void url_chat_command(const PTR_getter<chat_user> &__U,cs_conn_data *cc)
{

    if (!__U) {
        return;
    }
    if (!inchat$(__U)) {
        logErr2("return %s %d",__FILE__,__LINE__);
        return;
    }
    string cmd=cc->params["cmd"];
    if (cmd=="invite") {
        url_invite_user(__U,cc);
    }
    else if (cmd=="kick") {
        url_kick_user(__U,cc);
    }
    else if (cmd=="ignore") {
        url_ignore_user(__U,cc);
    }
    else if (cmd=="nick") {
        url_change_nick(__U,cc);
    }
    /*    if(cmd=="topic"){
            url_set_topic(__U,cc);
        }*/
    else if (cmd=="cmode") {
        url_change_mode(__U,cc);
    }
    else if (cmd=="vmode") {
        url_change_voice(__U,cc);
    }
    else if (cmd=="clmode") {
        url_change_contact_mode(__U,cc);
    }
    else if (cmd=="fmmode") {
        url_change_female_mode(__U,cc);
    }
    else if (cmd=="mmmode") {
        url_change_male_mode(__U,cc);
    }
    else logErr2("invalid cmd %s",cmd.c_str());
    cc->html_out="done";

}
void url_invite_user(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    if (!__UU) {
        return;
    }
    if (!inchat$(__UU)) {
        return;
    }
    user_pair __U(__UU);
    chat_event_INVITE *event=new chat_event_INVITE;
    event->msg=cc->params["msg"];
    event->zid.container=atoi(cc->params["id"]);
    event->uid=user$id(__U);
    send_chat_event(event,true);
    cc->html_out="\r\n\r\nUser invited.";
}


void url_ignore_user(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);



    map<string,string> m;
    DB_id zid;
    zid.container=atoi(cc->params["id"]);
    if (zid==user$id(__U)) return;
    if (zid.container==0) throw cError("--Error: on_IGNORE zid 0");
    bool cantignore=false;
    unsigned int zlevel,ulevel=user$level(__U);
    {
        PGLR(user_profile,z,user_profiles.find_by_id(zid));
        zlevel=z->level;
    }
    if (zlevel/sub_levels>=am_killer) {
        if (ulevel/sub_levels < zlevel/sub_levels) {
            send_syspriv_msg(__U,_MSG("cantignore"));
            return;
        }
    }
    bool need_add=false;
    {
        PGLR(ignore_vec,u,ignore_vecs.find_by_id(cc->user_id));
        if (u->ignore.count(zid)) need_add=false;
        else need_add=true;
    }

    if (need_add) {
        send_update_g3(ignore$add,cc->user_id,zid.container);
        send_syspriv_msg(__U,"user ignored");
        {
            PGLW(ignore_vec,u,ignore_vecs.find_by_id(cc->user_id));
            u->ignore.insert(zid);
        }
    }
    else
    {
        send_update_g3(ignore$remove,cc->user_id,zid.container);
        send_syspriv_msg(__U,"user unignored");
        {
            PGLW(ignore_vec,u,ignore_vecs.find_by_id(cc->user_id));
            u->ignore.erase(zid);
        }
    }
    chat_event_IGNORE *e=new chat_event_IGNORE;
    e->uid=cc->user_id;
    e->zid=zid;
    send_chat_event(e,true);
    cc->html_out+="<html>OK. (un)ignored";
}

void kick_user(const DB_id &zid,const string &msgs);
void url_change_nick(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    if (!__UU || cc->user_unregistered) return;
    user_pair __U(__UU);
    unsigned int nn;
    bool tofast=false;
    {
        __UC_LOCK;
        tofast=time(NULL)-u->last_change_nick<2;
    }
    if (tofast) {
        send_syspriv_msg(__U,_MSG("changenickistoofast"));
        return;
    }
    {
        __UC_LOCK;
        u->last_change_nick=time(NULL);
    }
    nn=atoi(cc->params["id"]);
    if (nn==GET_CNICK_ID(__U)) {
        return;
    }
    DB_id zzzz;
    user_nick nnn("undef",user_state::UNDEF,zzzz,false,0);
    DB_id uid=user$id(__U);
    {
        PGLR(nick_vec, u,nick_vecs.find_by_id(uid));
        if (u->u_nicks.count(nn)) {
            nnn=u->u_nicks.find(nn)->second;
        }
        else
        {
            if (u->u_nicks.size())
                nnn=u->u_nicks.begin()->second;
        }
    }
    out_oscar_buffer o;
    o<<user_state::SET_NICK<<user$id(__U)<<nnn;
    set_user_state(o);
    DB_id u_dbid=user$id(__U);
    send_update_g3(user_set$last_nick,u_dbid,nnn.name);
    send_update_g3(user_set$last_nick_id,u_dbid,nnn.id);

    cc->html_out="\r\n\r\n nick changed.";
}

void url_kick_user(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);
    string cnick=GET_CNICK(__U);
    string login=user$login(__U);
    string ip=cc->peer_ipaddress;
    string pip=cc->proxy_ip;
    unsigned int levelsub_levels=cc->sub_level;
    if (levelsub_levels<am_killer) return;
    DB_id zid;
    zid.container=atoi(cc->params["id"]);
    PTR_getter<chat_user> __ZZ=local_users.get(zid);
    bool done=false;

    if (__ZZ) {

        user_pair __Z(__ZZ);
        int u_kick_ability=LEVELS(user$level(__U)).kick_ability;
        int z_kick_shield=LEVELS(user$level(__Z)).kick_shield;

        int zlevel;
        zlevel=user$level(__Z);
        if (u_kick_ability>z_kick_shield) {
            kick_user(zid,cc->params["msg"]);
            send_update_g2(user_stat$inc_kick_count,user$id(__U));
            send_update_g2(user_stat$inc_kicked_count,user$id(__Z));
            logErr2("User %s (%s) was kicked by %s (%s) - %s [%s - %s] {%d}",GET_CNICK(__Z).c_str(),user$login(__Z).c_str(),cnick.c_str(),login.c_str(),cc->params["msg"].c_str(),ip.c_str(),pip.c_str(),user$get_spent_time(__Z));
            done=true;
        } else {
            cc->html_out+="<script>alert('"+_MSG("noen_kickability")+"');</script>";
            return;
        }

    }
    else
    {
        send_syspriv_msg(__U,_MSG("cantkick"));
    }
    cc->html_out+="kicked";
}

void url_chat_sendmessage(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    if (!__UU) {
        return;
    }
    if (!inchat$(__UU)) {
        return;
    }
    user_pair __U(__UU);
    chat_event_SEND_MESSAGE *e=new chat_event_SEND_MESSAGE;
    e->from_uid=user$id(__U);
    e->msg=cc->params["msg"];
    e->tonick=cc->params["fornick"];
    e->priv=strupper(cc->params["priv"])=="ON";
    e->sys=strupper(cc->params["sys"])=="ON";
    e->makeit=strupper(cc->params["makeit"])=="ON";
    e->user_type=TYPE_WWW;
    {
        PGLR(chat_user,u,__UU);
        if (u->cstate.channel.size())
            e->channel=*u->cstate.channel.begin();
        else throw cError("not in channel");
    }
    send_chat_event(e,true);
    cc->html_out="\r\n\r\nmessage sent";
    {
        __UC_LOCK;
        u->last_m_time = time(NULL);
    }
}
void url_chat_messages(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    if (!__UU) {
        return;
    }
    if (!inchat$(__UU)) {
        return;
    }
    if (!cc->wc) throw cError("if(!cc->wc)");
    user_pair __U(__UU);
    chat_event_CHAT_MESSAGES *e=new chat_event_CHAT_MESSAGES;
    e->c=cc->params["c"];
    e->uid=user$id(__U);
    send_chat_event(e,false);
    cc->wc->allow_build_response=false;
    {
        __UC_LOCKW;

        u->psocket=cc->wc->socket;
        u->www_offline_time=0;
        u->www_inchat=true;
    }
}

void url_chat_addmessage(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    if (!__UU) {

        return;
    }
    if (!inchat$(__UU)) {

        return;
    }
    user_pair __U(__UU);
    map<string,hstring> m;
    string s;
    unsigned int ulevel=user$level(__U);
    bool hinv=has_inv(__U);

    user_status status;
    {
        __UC_LOCK;
        status=u->cstate.status;
    }
    unsigned char gender=user$gender(__U);
    {

        PGLW(user_profile,u,__U.up);
        map<unsigned int,user_status> &st=u->status;
        for (map<unsigned int,user_status>::iterator i=st.begin();i!=st.end();i++)
        {

            if (i->first==st_offinvisible) continue;
            if (i->first==st_invisible && !hinv) continue;
            if (i->first==st_offline) continue;
            s+="<OPTION VALUE="+itostring(i->first);

            if (i->first==status.id)
                s+=" SELECTED";
            string n=i->second.name;
            if (n.size()>16) n=n.substr(0,15)+"...";
            s+=">"+n;
        }
    }
    if (ulevel/sub_levels>=am_admin) {
        m["~s_script~"]="";
        m["~es_script~"]="";
        m["~hsys~"]="";
        m["~ehsys~"]="";
        m["~sysmsg~"]="";
        m["~esysmsg~"]="";
    } else {
        m["~s_script~"]="/*";
        m["~es_script~"]="*/";
        m["~hsys~"]="<!--";
        m["~ehsys~"]="-->";
        m["~sysmsg~"]="<!--";
        m["~esysmsg~"]="-->";
    }
    m["~status~"]=s;

    m["~msglen~"]=itostring(LEVELS(user$level(__U)).max_msg_len);
    m["~cansettopic~"]=itostring(user$privileges(__U)&u_allow_set_topic);
    set<CH_id> uch=user$channel(__U);
    bool moderated=false;
    if (uch.size()!=1) throw cError("uch.size()!=1 ");
    {
        {
            __CH_LOCK(chat_channels[*uch.begin()]);
            moderated=CH->cd.moderated;
        }
        m["~channel~"]=itostring(uch.begin()->container);
    }


    m["~moderated~"]=checked(moderated);

    cc->html_out=make_pair(m,"chat/add_message");
}
void kick_user(const DB_id &uid,const string &msgs)
{

    out_oscar_buffer o;
    o<<user_state::KICK<<uid<<msgs;
    set_user_state(o);
}

void url_chat_enter(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    if (!__UU) return;
    user_pair __U(__UU);
    user_state sta;
    {
        __UC_LOCK;
        sta=u->cstate;
    }
    if (!inchat$(__UU))
    {


        if (cc->user_unregistered) {
            int g=atoi(cc->params["gender"]);
            if (g<0 || g>2) {
                g=0;
            }
            int oldgd=user$gender(__U);
            if (oldgd!=g)
            {
                PGLW(user_profile, u,__U.up);
                u->set_gender(g);
                send_update_g3(user_profile$gender,cc->user_id,g);

            }
        }

        unsigned int new_nick_id=atoi(cc->params["nick"]);

        if (user$nicks_size(__U) <= 0) {
            cc->redirect("/login");
            logErr2("return %s %d",__FILE__,__LINE__);
            return;
        }
        sta.nick=GET_NICK(__U,new_nick_id);
        vector<CH_id> chs=chat_channels.keys();
        CH_id channel;
        int ich=atoi(cc->params["channel"]);
        if (ich > chs.size()-1 || ich<0) ich=0;
        channel=chs[ich];

        map<string,string> m;
        {
            __UC_LOCKW;

            u->www_offline_time=0;
        }
        sta.channel.clear();
        sta.channel.insert(channel);
        if (has_inv(__U))
        {
            if (cc->params["ininv"]=="on") {

                sta.status=get_user_status_by_id(__U,st_invisible);

            }
            else
            {
                if (sta.status.id==st_invisible || sta.status.id==st_offinvisible)
                {
                    sta.status=get_user_status_by_id(__U,st_online);
                }
            }
        }
        if (sta.status.id==user_state::UNDEF) sta.status=get_user_status_by_id(__U,st_online);
        if (sta.status.id==st_offline) sta.status=get_user_status_by_id(__U,st_online);
        if (sta.status.id==st_offinvisible) sta.status=get_user_status_by_id(__U,st_invisible);
        if (sta.status.id==st_away) sta.status=get_user_status_by_id(__U,st_online);
        if (sta.status.id==st_na) sta.status=get_user_status_by_id(__U,st_online);
        {
            PGLW(user_set,u,__U.us);
            if (sta.status.id!=u->last_status_id)
            {
                send_update_g3(user_set$last_status_id,cc->user_id,sta.status.id);
                u->last_status_id=sta.status.id;
            }
        }

        if (cc->params["showadm"]=="on") {
            PGLW(user_set, u,__U.us);
            if (!u->setting_show_eye)
            {
                if (u->setting_show_eye!=true)
                {
                    u->setting_show_eye=true;
                    send_update_g3(user_set$setting_show_eye,cc->user_id,u->setting_show_eye);
                }
            }
        } else {

            PGLW(user_set, u,__U.us);
            if (u->setting_show_eye)
            {
                if (u->setting_show_eye!=false)
                {
                    u->setting_show_eye=false;
                    send_update_g3(user_set$setting_show_eye,cc->user_id,u->setting_show_eye);
                }
            }
        }

        unsigned int neye=atoi(cc->params["eye"]);
        if (user$level(__U)/sub_levels<am_sadmin && user$neye(__U)>chat_config.number_of_eyes)
        {
            PGLW(user_set, u,__U.us);
            neye=0;
        }
        {
            PGLW(user_set, u,__U.us);
            if (u->neye!=neye)
            {
                u->neye=neye;
                send_update_g3(user_set$neye,cc->user_id,u->neye);
            }
        }
        {
            __UC_LOCKW;
            u->www_offline_time=0;
            u->www_inchat=true;
        }
    }
    out_oscar_buffer o;
    o<<user_state::SET_BIN_STATE<<user$id(__U)<<sta;
    set_user_state(o);
    {
        __UC_LOCKW;
        u->cstate=sta;
    }
    {
        PGLW(user_set, u,__U.us);
        if (u->last_nick_id!=sta.nick.id)
        {
            u->last_nick_id=sta.nick.id;
            u->last_nick=sta.nick.name;
            send_update_g3(user_set$last_nick,cc->user_id,sta.nick.name);
            send_update_g3(user_set$last_nick_id,cc->user_id,sta.nick.id);
        }
        if (sta.status.id!=u->last_status_id)
        {
            send_update_g3(user_set$last_status_id,cc->user_id,sta.status.id);
            u->last_status_id=sta.status.id;
        }
    }

    cc->redirect("/chat/");
}

void url_chat_status(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    if (!__UU) {
        return;
    }
    if (!inchat$(__UU)) {
        return;
    }
    user_pair __U(__UU);
    map<string,string> m;
    unsigned int st=atoi(cc->params["status"]);
    user_status ust=get_user_status_by_id(__U,st);
    out_oscar_buffer o;
    o<<user_state::SET_STATUS<<user$id(__U)<<ust;
    set_user_state(o);

    send_update_g3(user_set$last_status_id,user$id(__U),ust.id);

    cc->html_out="\r\n\r\nstatus changed";
}

void url_chat(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    if (!__UU) {
        cc->html_out=cc->redirect();
        return;
    }
    user_pair __U(__UU);
    switch_cc_ret("enter",url_chat_enter(__UU,cc));
    switch_cc_ret("users",url_chat_users(cc));
    switch_cc_ret("buttons",url_chat_buttons(__UU,cc));
    switch_cc_ret("messages",url_chat_messages(__UU,cc));
    switch_cc_ret("addmessage",url_chat_addmessage(__UU,cc));
    switch_cc_ret("sendmessage",url_chat_sendmessage(__UU,cc));
    switch_cc_ret("exit",url_chat_exit(__UU,cc));
    switch_cc_ret("setstatus",url_chat_status(__UU,cc));
    switch_cc_ret("userinfo",url_user_info(__UU,cc));
    switch_cc_ret("cmd",url_chat_command(__UU,cc));
    map<string,hstring> m;
    if (!__UU) {
        logErr2("!__UU %s %d",__FILE__,__LINE__);
        return;
    }
    CH_id uch;
    {
        PGLR(user_set, u,__U.us);
        uch.container=u->last_channel;
    }
    vector<CH_id> chs=chat_channels.keys();
    bool found=false;
    for (unsigned i=0;i<chs.size();i++)
    {
        if (uch==chs[i]) found=true;
    }
    if (!chs.size()) throw cError("!chs.size()");
    if (!found) {
        uch=chs[0];
        PGLW(user_set, u,__U.us);
        u->last_channel=uch.container;
    }

    m["~uid~"]=itostring(user$id(__U).container);


    m["~level~"]=itostring(user$level(__U)/sub_levels);
    {
        PGLR(user_set,u,__U.us);
        m["~acs~"]=itostring(u->setting_autochange);
        m["~invite_sound~"]=itostring(u->setting_invite_sound);
        m["~full_buttons~"]=itostring(u->setting_full_buttons);
        m["~contact_mode~"]=u->ul_mode_contacts_only?"1":"0";
        m["~hide_female~"]=u->ul_mode_hide_female?"1":"0";
        m["~hide_male~"]=u->ul_mode_hide_male?"1":"0";
    }
    m["~has_inv~"]=itostring(has_inv(__U));
    m["~ccount~"]=itostring(chs.size());
    {
        __CH_LOCK(chat_channels[uch]);
        m["~moderated~"]=itostring(CH->cd.moderated);
    }
    cc->html_out=make_pair(m,"chat/chat");
}
