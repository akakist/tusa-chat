#include "stdafx.h"
#include "_mutex.h"
#include <list>
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
#include "chat_funny.h"
#include "levels.h"
#include "channels.h"
#include "server_config.h"
#include "chat_config.h"
#include "app_def.h"
#include "user_stat.h"
#include "cs_conn_data.h"
#include "chat_def.h"
#include "chat_globals.h"

void make_login_out_notes(const PTR_getter<chat_user> &__UU,cs_conn_data *cc, const DB_id& id,hstring &fold, int &new_notes, int &total_notes)
{
    user_pair __U(__UU);

    retr_result r=retrive_folders(cc,0,__UU);
    for (unsigned int i=0;i<r.vec_folders.size();i++) {
        map<string,hstring> q;
        {
            q["~id~"]=itostring(r.vec_folders[i].id);
            q["~name~"]=r.vec_folders[i].name;
            q["~cnt~"]=itostring(r.vec_folders[i].cnt);
        }
        {
            int newn=r.vec_folders[i].new_cnt;
            new_notes+=newn;
            if (newn) {
                q["~new~"]="";
                q["~enew~"]="";
            } else {
                q["~new~"]="<!--";
                q["~enew~"]="-->";
            }
            q["~newcnt~"]=itostring(newn);
        }
        {
            fold+=make_pair(q,"login/login_notes_folder");
            total_notes+=r.vec_folders[i].cnt;
        }
    }
}
void make_login_out_for_notreged(const PTR_getter<chat_user> &__UU,cs_conn_data *cc, map<string,hstring>&m,double &summa,int& new_notes, hstring &fold, int & total_notes)
{
    if (!__UU) return;
    map<string,string> g;
    g["0"]=_MSG("sex0");
    g["1"]=_MSG("sex1");
    g["2"]=_MSG("sex2");
    bool is_reged=false;
    if (inchat$(__UU)) is_reged=true;
    user_pair __U(__UU);
    set<CH_id>uch=user$channel(__U);
    if (uch.size()!=1) throw cError("uch.size()!=1 ");
    if (is_reged) {
        m["~gender~"]="<b>"+g[itostring(user$gender(__U))]+"</b>";
        {
            __CH_LOCK(chat_channels[*uch.begin()]);
            m["~channel~"]="<b>"+CH->cd.name()+"</b>";
        }
    } else {
        m["~gender~"]=make_select("gender",g,"0","class=sl");
    }

}
int get_used_space(const user_pair& __U);
void make_login_out_for_reged(const PTR_getter<chat_user> &__UU,cs_conn_data *cc, map<string,hstring>&m,double &summa,int& new_notes, hstring &fold, int & total_notes)
{
    user_pair __U(__UU);

    c_level lv=LEVELS(user$level(__U));
    DB_id uid=user$id(__U);
    bool can_addnick=can_add_nick(__U);
    int quota=lv.quota;
    int used_space=get_used_space(__U);
    int invisibility=lv.invisibility;
    {
        PGLR(user_set,u,__U.us);
        quota+=u->bought_quota;
        invisibility+=u->bought_invisibility;
    }

    int kick_ability=lv.kick_ability;
    int kick_shield=lv.kick_shield;
    int levelup_ability=lv.levelup_ability;
    int leveldown_ability=lv.leveldown_ability;
    time_t last_date;
    string last_ip;
    int v_count;
    int m_count;
    time_t t_count;
    unsigned int kick_count;
    unsigned int kicked_count;
//    if(uid.container<UNREG_BASE)
    {
        {
            PGLR(user_stat, u,user_stats.find_by_id(uid));
            last_date=u->last_date;
            last_ip=u->last_ip;
            v_count=u->v_count;
            m_count=u->m_count;
            t_count=u->t_count;
            kick_count=u->kick_count;
            kicked_count=u->kicked_count;
        }
    }


    bool _inchat=inchat$(__U.cu);
    bool u_isinv=is_inv(__U);
    string cnick=GET_CNICK(__U);
    if (_inchat) {
        m["~nicks~"]="<b>"+cnick+"</b>";
    } else {
        map<string,hstring> mm;
        m["~nicks~"]=build_nicks_select(__U,"nick",GET_CNICK_ID(__U),"class=sl");
    }
    if (!_inchat) {
        if (user$nicks_size(__U)!=0) {
            m["~rbutt~"]="";
            m["~erbutt~"]="";
        } else {
            m["~rbutt~"]="<!--";
            m["~erbutt~"]="-->";
        }
        if (can_addnick) {
            m["~newnick~"]="";
            m["~enewnick~"]="";
        } else {
            m["~newnick~"]="<!--";
            m["~enewnick~"]="-->";
        }
    } else {
        m["~newnick~"]="<!--";
        m["~enewnick~"]="-->";
        m["~rbutt~"]="<!--";
        m["~ebutt~"]="-->";
    }
    bool setting_show_hints,setting_show_stat;
    {
        PGLR(user_set,u,__U.us);
        setting_show_hints=u->setting_show_hints;
        setting_show_stat=u->setting_show_stat;
    }
    if (setting_show_hints) {
        map<string,hstring> q;
        q["~hint~"]=HINTS();
        m["~hint~"]=make_pair(q,"login/hint");
    }
    else {
        m["~hint~"]="";
    }
    if (setting_show_stat) {
        map<string,hstring>q;
        if (summa<1) {
            q["~calert~"]="";
            q["~ecalert~"]="";
        } else {
            q["~calert~"]="<!--";
            q["~ecalert~"]="-->";
        }
        char ss[200];
        snprintf(ss,sizeof(ss)-1,"%4.2f",summa);
        q["~credits~"]=ss;
        if (invisibility>0)
        {
            double ddd;
            ddd=invisibility;
            ddd/=100;
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
            ddd/=100;
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
            ddd/=100;
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
        if (leveldown_ability>0)
        {
            char ss[200];
            snprintf(ss,sizeof(ss)-1,"%d",leveldown_ability);
            q["~leveldown~"]=ss;
            q["~cleveldown~"]="";
            q["~eleveldown~"]="";
        }
        else
        {
            q["~cleveldown~"]="<!--";
            q["~eleveldown~"]="-->";
        }


        string t;
        t=make_time(t_count);
        q["~viscnt~"]=itostring(v_count);
        q["~msgcnt~"]=itostring(m_count);
        q["~hourcnt~"]=t;
        string df=chat_config.date_format;
        if (df.size()) {
            char ss[300];
            tm TM;
            TM=LOCALTIME(last_date);
            int z=strftime(ss,sizeof(ss)-2,df.c_str(),&TM);
            string ld(ss,z);
            {
                PGLR(user_profile, u,__U.up);
                TM=LOCALTIME(u->reg_date);
            }
            z=strftime(ss,sizeof(ss)-2,df.c_str(),&TM);
            string rd(ss,z);
            q["~lastdate~"]=ld;
            q["~regdate~"]=rd;
        } else {
            q["~lastdate~"]=datetime2rus(last_date);
            {
                PGLR(user_profile, u,__U.up);
                q["~regdate~"]=date2rus(u->reg_date);
            }
        }
        q["~level~"]=LEVEL_NAME(user$level(__U),user$gender(__U));
        if (quota-used_space<=10000) {
            q["~alert~"]="";
            q["~ealert~"]="";
        } else {
            q["~alert~"]="<!--";
            q["~ealert~"]="-->";
        }
        if (used_space>quota) {
            q["~freespace~"]=number2text(0);
            q["~allspace~"]=number2text(quota);
            q["~per~"]="0";
        } else {
            q["~freespace~"]=number2text(quota - used_space);
            q["~allspace~"]=number2text(quota);
            if (quota)
                q["~per~"]=itostring(100-((used_space*100)/quota));
            else q["~per~"]=itostring(100-((used_space*100)/(quota+1)));
        }
        if (user$level(__U)/sub_levels>=am_admin) {
            q["~showip~"]="";
            q["~eshowip~"]="";
        } else {
            q["~showip~"]="<!--";
            q["~eshowip~"]="-->";
        }
        q["~ip~"]=last_ip;
        m["~stat~"]=make_pair(q,"login/statistic");
    } else {
        m["~stat~"]="";
    }
    if (new_notes!=0) {
        m["~newn~"]="";
        m["~enewn~"]="";
    } else {
        m["~newn~"]="<!--";
        m["~enewn~"]="-->";
    }
    m["~newnotes~"]=itostring(new_notes);
    m["~folders~"]=fold;
    m["~allnotes~"] = itostring(total_notes);
    if (user$level(__U)/sub_levels>=am_killer || u_has_console(__U)) {
        m["~admcon~"]="";
        m["~eadmcon~"]="";
    } else {
        m["~admcon~"]="<!--";
        m["~eadmcon~"]="-->";
    }
    if ((has_inv(__U)) && !_inchat) {
        if (u_isinv) {
            m["~invcheck~"]=" checked";
        } else {
            m["~invcheck~"]="";
        }
        m["~inv~"]="";
        m["~einv~"]="";
    } else {
        m["~inv~"]="<!--";
        m["~einv~"]="-->";
    }
    if (user$level(__U)/sub_levels>=am_admin && !_inchat) {
        {
            PGLR(user_set,u,__U.us);
            if (u->setting_show_eye)
                m["~eyecheck~"]="checked";
            else
                m["~eyecheck~"]="";
        }
        m["~eye~"]="";
        m["~eeye~"]="";
        map<string,string> q;
        unsigned int nm;
        if (user$level(__U)/sub_levels==am_admin) {
            nm=chat_config.number_of_eyes;
        } else {
            nm=chat_config.number_of_eyes_for_main_admin;
        }
        for (unsigned int i=0;i<nm;i++) {
            q[itostring(i)]=_MSG("eye"+itostring(i));
        }
        m["~eyes~"]=make_select("eye",q,itostring(user$neye(__U)));
    } else {
        m["~eye~"]="<!--";
        m["~eeye~"]="-->";
        m["~eyes~"]="";
    }
}
void make_login_out(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);
    DB_id uid;
    uid=user$id(__U);
    hstring fold;
    int new_notes=0;
    int total_notes=0;
    make_login_out_notes(__UU,cc,uid, fold, new_notes, total_notes);
    map<string,hstring> mmm;
    {
        __UC_LOCK;
        u->cu_ip=cc->peer_ipaddress;
        u->www_proxy_ip=cc->proxy_ip;
        u->ua=cc->params["USER-AGENT"];
        if (cc->params["scr"].size()) u->www_screen_resolution=cc->params["scr"];
    }
    {
        mmm["~login~"]=user$login(__U);
        mmm["~button~"]="";
        mmm["~msg~"]="";

    }
    double summa=credit_reminder(uid);


    make_login_out_for_reged(__UU,cc,mmm,summa, new_notes, fold, total_notes);

    map<string,string> c;
    vector<CH_id> chs=chat_channels.keys();
    for (unsigned int i=0;i<chs.size();i++) {
        __CH_LOCK(chat_channels[chs[i]]);
        c[itostring(i)]=CH->cd.name();
    }
    bool is_inchat=inchat$(__U.cu);
    unsigned int uch;

    if (is_inchat) {
        set<CH_id>uch=user$channel(__U);
        if (uch.size()!=1) throw cError("uch.size()!=1 "+itostring(uch.size())+" ");
        string s1=_MSG("alreadyinchat");
        s1+="<br><br>";
        mmm["~msg~"]=s1;
        {
            __CH_LOCK(chat_channels[*uch.begin()]);
            string s2="<b>";
            s2+=CH->cd.name();
            s2+="</b>";
            mmm["~channels~"]=s2;
        }
    } else {
        CH_id chan;
        {
            PGLR(user_set, u,__U.us);
            chan.container=u->last_channel;
        }
        int chidx=0;
        for (unsigned int i=0;i<chs.size();i++)
        {
            if (chs[i]==chan)chidx=i;
        }
        mmm["~channels~"]=make_select("channel",c,itostring(chidx),"class=sl");
    }

    if (chs.size()==1) {
        mmm["~schannel~"]="<!--";
        mmm["~eschannel~"]="-->";
    } else {
        mmm["~schannel~"]="";
        mmm["~eschannel~"]="";
    }
    {
        mmm["~name~"] = get_full_name(__U);
        mmm["~nusr~"] = "";
        mmm["~uid~"]=itostring(uid.container);
        cc->html_out+=make_pair(mmm,"login/login");
    }
}
