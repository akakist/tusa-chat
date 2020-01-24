#ifndef CHAT_USER_H__
#define CHAT_USER_H__
#include "_mutex.h"
#include <time.h>
#include <list>
#include "levels.h"
#include <map>
#include "message.h"
#include <set>
#include "oscar_buffer.h"
#include "DB_id.h"
#include "CH_id.h"
#include "S_id.h"

#define u_is_forum_admin	2
#define u_allow_view_logs	4
#define u_is_settings_admin	8
#define u_is_funny_admin	16

#define u_is_vote_admin		64
#define u_is_privs_admin	128
#define u_is_accounts_admin	256
#define u_is_hints_admin	512
#define u_is_news_admin		1024

#define u_allow_set_topic	(1024*4)

#define u_allow_tags		(1024*8)
#define u_is_advertizer_admin	(1024*16)
#define u_is_smiles_admin	(1024*32)
#define u_is_credit_operator	(1024*64)
#define u_is_photo_admin		(1024*128)


#include "user_nick.h"
#include "user_status.h"
#include "user_state.h"
#include "nick_vec.h"
#include "user_profile.h"
#include "user_set.h"
#include "c_conn.h"
class app_server;

class irc_connection;
struct u_notes;
struct u_fotos;


bool user_privs(int p,int wh);
class sms_chat_user;
class user_nick;
struct user_status;
class user_state;


class user_profile;
class user_set;
class user_stat;
class nick_vec;
class user_fotos;
struct _chat_user
{

};
enum
{
    TYPE_UNKNOWN,
    TYPE_WWW=1,
    TYPE_IRC=2
};
struct chat_user$
{
    bool erased;
    time_t last_change_nick;
    time_t last_m_time;
    time_t last_access_time;	// last access time (last http_request)
    time_t login_date;
    time_t last_pincode_entered;
    string cu_ip;
    string ua;

    unsigned char user_type;
    time_t create_time;
    DB_id db_id;

    chat_user$();
    ~chat_user$();

};
struct www_chat_user$
{
    unsigned int www_data_send_count;
    time_t www_last_send_time; /* last data_push_back time & send used
					for send \r\n for keep concurrent connection*/
    string www_cookie;
public:
    string www_push_buffer;
    bool www_unregistered;	//login without registration
    bool www_offline_status_sent;
    time_t www_offline_time;
    bool www_inchat;
    string www_proxy_ip;
    string www_screen_resolution;	// screen resolution  scr
    user_state cstate;
    www_chat_user$();

};

class chat_user: public base_container, public chat_user$, public www_chat_user$
{

public:
//	PTR_getter<c_socket>  www_socket;
//	PTR_getter<c_socket>  irc_socket;
    PTR_getter<c_socket>  psocket;
    chat_user(int t);



    PTR_getter<user_profile> __user_profile;
    PTR_getter<user_set> __user_set;
    virtual ~chat_user();
};

class user_profile;
class user_set;
class user_stat;
class nick_vec;
struct user_pair
{
    PTR_getter<chat_user> cu;
    PTR_getter<user_profile> up;
    PTR_getter<user_set> us;
    DB_id uid;

    explicit user_pair(const PTR_getter<chat_user> &CU);
};
class chat_users_container
{

    _mutex Mutex;
    map<DB_id,PTR_getter<chat_user> > container;
public:

    void insert(const PTR_getter<chat_user> &p);
    PTR_getter<chat_user> get(const DB_id& uid);
    PTR_getter<chat_user> get_throw(const DB_id& uid);
    vector<PTR_getter<chat_user> > values();
    size_t size();
    size_t count(const DB_id& zid);
    size_t count(const PTR_getter<chat_user> &);
    void erase(const DB_id& uid);
    void clean();
    chat_users_container():Mutex("chat_users_container") {}
};
class cookie_2_session_id
{
    _mutex Mutex;
    map<string,pair<DB_id, time_t> > container;
public:
    cookie_2_session_id():Mutex("cookie_2_session_id") {}
    DB_id get(const string &s);
    void set(const string& s, const DB_id&);
    void clean();
    void erase(const string&s);
    vector<string> keys();
};
extern cookie_2_session_id __cookie_2_session_id;
extern chat_users_container local_users;



#define __UC_LOCK PGLW(chat_user, u,__U.cu);
#define __ZC_LOCK PGLW(chat_user, z,__Z.cu);
#define __UC_LOCKW PGLW(chat_user, u,__U.cu);
#define __ZC_LOCKW PGLW(chat_user, z,__Z.cu);

#define __S_LOCK PGLW(c_socket, s,__S);

bool inchat$(const PTR_getter<chat_user> &__U);
bool is_inv(const user_pair&);
bool user__connection_is_active(const user_pair&__U);
bool user$erased(const user_pair& __U);
bool user$ignored(const user_pair& __U, const DB_id& id);

bool user$nick_entered(const user_pair& __U);
class chat_message;
struct user_pair;

int has_inv(const user_pair& __U);
int user$gender(const user_pair& __U);
int user$get_spent_time(const user_pair& __U);
int user$lpp(const user_pair&__U);
int user$neye(const user_pair&__U);
int user$privileges(const user_pair& __U);

int user$vote_balls(const user_pair&__U);
string build_nicks_select(const user_pair& __U,const string &name,const string & defnick,const string &addp);
string build_nicks_select(const user_pair& __U,const string &name,int def,const string &addp);
string build_nicks_select(unsigned int uid,const string &name,const string & defnick,const string &addp);
string build_nicks_select(unsigned int uid,const string &name,int def,const string &addp);
string get_full_name(const user_pair&);
hstring make_user_info(const DB_id& zid,const DB_id& uid, bool admin,bool iu,string irc_host,string cnick, bool logined);
string user$fname(const user_pair&__U);
string user$ip(const user_pair& __U);
string user$lname(const user_pair&__U);
string user$login(const user_pair& __U);
string user$login(const DB_id& uid);
string user$pass(const user_pair& __U);
string user$proxy_ip(const user_pair& __U);
struct user_status;
set<CH_id> user$channel(const user_pair& __U);

DB_id user$id(const user_pair& __U);
DB_id user$id(const PTR_getter<chat_user>& __U);
unsigned int user$level(const user_pair& __U);
unsigned int user$max_msg_len(const user_pair&__U);
unsigned int user$max_nick_count(const user_pair&__U);
unsigned int user$n_color_pack(const user_pair&__U);
unsigned int user$nicks_size(const user_pair&__U);
unsigned int user$nicks_size(unsigned int uid);

user_state get_user_state(const user_pair &__U);
user_status get_user_status_by_id(const user_pair&__U, int id);
void set_user_state(const out_oscar_buffer &s);

class chat_channel;


void data_push_back(const PTR_getter<chat_user>&,const string&);
void data_push_back(const user_pair&,const string&);

void kick_user(const DB_id &uid,const string &msgs);

void send_syspriv_msg(const user_pair&__U,const string &s);
void send_syspriv_msg(const PTR_getter<chat_user>&__U,const string &s);
void SET_PASS(const user_pair&__U,const string& s);
void _unset(db_var<unsigned int> &s, unsigned int n);
void user$add_ignore(const user_pair& __U, const DB_id& id);
void user_destroy(const PTR_getter<chat_user> &__UU);
void user_exit_chat(const PTR_getter<chat_user> &__UU,bool killed);
bool can_write_diskspace(const user_pair& __U, int space);
void user_register_all_nicks(const DB_id&, bool broadcast);
void user_unregister_all_nicks(const DB_id&, bool broadcast);
void user_unregister_1_nick(const string & nick, bool broadcast);
void user$remove_ignore(const user_pair& __U, const DB_id& id);
void broadcast_user_logged_in(const DB_id&);
void broadcast_user_logged_out(const DB_id&);

bool can_add_nick(const user_pair &__U);
bool do_change_mode(PTR_getter<chat_channel> &ML,const PTR_getter<chat_user> &__UU,int mode);
bool do_change_voice(const CH_id &ch,const DB_id &uid,string nick, int voice);
bool u_has_console(const user_pair& __U);
bool I_can_see(const PTR_getter<chat_user>__U,const PTR_getter<chat_user>__Z);



#define MB (1024*1024)
#define KB (1024)

#endif
