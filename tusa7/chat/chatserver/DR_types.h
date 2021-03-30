#ifndef data_requests__h
#define data_requests__h

enum {
    DR_nick_vec		=1,
    DR_user_profile		=2,
    DR_user_set		=3,
    DR_user_stat		=4,
    DR_user_fotos		=5,
    DR_ignore_vec		=6,
    DR_contact_vec		=7,
    DR_u_notes		=8,
    DR_note_text		=9,
    DR_load_channels	=10,
    DR_gallery_request	=11,
    DR_select_uid_nick_by_ids=12,
    DR_get_uid_by_nick	=13,
    DR_calc_statistic	=14,
    DR_get_users_counts	=15,
    DR_check_for_ipban	=16,
    DR_do_nickban		=17,
    DR_do_loginban		=18,
    DR_do_ipban		=19,
    DR_load_levels		=20,
    DR_register_io		=21,
    DR_login_io		=22,
    DR_get_id_uid_nick_by_nick=23,
    DR_get_pass_by_nick	=24,
    DR_get_uid_time_cnt_descr_from_banned_login_by_uid=25,
    DR_load_hints		=26,
    DR_load_news		=27,
    DR_user_credit		=28,
    DR_get_user_states	=29,
    DR_get_g_session	=30,
    DR_get_foto		=31,
    DR_get_attach		=32,
};
enum
{
    TSD_user_profile	=1,
    TSD_user_set		=2,
    TSD_user_stat		=3,
    TSD_nick_vec		=4,
    TSD_ignore_vec		=5,
    TSD_contact_vec	=6,
    TSD_user_fotos		=7,
    TSD_user_state		=8,
    TSD_levels		=9,
    TSD_news		=10,
    TSD_hints		=11,
    TSD_channels		=12,
    TSD_chat_config2	=13,

};
#ifdef __CLAN
string clan_data_request(int reqtype,const out_oscar_buffer& s);
string clan_data_request(int reqtype,const DB_id &s);
string clan_data_request(int reqtype);
#endif
#endif
