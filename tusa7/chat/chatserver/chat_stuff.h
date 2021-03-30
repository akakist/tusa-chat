#ifndef CHAT_STUFFFF___HH
#define CHAT_STUFFFF___HH


#include "chat_channel_data.h"
#include "PTR.h"
#define ACCEPT_ALL_PUB 1
#define ACCEPT_ALL_PRIV 2
#define ACCEPT_PRIV_CONTACT 4
#define ACCEPT_ALL_CONTACT 8

class c_level;
struct chat_stuff_user
{
    DB_id dbid;

    set<DB_id> ignores;
    set<DB_id> contacts;
    unsigned char gender;
    string ip,pip;
    int invisibility;
    int bought_invisibility;
    user_state cstate;
    string nickstyle;

    unsigned int level;
    c_level clevel;


    bool setting_show_eye;
    string city;

    int neye;
    int lpp;
    string b_day;
    int b_mon;
    bool hide_bdate;
    unsigned int n_color_pack;
    unsigned char user_type;
    string login;
    unsigned int privileges;
    unsigned int db_privileges;
    unsigned int contact_options;


    bool ul_mode_contacts_only;
    bool ul_mode_hide_male;
    bool ul_mode_hide_female;

    map<unsigned int, string> str_nicks;

    //tmp
    time_t last_m_time;
    string last_message;// not need to init

    time_t last_invite_time;
    int msg_cnt_per_time;



    bool I_can_see(const chat_stuff_user &zz);
    chat_stuff_user():user_type((unsigned char)-1),last_m_time(0)
    {
    }

};
out_oscar_buffer & operator<<(out_oscar_buffer&b, const chat_stuff_user &n);
oscar_buffer & operator>>(oscar_buffer&b, chat_stuff_user &n);

struct chat_stuff_user_p:public base_container_nm, public chat_stuff_user
{
    chat_stuff_user ud;
};
class chat_channel_data;
struct c_set
{
    map<DB_id/*user*/,pair<PTR_getter_nm<chat_stuff_user_p>, map<DB_id/*visible for*/,PTR_getter_nm<chat_stuff_user_p> > > > u_list;
    chat_channel_data cd;

};
out_oscar_buffer & operator<<(out_oscar_buffer&b, const c_set &n);
oscar_buffer & operator>>(oscar_buffer&b, c_set &n);

struct chat_thread_stuff
{
    deque<PTR_getter_nm<chat_msg> > messages;
    deque<PTR_getter_nm<chat_msg> > backup_messages;
    map<CH_id,c_set> channels;
    map<DB_id,PTR_getter_nm<chat_stuff_user_p> > users;
    map<string, PTR_getter_nm<chat_stuff_user_p> > strnick2__u;
    string to_all;
    map<DB_id,time_t> join_time;
    map<DB_id,time_t> trash;
};
out_oscar_buffer & operator<<(out_oscar_buffer&b, const chat_thread_stuff &n);
oscar_buffer & operator>>(oscar_buffer&b, chat_thread_stuff &n);

void send_chat_msg(chat_msg$ *e,chat_thread_stuff& stuff);



#endif
