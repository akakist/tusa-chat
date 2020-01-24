#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include "_mutex.h"
#include <list>

#include <stdio.h>
#include <map>
#include <vector>
#include "web_server.h"
#include "chat_def.h"
#include "utils.h"
#include "user.h"
#include "message.h"
#include "str_lib.h"
#include "st_stuff.h"
#include "web_server_data.h"
#include "web_tools.h"
#include "file_set.h"
#include "user_credits.h"
#include "chat_funny.h"
#include "levels.h"
#include "channels.h"
#include "server_config.h"

#include "chat_config.h"
#include "chat_colors.h"
#include "app_def.h"
#include "register.h"
#include "update_cmd.h"
#include "contact_vec.h"
#include "chat_thread_event.h"
#include "des_sid.h"
#include "html_out.h"
#include "cs_conn_data.h"
#include "chat_globals.h"
#include "login_result.h"

bool is_user_banned(app_connection * cc, const string & ip, const string & login, const string & conf);

void make_login_out(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void reload(const PTR_getter<nick_vec> &N);
string login_io(const string& login, const string& pass);









static bool create_reg_user(PTR_getter<chat_user> &__UU,cs_conn_data *cc,const string& __login, const string&__pass, bool check_pass)
{
    string login=__login;
    string pass=bin2hex(MD5(__pass),0);
    map<string,hstring> m;
    m["~login~"]=login;

    if (login.size()>MAX_NICK_SIZE || !check_nick(login) || !check_maty(" "+login) || login.size()==0) {
        cc->html_out=make_pair(m, "login/badnick");
        return false;
    }
    PTR_getter<chat_user> __ZZ(NULL);
    DB_id zid=all_user_nick_2_DB_id(login);
    if (zid.container)   __ZZ=local_users.get(zid);
    if (__ZZ)
    {
        int ztype;
        {
            PGLR(chat_user,z,__ZZ);
            ztype=z->user_type;
        }
        if (ztype==TYPE_IRC)
        {
            user_pair __Z(__ZZ);
            if (string(user$pass(__Z))==pass || !check_pass)
            {
                {
                    __ZC_LOCK;
                    z->erased=true;
                }
                __ZZ=NULL;
            }
        }
    }

    if (__ZZ)
    {

        user_pair __Z(__ZZ);

        if (string(user$pass(__Z))==pass || !check_pass) {
        } else {
            cc->html_out=make_pair(m,"login/incorrect");

            return false;
        }


        __UU=__ZZ;
        local_users.erase(zid);
        broadcast_user_logged_out(zid);


        user_pair __U(__UU);



        string cookie;
        string old_cookie;
        DB_id __uid=user$id(__U);
        {
            __UC_LOCK;
            u->erased=false;
            u->cu_ip=cc->peer_ipaddress;
            u->www_proxy_ip=cc->proxy_ip;

            sid_t st;
            st.user_map_key=u->db_id.container;
            st.user_map_key1=rand();
            old_cookie=u->www_cookie;
            u->www_cookie=get_des_hex_sid(st);
            cc->cookies["cid"]=u->www_cookie;
            cookie=u->www_cookie;
        }


        {
            send_update_g3(user_stat$last_date,__uid,time(NULL));
            send_update_g3(user_stat$last_ip,__uid,cc->peer_ipaddress);
            send_update_g3(user_stat$last_pip,__uid,cc->proxy_ip);
        }
        user_register_all_nicks(__uid,true);
        local_users.insert(__UU);
        broadcast_user_logged_in(__uid);
        __cookie_2_session_id.erase(old_cookie);
        __cookie_2_session_id.set(cookie,__uid);
        return true;
    }
    string l_res=login_io(login,pass);
    oscar_buffer b(l_res.data(),l_res.size());
    int log_res;
    b>>log_res;
    if (log_res==LOGIN_INCORRECT)
    {
        cc->html_out=make_pair(m,"login/incorrect");

        return false;

    }
    if (log_res==LOGIN_BANNED)
    {
        string time_cnt,reason;
        int time_free,time_ban;
        b>>time_cnt>>time_free>>time_ban>>reason;


        m["~time_cnt~"]=time_cnt;
        m["~time_free~"]=date2rus(time_free);
        m["~time_ban~"]=date2rus(time_ban);
        m["~reason~"]=reason;
        cc->html_out=make_pair(m,"login/loginbanned");

        return false;

    }
    if (log_res!=LOGIN_SUCCESS)
    {
        throw cError("log_res!=LOGIN_SUCCESS");
    }


    DB_id uid;
    b>>uid;
    //All OK. Creating registered user.
    __UU=new chat_user(TYPE_WWW);

    {
        PGLW(chat_user, u,__UU);
        u->__user_profile=user_profiles.find_by_id(uid);
        u->__user_set=user_sets.find_by_id(uid);
    }
    user_pair __U(__UU);
    {
        send_update_g3(user_stat$last_date,uid,time(NULL));
        send_update_g2(user_stat$inc_v_count,uid);

    }

    {
        __UC_LOCKW;
        u->db_id=uid;
    }

    cc->user_id=uid;
    logErr2("%s (%s) logged in. [%s - %s]",login.c_str(),string(user$login(__U)).c_str(),cc->peer_ipaddress.c_str(),cc->proxy_ip.c_str());


    sid_t st;
    st.user_map_key=uid.container;
    st.user_map_key1=rand();
    string cookie=get_des_hex_sid(st);
    __cookie_2_session_id.set(cookie,uid);

    {
        __UC_LOCK;

        u->cu_ip=cc->peer_ipaddress;
        u->www_proxy_ip=cc->proxy_ip;
        u->ua=cc->params["USER-AGENT"];
        u->login_date=time(NULL);
        u->last_access_time=time(NULL);
        u->www_unregistered=false;
        u->erased=false;
        u->www_cookie=cookie;
        cc->cookies["cid"]=cookie;

    }
    user_register_all_nicks(uid,true);

    local_users.insert(__UU);
    broadcast_user_logged_in(uid);
    chat_event_UPDATE_USER_SESSION *ce=new chat_event_UPDATE_USER_SESSION;
    ce->uid=uid;
    ce->user_type=TYPE_WWW;
    ce->ip=cc->peer_ipaddress;
    ce->pip=cc->proxy_ip;
    send_chat_event(ce,false);
    if (__UU) return true;
    else return false;

}



struct enter_login: public base_container
{
    _mutex *Mutex;
    enter_login():base_container("enter_login") {
        Mutex=new _mutex("enter_login");
    }
    ~enter_login() {
        delete Mutex;
    }
};
map<string,PTR_getter<enter_login> > l_mutexes;
_mutex l_mutexes_MX("l_mutexes_MX");

struct login_enterer
{
    PTR_getter<enter_login> et;
    _mutex *mU;
    string login;

    login_enterer(const string & __login): et(NULL),mU(NULL),login(__login)
    {
        map < string, PTR_getter<enter_login > >::iterator i;
        {
            M_LOCK(l_mutexes_MX);

            if (!l_mutexes.count(__login)) {
                l_mutexes.insert(pair < string, PTR_getter<enter_login > >(__login, PTR_getter<enter_login > (new enter_login)));
            }
            i = l_mutexes.find(__login);
            if (i == l_mutexes.end())
                throw cError("i==l_mutexes.end()" );
            et = i->second;
        }
        if (!et)
            throw cError("!et");
        {
            PGLR(enter_login, bb,et);
            mU = bb->Mutex;
        }

    }
    ~login_enterer()
    {
        M_LOCK(l_mutexes_MX);
        l_mutexes.erase(login);
    }
};

void url_login(PTR_getter<chat_user> &__UU,cs_conn_data * cc)
{

    string login,pass;
    bool check_pass=true;

    {
        login = cc->params["login"];
        pass = cc->params["pass"];
    }

    map < string, hstring > m;
    m["~login~"] = login;
    string add_s;

    if ((pass.size() == 0 && check_pass) && login.size() != 0)
    {
        return;
        //login without registration
#ifdef KALL
        if (!check_unreg_login(__UU, cc,login)) {
            cc->cookies["cid"] = "0";
            cc->html_out=cc->redirect();

            return;
        }

        create_unreg_user(__UU, cc,login);
        logErr2("%s logged in without registration [%s - %s]", login.c_str(), cc->peer_ipaddress.c_str(), cc->proxy_ip.c_str());
#endif

    }

    if (login.size() > 0 && (pass.size() > 0 || !check_pass) ) {//;	//login with registration

        if (!create_reg_user(__UU, cc,login,pass,check_pass)) {
            cc->cookies["cid"] = "0";
            if (cc->html_out.hstr_size()==0)
                cc->html_out=cc->redirect();
            return;
        }
    }
    if (!__UU) {
        logErr2("if(!__UU) (%s) %s %d",cc->peer_ipaddress.c_str(),__FILE__,__LINE__);
        cc->html_out=cc->redirect();
        return;
    }

    user_pair __U(__UU);

    {
        __UC_LOCK;
        u->cu_ip=cc->peer_ipaddress;
        u->www_proxy_ip=cc->proxy_ip;
    }
    DB_id uid=user$id(__U);
    {
        send_update_g3(user_stat$last_ip,uid,cc->peer_ipaddress);
        send_update_g3(user_stat$last_pip,uid,cc->proxy_ip);
    }
    {
        __UC_LOCKW;
        if (!local_users.count(u->db_id)) {
            cc->cookies["cid"]="0";
            cc->html_out = make_pair(m, add_s+"login/incorrect");
            return;
        }
    }
    if (user$level(__U)/sub_levels <am_admin)
    {
        if (!check_for_ipban(cc->peer_ipaddress, cc->proxy_ip)) {	//may be banned.
            m["~ip~"] = cc->peer_ipaddress;
            cc->html_out = make_pair(m, add_s+"login/ipbanned");
            logErr2("Attempt to login from BANNED ip address %s [%s,%s]", login.c_str(), cc->peer_ipaddress.c_str(), cc->proxy_ip.c_str());
            cc->cookies["cid"] = "0";
            return;
        }

    }


    user_register_all_nicks(uid,true);
    make_login_out(__UU, cc);
}


void url_login_settings(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    if (!__UU) return;
    user_pair __U(__UU);
    DB_id id=user$id(__U);


    if (cc->params["hints"]=="0") {
        PGLW(user_set, u,user_sets.find_by_id(id));
        u->setting_show_hints^=u->setting_show_hints;
        send_update_g3(user_set$setting_show_hints,id,u->setting_show_hints);
    }
    if (cc->params["stat"]=="0") {
        PGLW(user_set, u,user_sets.find_by_id(id));
        u->setting_show_stat^=u->setting_show_stat;
        send_update_g3(user_set$setting_show_stat,id,u->setting_show_stat);
    }

    string login=user$login(__U);
    if (cc->params["removenick"]=="yes") {
        unsigned int nick_id=atoi(cc->params["nick"]);
        if (user$nicks_size(__U)>1) {
            {
                PGLW(nick_vec,n,nick_vecs.find_by_id(id));
                if (n->u_nicks.count(nick_id))
                {
                    user_unregister_1_nick(n->u_nicks[nick_id].name,true);
                    n->u_nicks.erase(nick_id);
                    send_update_g3(nick$remove,id,nick_id);
                }
            }
        }
    }
    cc->redirect("/login");
}
