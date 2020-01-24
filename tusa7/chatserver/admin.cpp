#ifdef __GNUC__
#pragma implementation				// gcc: implement sql_udf.h
#endif

#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <time.h>
#include <map>
#include "mysql_extens.h"
#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include "web_server.h"
#include "message.h"
#include "chat_def.h"

#include "register.h"

#include <algorithm>
#include "web_server_data.h"
#include "file_set.h"
#include "copy_file.h"

#include "channels.h"
#include "server_config.h"
#include "user.h"
#include "app_def.h"
#include "user_set.h"
#include "cs_conn_data.h"
#include "html_out.h"
void url_admin_userlist(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void url_admin_logininfo(const PTR_getter<chat_user>&__U,cs_conn_data *cc);
void url_admin_userlist_command(const PTR_getter<chat_user> &__U,cs_conn_data *cc);


void url_admin_index(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);
    if (cc->sub_level>=am_killer || u_has_console(__U)) {
    }
    else {
        return;
    }

    map<string,hstring> m;
    if ((user$privileges(__U)&u_is_settings_admin)) {
        m["~settings~"]="";
        m["~esettings~"]="";
    } else {
        m["~settings~"]="<!--";
        m["~esettings~"]="-->";
    }
    if ((user$privileges(__U)&u_allow_view_logs)) {
        m["~logs~"]="";
        m["~elogs~"]="";
    } else {
        m["~logs~"]="<!--";
        m["~elogs~"]="-->";
    }
    if (!(user$privileges(__U)&u_is_funny_admin)) {
        m["~funnyadm~"]="<!--";
        m["~efunnyadm~"]="-->";
    } else {
        m["~funnyadm~"]="";
        m["~efunnyadm~"]="";
    }
    if (cc->sub_level<am_admin) {
        m["~adm~"]="<!--";
        m["~eadm~"]="-->";
    } else {
        m["~adm~"]="";
        m["~eadm~"]="";
    }
    if (!(user$privileges(__U)&u_is_vote_admin)) {
        m["~voteadm~"]="<!--";
        m["~evoteadm~"]="-->";
    } else {
        m["~voteadm~"]="";
        m["~evoteadm~"]="";
    }
    if (!(user$privileges(__U)&u_is_privs_admin)) {
        m["~privsadm~"]="<!--";
        m["~eprivsadm~"]="-->";
    } else {
        m["~privsadm~"]="";
        m["~eprivsadm~"]="";
    }
    if (!(user$privileges(__U)&u_is_accounts_admin)) {
        m["~accounts~"]="<!--";
        m["~eaccounts~"]="-->";
    } else {
        m["~accounts~"]="";
        m["~eaccounts~"]="";
    }
    if (!(user$privileges(__U)&u_is_hints_admin)) {
        m["~hintsadm~"]="<!--";
        m["~ehintsadm~"]="-->";
    } else {
        m["~hintsadm~"]="";
        m["~ehintsadm~"]="";
    }
    if (!(user$privileges(__U)&u_is_news_admin)) {
        m["~newsadm~"]="<!--";
        m["~enewsadm~"]="-->";
    } else {
        m["~newsadm~"]="";
        m["~enewsadm~"]="";
    }
    int levelup_ability,leveldown_ability;
    {
        c_level lv=LEVELS(user$level(__U));
        levelup_ability=lv.levelup_ability;
        leveldown_ability=lv.leveldown_ability;
    }
    if (levelup_ability==0) {
        m["~levelupadm~"]="<!--";
        m["~elevelupadm~"]="-->";
    } else {
        m["~levelupadm~"]="";
        m["~elevelupadm~"]="";
    }
    if (leveldown_ability==0) {
        m["~leveldownadm~"]="<!--";
        m["~eleveldownadm~"]="-->";
    } else {
        m["~leveldownadm~"]="";
        m["~eleveldownadm~"]="";
    }
    if (!(user$privileges(__U)&u_is_smiles_admin)) {
        m["~smilesadm~"]="<!--";
        m["~esmilesadm~"]="-->";
    } else {
        m["~smilesadm~"]="";
        m["~esmilesadm~"]="";
    }
    if (!(user$privileges(__U)&u_is_advertizer_admin)) {
        m["~advertizeradm~"]="<!--";
        m["~eadvertizeradm~"]="-->";
    } else {
        m["~advertizeradm~"]="";
        m["~eadvertizeradm~"]="";
    }

    if (!(user$privileges(__U)&u_is_credit_operator)) {
        m["~credopadm~"]="<!--";
        m["~ecredopadm~"]="-->";
    } else {
        m["~credopadm~"]="";
        m["~ecredopadm~"]="";
    }

    m["~level~"]=itostring(cc->sub_level);
    cc->html_out=make_pair(m,"admin/index");
}




string log_name();

void url_admin_logs(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);

    if (!(user$privileges(__U)&u_allow_view_logs)) {
        return;
    }
    int levelsub_levels=cc->sub_level;

    string logname = log_name();


    st_FILE f(logname,"r");
    vector<string> v;
    try {
        while (1) {
            st_malloc buf(300);
            f.gets((char*)buf.buf,290);
            string z((char*) buf.buf,strlen((char*) buf.buf));
            v.push_back(z);
        }
    }
    catch (...) {
    }
    map<string,hstring> K;
    cc->html_out=make_pair(K,"admin/logs/logs");
    for (int i=v.size()-1;i>=0;i--) {
        string q=remove_tags(v[i]);
        if (q.find("logged in",0)!=-1) {
            cc->html_out+="<font class=lg>"+q+"</font><br>";
            continue;
        }
        if (q.find("--Error",0)!=-1) {
            if (levelsub_levels==am_sadmin) cc->html_out+="<font class=er>"+q+"</font><br>";
            continue;
        }
        if (q.find("kicked",0)!=-1) {
            cc->html_out+="<font class=kick>"+q+"</font><br>";
            continue;
        }
        if (q.find("banned",0)!=-1) {
            cc->html_out+="<font class=ban>"+q+"</font><br>";
            continue;
        }
        if (levelsub_levels!=am_sadmin) continue;
        cc->html_out+=remove_tags(q)+"<br>";
    }
}


void url_pic_adm(const PTR_getter<chat_user> &__U,cs_conn_data *);
void url_anek_adm(const PTR_getter<chat_user> &__U,cs_conn_data *);
void url_hist_adm(const PTR_getter<chat_user> &__U,cs_conn_data *);

void url_admin_settings(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void url_admin_privs(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void url_admin_vote(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void url_admin_hints(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void url_admin_news(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void url_admin_accounts(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void url_admin_levelup(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void url_admin_leveldown(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void url_admin_credgen(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void url_admin_ipban(const PTR_getter<chat_user> &__UU,cs_conn_data *cc);
void url_admin_loginban(const PTR_getter<chat_user> &__UU,cs_conn_data *cc);
void url_admin_nickban(const PTR_getter<chat_user> &__UU,cs_conn_data *cc);
void url_admin_channels(const PTR_getter<chat_user> &__UU,cs_conn_data *cc);
struct smile_st
{
    unsigned int id;
    string key,val;
    double cost;
    string grp;
    bool is_sound;
    bool enabled;
};
static int sm_sort(const smile_st& a,const smile_st &  b)
{
    return a.grp<b.grp;
}
void load_smiles()
{
    st_dbh d;
    vector<vector<string> >v=d.dbh->exec("select id,_key,_val,cost,grp,is_sound,enabled from smiles where deleted<>'1' and enabled='1' order by grp");
}
void url_admin_smiles(const PTR_getter<chat_user> &__UU,cs_conn_data* cc)
{
    user_pair __U(__UU);
    if (!(user$privileges(__U)&u_is_smiles_admin)) {
        return;
    }
    if (cc->params["todo"]=="delete")
    {
        unsigned int id=atoi(cc->params["id"].c_str());
        st_dbh d;
        d.dbh->real_queryQ((QUERY)"update smiles set deleted='1' where id=?"<<id);
    }
    if (cc->params["todo"]=="enable")
    {
        unsigned int id=atoi(cc->params["id"].c_str());
        st_dbh d;
        d.dbh->real_queryQ((QUERY)"update smiles set enabled='1' where id=?"<<id);
    }
    if (cc->params["todo"]=="disable")
    {
        unsigned int id=atoi(cc->params["id"].c_str());
        st_dbh d;
        d.dbh->real_queryQ((QUERY)"update smiles set enabled='0' where id=?"<<id);
    }
    if (cc->params["todo"]=="new")
    {
        string key=cc->params["key"];
        string val=cc->params["val"];
        double cost=atof(cc->params["cost"].c_str());
        string grp=cc->params["grp"];
        bool is_sound=cc->params["is_sound"]=="on";
        st_dbh d;
        d.dbh->real_queryQ((QUERY)"insert into smiles (_key,_val,deleted,cost,grp,is_sound,enabled) values('?','?','0',?,'?','?','0')"<<
                           key<<val<<cost<<grp<<is_sound);
    }
    st_dbh d;
    vector<vector<string> >v=d.dbh->exec("select id,_key,_val,cost,grp,is_sound,enabled from smiles where deleted<>'1' order by grp");
    map<string,vector<smile_st> > vsm;
    for (unsigned i=0;i<v.size();i++)
    {
        map<string,hstring>q;
        if (v[i].size()==7)
        {
            smile_st sm;
            sm.id=atoi(v[i][0].c_str());
            sm.key=v[i][1];
            sm.val=v[i][2];
            sm.cost=atof(v[i][3].c_str());
            sm.grp=v[i][4];
            sm.is_sound=atoi(v[i][5].c_str());
            sm.enabled=atoi(v[i][6].c_str());
            vsm[sm.grp].push_back(sm);
        }
    }
    hstring tb;
    {
        for (map<string,vector<smile_st> >::iterator i=vsm.begin();i!=vsm.end();i++)
        {
            {
                map<string,hstring>q;
                string s="admin/smiles/names/"+i->first;
                q["~name~"]=make_pair(q,s);
                tb+=make_pair(q,"admin/smiles/head_grp");
            }
            for (vector<smile_st>::iterator j=i->second.begin();j!=i->second.end();j++)
            {
                map<string,hstring>q;
                q["~id~"]=itostring(j->id);
                q["~key~"]=j->key;
                q["~val~"]=j->val;
                q["~cost~"]=get_f22(j->cost);
                if (j->enabled)
                    q["~state~"]=make_pair(q,"admin/smiles/_enabled");
                else
                    q["~state~"]=make_pair(q,"admin/smiles/_disabled");

                if (j->is_sound)
                {
                    tb+=make_pair(q,"admin/smiles/row_snd");
                }
                else
                {
                    tb+=make_pair(q,"admin/smiles/row");
                }
            }
        }
    }

    map<string,hstring> m;
    m["~rows~"]=tb;
    cc->html_out+=make_pair(m,"admin/smiles/index");
}



void url_admin(const PTR_getter<chat_user> &__U,cs_conn_data* cc)
{
    switch_cc_ret("ipban",url_admin_ipban(__U,cc));
    switch_cc_ret("loginban",url_admin_loginban(__U,cc));
    switch_cc_ret("nickban",url_admin_nickban(__U,cc));
    switch_cc_ret("logs",url_admin_logs(__U,cc));
    switch_cc_ret("logininfo",url_admin_logininfo(__U,cc));
    switch_cc_ret("userlist",url_admin_userlist(__U,cc));
    switch_cc_ret("userlist_command",url_admin_userlist_command(__U,cc));
    switch_cc_ret("settings",url_admin_settings(__U,cc));
    switch_cc_ret("privileges",url_admin_privs(__U,cc));
    switch_cc_ret("vote",url_admin_vote(__U,cc));
    switch_cc_ret("hints",url_admin_hints(__U,cc));
    switch_cc_ret("news",url_admin_news(__U,cc));
    switch_cc_ret("accounts",url_admin_accounts(__U,cc));
    switch_cc_ret("pictures",url_pic_adm(__U,cc));
    switch_cc_ret("anekdots",url_anek_adm(__U,cc));
    switch_cc_ret("histories",url_hist_adm(__U,cc));
    switch_cc_ret("channels",url_admin_channels(__U,cc));
    switch_cc_ret("levelup",url_admin_levelup(__U,cc));
    switch_cc_ret("leveldown",url_admin_leveldown(__U,cc));
    switch_cc_ret("smiles",url_admin_smiles(__U,cc));
    switch_cc_ret("credgen",url_admin_credgen(__U,cc));
    url_admin_index(__U,cc);
}
