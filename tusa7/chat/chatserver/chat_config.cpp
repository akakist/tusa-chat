#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include <signal.h>
#include <errno.h>
#include "file_set.h"
#include "oscar_buffer.h"
#include "chat_config.h"
#include "server_config.h"

#include "str_lib.h"
#include "message.h"
#include "chat_funny.h"
#include "message.h"
#include "cm_container.h"

string str_nick(const string &n);

bool load_channels();
void load_color_packs(const string &scpack,const string& conf_name);
bool load_messages();
bool load_levels(const string &pn);
vector< vector<string> > load_st_file(const string &pn);
vector<string> load_l_file(const string &fn);

vector< vector<string> > load_st_file(const string &fname)
{
    vector< vector<string> > v;
    for (int i=0;i<3;i++) {
        string fn=fname+"."+itostring(i)+".msg";
        v.push_back(load_l_file(fn));
    }
    return v;
}


__chat_config chat_config;
__chat_config2 chat_config2;
__chat_config::__chat_config()
{
}
__chat_config2::__chat_config2()
{
}
void __chat_config2::pack(out_oscar_buffer &b)
{
    char s[200];
    snprintf(s,sizeof(s),"%f",change_eqlevel_cost.get());
    b<<(string)s;
    snprintf(s,sizeof(s),"%f",invis_cost.get());
    b<<(string)s;
    snprintf(s,sizeof(s),"%f",quota_cost.get());
    b<<(string)s;
    snprintf(s,sizeof(s),"%f",nick_cost.get());
    b<<(string)s;
    b<<change_eqlevel_limit.get();
    b<<change_eqlevel_saler_account.get();
    b<<invis_saler_account.get();
    b<<levelup_saler_account.get();
    b<<topic_saler_account.get();
    b<<quota_saler_account.get();
    b<<nick_saler_account.get();
    b<<vote_yes_percent.get();
    b<<system_note_uid.get();
    b<<levelup_cost.get();
    b<<topic_step_rate_percent.get();
    b<<topic_down_rate_per_hour.get();

}
void __chat_config2::unpack(oscar_buffer &b)
{
    string s;
    unsigned int n;
    b>>s;
    change_eqlevel_cost=atof(s.c_str());
    b>>s;
    invis_cost=atof(s.c_str());
    b>>s;
    quota_cost=atof(s.c_str());;
    b>>s;
    nick_cost=atof(s.c_str());;
    b>>n;
    change_eqlevel_limit=n;
    b>>n;
    change_eqlevel_saler_account=n;
    b>>n;
    invis_saler_account=n;
    b>>n;
    levelup_saler_account=n;
    b>>n;
    topic_saler_account=n;
    b>>n;
    quota_saler_account=n;
    b>>n;
    nick_saler_account=n;
    b>>n;
    vote_yes_percent=n;
    b>>n;
    system_note_uid=n;
    b>>s;
    levelup_cost=s;
    b>>n;
    topic_step_rate_percent=n; // %
    b>>n;
    topic_down_rate_per_hour=n; // %

}

void __chat_config2::load_config(const string&pn)
{
    map<string,string>	m=load_m_file(pn);
    set_cfg_f(m,"change_eqlevel_cost", pn,change_eqlevel_cost,5.0);
    set_cfg_f(m,"invis_cost", pn,invis_cost,50);
    set_cfg_f(m,"quota_cost", pn,quota_cost,3);
    set_cfg_f(m,"nick_cost", pn,nick_cost,1);
    set_cfg_i(m,"invis_saler_account", pn,invis_saler_account,1);
    set_cfg_i(m,"levelup_saler_account", pn,levelup_saler_account,1);
    set_cfg_i(m,"topic_saler_account", pn,topic_saler_account,1);
    set_cfg_i(m,"topic_step_rate_percent", pn,topic_step_rate_percent,10);
    set_cfg_i(m,"topic_down_rate_per_hour", pn,topic_down_rate_per_hour,10);
    set_cfg_i(m,"quota_saler_account", pn,quota_saler_account,1);
    set_cfg_i(m,"nick_saler_account", pn,nick_saler_account,1);
    set_cfg_i(m,"vote_yes_percent", pn,vote_yes_percent,75);
    set_cfg_i(m,"system_note_uid", pn,system_note_uid,26);
    set_cfg_i(m,"change_eqlevel_limit", pn,change_eqlevel_limit,50);
    set_cfg_i(m,"change_eqlevel_saler_account", pn,change_eqlevel_saler_account,1);
    set_cfg_str(m,"levelup_cost", pn,levelup_cost,"1:15,2:30,3:70");
    print_rest_cfg(m,pn);
}
void __chat_config::load_config(const string&pn)
{
    map<string,string>	m=load_m_file(pn);
    set_cfg_str(m,"to_all", pn,to_all,"бяел");

    set_cfg_str(m,"date_format", pn,date_format,"");
    set_cfg_str(m,"time_format", pn,time_format,"%k:%M");
    set_cfg_b(m,"use_advert_in_chat", pn,use_advert_in_chat,false);
    set_cfg_i(m,"chat_offline_timeout", pn,chat_offline_timeout,300);


    set_cfg_i(m,"news_count_in_index_page", pn,news_count_in_index_page,3);
    set_cfg_i(m,"news_per_page", pn,news_per_page,20);
    set_cfg_i(m,"number_of_eyes", pn,number_of_eyes,2);
    set_cfg_i(m,"number_of_eyes_for_main_admin", pn,number_of_eyes_for_main_admin,5);

    set_cfg_i(m,"data_update_timeout", pn,data_update_timeout,120);
    set_cfg_i(m,"data_drop_timeout", pn,data_drop_timeout,1000);

    set_cfg_i(m,"user_max_inactive_time", pn,user_max_inactive_time,1);


    set_cfg_str(m,"funny_dir", pn,funny_dir,"./www/pics/funnypics");
    set_cfg_str(m,"history_dir", pn,history_dir,"/var/chat/history");

    set_cfg_str(m,"status_dir", pn,status_dir,"./www/pics/s");

    set_cfg_b(m,"use_replacement_for_netscape", pn,use_replacement_for_netscape,false);

    load_messages();
    load_levels(get_cfg_str(m,"levels_config",pn, "./conf/levels.conf"));
    msgs_defstatus.assign(load_st_file(get_cfg_str(m,		"status",pn, "./www/messages/status")));
    msgs_greeting.assign_ck(load_st_file(get_cfg_str(m,		"greeting",pn, "./www/messages/greetings")));
    msgs_bye.assign_ck(load_st_file( get_cfg_str(m,		"bye",pn, "./www/messages/byes")));
    msgs_kicking.assign_ck(load_st_file(get_cfg_str(m,		"kicking",pn, "./www/messages/kickings")));
    msgs_killing.assign_ck(load_st_file(get_cfg_str(m,		"killing",pn, "./www/messages/killing")));
    msgs_changes.assign_ck(load_st_file(get_cfg_str(m,		"changes",pn, "./www/messages/channels")));
    msgs_nickchanges.assign_ck(load_st_file(get_cfg_str(m,	"nickchanges",pn, "./www/messages/nickchanges")));
    msgs_topicchanges.assign_ck(load_st_file(get_cfg_str(m,	"topicchanges",pn, "./www/messages/topicchanges")));
    msgs_modechanges.assign_ck(load_st_file(get_cfg_str(m,	"modechanges",pn, "./www/messages/modechanges")));
    msgs_maty.assign_ck(load_st_file(get_cfg_str(m,		"censmess",pn, "./www/messages/censored")));
    vector<string> v=load_l_file(get_cfg_str(m,			"bad_words",pn, "./www/messages/bad_words")+".msg");
    if (v.size()>0) {
        string b=v[0];
        for (unsigned int i=1;i<v.size();i++) {
            if (v[i]!="") {
                b+="|"+v[i];
            }
        }
        bad_words=str_nick(b);
    }
    load_color_packs(get_cfg_str(m,"color_packs", pn,"0:./conf/colors/std.conf,1:./conf/colors/1blue.conf,2:./conf/colors/2green.conf,3:./conf/colors/3red.conf,4:./conf/colors/4pink.conf"),pn);

    load_channels();
    load_funnypics();
    load_anekdots();
    load_histories();
    load_hints();
    load_news();
    print_rest_cfg(m,pn);
}
