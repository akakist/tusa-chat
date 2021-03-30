#ifndef update_cmd__h
#define update_cmd__h
enum UCMD {
    user_stat$last_date,
    user_stat$last_ip,
    user_stat$last_pip,
    user_stat$inc_v_count,
    user_stat$inc_m_count,
    user_stat$add_t_count,
    user_stat$inc_kick_count,
    user_stat$inc_kicked_count,
    user_profile$pass,
    user_profile$level,
    user_profile$db_privileges,
    user_profile$vote_balls,
    user_profile$login,
    user_profile$fname,
    user_profile$lname,
    user_profile$b_day,
    user_profile$b_mon,
    user_profile$b_year,
    user_profile$city,
    user_profile$homepage,
    user_profile$email,
    user_profile$icq,
    user_profile$tel,
    user_profile$info,
    user_profile$reg_date,
    user_set$poweshen,
    user_profile$gender,
    user_set$neye,
    user_set$notes_save_copy,
    user_set$notes_msg_per_page,
    user_set$notes_sort,
    user_set$notes_sort_desc,
    user_set$n_color_pack,
    user_set$setting_autochange,
    user_set$setting_show_eye,
    user_set$setting_show_hints,
    user_set$show_credits,
    user_set$setting_show_stat,
    user_set$setting_invite_sound,
    user_set$setting_full_buttons,
    user_set$hide_fname,
    user_set$hide_lname,
    user_set$hide_bdate,
    user_set$hide_tel,
    user_set$hide_email,
    user_set$hide_icq,
    user_set$bought_quota,
    user_set$bought_invisibility,
    user_set$contact_options,
    user_set$show_level,
    user_set$show_nicks,
    user_set$lpp,

    user_set$last_nick,
    user_set$last_nick_id,
    user_set$last_status_id,
    user_set$last_channel,
    user_set$ul_mode_contacts_only,
    user_set$ul_mode_hide_male,
    user_set$ul_mode_hide_female,
    contact$add,
    contact$remove,

    channel$topic,
    status$add,
    status$remove,

    ignore$add,
    ignore$remove,

    foto$remove,
    foto$change_description,
    foto$add,
    nick$add,
    nick$remove,
    credit$set_summa,
    channel_tmp$moderated,
    nick$unmark_for_sale,
    note$set_msg,
    note$folder_create,
    note$folder_rename,
    note$folder_remove,
    note$set_status,
    note$set_unread,
    note$filter_out_delete,
    note$filter_out_insert,
    note$filter_in_delete,
    note$filter_in_insert,
    note$set_head,
    note$remove,
    note$move_message,
    note$set_attachment,
    foto$set_body,
    nick$change_nick,
    nick$change_cost,
    foto$set_rate,

};
struct user_status;
void send_update_g4(const  UCMD &cmd,unsigned int id, unsigned int status_id,const user_status &s);
void send_update_g3(const  UCMD &cmd,unsigned int id, unsigned int v);
void send_update_g3(const  UCMD &cmd,unsigned int id, const string &v);
void send_update_g2(const  UCMD &cmd,unsigned int id);
void send_update_g2(const  UCMD &cmd,const out_oscar_buffer&);
void send_update_g2_cs_only(const  UCMD &cmd,const out_oscar_buffer&);

void send_update_g4(const  UCMD &cmd,unsigned int, unsigned int ,const string&);
void send_update_g4(const  UCMD &cmd,unsigned int, unsigned int ,int);
void send_update_g4(const  UCMD &cmd,const DB_id &, unsigned int ,const string&);
void send_update_g4(const  UCMD &cmd,const DB_id &, unsigned int ,int);
void send_update_g4(const  UCMD &cmd,const DB_id& id, unsigned int status_id,const user_status &s);

void send_update_g3(const  UCMD &cmd,const DB_id& id, unsigned int v);
void send_update_g3(const  UCMD &cmd,const DB_id& id, const string &v);
void send_update_d3(const  UCMD &cmd,const DB_id& id, const double &v);
void send_update_d3(const  UCMD &cmd,unsigned int id, const double &v);
void send_update_d4(const  UCMD &cmd,const DB_id& id, unsigned int, const double &v);
void send_update_g2(const  UCMD &cmd,const DB_id& id);
#endif
