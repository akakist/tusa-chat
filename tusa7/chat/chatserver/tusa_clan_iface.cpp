#include "stdafx.h"
#include <signal.h>
#include <errno.h>
#include "file_set.h"
#include "PTR.h"
#include "chat_def.h"
#include "web_server_data.h"
#include "mysql_extens.h"
#include "user.h"
#include "utils.h"
#include "PTR.h"
#include "tcp_server_data.h"
#include "app_server.h"
#include "app_def.h"
#include "version.h"
#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include "irc_server.h"

#include "irc_server_config.h"
#ifndef _NO_PROXY
#include "pgate_server.h"
#include "pgate_server_config.h"
#endif
#include "G_session.h"
#include "app_cs_server_iface.h"
#include "chat_clans.h"
#include "central_server.h"
#include "RTYPES_CORE.h"
#include "RTYPES_CLAN.h"
#include "html_out.h"
#include "cs_conn_data.h"
#include "DR_types.h"
#include "contact_vec.h"
#include "ignore_vec.h"
#include "user_stat.h"
#include "DR_types.h"
#include "fotos.h"
#include "channels.h"
#include "notes.h"
#include "user_credits.h"
#include "chat_thread_event.h"
#include "chat_config.h"
app_server* wwwserver=NULL;
app_server* cassaserver=NULL;
irc_server *ircserver=NULL;
void chat_process_web(cs_conn_data *cc,PTR_getter<chat_user>&__U);
void on_FAM_DATA_REQUEST$TYPE_SEND_REQUEST(const PTR_getter<chat_clan> &__SD,oscar_buffer& b, const G_session&);
extern M_DEQUE<string> update_commands;

void start_chat_processor();
void start_update_processor();
void load_app_configuration();
__chat_clans chat_clans;
vector< vector<string> > gallery_request(const string &snick);
vector<string> select_uid_nick_by_ids(const DB_id &uid, unsigned int nid);
DB_id get_uid_by_nick(const string& nick);
extern M_MAP<string,string> chat_stat;
map<time_t,unsigned int> get_users_counts(time_t t, time_t rt);
bool check_for_ipban(const string &ip,const string &proxyip);
int do_nickban(const string &nick_orig,const DB_id& id,unsigned int level) ;
int do_loginban(const DB_id &zuid,const string &descr,time_t t,const DB_id& adm_uid,unsigned int level);
int do_ipban(const string &ip_orig,const string &proxy_orig,time_t t,const DB_id& id);
void pack_levels(out_oscar_buffer&b );
string register_io(map<string,string> &params);
string login_io(const string& login, const string& pass);
vector<string> get_id_uid_nick_by_nick(const string &to_nick);
pair<string,DB_id> get_pass_by_nick(const string &nick);
vector<string> get_uid_time_cnt_descr_from_banned_login_by_uid(const DB_id &uid);
void pack_news(out_oscar_buffer &b);
void pack_hints(out_oscar_buffer &b);
void check_scaled_foto(const DB_id &uid,unsigned int pid,const string& ext,int xsz);
string foto_pn_cache(const DB_id& uid,unsigned int pid, unsigned int xsize,const string& ext);
string attach_pn(const DB_id&,unsigned int msgid, const string& orig);
void pack_channels(out_oscar_buffer &bb);
void deinit_tusa_clan()
{
    delete wwwserver;
    delete cassaserver;
    delete ircserver;
}
void init_tusa_clan()
{
    try {
        string conf="./conf/CS.conf";

        map<string,string> m=load_m_file(conf);
        {
            
            logErr2("Starting webserver");
#ifdef __MCASSA
            wwwserver=new app_server(false);
#else
            wwwserver=new app_server();
#endif
            
        }
        {
            
            wwwserver->start(conf,"www_server_",m);
            
        }

        logErr2("Starting cassaserver");
#ifdef __MCASSA
        {
            
            cassaserver=new app_server(true);
            cassaserver->start(conf,"cassa_",m);
            
        }
#endif



        start_chat_processor();
        start_update_processor();

        {
            logErr2("Starting ircd");
            ircserver=new irc_server();
            ircserver->start(conf,"irc_server_",m);
        }
    }STDCATCHS("init_tusa_clan");

}
void on_delete_session_tusa_clan(const G_session& app_data,const PTR_getter<session_data>&SD)
{

    chat_clans.erase(app_data);
    PTR_getter<chat_clan> __C=chat_clans.find(app_data);
    set<DB_id> lu;
    if (__C)
    {
        PGLR(chat_clan,c,__C);
        lu=c->local_users;
    }
    for (typeof(lu.begin())i=lu.begin();i!=lu.end();i++)
    {
        out_oscar_buffer o;
        o<<user_state::PARTALL<<(*i);
        set_user_state(o);
    }

    //    logErr2("fm_LOGOFF U=%s ID=%d IP=%s LT=%d UC=%d",nick.c_str(),id.container,ip.c_str(),time(NULL)-lt,fm_users.size());

}
void on_TYPE_SEND_HTTP_REQUEST(const PTR_getter<chat_clan> &__SD,oscar_buffer& b)
{

    int luid;
    string url,peer_ipaddress,proxy_ip;//,www_sid;
    map<string,string> params;
    DB_id uid;

    b>>luid>>uid>>url>>params>>peer_ipaddress>>proxy_ip;//>>www_sid;
    //    logErr2("url %s",url.c_str());
    vector<string> vurl=splitTOK("/",url);
    map<string,string> cookies;
    hstring html_out;
    bool user_unregistered=true;
    //    DB_id user_id;
    unsigned int sub_level;
    unsigned int clan_id;
    {
        PGLR(chat_clan,s,__SD);
        clan_id=s->clan_id;
    }
    cs_conn_data csc(NULL,
                     params,
                     url,
                     vurl,
                     proxy_ip,
                     peer_ipaddress,
                     clan_id,
                     cookies,
                     html_out,
                     user_unregistered,
                     uid,
                     sub_level);

    PTR_getter<chat_user>	__US(NULL);

    try {

        if (uid.container)
        {
            chat_user *u=new chat_user(TYPE_WWW);
            u->__user_profile=user_profiles.find_by_id(uid);
            u->__user_set=user_sets.find_by_id(uid);
            {
                PGLR(user_profile,z,u->__user_profile);
                sub_level=z->level/sub_levels;
            }
            u->db_id=uid;
            csc.user_id=uid;
            u->cu_ip=peer_ipaddress;
            u->www_proxy_ip=proxy_ip;
            u->login_date=time(NULL);
            u->last_access_time=time(NULL);
            u->www_unregistered=false;
            u->erased=false;
            __US=u;
            user_unregistered=false;
        }
        if (__US) {
            user_pair __U(__US);
            {
                __UC_LOCK;
                user_unregistered=u->www_unregistered;
            }
            sub_level=user$level(__U)/sub_levels;
        }

        chat_process_web(&csc,__US);
    }
    catch (cError e)
    {
        logErr2("catched %s %s %d",e.what(),__FILE__,__LINE__);

    }
    catch (...)
    {
        logErr2("catched %s %d",__FILE__,__LINE__);
    }
    out_oscar_buffer bb;
    bb<<luid<<cookies<<html_out<<csc.redirect_url;

    reply_chat_clan(__SD,__TYPE_SEND_HTTP_REQUEST,bb);


}
void process_data_event_tusa_clan(const G_session& app_data, const PTR_getter<session_data> &__SD, oscar_buffer& b,int _msg)
{
    PTR_getter<chat_clan> __CSU=chat_clans.find(app_data);
    if (!__CSU)
    {
        logErr2("if(!__CSU) ");
        return;
    }
    CLAN_MSG msg=( CLAN_MSG)_msg;
    switch (msg)
    {
    case __TYPE_SEND_HTTP_REQUEST:
        on_TYPE_SEND_HTTP_REQUEST(__CSU,b);
        break;
    case __TYPE_NOTIFY_USER_LOGGED_IN:
    {
        DB_id uid;
        b>>uid;
        {
            PGLW(chat_clan,c,__CSU);
            c->local_users.insert(uid);
        }
        map<G_session, PTR_getter<chat_clan> > m=chat_clans.get_container();
        for (typeof(m.begin())i=m.begin();i!=m.end();i++)
        {
            if (i->first!=app_data)
            {
                out_oscar_buffer bb;
                bb<<uid;
                reply_chat_clan(i->second,__TYPE_NOTIFY_USER_LOGGED_IN,bb);

            }
        }
        PTR_getter<chat_user> __U=local_users.get(uid);
        if (__U)
        {
            {
                PGLW(chat_user,u,__U);
                u->erased=true;
            }
            local_users.erase(uid);
        }


    }break;
    case __TYPE_NOTIFY_USER_LOGGED_OUT:
    {
        DB_id uid;
        b>>uid;
        {
            PGLW(chat_clan,c,__CSU);
            c->local_users.erase(uid);
        }
        map<G_session, PTR_getter<chat_clan> > m=chat_clans.get_container();
        for (typeof(m.begin())i=m.begin();i!=m.end();i++)
        {
            if (i->first!=app_data)
            {
                out_oscar_buffer bb;
                bb<<uid;
                reply_chat_clan(i->second,__TYPE_NOTIFY_USER_LOGGED_OUT,bb);

            }
        }

    }break;
    case __TYPE_REGISTER_ALL_NICKS:
    {
        DB_id uid;
        b>>uid;
        user_register_all_nicks(uid,false);
        map<G_session, PTR_getter<chat_clan> > m=chat_clans.get_container();
        for (typeof(m.begin())i=m.begin();i!=m.end();i++)
        {
            if (i->first!=app_data)
            {
                out_oscar_buffer bb;
                bb<<uid;
                reply_chat_clan(i->second,__TYPE_REGISTER_ALL_NICKS,bb);

            }
        }

    }break;
    case __TYPE_UNREGISTER_ALL_NICKS:
    {
        DB_id uid;
        b>>uid;
        user_unregister_all_nicks(uid,false);
        map<G_session, PTR_getter<chat_clan> > m=chat_clans.get_container();
        for (typeof(m.begin())i=m.begin();i!=m.end();i++)
        {
            if (i->first!=app_data)
            {
                out_oscar_buffer bb;
                bb<<uid;
                reply_chat_clan(i->second,__TYPE_UNREGISTER_ALL_NICKS,bb);

            }
        }

    }break;
    case __TYPE_UNREGISTER_1_NICKS:
    {
        string n;
        b>>n;
        user_unregister_1_nick(n,false);

        map<G_session, PTR_getter<chat_clan> > m=chat_clans.get_container();
        for (typeof(m.begin())i=m.begin();i!=m.end();i++)
        {
            if (i->first!=app_data)
            {
                out_oscar_buffer bb;
                bb<<n;
                reply_chat_clan(i->second,__TYPE_UNREGISTER_1_NICKS,bb);

            }
        }


    }break;
    case __TYPE_SEND_CHAT_DATA_TO_CS_ONLY:
    {
        string cmd;
        b>>cmd;
        update_commands.push_back(cmd);
    }break;
    case __TYPE_SEND_CHAT_DATA:
    {
        string cmd;
        b>>cmd;
        map<G_session, PTR_getter<chat_clan> > m=chat_clans.get_container();
        for (typeof(m.begin())i=m.begin();i!=m.end();i++)
        {
            if (i->first!=app_data)
            {
                out_oscar_buffer bb;
                bb<<cmd;
                reply_chat_clan(i->second,__TYPE_SEND_CHAT_DATA,bb);

            }
        }

        update_commands.push_back(cmd);

    }break;
    case __TYPE_SEND_CHAT_EVENT:
    {
        int etype;
        b>>etype;
        chat_event *e=NULL;
        switch (etype)
        {
        case chat_event::INVITE			 :
            e=new chat_event_INVITE;
            break;
        case chat_event::CHMODE                  :
            e=new chat_event_CHMODE;
            break;
        case chat_event::CHVOICE                 :
            e=new chat_event_CHVOICE;
            break;
        case chat_event::CHAT_MESSAGES           :
            e=new chat_event_CHAT_MESSAGES;
            break;
        case chat_event::SEND_MESSAGE            :
            e=new chat_event_SEND_MESSAGE;
            break;
        case chat_event::SET_USER_STATE          :
            e=new chat_event_SET_USER_STATE;
            break;
        case chat_event::SEND_DATA_TO_WWW_USERS  :
            e=new chat_event_SEND_DATA_TO_WWW_USERS;
            break;
        case chat_event::CHTOPIC                 :
            e=new chat_event_CHTOPIC;
            break;
        case chat_event::UPDATE_DATA             :
            e=new chat_event_UPDATE_DATA;
            break;
        case chat_event::UPDATE_USER_SESSION     :
            e=new chat_event_UPDATE_USER_SESSION;
            break;
        case chat_event::__IGNORE                  :
            e=new chat_event_IGNORE;
            break;
        default:
            logErr2("INVALID event type %s","");
        }
        if (e)
        {
            e->unpack(b);
            map<G_session, PTR_getter<chat_clan> > m=chat_clans.get_container();
            for (typeof(m.begin())i=m.begin();i!=m.end();i++)
            {
                if (i->first!=app_data)
                {
                    out_oscar_buffer bb;
                    bb<<e->type;
                    e->pack(bb);
                    reply_chat_clan(i->second,__TYPE_SEND_CHAT_EVENT,bb);

                }
            }
            __chat_events.push_back(e);
        }

    }
    break;
    default:
        logErr2("undefined CLAN_MSG 0x%x",msg);
        {

        }
    }

}
bool process_request_tusa_clan(const G_session& app_data, const PTR_getter<session_data> &__SD, oscar_buffer& b,int msg,  int req_id, out_oscar_buffer& bb)
{
    PTR_getter<chat_clan> __CSU=chat_clans.find(app_data);
    if (!__CSU)
    {
        logErr2("if(!__CSU) ");
        return false;
    }
    switch (msg)
    {
    case DR_get_attach:
    {
        DB_id uid;
        int msgid;
        string attfn;
        b>>uid>>msgid>>attfn;
        string fn=attach_pn(uid,msgid,attfn);
        string body;
        int r=load_1_file(body,fn);
        bb<<body;


    } break;
    case DR_get_foto:
    {
        DB_id uid;
        int pid;
        string ext;
        int xsz;
        b>>uid>>pid>>ext>>xsz;
        string fc=foto_pn_cache(uid,pid, xsz,ext);
        check_scaled_foto(uid,pid,ext,xsz);
        string body;
        int r=load_1_file(body,fc);
        bb<<body;
    }break;
    case DR_get_user_states:
    {
        int rid=req_id;
        chat_event_SEND_USER_STATES *e=new chat_event_SEND_USER_STATES(rid,msg,__SD);
        __chat_events.push_back(e);
        return false;
    }
    break;
    case DR_get_g_session:
    {
        bb<<app_data;
    }
    break;
    case DR_load_news:
        pack_news(bb);
        break;
    case DR_load_hints:
        pack_hints(bb);
        break;
    case DR_get_uid_time_cnt_descr_from_banned_login_by_uid:
    {
        DB_id uid;
        b>>uid;
        vector<string>v=get_uid_time_cnt_descr_from_banned_login_by_uid(uid);
        bb<<v;
    }break;
    case DR_get_pass_by_nick:
    {
        string n;
        b>>n;
        pair<string,DB_id> p=get_pass_by_nick(n);
        bb<<p;
    }break;
    case DR_get_id_uid_nick_by_nick:
    {
        string to_nick;
        b>>to_nick;
        bb<<get_id_uid_nick_by_nick(to_nick);
    }break;
    case DR_login_io:
    {
        string l,p;
        b>>l>>p;
        bb<<login_io(l,p);
    }break;
    case DR_register_io:
    {
        map<string,string> p;
        b>>p;
        bb<<register_io(p);
    }break;
    case DR_load_levels:
        pack_levels(bb);
        break;
    case DR_note_text:
    {
        string id;
        b>>id;
        {
            PGLR(note_text,u,note_texts.find_by_id(id));
            u->pack(bb);

        }
    }break;
    case DR_check_for_ipban:
    {
        string ip,proxyip;
        b>>ip>>proxyip;
        bb<<check_for_ipban(ip,proxyip);
    }break;
    case DR_do_nickban:
    {
        string nick_orig;
        DB_id id;
        unsigned int level;
        b>>nick_orig>>id>>level;
        bb<<do_nickban(nick_orig,id,level);

    }break;
    case DR_do_loginban:
    {
        DB_id zuid;
        string descr;
        time_t t;
        DB_id adm_uid;
        unsigned int level;
        b>>zuid>>descr>>t>>adm_uid>>level;
        bb<<do_loginban(zuid,descr,t,adm_uid,level);
    }break;
    case DR_do_ipban:
    {
        string ip_orig,proxy_orig;
        time_t t;
        DB_id id;
        b>>ip_orig>>proxy_orig>>t>>id;
        bb<<do_ipban(ip_orig,proxy_orig,t,id);

    }break;

    case DR_get_users_counts:
    {
        time_t t,rt;
        b>>t>>rt;

        bb<<get_users_counts(t,rt);
    }break;
    case DR_calc_statistic:
    {
        bb<<chat_stat.get_container();

    }break;
    case DR_get_uid_by_nick:
    {
        string nick;
        b>>nick;

        bb<<get_uid_by_nick(nick);

    }break;
    case DR_select_uid_nick_by_ids:
    {
        DB_id uid;
        unsigned int nid;
        b>>uid>>nid;

        bb<<select_uid_nick_by_ids(uid,nid);


    }break;
    case DR_gallery_request:
    {
        string snick;
        b>>snick;
        bb<<gallery_request(snick);

    }break;
    case DR_load_channels:
    {
        vector<CH_id>chs=chat_channels.keys();
        bb<<chs.size();
        for (unsigned int i=0;i<chs.size();i++) {
            __CH_LOCK(chat_channels[chs[i]]);
            bb<<CH->cd;
        }
    }
    break;
    case DR_nick_vec:
    case DR_u_notes:
    case DR_user_stat:
    case DR_user_profile:
    case DR_user_set:
    case DR_user_fotos:
    case DR_ignore_vec:
    case DR_contact_vec:
    case DR_user_credit:
    {
        DB_id uid;
        b>>uid;



        switch (msg)
        {
        case DR_user_credit:
        {
            PGLR(user_credit,u,user_credits.find_by_id(uid));
            u->pack(bb);
        }break;
        case DR_u_notes:
        {
            PGLR(u_notes,u,__notes.find_by_id(uid));
            u->pack(bb);
        }break;
        case DR_nick_vec:
        {
            PGLR(nick_vec,u,nick_vecs.find_by_id(uid));
            u->pack(bb);
        }break;
        case DR_user_stat:
        {
            PGLR(user_stat,u,user_stats.find_by_id(uid));
            u->pack(bb);
        }break;
        case DR_user_profile:
        {
            PGLR(user_profile,u,user_profiles.find_by_id(uid));
            u->pack(bb);
        }break;
        case DR_user_set:
        {
            PGLR(user_set,u,user_sets.find_by_id(uid));
            u->pack(bb);
        }break;
        case DR_user_fotos:
        {
            PGLR(user_fotos,u,users_fotos.find_by_id(uid));
            u->pack(bb);
        }break;
        case DR_ignore_vec:
        {
            PGLR(ignore_vec,u,ignore_vecs.find_by_id(uid));
            u->pack(bb);
        }break;
        case DR_contact_vec:
        {
            PGLR(contact_vec,u,contact_vecs.find_by_id(uid));
            u->pack(bb);
        }break;
        default :
            logErr2("--Error: invalid reqtype %d",msg);
        }


    }break;
    default:
        logErr2("--Error: invalid reqtype %d",msg);
        break;
    }
    return true;
}
extern M_MAP<DB_id,user_state> global_states;
bool do_application_login_tusa_clan(const G_session &g_sess, const PTR_getter<session_data> &__SD,const string& ip,map<string,string> &m)
{
    st_dbh d;
    vector<string> v=d.dbh->select_1_rowQ((QUERY)"select pass, has_clan from user_profiles where login='?'"<<m["login"]);
    bool login_ok=false;
    bool has_clan=false;
    if (v.size()==2)
    {
        if (bin2hex(MD5(m["pass"]),0)==v[0])
            login_ok=true;
        has_clan=atoi(v[1]);
    }
    chat_clan *ccl=new chat_clan;
    ccl->session_id=g_sess;
    ccl->session=__SD;
    if (login_ok)
    {
        ccl->login=m["login"];
        ccl->login_ok=login_ok;
    }
    ccl->ip=ip;
    ccl->login_time=time(NULL);
    ccl->has_clan=has_clan;
    PTR_getter<chat_clan> pccl(ccl);
    chat_clans.insert(g_sess,pccl);
    map<string,string> mm=m;
    mm.erase("pass");
    mm.erase("client_type");
    mm["login_ok"]=itostring(login_ok);
    mm["has_clan"]=itostring(has_clan);
    mm["SV"]=SERVER_VERSION_INT;
    {

        central_server::reply_login_ok(__SD,mm);


    }
    if (0)// Invalid login
    {
        central_server::reply_login_failed(__SD,mm);

        return false;

    }
    {
        map<DB_id,user_state> gu=global_states.get_container();
        {
            out_oscar_buffer b;
            b<<TSD_levels;
            pack_levels(b);
            reply_chat_clan(pccl,__TYPE_SET_DATA,b);
        }
        {
            out_oscar_buffer b;
            b<<TSD_channels;
            pack_channels(b);
            reply_chat_clan(pccl,__TYPE_SET_DATA,b);
        }
        {
            out_oscar_buffer b;
            b<<TSD_hints;
            pack_hints(b);
            reply_chat_clan(pccl,__TYPE_SET_DATA,b);
        }
        {
            out_oscar_buffer b;
            b<<TSD_news;
            pack_news(b);
            reply_chat_clan(pccl,__TYPE_SET_DATA,b);
        }
        {
            out_oscar_buffer b;
            b<<TSD_chat_config2;
            chat_config2.pack(b);
            reply_chat_clan(pccl,__TYPE_SET_DATA,b);
        }

        for (typeof(gu.begin())i=gu.begin();i!=gu.end();i++)
        {
            {
                out_oscar_buffer b;
                b<<TSD_user_profile<<i->first;
                {
                    PGLR(user_profile,u,user_profiles.find_by_id(i->first));
                    u->pack(b);
                }
                reply_chat_clan(pccl,__TYPE_SET_DATA,b);

            }
            {
                out_oscar_buffer b;
                b<<TSD_user_set<<i->first;
                {
                    PGLR(user_set,u,user_sets.find_by_id(i->first));
                    u->pack(b);
                }
                reply_chat_clan(pccl,__TYPE_SET_DATA,b);
            }
            {
                out_oscar_buffer b;
                b<<TSD_user_stat<<i->first;
                {
                    PGLR(user_stat,u,user_stats.find_by_id(i->first));
                    u->pack(b);
                }
                reply_chat_clan(pccl,__TYPE_SET_DATA,b);
            }
            {
                out_oscar_buffer b;
                b<<TSD_nick_vec<<i->first;
                {
                    PGLR(nick_vec,u,nick_vecs.find_by_id(i->first));
                    u->pack(b);
                }
                reply_chat_clan(pccl,__TYPE_SET_DATA,b);
            }
            {
                out_oscar_buffer b;
                b<<TSD_ignore_vec<<i->first;
                {
                    PGLR(ignore_vec,u,ignore_vecs.find_by_id(i->first));
                    u->pack(b);
                }
                reply_chat_clan(pccl,__TYPE_SET_DATA,b);
            }
            {
                out_oscar_buffer b;
                b<<TSD_contact_vec<<i->first;
                {
                    PGLR(contact_vec,u,contact_vecs.find_by_id(i->first));
                    u->pack(b);
                }
                reply_chat_clan(pccl,__TYPE_SET_DATA,b);
            }
            {
                out_oscar_buffer b;
                b<<TSD_user_fotos<<i->first;
                {
                    PGLR(user_fotos,u,users_fotos.find_by_id(i->first));
                    u->pack(b);
                }
                reply_chat_clan(pccl,__TYPE_SET_DATA,b);
            }
            {
                out_oscar_buffer b;
                b<<TSD_user_state<<i->first<<i->second;
                reply_chat_clan(pccl,__TYPE_SET_DATA,b);
            }


        }
    }
    return true;
}
string do_adminfo_tusa_clan()
{

    string out;
    //    out += "Currently " + itostring(fm_users.size()) + " online fm users\n";
    return out;
}
void on_iterate_tusa_clan(map<string,string>& m)
{
    try {

    }
    catch (cError e) {
        logErr2("cError: %s",e.what());
    }catch (...) {
        logErr2("unknown exteption: ");
    }
}
void load_config_tusa_clan(const string &s)
{
    load_app_configuration();
}


app_interface iface_tusa_clan[]=
{
    {2,
        on_delete_session_tusa_clan,
        do_application_login_tusa_clan,
        do_adminfo_tusa_clan,
        on_iterate_tusa_clan,
        load_config_tusa_clan,
        init_tusa_clan,
        process_data_event_tusa_clan,
        process_request_tusa_clan
    },
    {-1}
};
void add_handler(app_interface* iface);

void add_handler_tusa_clan()
{
    add_handler(iface_tusa_clan);
}
chat_clan::chat_clan(): base_container("chat_clan"),session(NULL),clan_id(0)
{

}
