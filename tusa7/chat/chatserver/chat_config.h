#ifndef chatWEBSERVER_CONFIGH
#define chatWEBSERVER_CONFIGH
using namespace std;
#include "M_MAP.h"
#include "M_SET.h"
#include "m_var.h"
#include "file_set.h"

struct __chat_config2
{
    m_var<double>change_eqlevel_cost;
    m_var<double>invis_cost;
    m_var<double>quota_cost;
    m_var<double>nick_cost;
    m_var<unsigned int>change_eqlevel_limit;
    m_var<unsigned int>change_eqlevel_saler_account;
    m_var<unsigned int>invis_saler_account;
    m_var<unsigned int>levelup_saler_account;
    m_var<unsigned int>topic_saler_account;
    m_var<unsigned int>quota_saler_account;
    m_var<unsigned int>nick_saler_account;
    m_var<unsigned int> vote_yes_percent;
    m_var<unsigned int> system_note_uid;
    m_var<string>levelup_cost;
    m_var<unsigned int>topic_step_rate_percent; // %
    m_var<unsigned int>topic_down_rate_per_hour; // %
    void load_config(const string&pn);
    void pack(out_oscar_buffer &b);
    void unpack(oscar_buffer &b);
    __chat_config2();
};
struct __chat_config
{
    m_var<bool>use_advert_in_chat;
    m_var<unsigned int>chat_offline_timeout;



    m_var<unsigned int>news_count_in_index_page;
    m_var<unsigned int>news_per_page;
    m_var<unsigned int>number_of_eyes;
    m_var<unsigned int>number_of_eyes_for_main_admin;
    m_var<unsigned int> data_update_timeout;
    m_var<unsigned int> data_drop_timeout;


    m_var<unsigned int>user_max_inactive_time;
    m_var<bool>use_replacement_for_netscape;

    m_var<string>date_format;
    m_var<string>funny_dir;
    m_var<string>history_dir;
    m_var<string>status_dir;
    m_var<string>time_format;

    m_var<string> bad_words;
    m_var<string> to_all;
    void load_config(const string&pn);
    __chat_config();
};
extern __chat_config chat_config;
extern __chat_config2 chat_config2;


#endif
