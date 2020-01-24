#include "stdafx.h"
#ifdef _DEBUG
#define New DEBUG_NEW
#endif

#include "_mutex.h"
#include <list>
#include "mutex_inspector.h"
#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include "utils.h"
#include "user.h"
#include "message.h"
#include "web_tools.h"
#include "file_set.h"
#include "notes.h"
#include "user_credits.h"

#include "levels.h"
#include "channels.h"
#include "server_config.h"
#include "chat_config.h"
#include "app_def.h"
#include "user_profile.h"

#include "chat_def.h"
#include "chat_globals.h"
#include "global_state.h"
#include "web_connection.h"
#ifdef __WITH_LICENSE
#include "license.h"
#endif
#include "app_con.h"

void make_login_out_notes(const PTR_getter<chat_user> &__UU,app_connection*cc, const DB_id& id,string &fold, int &new_notes, int &total_notes)
{
    MUTEX_INSPECTOR;
    user_pair __U(__UU);
    LICENSE_CK(8);
    retr_result r=retrive_folders(cc,0,__UU);
    for (unsigned int i=0;i<r.vec_folders.size();i++){
        map<string,string> q;
        {
            q["~id~"]=itostring(r.vec_folders[i].id);
            q["~name~"]=r.vec_folders[i].name;
            q["~cnt~"]=itostring(r.vec_folders[i].cnt);
        }
        {
            int newn=r.vec_folders[i].new_cnt;
            new_notes+=newn;
            if (newn){
                q["~new~"]="";
                q["~enew~"]="";
            }else{
                q["~new~"]="<!--";
                q["~enew~"]="-->";
            }
            q["~newcnt~"]=itostring(newn);
        }
        {
            fold+=RVfiles(q,"login/login_notes_folder");
            total_notes+=r.vec_folders[i].cnt;
        }
    }
}
int get_used_space(const user_pair& __U);
void make_login_out_for_reged(const PTR_getter<chat_user> &__UU,app_connection*cc, map<string,string>&m,Double &summa,int& new_notes, string &fold, int & total_notes)
{
    MUTEX_INSPECTOR;
    user_pair __U(__UU);
    LICENSE_CK(19);
    c_level lv=__LEVELS(user$level(__U));
    DB_id uid=user$id(__UU);
    bool can_addnick=can_add_nick(__U);
    int invisibility=lv.invisibility;
    {
        PGLR(user_profile,u,__U.up);
        invisibility+=u->bought_invisibility;
    }

    int kick_ability=lv.kick_ability;
    int kick_shield=lv.kick_shield;
    int levelup_ability=lv.levelup_ability;

    time_t stat_last_date;
    string stat_last_ip;
    int stat_v_count;
    int stat_m_count;
    time_t stat_t_count;
    unsigned int kick_count;
    unsigned int kicked_count;

    {
        PGLR(user_profile, u,user$profiles.FindByID(CONTAINER(uid)));
		stat_last_date=u->stat_last_date;
		stat_last_ip=u->stat_last_ip;
		stat_v_count=u->stat_v_count;
		stat_m_count=u->stat_m_count;
		stat_t_count=u->stat_t_count;
		kick_count=u->kick_count;
		kicked_count=u->kicked_count;
	}



    bool _inchat=global_state.inchat$www(uid);
    bool u_isinv=is_inv(uid);
    string cnick=GET_CNICK(__U);
    if (_inchat){
        m["~nicks~"]="<b>"+cnick+"</b>";
    }else{
        map<string,string> mm;
        m["~nicks~"]=build_nicks_select(user$id(__UU),"nick",GET_CNICK_ID(__U),"class=sl");
    }
    if (!_inchat)
    {
        if (user$nicks_size(user$id(__UU))!=0){
            m["~rbutt~"]="";
            m["~erbutt~"]="";
        }else{
            m["~rbutt~"]="<!--";
            m["~erbutt~"]="-->";
        }
        if (can_addnick){
            m["~newnick~"]="";
            m["~enewnick~"]="";
        }else{
            m["~newnick~"]="<!--";
            m["~enewnick~"]="-->";
        }
    }else{
        m["~newnick~"]="<!--";
        m["~enewnick~"]="-->";
        m["~rbutt~"]="<!--";
        m["~ebutt~"]="-->";
    }
    bool setting_show_stat;
    {
        PGLR(user_profile,u,__U.up);
        setting_show_stat=u->setting_show_stat;
    }
    if (setting_show_stat){
        map<string,string>q;
        if (summa.container<1){
            q["~calert~"]="";
            q["~ecalert~"]="";
        }else{
            q["~calert~"]="<!--";
            q["~ecalert~"]="-->";
        }
        char ss[200];
        snprintf(ss,sizeof(ss)-1,"%4.2f",summa.container);
        q["~credits~"]=ss;
        if (invisibility>0)
        {
            double ddd;
            ddd=invisibility;
//            ddd/=100;
            char ss[200];
            snprintf(ss,sizeof(ss)-1,"%4.2f",ddd);
            q["~invisibility~"]=ss;
            q["~cinvisibility~"]="";
            q["~einvisibility~"]="";
        }
        else
        {
            q["~cinvisibility~"]="<!--";
            q["~einvisibility~"]="-->";

        }
        if (kick_ability>0)
        {
            double ddd;
            ddd=kick_ability;
//            ddd/=100;
            char ss[200];
            snprintf(ss,sizeof(ss)-1,"%4.2f",ddd);
            q["~kick_ability~"]=ss;
            q["~ckick_ability~"]="";
            q["~ekick_ability~"]="";
        }
        else
        {
            q["~ckick_ability~"]="<!--";
            q["~ekick_ability~"]="-->";
        }
        if (kick_shield>0)
        {
            double ddd;
            ddd=kick_shield;
//            ddd/=100;
            char ss[200];
            snprintf(ss,sizeof(ss)-1,"%4.2f",ddd);
            q["~kick_shield~"]=ss;
            q["~ckick_shield~"]="";
            q["~ekick_shield~"]="";
        }
        else
        {
            q["~ckick_shield~"]="<!--";
            q["~ekick_shield~"]="-->";
        }
        if (levelup_ability>0)
        {
            char ss[200];
            snprintf(ss,sizeof(ss)-1,"%d",levelup_ability);
            q["~levelup~"]=ss;
            q["~clevelup~"]="";
            q["~elevelup~"]="";
        }
        else
        {
            q["~clevelup~"]="<!--";
            q["~elevelup~"]="-->";
        }


        string t;
        t=make_time(stat_t_count);
        q["~viscnt~"]=itostring(stat_v_count);
        q["~msgcnt~"]=itostring(stat_m_count);
        q["~hourcnt~"]=t;
        string df=chat_config.date_format;
        if (df.size()){
            char ss[300];
            tm TM;
            TM=LOCALTIME(stat_last_date);
            size_t  z=strftime(ss,sizeof(ss)-2,df.c_str(),&TM);
            string ld(ss,z);
            {PGLR(user_profile, u,__U.up);
                TM=LOCALTIME(u->reg_date);
            }
            z=strftime(ss,sizeof(ss)-2,df.c_str(),&TM);
            string rd(ss,z);
            q["~lastdate~"]=ld;
            q["~regdate~"]=rd;
        }else{
            q["~lastdate~"]=datetime2rus(stat_last_date);
            {PGLR(user_profile, u,__U.up);
                q["~regdate~"]=date2rus(u->reg_date);
            }
        }
        q["~level~"]=LEVEL_NAME(user$level(__U),user$gender(__U));
        if (user$level(__U)/sub_levels>=am_admin){
            q["~showip~"]="";
            q["~eshowip~"]="";
        }else{
            q["~showip~"]="<!--";
            q["~eshowip~"]="-->";
        }
        q["~ip~"]=stat_last_ip;
        m["~stat~"]=RVfiles(q,"login/statistic");
    }else{
        m["~stat~"]="";
    }
    if (new_notes!=0){
        m["~newn~"]="";
        m["~enewn~"]="";
    }else{
        m["~newn~"]="<!--";
        m["~enewn~"]="-->";
    }
    m["~newnotes~"]=itostring(new_notes);
    m["~folders~"]=fold;
    m["~allnotes~"] = itostring(total_notes);
    if (user$level(__U)/sub_levels>=am_killer || u_has_console(__U)){
        m["~admcon~"]="";
        m["~eadmcon~"]="";
    }else{
        m["~admcon~"]="<!--";
        m["~eadmcon~"]="-->";
    }
    if ((has_inv(__U)) && !_inchat){
        if (u_isinv){
            m["~invcheck~"]=" checked";
        }else{
            m["~invcheck~"]="";
        }
        m["~inv~"]="";
        m["~einv~"]="";
    }else{
        m["~inv~"]="<!--";
        m["~einv~"]="-->";
    }
    if (user$level(__U)/sub_levels>=am_admin && !_inchat){
        {
            PGLR(user_profile,u,__U.up);
            if (u->setting_show_eye)
                m["~eyecheck~"]="checked";
            else
                m["~eyecheck~"]="";
        }
        m["~eye~"]="";
        m["~eeye~"]="";
        map<string,string> q;
        unsigned int nm;
        if (user$level(__U)/sub_levels==am_admin){
            nm=chat_config.number_of_eyes;
        }else{
            nm=chat_config.number_of_eyes_for_main_admin;
        }
        for (unsigned int i=0;i<nm;i++){
            q[itostring(i)]=_MSG("eye"+itostring(i));
        }
        int setting_lpp;
        {
            PGLR(user_profile, u,__U.up);
            setting_lpp=u->setting_lpp;
        }

        m["~eyes~"]=make_select("eye",q,itostring(setting_lpp));
    }else{
        m["~eye~"]="<!--";
        m["~eeye~"]="-->";
        m["~eyes~"]="";
    }
}
void make_login_out(const PTR_getter<chat_user> &__UU,app_connection*cc)
{
    LICENSE_CK(11);
    MUTEX_INSPECTOR;
    if (!__UU){ cc->html_out=cc->redirect();return;}
    DB_id cc_user_id=user$id(__UU);

    user_pair __U(__UU);

    string fold;
    int new_notes=0;
    int total_notes=0;
    LICENSE_CK(10);
    make_login_out_notes(__UU,cc,cc_user_id, fold, new_notes, total_notes);
    map<string,string> mmm;
    {
        MUTEX_INSPECTOR;
        __UC_LOCK;
        u->cu_ip=cc->peer_ipaddress;
        u->ua=cc->headers["USER-AGENT"];
        if (cc->params["scr"].size()) u->www_screen_resolution=cc->params["scr"];
    }
    {
        MUTEX_INSPECTOR;
        mmm["~login~"]=user$login(__U);
        mmm["~button~"]="";
        mmm["~msg~"]="";

    }
    Double summa=credit_reminder(cc_user_id);


    make_login_out_for_reged(__UU,cc,mmm,summa, new_notes, fold, total_notes);

    vector<pair<CH_id,string > > c;
    vector<CH_id>chs=chat_channels._keys();//splitTOK(" ,",chat_config.channel_list.get());

    for (unsigned int i=0;i<chs.size();i++){
        MUTEX_INSPECTOR;
        if (chat_channels.count(chs[i]))
        {
            MUTEX_INSPECTOR;
            __CH_LOCK(chat_channels[chs[i]]);
            c.push_back(make_pair(chs[i],CH->cd.name));
        }
    }

    set<CH_id> __uch=global_state.get_user_channel(T_WWW,user$id(__UU));

    if (__uch.size()){
        MUTEX_INSPECTOR;
        string s1=_MSG("alreadyinchat");
        s1+="<br><br>";
        mmm["~msg~"]=s1;
        {
            MUTEX_INSPECTOR;
            __CH_LOCK(chat_channels[*__uch.begin()]);
            string s2="<b>";
            s2+=CH->cd.name;
            s2+="</b>";
            mmm["~channels~"]=s2;
        }
    }else{
        CH_id chan;CONTAINER(chan)=0;
        {
            MUTEX_INSPECTOR;
            PGLR(user_profile, u,__U.up);
            chan=u->last_channel;
        }

        mmm["~channels~"]=make_select("channel",c,chan,"class=sl");
    }

    if (chs.size()==1){
        mmm["~schannel~"]="<!--";
        mmm["~eschannel~"]="-->";
    }else{
        mmm["~schannel~"]="";
        mmm["~eschannel~"]="";
    }
    {
        MUTEX_INSPECTOR;
        mmm["~name~"] = get_full_name(__U);
        mmm["~nusr~"] = "";
        mmm["~uid~"]=itostring(CONTAINER(cc_user_id));
        cc->html_out+=cc->rvfiles(mmm,"login/login");
    }
}
