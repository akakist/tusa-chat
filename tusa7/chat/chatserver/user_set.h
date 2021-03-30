#ifndef ISER_SET__HHH
#define ISER_SET__HHH

#include <string>
#include <map>
using namespace std;

///

class user_set: public db_row
{
public:
    int load_from_db(const string & table_name);
    user_set();
    ~user_set();

    int lpp;		//LinesPerPage
    int neye;
    unsigned int n_color_pack;
    unsigned int bought_quota;
    unsigned int bought_max_nick_count;
    unsigned int last_nick_id;
    string last_nick;
    unsigned int last_channel;
    unsigned int last_status_id;
    unsigned int contact_options;
    bool ul_mode_contacts_only;
    bool ul_mode_hide_male;
    bool ul_mode_hide_female;

    int bought_invisibility;
    DB_id poweshen;
    unsigned int  notes_msg_per_page;
    bool  notes_save_copy;
    unsigned char  notes_sort;
    bool  notes_sort_desc;
    time_t binv_last_recalc;
    bool show_nicks;
    bool show_level;
    bool show_credits;
//	bool setting_autologin;
    bool setting_autochange;
    bool setting_show_eye;
    bool setting_show_hints;
    bool setting_show_stat;
    bool setting_invite_sound;
    bool setting_full_buttons;
    bool hide_fname;
    bool hide_lname;
    bool hide_bdate;
    bool hide_tel;
    bool hide_email;
    bool hide_icq;
    enum {
        CONTACT_ADD_IN_PRIV=0x01,
        CONTACT_ADD_OUT_PRIV=0x02

    };
    void pack(out_oscar_buffer &b) const;
    void unpack(oscar_buffer &b);

};
extern db_map<user_set> user_sets;

#endif
