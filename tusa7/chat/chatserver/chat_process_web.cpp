
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
#include "mysql_extens.h"
#include "utils.h"
#include <algorithm>
#include "user.h"
#include "message.h"
#include "app_con.h"
#include "web_server_data.h"
#include "file_set.h"
#include "register.h"
#include "server_config.h"
#include "chat_config.h"
#include "app_def.h"
#include "chat_def.h"
#include "thread_descr.h"
#include "copy_file.h"
#include "cs_conn_data.h"

bool stop_threads=false;


string error_http(app_connection *cc,const string &e);

void url_a_user_info(cs_conn_data*);		//gallery.c
void url_addfunny(const PTR_getter<chat_user>&__U, cs_conn_data *);
void url_admin(const PTR_getter<chat_user>&__U, cs_conn_data*);		// /chat/admin
void url_anekdots(const PTR_getter<chat_user>&__U, cs_conn_data*);
void url_change_info(const PTR_getter<chat_user>&__U, cs_conn_data*);		//setting.c
void url_chat(const PTR_getter<chat_user>&__U, cs_conn_data*);		// /chat
void url_empty_frame(cs_conn_data*);		// /emtyframe
void url_forum(const PTR_getter<chat_user>&__U, cs_conn_data*);	//forum.c
void url_funny_pics(const PTR_getter<chat_user>&__U, cs_conn_data*);	//other.c
void url_gallery(const PTR_getter<chat_user>&__U,cs_conn_data*);		//gallery.c
void url_histories(const PTR_getter<chat_user>&__U, cs_conn_data*);
void url_index(const PTR_getter<chat_user>&__user, cs_conn_data *);		//main.c index.html
void url_login(PTR_getter<chat_user> &__UU,cs_conn_data*);		//login.c
void url_login_settings(const PTR_getter<chat_user>&__U, cs_conn_data*);// /login/settings
#ifdef __MCASSA
//void url_mcassa(/*const PTR_getter<chat_user>&__U,*/ cs_conn_data*);
#endif
void url_logout(const PTR_getter<chat_user>&__U, cs_conn_data*);			// /logout kill session
void url_new_nick(const PTR_getter<chat_user>&__U, cs_conn_data*);		// /newnick
void url_news(cs_conn_data *);		//main.c
void url_notes(const PTR_getter<chat_user>&__U, cs_conn_data*);		// /chat/admin
void url_notes_attach(const PTR_getter<chat_user>&__U, cs_conn_data* cc);
void url_picz(cs_conn_data *);			//other.c
void url_registration(cs_conn_data *cc);
void url_relogin(cs_conn_data *);
void url_settings(const PTR_getter<chat_user>&__U, cs_conn_data*);	//setting.c
void url_st_pic(cs_conn_data*);		//main.c
void url_statistic(cs_conn_data *cc);
void url_user_photo(cs_conn_data* cc);
void url_user_photos(cs_conn_data*);		//gallery.c
void url_users(const PTR_getter<chat_user>&__U, cs_conn_data*);		// /usersframe
void url_users_statistic(cs_conn_data *cc);
void url_vote(const PTR_getter<chat_user>&__U, cs_conn_data*);	//vote.c
void url_settings_edit_contacts(const PTR_getter<chat_user>  &__UU,cs_conn_data *cc);
void url_settings_privs(const PTR_getter<chat_user> &__UU,cs_conn_data *cc);
void url_settings_chat(const PTR_getter<chat_user> &__UU,cs_conn_data *cc);
void url_settings_colors(const PTR_getter<chat_user> &__UU,cs_conn_data *cc);
void url_settings_status(const PTR_getter<chat_user> &__UU,cs_conn_data *cc);
void url_settings_credits(const PTR_getter<chat_user> &__UU,cs_conn_data *cc);
void url_settings_nicks(const PTR_getter<chat_user> &__UU,cs_conn_data *cc);
void url_settings_nick_buy(const PTR_getter<chat_user> &__UU,cs_conn_data *cc);
void url_chat_topic(cs_conn_data *cc);

extern M_MAP<pthread_t,string> pthread_2_url_map;
struct st_pthread_2_url_map
{
    st_pthread_2_url_map(const string &s)
    {
        pthread_2_url_map.set(pthread_self(),s);

    }
    ~st_pthread_2_url_map()
    {
        pthread_2_url_map.erase_key(pthread_self());
    }
};




void do_adminfo(app_connection * cc, const string & title);


string error_http(app_connection *cc,const string &e)
{
    map<string,string> m;
    m["~error~"]=e;
    return cc->rvfiles(m,"500");
}


//string thread_info_html(const map<pthread_t, string> &add_map);

M_DEQUE<pair<string,string> > dump_urls;
void dump_url_log()
{
    deque<pair<string,string> > d=dump_urls.extract_all();
    string out;
    for (typeof(d.begin())i=d.begin();i!=d.end();i++)
    {
        out+=i->first+" "+i->second+"\n";
    }


    string fn__=(string)chat_config.history_dir+split_char+"URL."+date4file(time(NULL));
    try {
        if (out.size())
        {
            string fn=fn__+".log";
            check_path_wfn(fn.c_str());
            st_FILE f(fn,"ab");
            f.write(out);
        }
    }
    catch (cError e)
    {
        logErr2("catched %s %d '%s'",__FILE__,__LINE__,e.what());
    }
    catch (...)
    {

    }

}
void chat_process_web(cs_conn_data *cc,PTR_getter<chat_user>&__U)
{
//    logErr2("chat_process_web %s",cc->url.c_str());;
    string chat_url=strlower(cc->url);
    dump_urls.push_back(make_pair(chat_url,cc->peer_ipaddress));
    if (chat_url=="/users") {
        url_users(__U,cc);
    }

    if (chat_url=="/relogin") {
        url_relogin(cc);
    }
    if (chat_url.substr(0,6)=="/picz/") {
        url_picz(cc);
    }

    if (chat_url=="/") {
        url_index(__U,cc);
    }

    if (chat_url=="/login") {
        url_login(__U,cc);
    }
    if (chat_url=="/emptyframe") {
        url_empty_frame(cc);
    }
    if (chat_url=="/news") {
        url_news(cc);
    }
    if (chat_url=="/stpic") {
        url_st_pic(cc);
    }
    if (chat_url=="/userphotos") {
        url_user_photos(cc);
    }

    //chatter corner
    if (chat_url=="/funnypics") {
        url_funny_pics(__U,cc);
    }
    if (chat_url=="/histories") {
        url_histories(__U,cc);
    }
    if (chat_url=="/anekdots") {
        url_anekdots(__U,cc);
    }
    if (chat_url=="/addfunny") {
        url_addfunny(__U,cc);
    }

    if (chat_url=="/stat") {
        url_statistic(cc);
    }
    if (chat_url=="/users_stat") {
        url_users_statistic(cc);
    }

    if (chat_url.substr(0,7)=="/photos") {
        url_user_photo(cc);
        return;
    }


    //URLs with may be authorize
    if (chat_url=="/auserinfo") {
        url_a_user_info(cc);
    }

    if (chat_url=="/registration") {
        url_registration(cc);
    }

    switch_cc("vote",url_vote(__U,cc));
    switch_cc("forum",url_forum(__U,cc));


    if (chat_url=="/gallery") {
        url_gallery(__U,cc);
    }


    if (!__U)
    {	    //not authorized
//        cc->html_out=cc->redirect();
//        return;
    }

    if (__U) {
        bool erased;
        {
            PGLR(chat_user, u,__U);
            erased=u->erased;
        }
        if (erased) {	//kicked user
            cc->html_out=cc->redirect();
            return;
        }
    }

    //authorized URLs
    if (chat_url=="/login/settings") {
        url_login_settings(__U,cc);
    }
    if (chat_url=="/logout") {
        url_logout(__U,cc);
    }
    if (chat_url=="/newnick") {
        url_new_nick(__U,cc);
    }
    switch_cc("admin",url_admin(__U,cc));
    switch_cc("notes",url_notes(__U,cc));
    if (chat_url.substr(0,7)=="/attach") {
        url_notes_attach(__U,cc);
        return;
    }
    switch_cc("chat",url_chat(__U,cc));

    switch_cc_ret("settings",url_settings_status(__U,cc));
    switch_cc_ret("settings_status",url_settings_status(__U,cc));
    switch_cc_ret("settings_chat",url_settings_chat(__U,cc));
    switch_cc_ret("settings_color",url_settings_colors(__U,cc));
    switch_cc_ret("settings_privs",url_settings_privs(__U,cc));
    switch_cc_ret("settings_edit_contacts",url_settings_edit_contacts(__U,cc));
    switch_cc_ret("settings_credit",url_settings_credits(__U,cc));
    switch_cc_ret("settings_nicks",url_settings_nicks(__U,cc));
    switch_cc_ret("nick_buy",url_settings_nick_buy(__U,cc));
    switch_cc_ret("chat_topic",url_chat_topic(cc));

    if (chat_url=="/changeinfo") {
        url_change_info(__U,cc);
    }
    if (chat_url!="/chat/messages") {		//live connect
        if (cc->html_out.hstr_size()==0) {		//All others URL
            cc->html_out=cc->redirect();
        }
    }

}

M_MAP<pthread_t,string> pthread_2_url_map;


void app_connection::process_web()
{

    vurl = splitTOK("/", url);
    st_pthread_2_url_map kalllll(url+" ("+peer_ipaddress+")");

    unsigned int clan_id=0;

#ifdef __MCASSA
    if (is_cassa)
    {
        if (url=="/495/mcassa")
        {
            cs_conn_data csc(this,
                             params,
                             url,
                             vurl,
                             proxy_ip,
                             peer_ipaddress,
                             clan_id,
                             cookies,
                             html_out,
                             user_unregistered,
                             user_id,
                             sub_level
                            );

//            url_mcassa(&csc);
        }
        return;
    }
#endif

    if (url==server_ref->adminfo_url) {
        do_adminfo(this,"Server Info");
        return;
    }

    PTR_getter<chat_user>	__US(NULL);
    DB_id session_id=__cookie_2_session_id.get(params["cid"]);
    if (session_id.container!=0 && local_users.count(session_id))
    {
        __US=local_users.get(session_id);
    }
    try {
        init_temp_vars(__US);
        bool valid_user=false;
        if (__US&& local_users.count(__US))
        {
            PGLR(chat_user, u,__US);
            if (peer_ipaddress==u->cu_ip && u->www_cookie==params["cid"]) {
                if (proxy_ip==u->www_proxy_ip) {
                    valid_user=true;
                }

            }

        }
        if (!valid_user) {
            params.erase("cid");
        }
        //URls without authorize

        if (__US) {
            PGLW(chat_user, u,__US);
            u->last_access_time=time(NULL);
        }
        cs_conn_data csc(this,
                         params,
                         url,
                         vurl,
                         proxy_ip,
                         peer_ipaddress,
                         clan_id,
                         cookies,
                         html_out,
                         user_unregistered,
                         user_id,
                         sub_level
                        );

        chat_process_web(&csc,__US);
    }
    catch (socketError e)
    {
    }
    catch (cError e) {
        logErr2("--Error: %s URL=%s [%s - %s]",e.error_string.c_str(),url.c_str(),peer_ipaddress.c_str(),proxy_ip.c_str());
        html_out=error_http(this,e.error_string);
    }
    catch (...) {
        logErr2("--Error: UNKNOW!!! URL=%s [%s - %s]",url.c_str(),peer_ipaddress.c_str(),proxy_ip.c_str());
        html_out=error_http(this,"unknow error ");
    }
}
void url_empty_frame(cs_conn_data* cc)
{
    cc->html_out=global_config.files_get("chat/users");
}



