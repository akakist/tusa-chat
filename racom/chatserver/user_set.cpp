#include "stdafx.h"
#include <string>
using namespace std;
#include "user.h"
#include "utils.h"
#include "db_var.h"
#include "user_set.h"
#include "html_out.h"
#include "notes.h"
#include "DR_types.h"
#ifdef __CLAN


int user_set::load_from_db(const string & table_name)
{
    DB_id id;
    id.container=get_db_row_id().as_int();
    string r=clan_data_request(DR_user_set,id);
    oscar_buffer bb(r.data(),r.size());
    unpack(bb);
    return 0;
}
#else
int user_set::load_from_db(const string & table_name)
{
    unsigned int uid=get_db_row_id().as_int();
    if (uid==0) {
        logErr2(" uid==0 || uid>UNREG_BASE uid %d %s",uid,"");
        throw cError("if(get_db_row_id().as_int()==0) || uid>UNREG_BASE");
    }
    st_dbh d;
    QUERY q=(QUERY)"select lpp,neye,n_color_pack,bought_quota,bought_max_nick_count,last_nick_id,last_nick,last_channel,last_status_id,contact_options,"
            "bought_invisibility,poweshen,notes_msg_per_page, notes_save_copy,notes_sort,notes_sort_desc,binv_last_recalc,"
            "show_nicks,show_level,setting_autologin,setting_autochange,setting_show_eye,setting_show_hints,setting_show_stat,setting_invite_sound,"
            "setting_full_buttons,hide_fname,hide_lname,hide_bdate,hide_tel,hide_email,hide_icq,"
            "ul_mode_contacts_only,ul_mode_hide_male,ul_mode_hide_female,show_credits from user_sets where refid=?"<<uid;
    vector <string> v=d.dbh->select_1_rowQ(q);
    if (v.size()!=36) return -1;
    lpp			=atoi(v[0]);
    neye			=atoi(v[1]);
    n_color_pack		=atoi(v[2]);
    bought_quota		=atoi(v[3]);
    bought_max_nick_count	=atoi(v[4]);
    last_nick_id		=atoi(v[5]);
    last_nick		=v[6];
    last_channel		=atoi(v[7]);
    last_status_id		=atoi(v[8]);
    contact_options		=atoi(v[9]);
    bought_invisibility	=atoi(v[10]);
    poweshen.container	=atoi(v[11]);
    notes_msg_per_page	=atoi(v[12]);
    notes_save_copy		=atoi(v[13]);
    notes_sort		=atoi(v[14]);
    notes_sort_desc		=atoi(v[15]);
    binv_last_recalc	=atoi(v[16]);
    show_nicks		=atoi(v[17]);
    show_level		=atoi(v[18]);
//    setting_autologin	=atoi(v[19]);
    setting_autochange	=atoi(v[20]);
    setting_show_eye	=atoi(v[21]);
    setting_show_hints	=atoi(v[22]);
    setting_show_stat	=atoi(v[23]);
    setting_invite_sound	=atoi(v[24]);
    setting_full_buttons	=atoi(v[25]);
    hide_fname		=atoi(v[26]);
    hide_lname		=atoi(v[27]);
    hide_bdate		=atoi(v[28]);
    hide_tel		=atoi(v[29]);
    hide_email		=atoi(v[30]);
    hide_icq		=atoi(v[31]);
    ul_mode_contacts_only	=atoi(v[32]);
    ul_mode_hide_male	=atoi(v[33]);
    ul_mode_hide_female	=atoi(v[34]);
    show_credits=atoi(v[35]);
    return 0;
}
#endif
string update_to_db(const PTR_getter<user_set> &__U,const string& table_name)
{
    return "";

}
user_set::user_set() {
    lpp=100;
    show_nicks=true;
    show_level=true;
    neye=-1;
    n_color_pack=0;
    bought_quota=0;
    bought_max_nick_count=0;
    bought_invisibility=0;
    contact_options=CONTACT_ADD_IN_PRIV|CONTACT_ADD_OUT_PRIV;
    notes_sort=u_notes::sort_date;
    notes_sort_desc=true;
    notes_save_copy=true;
    notes_msg_per_page=20;
    binv_last_recalc=time(NULL);
    ul_mode_contacts_only=false;
    ul_mode_hide_male=false;
    ul_mode_hide_female=false;


}
user_set::~user_set() {}

void user_set::pack(out_oscar_buffer &b) const
{
    b<< lpp<<		//LinesPerPage
    neye<<
    n_color_pack<<
    bought_quota<<
    bought_max_nick_count<<
    last_nick_id<<
    last_nick<<
    last_channel<<
    last_status_id<<
    contact_options<<
    ul_mode_contacts_only<<
    ul_mode_hide_male<<
    ul_mode_hide_female<<

    bought_invisibility<<
    poweshen<<
    notes_msg_per_page<<
    notes_save_copy<<
    notes_sort<<
    notes_sort_desc<<
    binv_last_recalc<<
    show_nicks<<
    show_level<<
    setting_autochange<<
    setting_show_eye<<
    setting_show_hints<<
    setting_show_stat<<
    setting_invite_sound<<
    setting_full_buttons<<
    hide_fname<<
    hide_lname<<
    hide_bdate<<
    hide_tel<<
    hide_email<<
    hide_icq<<show_credits;

}
void user_set::unpack(oscar_buffer &b)
{
    b>> lpp>>		//LinesPerPage
    neye>>
    n_color_pack>>
    bought_quota>>
    bought_max_nick_count>>
    last_nick_id>>
    last_nick>>
    last_channel>>
    last_status_id>>
    contact_options>>
    ul_mode_contacts_only>>
    ul_mode_hide_male>>
    ul_mode_hide_female>>

    bought_invisibility>>
    poweshen>>
    notes_msg_per_page>>
    notes_save_copy>>
    notes_sort>>
    notes_sort_desc>>
    binv_last_recalc>>
    show_nicks>>
    show_level>>
    setting_autochange>>
    setting_show_eye>>
    setting_show_hints>>
    setting_show_stat>>
    setting_invite_sound>>
    setting_full_buttons>>
    hide_fname>>
    hide_lname>>
    hide_bdate>>
    hide_tel>>
    hide_email>>
    hide_icq>>show_credits;

}
