#include "stdafx.h"
#include <string>
using namespace std;
#include "oscar_buffer.h"
#include "DB_id.h"
#include "update_cmd.h"
#include "user.h"
#include "M_DEQUE.h"
#include "user_stat.h"
#include "chat_thread_event.h"
#include "ignore_vec.h"
#include "channels.h"
#include "fotos.h"
#include "copy_file.h"
#include "st_stuff.h"
#include "utils.h"
#include "user_credits.h"
#include "contact_vec.h"
#include "notes.h"
#include "RTYPES_CLAN.h"
#ifndef __CLAN
#endif
#include <math.h>
void  log_start_thread(const std::string &n);
#ifdef DEBUG
string get_update_code(int cmd);
#endif

M_DEQUE<string> update_commands;
#ifdef __CLAN
M_DEQUE<string> update_commands_cs;
M_DEQUE<string> update_commands_cs_only;
#else
M_DEQUE<string> update_commands_clans;
#endif
string attach_pn(const DB_id&  uid,unsigned int msgid, const string& orig);
void note_resort(const DB_id &uid);
void foto_rm_cache(const DB_id& uid,unsigned int pid);
#ifdef __CLAN
void send_packet_to_cs(bool immed,CLAN_MSG,const out_oscar_buffer & b);
#endif
int calc_photo_rating(const map<DB_id,int> &m);

void process_update_command(const string& cmd)
{
#ifdef __CLAN

    update_commands_cs.push_back(cmd);

#else
    update_commands_clans.push_back(cmd);
#endif

    update_commands.push_back(cmd);
}
void process_update_command_cs_only(const string& cmd)
{
#ifdef __CLAN
    update_commands_cs_only.push_back(cmd);
#endif
    update_commands.push_back(cmd);
}
#ifdef DEBUG
#ifdef __CLAN
void update_log(const  UCMD &cmd)
{


}
#endif
#endif
void send_update_g3(const  UCMD &cmd,unsigned int id, unsigned int v)
{
#ifdef DEBUG
#ifdef __CLAN
    DBG(update_log(cmd));
#endif
#endif
    out_oscar_buffer o;
    o<<cmd<<id<<v;
    process_update_command(o.as_string());
}
void send_update_g3(const  UCMD &cmd,unsigned int id, const string &v)
{
#ifdef DEBUG
#ifdef __CLAN
    DBG(update_log(cmd));
#endif
#endif
    out_oscar_buffer o;
    o<<cmd<<id<<v;
    process_update_command(o.as_string());

}
void send_update_g2(const  UCMD &cmd,unsigned int id)
{
#ifdef DEBUG
#ifdef __CLAN
    DBG(update_log(cmd));
#endif
#endif
    out_oscar_buffer o;
    o<<cmd<<id;
    process_update_command(o.as_string());

}
void send_update_g4(UCMD const& a, DB_id const& b, unsigned int c, int d)
{
#ifdef DEBUG
#ifdef __CLAN
    DBG(update_log(a));
#endif
#endif
    out_oscar_buffer o;
    o<<a<<b<<c<<d;
    process_update_command(o.as_string());

}
void send_update_g4(const  UCMD &cmd,unsigned int id, unsigned int status_id,const user_status &s)
{
#ifdef DEBUG
#ifdef __CLAN
    DBG(update_log(cmd));
#endif
#endif
    out_oscar_buffer o;
    o<<cmd<<status_id<<s;
    process_update_command(o.as_string());

}

void send_update_g3(const  UCMD &cmd,const DB_id& id, unsigned int v)
{
#ifdef DEBUG
#ifdef __CLAN
    DBG(update_log(cmd));
#endif
#endif
    out_oscar_buffer o;
    o<<cmd<<id<<v;
    process_update_command(o.as_string());

}
void send_update_g3(const  UCMD &cmd,const DB_id& id, const string &v)
{
#ifdef DEBUG
#ifdef __CLAN
    DBG(update_log(cmd));
#endif
#endif
    out_oscar_buffer o;
    o<<cmd<<id<<v;
    process_update_command(o.as_string());
}
void send_update_g2(const  UCMD &cmd,const DB_id& id)
{
#ifdef DEBUG
#ifdef __CLAN
    DBG(update_log(cmd));
#endif
#endif
    out_oscar_buffer o;
    o<<cmd<<id;
    process_update_command(o.as_string());

}

void send_update_g4(const  UCMD &cmd,const DB_id& id, unsigned int status_id,const user_status &s)
{
#ifdef DEBUG
#ifdef __CLAN
    DBG(update_log(cmd));
#endif
#endif
    out_oscar_buffer o;
    o<<cmd<<id<<status_id<<s;
    process_update_command(o.as_string());

}
void send_update_g4(const  UCMD &cmd,const DB_id &id, unsigned int n,const string& s)
{
#ifdef DEBUG
#ifdef __CLAN
    DBG(update_log(cmd));
#endif
#endif
    out_oscar_buffer o;
    o<<cmd<<id<<n<<s;
    process_update_command(o.as_string());

}
void send_update_g4(const  UCMD &cmd,unsigned int id, unsigned int n,const string& s)
{
#ifdef DEBUG
#ifdef __CLAN
    DBG(update_log(cmd));
#endif
#endif
    out_oscar_buffer o;
    o<<cmd<<id<<n<<s;
    process_update_command(o.as_string());

}
void send_update_g2(const  UCMD &cmd,const out_oscar_buffer &s)
{
#ifdef DEBUG
#ifdef __CLAN
    DBG(update_log(cmd));
#endif
#endif
    out_oscar_buffer o;
    o<<cmd;
    o.Pack((char*)s.const_data(),s.size());
    process_update_command(o.as_string());

}
void send_update_g2_cs_only(const  UCMD &cmd,const out_oscar_buffer &s)
{
#ifdef DEBUG
#ifdef __CLAN
    DBG(update_log(cmd));
#endif
#endif
    out_oscar_buffer o;
    o<<cmd;
    o.Pack((char*)s.const_data(),s.size());
    process_update_command_cs_only(o.as_string());

}
void send_update_d3(const  UCMD &cmd,const DB_id& id, const double &v)
{
#ifdef DEBUG
#ifdef __CLAN
    DBG(update_log(cmd));
#endif
#endif
    char s[200];
    snprintf(s,sizeof(s),"%f",v);
    out_oscar_buffer o;
    o<<cmd<<id<<s;
    process_update_command(o.as_string());

}
void send_update_d4(const  UCMD &cmd,const DB_id& id, unsigned int n,const double &v)
{
#ifdef DEBUG
#ifdef __CLAN
    DBG(update_log(cmd));
#endif
#endif
    char s[200];
    snprintf(s,sizeof(s),"%f",v);
    out_oscar_buffer o;
    o<<cmd<<id<<n<<s;
    process_update_command(o.as_string());

}
void send_update_d3(const  UCMD &cmd,unsigned int id, const double &v)
{
#ifdef DEBUG
#ifdef __CLAN
    DBG(update_log(cmd));
#endif
#endif
    char s[200];
    snprintf(s,sizeof(s),"%f",v);
    out_oscar_buffer o;
    o<<cmd<<id<<s;
    process_update_command(o.as_string());

}
#ifdef DEBUG
string get_update_code(int cmd)
{
    map <int,string>m;
    m[user_stat$last_date]="user_stat$last_date";
    m[user_stat$last_ip]="user_stat$last_ip";
    m[user_stat$last_pip]="user_stat$last_pip";
    m[user_stat$inc_v_count]="user_stat$inc_v_count";
    m[user_stat$inc_m_count]="user_stat$inc_m_count";
    m[user_stat$add_t_count]="user_stat$add_t_count";
    m[user_stat$inc_kick_count]="user_stat$inc_kick_count";
    m[user_stat$inc_kicked_count]="user_stat$inc_kicked_count";
    m[user_profile$pass]="user_profile$pass";
    m[user_profile$level]="user_profile$level";
    m[user_profile$db_privileges]="user_profile$db_privileges";

    m[user_profile$vote_balls]="user_profile$vote_balls";
    m[user_profile$login]="user_profile$login";
    m[user_profile$fname]="user_profile$fname";
    m[user_profile$lname]="user_profile$lname";
    m[user_profile$b_day]="user_profile$b_day";
    m[user_profile$b_mon]="user_profile$b_mon";
    m[user_profile$b_year]="user_profile$b_year";
    m[user_profile$city]="user_profile$city";
    m[user_profile$homepage]="user_profile$homepage";
    m[user_profile$email]="user_profile$email";
    m[user_profile$icq]="user_profile$icq";
    m[user_profile$tel]="user_profile$tel";
    m[user_profile$info]="user_profile$info";
    m[user_profile$reg_date]="user_profile$reg_date";
    m[user_set$poweshen]="user_set$poweshen";

    m[contact$add]="contact$add";
    m[contact$remove]="contact$remove";
    m[user_profile$gender]="user_profile$gender";
    m[user_set$neye]="user_set$neye";
    m[user_set$notes_save_copy]="user_set$notes_save_copy";
    m[user_set$notes_msg_per_page]="user_set$notes_msg_per_page";
    m[user_set$notes_sort]="user_set$notes_sort";
    m[user_set$notes_sort_desc]="user_set$notes_sort_desc";
    m[user_set$n_color_pack]="user_set$n_color_pack";
    m[user_set$setting_autochange]="user_set$setting_autochange";
    m[user_set$setting_show_eye]="user_set$setting_show_eye";
    m[user_set$setting_show_hints]="user_set$setting_show_hints";
    m[user_set$show_credits]="user_set$show_credits";
    m[user_set$setting_show_stat]="user_set$setting_show_stat";
    m[user_set$setting_invite_sound]="user_set$setting_invite_sound";
    m[user_set$setting_full_buttons]="user_set$setting_full_buttons";
    m[user_set$hide_fname]="user_set$hide_fname";
    m[user_set$hide_lname]="user_set$hide_lname";
    m[user_set$hide_bdate]="user_set$hide_bdate";
    m[user_set$hide_tel]="user_set$hide_tel";
    m[user_set$hide_email]="user_set$hide_email";
    m[user_set$hide_icq]="user_set$hide_icq";

    m[user_set$bought_quota]="user_set$bought_quota";
    m[user_set$bought_invisibility]="user_set$bought_invisibility";
    m[user_set$contact_options]="user_set$contact_options";
    m[user_set$show_level]="user_set$show_level";
    m[user_set$show_nicks]="user_set$show_nicks";
    m[user_set$lpp]="user_set$lpp";
    m[status$add]="status$add";
    m[status$remove]="status$remove";

    m[ignore$add]="ignore$add";
    m[ignore$remove]="ignore$remove";
    m[user_set$last_nick]="user_set$last_nick";
    m[user_set$last_nick_id]="user_set$last_nick_id";
    m[user_set$last_status_id]="user_set$last_status_id";
    m[user_set$last_channel]="user_set$last_channel";
    m[channel$topic]="channel$topic";
    m[foto$remove]="foto$remove";
    m[foto$set_rate]="foto$set_rate";
    m[foto$change_description]="foto$change_description";
    m[foto$add]="foto$add";
    m[nick$add]="nick$add";
    m[nick$remove]="nick$remove";
    m[credit$set_summa]="credit$set_summa";
    m[channel_tmp$moderated]="channel_tmp$moderated";

    m[user_set$ul_mode_contacts_only]="user_set$ul_mode_contacts_only";
    m[user_set$ul_mode_hide_male]="user_set$ul_mode_hide_male";
    m[user_set$ul_mode_contacts_only]="user_set$ul_mode_contacts_only";
    m[note$set_msg]="note$set_msg";
    m[note$set_head]="note$set_head";
    m[note$folder_create]="note$folder_create";
    m[note$folder_rename]="note$folder_rename";
    m[note$folder_remove]="note$folder_remove";
    m[note$set_status]="note$set_status";
    m[note$set_unread]="note$set_unread";
    m[note$filter_out_delete]="note$filter_out_delete";
    m[note$filter_out_insert]="note$filter_out_insert";
    m[note$filter_in_delete]="note$filter_in_delete";
    m[note$filter_in_insert]="note$filter_in_insert";
    m[note$remove]="note$remove";
    m[note$move_message]="note$move_message";
    m[note$set_attachment]="note$set_attachment";
    m[nick$change_nick]="nick$change_nick";
    m[nick$change_cost]="nick$change_cost";
    if (m.count(cmd)) return m[cmd];
    else return "UNDEF";
}
#endif


void *update_processor(void *pr)
{
    log_start_thread("updater");

    while (1) {
        try {
#ifndef __CLAN
            st_dbh d;
#endif

            {
#ifdef __CLAN
                {
                    deque <string> de=update_commands_cs.extract_all();
                    for (unsigned i=0;i<de.size();i++)
                    {
                        out_oscar_buffer bb;
                        bb<<de[i];
                        send_packet_to_cs(false,__TYPE_SEND_CHAT_DATA,bb);
                    }
                }
                {
                    deque <string> de=update_commands_cs_only.extract_all();
                    for (unsigned i=0;i<de.size();i++)
                    {
                        out_oscar_buffer bb;
                        bb<<de[i];
                        send_packet_to_cs(false,__TYPE_SEND_CHAT_DATA_TO_CS_ONLY,bb);
                    }
                }
#else
                {
                    deque <string> de=update_commands_clans.extract_all();
                    for (unsigned i=0;i<de.size();i++)
                    {
                    }
                }
#endif
            }

            deque<string> de=update_commands.extract_all();
            for (unsigned i=0;i<de.size();i++)
            {
                chat_event_UPDATE_DATA *evu=new chat_event_UPDATE_DATA;
                evu->buf=de[i];
                send_chat_event(evu,false);
                oscar_buffer o(de[i].data(),de[i].size());
                int cmd;
                o>>cmd;
                switch (cmd)
                {
                case user_stat$last_date: {
                    DB_id uid;
                    time_t t;
                    o>>uid>>t;
                    PTR_getter<user_stat> p=user_stats.get(uid);
                    if (p)
                    {
                        PGLW(user_stat,u,p);
                        u->last_date=t;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_stats set last_date=FROM_UNIXTIME(?) where refid=?"<<t<<uid.container);
#endif
                }
                break;
                case user_stat$last_ip: {
                    DB_id uid;
                    string ip;
                    o>>uid>>ip;

                    PTR_getter<user_stat> p=user_stats.get(uid);
                    if (p)
                    {
                        PGLW(user_stat,u,p);
                        u->last_ip=ip;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_stats set last_ip='?' where refid=?"<<ip<<uid.container);
#endif
                }
                break;
                case user_stat$last_pip: {
                    DB_id uid;
                    string pip;
                    o>>uid>>pip;

                    PTR_getter<user_stat> p=user_stats.get(uid);
                    if (p)
                    {
                        PGLW(user_stat,u,p);
                        u->last_pip=pip;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_stats set last_pip='?' where refid=?"<<pip<<uid.container);
#endif
                }
                break;
                case user_stat$inc_v_count: {
                    DB_id uid;
                    o>>uid;

                    PTR_getter<user_stat> p=user_stats.get(uid);
                    if (p)
                    {
                        PGLW(user_stat,u,p);
                        u->v_count++;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_stats set v_count=v_count+1 where refid=?"<<uid.container);
#endif
                }
                break;
                case user_stat$inc_m_count: {
                    DB_id uid;
                    o>>uid;

                    PTR_getter<user_stat> p=user_stats.get(uid);
                    if (p)
                    {
                        PGLW(user_stat,u,p);
                        u->m_count++;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_stats set m_count=m_count+1 where refid=?"<<uid.container);
#endif
                }
                break;
                case user_stat$add_t_count: {
                    DB_id uid;
                    unsigned int tc;
                    o>>uid>>tc;

                    PTR_getter<user_stat> p=user_stats.get(uid);
                    if (p)
                    {
                        PGLW(user_stat,u,p);
                        u->t_count+=tc;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_stats set t_count=t_count+? where refid=?"<<tc<<uid.container);
#endif
                }
                break;
                case user_set$last_channel:
                {
                    DB_id uid;
                    unsigned int si;
                    o>>uid>>si;

                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->last_channel=si;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set last_channel='?' where refid=?"<<si<<uid.container);
#endif

                }break;
                case user_set$last_nick: {
                    DB_id uid;
                    string ln;
                    o>>uid>>ln;

                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->last_nick=ln;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set last_nick='?' where refid=?"<<ln<<uid.container);
#endif
                }
                break;
                case user_set$last_status_id: {
                    DB_id uid;
                    unsigned int si;
                    o>>uid>>si;

                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->last_status_id=si;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set last_status_id='?' where refid=?"<<si<<uid.container);
#endif
                }
                break;
                case user_set$last_nick_id: {
                    DB_id uid;
                    unsigned int ni;
                    o>>uid>>ni;

                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->last_nick_id=ni;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set last_nick_id='?' where refid=?"<<ni<<uid.container);
#endif
                }
                break;


                case user_stat$inc_kick_count:
                {
                    DB_id uid;
                    o>>uid;
                    PTR_getter<user_stat> p=user_stats.get(uid);
                    if (p)
                    {
                        PGLW(user_stat,u,p);
                        u->kick_count++;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_stats set kick_count=kick_count+1 where refid=?"<<uid.container);
#endif
                }break;
                case user_stat$inc_kicked_count:
                {
                    DB_id uid;
                    o>>uid;
                    PTR_getter<user_stat> p=user_stats.get(uid);
                    if (p)
                    {
                        PGLW(user_stat,u,p);
                        u->kicked_count++;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_stats set kicked_count=kicked_count+1 where refid=?"<<uid.container);
#endif
                }break;
                case user_profile$pass:
                {
                    DB_id uid;
                    string pass;
                    o>>uid>>pass;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->pass=pass;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set pass='?' where refid=?"<<pass<<uid.container);
#endif

                }break;
                case user_profile$level:
                {
                    DB_id uid;
                    int v;
                    o>>uid>>v;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->level=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set level='?' where refid=?"<<v<<uid.container);
#endif

                }break;
                case user_profile$db_privileges:
                {
                    DB_id uid;
                    int v;
                    o>>uid>>v;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->db_privileges=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set db_privileges='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_profile$vote_balls:
                {
                    DB_id uid;
                    int v;
                    o>>uid>>v;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->vote_balls=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set vote_balls='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_profile$login:
                {
                    DB_id uid;
                    string v;
                    o>>uid>>v;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->login=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set login='?' where refid=?"<<v<<uid.container);
#endif

                }break;
                case user_profile$fname:
                {
                    DB_id uid;
                    string v;
                    o>>uid>>v;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->fname=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set fname='?' where refid=?"<<v<<uid.container);
#endif

                }break;
                case user_profile$lname:
                {
                    DB_id uid;
                    string v;
                    o>>uid>>v;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->lname=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set lname='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_profile$b_day:
                {
                    DB_id uid;
                    string v;
                    o>>uid>>v;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->b_day=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set b_day='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_profile$b_mon:
                {
                    DB_id uid;
                    int v;
                    o>>uid>>v;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->b_mon=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set b_mon='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_profile$b_year:
                {
                    DB_id uid;
                    string v;
                    o>>uid>>v;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->b_year=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set b_year='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_profile$city:
                {
                    DB_id uid;
                    string v;
                    o>>uid>>v;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->city=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set city='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_profile$homepage:
                {
                    DB_id uid;
                    string v;
                    o>>uid>>v;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->homepage=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set homepage='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_profile$email:
                {
                    DB_id uid;
                    string v;
                    o>>uid>>v;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->email=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set email='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_profile$icq:
                {
                    DB_id uid;
                    string v;
                    o>>uid>>v;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->icq=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set icq='?' where refid=?"<<v<<uid.container);
#endif

                }break;
                case user_profile$tel:
                {
                    DB_id uid;
                    string v;
                    o>>uid>>v;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->tel=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set tel='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_profile$info:
                {
                    DB_id uid;
                    string v;
                    o>>uid>>v;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->info=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set info='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_profile$reg_date:
                {
                    DB_id uid;
                    time_t v;
                    o>>uid>>v;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->reg_date=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set reg_date=FROM_UNIXTIME(?) where refid=?"<<v<<uid.container);
#endif

                }break;
                case user_set$poweshen:
                {
                    DB_id uid;
                    DB_id v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->poweshen=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set poweshen='?' where refid=?"<<v.container<<uid.container);
#endif
                }break;
                case user_set$neye:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->neye=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set neye='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$ul_mode_contacts_only:
                {
                    DB_id uid;
                    bool v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->ul_mode_contacts_only=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set ul_mode_contacts_only='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$ul_mode_hide_male:
                {
                    DB_id uid;
                    bool v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->ul_mode_hide_male=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set ul_mode_hide_male='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$ul_mode_hide_female:
                {
                    DB_id uid;
                    bool v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->ul_mode_hide_female=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set ul_mode_hide_female='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_profile$gender:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_profile> p=user_profiles.get(uid);
                    if (p)
                    {
                        PGLW(user_profile,u,p);
                        u->set_gender(v);
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_profiles set gender='?' where refid=?"<<v<<uid.container);
#endif

                }break;
                case user_set$notes_save_copy:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->notes_save_copy=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set notes_save_copy='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$notes_msg_per_page:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->notes_msg_per_page=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set notes_msg_per_page='?' where refid=?"<<v<<uid.container);
#endif

                }break;
                case user_set$notes_sort:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->notes_sort=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set notes_sort='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$notes_sort_desc:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->notes_sort_desc=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set notes_sort_desc='?' where refid=?"<<v<<uid.container);
#endif

                }break;
                case user_set$n_color_pack:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->n_color_pack=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set n_color_pack='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$setting_autochange:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->setting_autochange=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set setting_autochange='?' where refid=?"<<v<<uid.container);
#endif

                }break;
                case user_set$setting_show_eye:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->setting_show_eye=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set setting_show_eye='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$setting_show_hints:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->setting_show_hints=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set setting_show_hints='?' where refid=?"<<v<<uid.container);
#endif

                }break;

                case user_set$show_credits:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->show_credits=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set show_credits='?' where refid=?"<<v<<uid.container);
#endif

                }break;

                case user_set$setting_show_stat:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->setting_show_stat=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set setting_show_stat='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$setting_invite_sound:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->setting_invite_sound=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set setting_invite_sound='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$setting_full_buttons:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->setting_full_buttons=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set setting_full_buttons='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$hide_fname:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->hide_fname=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set hide_fname='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$hide_lname:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->hide_lname=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set hide_lname='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$hide_bdate:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->hide_bdate=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set hide_bdate='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$hide_tel:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->hide_tel=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set hide_tel='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$hide_email:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->hide_email=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set hide_email='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$hide_icq:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->hide_icq=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set hide_icq='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$bought_quota:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->bought_quota=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set bought_quota='?' where refid=?"<<v<<uid.container);
#endif

                }break;
                case user_set$bought_invisibility:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->bought_invisibility=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set bought_invisibility='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$contact_options:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->contact_options=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set contact_options='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$show_level:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->show_level=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set show_level='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$show_nicks:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->show_nicks=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set show_nicks='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case user_set$lpp:
                {
                    DB_id uid;
                    unsigned int v;
                    o>>uid>>v;
                    PTR_getter<user_set> p=user_sets.get(uid);
                    if (p)
                    {
                        PGLW(user_set,u,p);
                        u->lpp=v;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update user_sets set lpp='?' where refid=?"<<v<<uid.container);
#endif
                }break;
                case status$add:
                {
                    DB_id uid;
                    unsigned int st_id;
                    user_status s;
                    o>>uid>>st_id>>s;
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"insert into user_status (id,uid,name,pic,disable_invite,uniq) values('?','?','?','?','?','?')"
                                       <<s.id<<uid.container<<s.name<<s.pic<<s.disable_invite<<s.uniq);
#endif
                    {
                        PTR_getter<user_profile> p=user_profiles.get(uid);
                        if (p)
                        {
                            PGLW(user_profile,u,p);
                            u->status[st_id]=s;
                        }
                    }
                }break;
                case status$remove:
                {
                    DB_id uid;
                    unsigned int st_id;
                    o>>uid>>st_id;
                    {
                        PTR_getter<user_profile> p=user_profiles.get(uid);
                        if (p)
                        {
                            PGLW(user_profile,u,p);
                            u->status.erase(st_id);
                        }
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"delete from user_status where id=? and uid=?"<<st_id<<uid.container);
#endif

                }break;
                case ignore$add:
                {
                    DB_id uid;
                    DB_id zid;
                    o>>uid>>zid;
                    PTR_getter<ignore_vec> p=ignore_vecs.get(uid);
                    if (p)
                    {
                        PGLW(ignore_vec,u,p);
                        u->ignore.insert(zid);
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"insert into ignores (uid,cuid) values (?,?)"<<uid.container<<zid.container);
#endif

                }break;
                case ignore$remove:
                {
                    DB_id uid;
                    DB_id zid;
                    o>>uid>>zid;
                    PTR_getter<ignore_vec> p=ignore_vecs.get(uid);
                    if (p)
                    {
                        PGLW(ignore_vec,u,p);
                        u->ignore.erase(zid);
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"delete from ignores where uid=? and cuid=?"<<uid.container<<zid.container);
#endif

                }break;
                case channel$topic:
                {
                    string top,set_by;
                    time_t t;
                    CH_id ch;
                    o>>ch>>top>>set_by>>t;
                    __CH_LOCKW(chat_channels[ch]);
                    CH->cd.topic=top;
                    CH->cd.set_by=set_by;
                    CH->cd.topic_time=t;

                }break;
                case foto$set_body:
                {

                    __foto f;
                    string picbody;
                    o>>f>>picbody;
                    string fn=foto_pn(f.uid,f.id,f.ext);
                    check_path_wfn(fn);
                    st_FILE fil(fn,"wb");

                    fil.puts(picbody);
                }
                case foto$add:
                {
                    __foto f;
                    o>>f;
                    PTR_getter<user_fotos> p=users_fotos.get(f.uid);
                    if (p)
                    {
                        PGLW(user_fotos,u,p);
                        u->fotos[f.id]=f;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"insert into photos (id,uid,orig_filename,descr,size,ext) values ('?','?','?','?','?','?')"
                                       <<f.id<<f.uid.container<<f.orig_fn<<f.descr<<f.size<<f.ext);
#endif


                }break;
                case foto$remove:
                {
                    DB_id uid;
                    unsigned int fid;
                    string fext;

                    o>>uid>>fid>>fext;
                    PTR_getter<user_fotos> p=users_fotos.get(uid);
                    if (p)
                    {
                        PGLW(user_fotos,u,p);
                        u->fotos.erase(fid);
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"delete from photos where id=? and uid=?"<<fid<<uid.container);
#endif
                    string fn=foto_pn(uid,fid,fext);
#ifdef WIN32
                    remove(fn.c_str());
#else
                    unlink(fn.c_str());
#endif
                    foto_rm_cache(uid,fid);
                }break;
                case foto$change_description:
                {
                    DB_id uid;
                    unsigned int fid;
                    string descr;
                    o>>uid>>fid>>descr;
                    PTR_getter<user_fotos> p=users_fotos.get(uid);
                    if (p)
                    {
                        PGLW(user_fotos,u,p);
                        u->fotos[fid].descr=descr;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update photos set descr='?' where uid=? and id=?"<<descr<<uid.container<<fid);
#endif

                }break;
                case foto$set_rate:
                {
//                        __foto f;
                    DB_id uid;
                    unsigned int fid;
                    DB_id ruid;
                    int value;
                    o>>uid>>fid>>ruid>>value;
                    PTR_getter<user_fotos> p=users_fotos.get(uid);
                    out_oscar_buffer b;
                    int rating_result=0;
                    if (p)
                    {
                        PGLW(user_fotos,u,p);
                        if (u->fotos.count(fid))
                        {
                            if (value==0)
                                u->fotos[fid].rates.erase(ruid);
                            else
                                u->fotos[fid].rates[ruid]=value;
                            b<<u->fotos[fid].rates;
                            rating_result=calc_photo_rating(u->fotos[fid].rates);
                        }

                    }

#ifndef __CLAN
//			if(rating_result)
                    {
                        d.dbh->real_query("update photos set rating_result="+itostring(rating_result)+", rating='"+MES(b.as_string())+"'  where uid="+itostring(uid.container)+" and id="+itostring(fid)+"");
                    }
#endif


                }break;

                case nick$change_cost:
                {
                    DB_id uid;
                    unsigned int nid;
                    string scost;
                    o>>uid>>nid>>scost;
                    {

                        PTR_getter<nick_vec> p=nick_vecs.get(uid);
                        if (p)
                        {
                            PGLW(nick_vec,u,p);
                            u->u_nicks[nid].cost=fabs(atof(scost.c_str()));
                            u->u_nicks[nid].ready_to_sale=true;

                        }
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update nicks set cost='?', ready_to_sale='1' where uid=? and id=?"
                                       <<scost<<uid.container<<nid);
#endif

                }break;

                case nick$change_nick:
                {
                    DB_id uid;
                    unsigned int nid;
                    string name;
                    o>>uid>>nid>>name;
                    {

                        PTR_getter<nick_vec> p=nick_vecs.get(uid);
                        if (p)
                        {
                            PGLW(nick_vec,u,p);
                            u->u_nicks[nid].name=name;

                        }
#ifndef __CLAN
                        d.dbh->real_queryQ((QUERY)"update nicks set nick='?' where uid=? and id=?"
                                           <<name<<uid.container<<nid);
#endif

                    }
                }break;
                case nick$add:
                {
                    user_nick n;
                    DB_id uid;
                    o>>uid;
                    o>>n;

                    PTR_getter<nick_vec> p=nick_vecs.get(uid);
                    if (p)
                    {
                        PGLW(nick_vec,u,p);
                        u->u_nicks[n.id]=n;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"insert into nicks (id,uid,nick,str_nick,banned) values ('?','?','?','?','0')"
                                       <<n.id<<uid.container<<n.name<<str_nick(n.name));
#endif

                }break;
                case nick$remove:
                {
                    DB_id uid;
                    unsigned int nid;
                    o>>uid>>nid;
                    PTR_getter<nick_vec> p=nick_vecs.get(uid);
                    if (p)
                    {
                        PGLW(nick_vec,u,p);
                        u->u_nicks.erase(nid);
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"delete from nicks where uid=? and id=?"<<uid.container<<nid);
#endif

                }break;
                case credit$set_summa:
                {
                    DB_id uid;
                    string s;
                    o>>uid>>s;
                    double d=atof(s.c_str());
                    PTR_getter<user_credit> p=user_credits.get(uid);
                    if (p)
                    {
                        PGLW(user_credit,u,p);
                        if (u->summa!=d)
                        {
                            u->summa.dbset(d);
                        }
                    }
#ifndef __CLAN
                    user_credits.make_1st_update(uid);
#endif
                }break;
                case contact$add:
                {
                    DB_id uid;
                    DB_id cid;
                    o>>uid>>cid;
                    PTR_getter<contact_vec> p=contact_vecs.get(uid);
                    if (p)
                    {
                        PGLW(contact_vec,u,p);
                        u->contact.insert(cid);
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"insert into contact (uid,cuid) values (?,?)"<<uid.container<<cid.container);
#endif
                }break;
                case contact$remove:
                {
                    DB_id uid;
                    DB_id cid;
                    o>>uid>>cid;
                    PTR_getter<contact_vec> p=contact_vecs.get(uid);
                    if (p)
                    {
                        PGLW(contact_vec,u,p);
                        u->contact.erase(cid);
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"delete from contact where uid=? and cuid=?"<<uid.container<<cid.container);
#endif
                }break;

                case channel_tmp$moderated:
                {
                    CH_id cid;
                    int mod;
                    o>>cid>>mod;
                    {
                        __CH_LOCKW(chat_channels[cid]);
                        CH->cd.moderated=mod;
                    }

                }break;
                case nick$unmark_for_sale:
                {
                    DB_id uid;
                    unsigned int nid;
                    o>>uid>>nid;
                    PTR_getter<nick_vec> p=nick_vecs.get(uid);
                    if (p) {
                        PGLW(nick_vec,n,p);
                        if (n->u_nicks.count(nid)) n->u_nicks[nid].ready_to_sale=false;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update nicks set ready_to_sale='0' where uid=? and id=?"<<uid.container<<nid);
#endif


                }break;
                case note$set_msg:
                {
                    DB_id uid;
                    unsigned int nid;
                    string msg;
                    o>>uid>>nid>>msg;
                    PTR_getter<note_text> p=note_texts.get(itostring(uid.container)+"."+itostring(nid));
                    if (p) {
                        PGLW(note_text,n,p);
                        n->body=msg;
                    }
#ifndef __CLAN
                    string q="insert into note_texts (message_id,body,owner_uid) values ('"+itostring(nid)+ "','"+MES(msg)+"',"+itostring(uid.container)+")";
                    d.dbh->real_query(q);
#endif

                }
                break;
                case note$folder_create:
                {
                    DB_id uid;
                    int fold;
                    string fname;
                    o>>uid>>fold>>fname;
                    PTR_getter<u_notes> p=__notes.get(uid);
                    if (p) {
                        PGLW(u_notes,u,p);
                        u->map_folders[fold].name=fname;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"insert into note_folders (id,uid,name) values (?,?,'?')"<<fold<<uid.container<<fname);
#endif
                }
                break;
                case note$folder_rename:
                {

                    DB_id uid;
                    int fold;
                    string fname;
                    o>>uid>>fold>>fname;
                    PTR_getter<u_notes> p=__notes.get(uid);
                    if (p) {
                        PGLW(u_notes,u,p);
                        u->map_folders[fold].name=fname;
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update note_folders set name='?' where id=? and uid=?"<<fname<<fold<<uid.container);
#endif
                }break;
                case note$folder_remove:
                {
                    DB_id uid;
                    int fold;
                    o>>uid>>fold;
                    PTR_getter<u_notes> p=__notes.get(uid);
                    if (p) {
                        PGLW(u_notes,u,p);
                        u->map_folders.erase(fold);
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"delete from note_folders where id=? and uid=?"<<fold<<uid.container);
#endif

                }break;
                case note$set_status:
                {
                    DB_id uid;
                    int msgid;
                    int status;
                    o>>uid>>msgid>>status;
                    PTR_getter<u_notes> p=__notes.get(uid);
                    if (p) {
                        PGLW(u_notes,u,p);
                        map<unsigned int,__note_head>::iterator h=u->map_msgs.find(msgid);
                        if (h!=u->map_msgs.end())
                        {
                            h->second.nfh.status=status;
                        }
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update notes set status=? where id=? and owner_uid=?"<<status<<msgid<<uid.container);
#endif

                }break;
                case note$set_unread:
                {
                    DB_id uid;
                    int msgid;

                    o>>uid>>msgid;
                    PTR_getter<u_notes> p=__notes.get(uid);
                    if (p) {
                        PGLW(u_notes,u,p);
                        map<unsigned int,__note_head>::iterator h=u->map_msgs.find(msgid);
                        if (h!=u->map_msgs.end())
                        {
                            h->second.nfh.unread=false;
                        }
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update notes set unread='0' where id=? and owner_uid=?"<<msgid<<uid.container);
#endif

                }break;
                case note$filter_out_delete:
                {
                    DB_id uid;
                    int fid;
                    DB_id zid;
                    o>>uid>>fid>>zid;
                    PTR_getter<u_notes> p=__notes.get(uid);
                    if (p)
                    {
                        PGLW(u_notes,u,p);
                        u->map_folders[fid].filter_out.erase(zid.container);
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"delete from filters_out where folder_id=? and owner_uid=? and uid=?"<<
                                       fid<<uid.container<<zid.container);
#endif


                }break;
                case note$filter_out_insert:
                {
                    DB_id uid;
                    int fid;
                    DB_id zid;
                    o>>uid>>fid>>zid;
                    PTR_getter<u_notes> p=__notes.get(uid);
                    if (p)
                    {
                        PGLW(u_notes,u,p);
                        u->map_folders[fid].filter_out.insert(zid.container);
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"insert into filters_out (folder_id,owner_uid,uid) values (?,?,?)"<<fid<<uid.container<<zid.container);
#endif

                }break;

                case note$filter_in_delete:
                {
                    DB_id uid;
                    int fid;
                    DB_id zid;
                    o>>uid>>fid>>zid;
                    PTR_getter<u_notes> p=__notes.get(uid);
                    if (p)
                    {
                        PGLW(u_notes,u,p);
                        u->map_folders[fid].filter_in.erase(zid.container);
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"delete from filters_in where folder_id=? and owner_uid=? and uid=?"<<
                                       fid<<uid.container<<zid.container);
#endif

                }break;
                case note$filter_in_insert:
                {
                    DB_id uid;
                    int fid;
                    DB_id zid;
                    o>>uid>>fid>>zid;
                    PTR_getter<u_notes> p=__notes.get(uid);
                    if (p)
                    {
                        PGLW(u_notes,u,p);
                        u->map_folders[fid].filter_in.insert(zid.container);
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"insert into filters_in (folder_id,owner_uid,uid) values (?,?,?)"<<fid<<uid.container<<zid.container);
#endif

                }break;
                case note$set_head:
                {
                    DB_id uid;
                    int fid;
                    __note_head hh;

                    o>>uid>>fid>>hh;
                    note_file_head &h=hh.nfh;
                    PTR_getter<u_notes> p=__notes.get(uid);
                    if (p)
                    {
                        PGLW(u_notes,u,p);
                        u->map_msgs[hh.id]=hh;
                        u->map_folders[fid].vec_msgs.push_back(hh.id);
#ifndef __CLAN
                        d.dbh->real_queryQ((QUERY)"insert into notes ( "
                                           "from_nick_id,to_nick_id,"
                                           "from_uid,to_uid,"
                                           "from_nick,to_nick,"
                                           "refcount, "
                                           "subject,send_date,"
                                           "status,unread,"
                                           "content_length, has_attachment,"
                                           "attachment_filename,attachment_content_length, important,system,owner_uid,owner_folder,notify_read,id) "
                                           "	values('?','?','?','?','?','?','?','?',FROM_UNIXTIME(?),'?','?','?','?','?','?','?','?','?','?','?','?') "
                                           <<h.from_nick_id<<h.to_nick_id
                                           <<h.from_uid<<h.to_uid
                                           <<h.from_nick<<h.to_nick
                                           <<1
                                           <<h.subject<<h.send_date
                                           <<h.status<<h.unread
                                           <<h.content_length<<h.has_attachment
                                           <<h.attachment_filename<<h.attachment_content_length
                                           <<h.important<<h.system<<uid.container<<fid<<h.notify_read<<hh.id);
#endif

                    }
                    note_resort(uid);

                }break;
                case note$remove:
                {
                    DB_id uid;
                    int msgid;
                    o>>uid>>msgid;

                    bool need_del_att=false;
                    string att;
                    PTR_getter<u_notes> p=__notes.get(uid);
                    if (p)
                    {
                        PGLW(u_notes,u,p);
                        for (map<unsigned int,__note_folder> ::iterator i=u->map_folders.begin();i!=u->map_folders.end();i++)
                        {
                            bool broken=false;
                            for (vector<unsigned int> ::iterator j=i->second.vec_msgs.begin();j!=i->second.vec_msgs.end() && !broken;j++)
                            {
                                if (*j==msgid)
                                {
                                    i->second.vec_msgs.erase(j);
                                    broken=true;
                                }
                            }
                        }
                        __note_head &h=u->map_msgs[msgid];
                        if (h.nfh.has_attachment)
                        {
                            att=attach_pn(uid,msgid,h.nfh.attachment_filename);
                            need_del_att=true;
                        }
                        u->map_msgs.erase(msgid);
                    }
                    note_resort(uid);

                    if (need_del_att)
                    {
#ifdef WIN32
                        remove(att.c_str());
#else
                        unlink(att.c_str());
#endif
                    }
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"delete from notes where id=? and owner_uid=?"<<msgid<<uid.container);
                    d.dbh->real_queryQ((QUERY)"delete from note_texts where message_id=? and owner_uid=?"<<msgid<<uid.container);
#endif

                }break;
                case note$move_message:
                {

                    DB_id uid;
                    int msgid;
                    int fold,tofold;
                    o>>uid>>msgid>>fold>>tofold;
                    PTR_getter<u_notes> p=__notes.get(uid);
                    {
                        PGLW(u_notes,u,p);
                        for (vector<unsigned int>::iterator i=u->map_folders[fold].vec_msgs.begin();i!=u->map_folders[fold].vec_msgs.end();i++)
                        {
                            if (*i==msgid)
                            {
                                u->map_folders[fold].vec_msgs.erase(i);
                                break;
                            }
                        }
                        u->map_folders[tofold].vec_msgs.push_back(msgid);
                    }
                    if (p)note_resort(uid);
#ifndef __CLAN
                    d.dbh->real_queryQ((QUERY)"update notes set owner_folder=? where owner_uid=? and id=?"<<tofold<<uid.container<<msgid);
#endif

                }break;
                case note$set_attachment:
                {
                    int n;
                    o>>n;
                    DB_id tuid,fuid;
                    int tmsgid=0,fmsgid=0;
                    string attfn;
                    string body;
                    if (n==1)
                    {
                        o>>tuid>>tmsgid;
                    }
                    else if (n==2)
                    {
                        o>>tuid>>tmsgid;
                        o>>fuid>>fmsgid;
                    }
                    o>>attfn;
                    o>>body;

                    string pn_to=attach_pn(tuid,tmsgid,attfn);

                    check_path_wfn(pn_to);
                    {
                        st_FILE f(pn_to,"wb");
                        f.write(body);
                    }
                    if (n==2)
                    {
                        string pn_from=attach_pn(fuid,fmsgid,attfn);
                        check_path_wfn(pn_from);
#ifdef WIN32
                        {
                            st_FILE f(pn_from,"wb");
                            f.write(body);
                        }
#else
                        link(pn_to.c_str(),pn_from.c_str());
#endif
                    }


                }break;


                default:
                    ;
#ifdef DEBUG
                    logErr2("unhandled update for %s",get_update_code(cmd).c_str());
#endif
                }

            }
            usleep(10000);
        }
        catch (cError e) {
            logErr2("--Error: updater! %s %s %d",e.what(),__FILE__,__LINE__);
            sleep(1);
        }
        catch (...) {
            logErr2("--Error: updater: unknow error! %s %d",__FILE__,__LINE__);
            sleep(1);
        }
    }
    return NULL;
}
/*


*/
void start_update_processor()
{
    pthread_t t;
    int r=pthread_create(&t,NULL,update_processor,NULL);
    if (r!=0) {
        logErr2("--Error while creating pthread_ceate: %d",r);
        return;
    }
}


