#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <time.h>
#include <map>
#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include "web_server.h"
#include "message.h"
#include "chat_def.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "register.h"
#include "copy_file.h"
#include "wrappers.h"
#include "web_tools.h"
#include "file_set.h"
#include "user_credits.h"
#include "levels.h"
#include "server_config.h"
#include "chat_colors.h"
#include "app_def.h"
#include "chat_config.h"

#include "update_cmd.h"

#include "contact_vec.h"
#include "cs_conn_data.h"
#include "html_out.h"
#include "chat_globals.h"
#include "user_stat.h"
#include <math.h>
int get_used_space(const user_pair& __U);
void url_settings_status(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    if (!__UU) {
        cc->html_out=cc->redirect();
        return;
    }
    user_pair __U(__UU);


    bool changed=false;
    bool data=cc->params["DATA"]!="";
    map<string,hstring> m;
    if (cc->params["new_s"]=="yes") {

        user_status s;
        s.name=_MSG("unnamed");
        s.pic=1;
        int max_id=0;
        {
            {
                PGLW(user_profile,u,user_profiles.find_by_id(cc->user_id));
                map<unsigned int,user_status> &st=u->status;
                for (map<unsigned int,user_status> ::iterator i=st.begin();i!=st.end();i++)
                {
                    if (i->first>max_id)max_id=i->first;
                }
                max_id++;
                s.id=max_id;
                s.disable_invite=false;
                st[max_id]=s;
            }
            send_update_g4(status$add,cc->user_id,max_id,s);
        }
        changed=false;
    }

    if (cc->params["remove"]!="") {
        int z=atoi(cc->params["remove"]);
        {
            {
                PGLW(user_profile,u,user_profiles.find_by_id(cc->user_id));
                map<unsigned int,user_status>  &st=u->status;
                st.erase(z);
            }
            send_update_g3(status$remove,cc->user_id,z);
        }
        changed=true;
    }

    bool need_location_reload=false;
    if (data) {
        PGLW(user_profile,u,user_profiles.find_by_id(cc->user_id));
        map<unsigned int,user_status>  &st=u->status;
        for (map<unsigned int,user_status> ::iterator i=st.begin();i!=st.end();i++)
        {
            if (i->first<=st_na) continue;
            string s=cc->params["st"+itostring(i->first)];
            if (s.size()>35) s=s.substr(0,35);
            s=str_replace("&","&amp;",s);
            s=str_replace("<","&lt;",s);
            s=str_replace(">","&gt;",s);
            s=str_replace("'","",s);
            s=str_replace("\\\\","",s);
            user_status stt;
            stt.name=s;
            stt.pic=atoi(cc->params["spi"+itostring(i->first)]);
            {
                string ppn=(string)chat_config.status_dir+"/sp"+itostring(stt.pic)+".gif";
                struct stat sta;
                if (stat(ppn.c_str(),&sta)==-1) {
                    stt.pic=1;
                }
            }
            stt.disable_invite=strupper(cc->params["sc"+itostring(i->first)])=="ON";
            if (stt.pic>990) stt.pic=1;

            if (st[i->first]!=stt)
            {
                st[i->first]=stt;
                send_update_g4(status$add,cc->user_id,i->first,stt);
            }
            changed=true;
        }
    }

    {
        if (changed) {
        }
        m["~st3~"]=get_user_status_by_id(__U,3).name;
        m["~st4~"]=get_user_status_by_id(__U,4).name;
        m["~st5~"]=get_user_status_by_id(__U,5).name;
        m["~st6~"]=get_user_status_by_id(__U,6).name;
        m["~st7~"]=get_user_status_by_id(__U,7).name;
        m["~st8~"]=get_user_status_by_id(__U,8).name;
        hstring sts;
        {

            PGLW(user_profile,u,__U.up);
            map<unsigned int,user_status> & st=u->status;

            for (map<unsigned int,user_status> ::iterator i=st.begin();i!=st.end();i++)
            {
                if (i->first<=st_na) continue;

                user_status &s=i->second;
                map<string,hstring> q;
                q["~i~"]=itostring(i->first);
                q["~name~"]=ESB(s.name);
                q["~picn~"]=itostring(s.pic);
                q["~id~"]=itostring(i->first);
                if (s.disable_invite) {
                    q["~checked~"]="checked";
                } else {
                    q["~checked~"]="";
                }
                sts+=make_pair(q,"settings/status_row");
            }
        }
        m["~userdef~"]=sts;
    }

    if (need_location_reload)
    {
        data_push_back(__UU,"<script>window.top.addmessage.location.reload();</script>");
    }
    m["~error~"]="";
    if (data) {
        m["~error~"]=_MSG("changed2");
    }

    cc->html_out=make_pair(m,"settings/status");
}

void url_settings_colors(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    if (!__UU) {
        cc->html_out=cc->redirect();
        return;
    }
    user_pair __U(__UU);


    map<string,hstring> m;
    bool data=cc->params["DATA"]!="";
    c_level lv=LEVELS(user$level(__U));
    set<unsigned int> cps=lv.colors;
    m["~error~"]="";
    {

        if (data) {
            unsigned int np=atoi(cc->params["ncolor"]);
            {
                PGLW(chat_user, u,__U.cu);
                if (!cps.count(np)) np=c_packs.get_first_id();
            }
            {
                PGLW(user_set, u,__U.us);
                if (u->n_color_pack!=np)
                {
                    u->n_color_pack=np;
                    send_update_g3(user_set$n_color_pack,cc->user_id,u->n_color_pack);
                }
            }
        }

        m["~error~"]=_MSG("changed2");
    }
    string s;
    string im;
    for (set<unsigned int>::iterator  i=cps.begin();i!=cps.end();i++) {

        map<string,hstring> q;
        string name,imagefname,nickstyle;
        if (!c_packs.count(*i)) continue;

        {
            PGLR(c_pack, c,c_packs.get(*i));
            name=c->name;
            imagefname=c->imagefname;
            nickstyle=c->nickstyle;
        }
        s+="<option value="+itostring(*i)+" style='"+nickstyle+"'";
        if (*i==user$n_color_pack(__U)) {
            s+=" SELECTED";
        }
        s+=">"+name;
        im+="imgnames["+itostring(*i)+"]='"+imagefname+"';\r\n";
    }
    m["~color_packs~"]=s;
    m["~imgnames~"]=im;
    cc->html_out=make_pair(m,"settings/colors");
}

void url_settings_chat(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    if (!__UU) {
        cc->html_out=cc->redirect();
        return;
    }
    user_pair __U(__UU);

    map<string,hstring> m;
    bool data=cc->params["DATA"]!="";
    string cn=GET_CNICK(__U);

    {
        string st;
        string e;
        bool need_reload=false;
        if (data) {
            PGLW(user_set, u,__U.us);

            int lpp=atoi(cc->params["lpp"]);
            if (lpp>100 || lpp<=0) {
                lpp=10;
            }
            if (u->lpp!=lpp)
            {
                u->lpp=lpp;
                send_update_g3(user_set$lpp,cc->user_id,u->lpp);
            }
            bool setting_autochange=strupper(cc->params["autochange"])=="ON";
            if (setting_autochange!=u->setting_autochange)
            {
                u->setting_autochange=setting_autochange;
                send_update_g3(user_set$setting_autochange,cc->user_id,u->setting_autochange);

            }
            bool setting_show_hints=strupper(cc->params["showhints"])=="ON";
            if (setting_show_hints!=u->setting_show_hints)
            {
                u->setting_show_hints=setting_show_hints;
                send_update_g3(user_set$setting_show_hints,cc->user_id,u->setting_show_hints);

            }


            bool show_credits=strupper(cc->params["showcredits"])=="ON";
            if (show_credits!=u->show_credits)
            {
                u->show_credits=show_credits;
                send_update_g3(user_set$show_credits,cc->user_id,u->show_credits);

            }


            bool setting_show_stat=strupper(cc->params["showstat"])=="ON";
            if (u->setting_show_stat!=setting_show_stat)
            {
                u->setting_show_stat=setting_show_stat;
                send_update_g3(user_set$setting_show_stat,cc->user_id,u->setting_show_stat);

            }

            bool setting_invite_sound=strupper(cc->params["inv_sound"])=="ON";
            if (u->setting_invite_sound!=setting_invite_sound)
            {
                u->setting_invite_sound=setting_invite_sound;
                send_update_g3(user_set$setting_invite_sound,cc->user_id,u->setting_invite_sound);

            }

            bool setting_full_buttons=strupper(cc->params["full_buttons"])=="ON";
            if (u->setting_full_buttons!=setting_full_buttons)
            {
                u->setting_full_buttons=setting_full_buttons;
                send_update_g3(user_set$setting_full_buttons,cc->user_id,u->setting_full_buttons);

            }

            bool show_nicks=strupper(cc->params["snicks"])=="ON";
            if (u->show_nicks!=show_nicks)
            {
                u->show_nicks=show_nicks;
                send_update_g3(user_set$show_nicks,cc->user_id,u->show_nicks);
            }

            bool show_level=strupper(cc->params["slevel"])=="ON";
            if (u->show_level!=show_level)
            {
                u->show_level=show_level;
                send_update_g3(user_set$show_level,cc->user_id,u->show_level);
            }


            unsigned int copt=0;
            if (strupper(cc->params["in_contact"])=="ON")
                copt|=user_set::CONTACT_ADD_IN_PRIV;
            if (strupper(cc->params["out_contact"])=="ON")
                copt|=user_set::CONTACT_ADD_OUT_PRIV;
            if (copt!=u->contact_options)
            {
                u->contact_options=copt;
                send_update_g3(user_set$contact_options,cc->user_id,u->contact_options);
                need_reload=true;
            }
        }
        string s;

        m["~lpp~"]=itostring(user$lpp(__U));
        {
            PGLR(user_set, u,__U.us);
            m["~ac~"]=checked(u->setting_autochange);		//autochange
            m["~sh~"]=checked(u->setting_show_hints);		//show_hints
            m["~sc~"]=checked(u->show_credits);
            m["~ss~"]=checked(u->setting_show_stat);		//show_stat
            m["~sn~"]=checked(u->show_nicks);	//show all nicks?
            m["~sl~"]=checked(u->show_level);	//show level?
            int contact_options=u->contact_options;
            m["~in_contact~"]=checked(contact_options & user_set::CONTACT_ADD_IN_PRIV);
            m["~out_contact~"]=checked(contact_options & user_set::CONTACT_ADD_OUT_PRIV);

            m["~is~"]=checked(u->setting_invite_sound);	//invite sound?
            m["~fb~"]=checked(u->setting_full_buttons);	//display full buttons?
        }

        m["~error~"]="";
        if (data) {
            m["~error~"]=_MSG("changed2");
        }
        cc->html_out=make_pair(m,"settings/chat");
    }

}

void url_settings_credits(const PTR_getter<chat_user> &__UU,cs_conn_data *cc);
string get_f22(double dd);
void url_settings_privs(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    if (!__UU) {
        cc->html_out=cc->redirect();
        return;
    }
    user_pair __U(__UU);
    map<string,hstring>m;
    unsigned int lev_id;
    map<unsigned int,c_level> levels=get_all_levels();
    hstring error;
    DB_id uid;
    lev_id=user$level(__U);
    unsigned char gender=user$gender(__U);
    uid=user$id(__U);
    m["~current_level_name~"]=LEVEL_NAME(lev_id,gender);
    if (cc->params.count("todo"))
    {
        if (cc->params["todo"]=="buy_invis")
        {

            int value=atoi(cc->params["invis_add"]);
            DB_id invis_saler_account;
            invis_saler_account.container=chat_config2.invis_saler_account.get();
            if (!buy_thing(cc->user_id,invis_saler_account,chat_config2.invis_cost.get()*value, "buy_invis"))
            {
                error=_MSG("not_enough_credits");
            }
            else
            {
                {
                    PGLW(user_set, u,__U.us);
                    u->bought_invisibility=u->bought_invisibility+value*100;
                    send_update_g3(user_set$bought_invisibility,uid,u->bought_invisibility);
                }

            }
        }
        if (cc->params["todo"]=="buy_next_level" && error.hstr_size()==0)
        {
            string ls=chat_config2.levelup_cost;
            double next_cost=0;
            vector<string> v=splitTOK(",",ls);
            for (unsigned int i=0;i<v.size();i++)
            {
                vector<string>vv=splitTOK(":",v[i]);
                if (vv.size()==2)
                {
                    if (atoi(vv[0])==lev_id/sub_levels)next_cost=atof(vv[1].c_str());
                }
            }
            if (next_cost)
            {
                if (credit_reminder(cc->user_id)>=next_cost)
                {
                    c_level new_lvl=LEVELS(atoi(cc->params["nextlevel_select"]));
                    if (new_lvl.id/sub_levels - lev_id/sub_levels>1) error="invalid level";
                    else {

                        DB_id levelup_saler_account;
                        levelup_saler_account.container=chat_config2.levelup_saler_account.get();
                        if (!buy_thing(cc->user_id,levelup_saler_account,next_cost, "levelup"))
                        {
                            error=_MSG("not_enough_credits");
                        }
                        {
                            PGLW(user_profile, u,__U.up);
                            u->level=new_lvl.id;
                            send_update_g3(user_profile$level,cc->user_id,u->level);
                            m["~current_level_name~"]=LEVEL_NAME(u->level,gender);
                            lev_id=u->level;
                        }
                        error=FREP("settings/privs_ch_lev_success");
                    }
                } //if(summa>next_cost)
                else error=FREP("settings/privs_no_eno_money");
            }//if(next_cost)
            else error=FREP("settings/privs_next_nolev");
        }//if(cc->params["todo"]=="buy_next_level")
        if (cc->params["todo"]=="buy_eq_level")
        {
            unsigned int new_lvl=atoi(cc->params["eqlevel_select"]);

            if ((lev_id/sub_levels)!=(new_lvl/sub_levels)) error="invalid level to change";
            else
            {
                if (credit_reminder(cc->user_id)>=chat_config2.change_eqlevel_cost)
                {
                    c_level lvl=LEVELS(new_lvl);

                    DB_id change_eqlevel_saler_account;
                    change_eqlevel_saler_account.container=chat_config2.change_eqlevel_saler_account.get();
                    if (buy_thing(cc->user_id,change_eqlevel_saler_account,chat_config2.change_eqlevel_cost, "eqlevel"))
                    {

                        {
                            PGLW(user_profile, u,__U.up);
                            u->level=lvl.id;
                        }
                        send_update_g3(user_profile$level,cc->user_id,lvl.id);

                        m["~current_level_name~"]=LEVEL_NAME(lvl.id,gender);
                        lev_id=lvl.id;
                    }
                    error=FREP("settings/privs_ch_lev_success");
                }
                else error=FREP("settings/privs_no_eno_money");

            }
        }//if(cc->params["todo"]=="buy_eq_level")
        if (cc->params["todo"]=="buy_quota")
        {
            if (cc->params.count("quota_add"))
            {
                int mbytes=atoi(cc->params["quota_add"]);
                {

                    DB_id quota_saler_account;
                    quota_saler_account.container=chat_config2.quota_saler_account.get();
                    if (buy_thing(cc->user_id,quota_saler_account,chat_config2.quota_cost*mbytes, "quota"))
                    {
                        PGLW(user_set, u,__U.us);
                        u->bought_quota=u->bought_quota+mbytes*MB;
                        send_update_g3(user_set$bought_quota,cc->user_id,u->bought_quota);
                    }

                }
            }
        }


    }//if(cc->params.count("todo"))


    m["~credits~"]=get_f22(credit_reminder(cc->user_id));


    map<string,string> seleqlev;
    for (map<unsigned int,c_level>::iterator i=levels.begin();i!=levels.end();i++)
    {

        if ((lev_id/sub_levels==i->first/sub_levels) && (lev_id!=i->first))
        {
            seleqlev[itostring(i->first)]=i->second.name(gender);
        }
    }
    if (lev_id>=chat_config2.change_eqlevel_limit) seleqlev.clear();
    if (seleqlev.size())
    {
        map<string,hstring>q;
        q["~equal_levels~"]=make_select("eqlevel_select",seleqlev);
        q["~change_eqlevel_cost~"]=get_f22(double(chat_config2.change_eqlevel_cost));
        m["~eq_level_form~"]=make_pair(q,"settings/privs_ch_eq_level");
    }
    else m["~eq_level_form~"]=FREP("settings/privs_ch_eq_nolevel");

    string ls=chat_config2.levelup_cost;
    double next_cost=0;
    vector<string> v=splitTOK(",",ls);
    {
        for (unsigned int i=0;i<v.size();i++)
        {
            vector<string>vv=splitTOK(":",v[i]);
            if (vv.size()==2)
            {
                if (atoi(vv[0])==lev_id/sub_levels)next_cost=atof(vv[1].c_str());
            }
        }
    }

    if (next_cost)
    {
        map<string,hstring>q;
        q["~next_level_cost~"]=get_f22(next_cost);
        map<string,string> selnextlev;
        for (map<unsigned int,c_level>::iterator i=levels.begin();i!=levels.end();i++)
        {

            if ( (lev_id/sub_levels)+1==i->second.id/sub_levels )
            {
                selnextlev[itostring(i->second.id)]=i->second.name(gender);
            }
        }
        q["~next_level_select~ "]=make_select("nextlevel_select",selnextlev);
        m["~next_level_form~"]=make_pair(q,"settings/privs_next_lev");
    }
    else m["~next_level_form~"]=FREP("settings/privs_next_nolev");

    m["~quota_mb_price~"]=get_f22(chat_config2.quota_cost.get());
    c_level lv=levels[lev_id];
    unsigned int used_space=get_used_space(__U);
    unsigned int quota=lv.quota;
    int invisibility=lv.invisibility;
    int kick_ability=lv.kick_ability;
    int kick_shield=lv.kick_shield;
    unsigned int bought_quota;
    {
        PGLR(user_set,u,__U.us);
        quota+=u->bought_quota;
        bought_quota=u->bought_quota;
    }
    unsigned int level_quota=lv.quota;

    {
        m["~quota~"]=get_f22(double(quota)/MB);
        m["~const_quota~"]=get_f22(double(level_quota)/MB);
        m["~free_space~"]=get_f22(double(quota-used_space)/MB);
        m["~used_space~"]=get_f22(double(used_space)/MB);
        m["~bought_quota~"]=get_f22(double(bought_quota)/MB);
        m["~invisibility~"]=get_f22(double(invisibility)/100);
        m["~kick_ability~"]=get_f22(double(kick_ability)/100);
        m["~kick_shield~"]=get_f22(double(kick_shield)/100);
    }
    {
        m["~invis_cost~"]=get_f22(chat_config2.invis_cost.get());
    }
    m["~error~"]=error;
    cc->html_out+=make_pair(m,"settings/privs");

}
struct smile_st1
{
    unsigned int id;
    string key,val;
    double cost;
    string grp;
    bool is_sound;
    time_t expired;
};
struct contact_display_struct
{
    string nick;
    DB_id uid;
    DB_id nid;
    time_t last_date;
};

int str_ct_d(const contact_display_struct&a, const contact_display_struct&b)
{
    return a.last_date<b.last_date;
}
int str_ct_d$(const contact_display_struct&a, const contact_display_struct&b)
{
    return a.last_date>b.last_date;
}
int str_ct_n(const contact_display_struct&a, const contact_display_struct&b)
{
    return strupper(a.nick)<strupper(b.nick);
}
int str_ct_n$(const contact_display_struct&a, const contact_display_struct&b)
{
    return strupper(a.nick)>strupper(b.nick);
}

void url_settings_edit_contacts(const PTR_getter<chat_user>  &__UU,cs_conn_data *cc)
{
    if (!__UU) {
        cc->html_out=cc->redirect();
        return;
    }
    user_pair __U(__UU);
    vector<DB_id> rm;
    {
        PGLW(contact_vec, u,contact_vecs.find_by_id(user$id(__U)));


        for (set<DB_id> ::iterator i=u->contact.begin();i!=u->contact.end();i++)
        {
            if (strupper(cc->params["cid"+itostring(i->container)])=="ON")
            {
                rm.push_back(*i);
            }
        }
        for (unsigned i=0;i<rm.size();i++)
        {
            u->contact.erase(rm[i]);
            send_update_g3(contact$remove,cc->user_id,rm[i].container);
        }


    }
    if (rm.size() && inchat$(__UU))
    {

        out_oscar_buffer o;
        o<<user_state::RECALC<<user$id(__U);
        set_user_state(o);
    }
    map<string,hstring>m;

    vector<contact_display_struct> vvv;
    vector<DB_id> vsid;
    {
        PGLW(contact_vec, u,contact_vecs.find_by_id(cc->user_id));
        for (set<DB_id> ::iterator i=u->contact.begin();i!=u->contact.end();i++)
            vsid.push_back(*i);
        m["~count~"]=itostring(u->contact.size());
    }
    map<DB_id, pair<pair<time_t,string>,DB_id> > ld;

    for (unsigned i=0;i<vsid.size();i++)
    {
        {
            time_t last_date;
            DB_id last_nick_id;
            string last_nick;
            {
                PGLR(user_stat,u,user_stats.find_by_id(vsid[i]));
                last_date=u->last_date;
            }
            {
                PGLR(user_set,u,user_sets.find_by_id(vsid[i]));
                last_nick=u->last_nick;
                last_nick_id.container=u->last_nick_id;

            }
            ld[vsid[i]]=make_pair(make_pair(last_date,last_nick),last_nick_id);
        }
    }
    {
        PGLW(contact_vec, u,contact_vecs.find_by_id(cc->user_id));
        for (set<DB_id> ::iterator i=u->contact.begin();i!=u->contact.end();i++)
        {
            if (i->container==0) continue;
            if (*i==cc->user_id) continue;
            contact_display_struct c;
            c.uid=*i;
            {
                c.nick=ld[*i].first.second;
                c.nid=ld[*i].second;
            }
            c.last_date=ld[*i].first.first;
            vvv.push_back(c);
        }
    }
    m["~ddir~"]="b";
    m["~ndir~"]="b";

    if (cc->params["srt"]=="d")
    {
        if (cc->params["dir"]=="b")
        {
            m["~ddir~"]="f";
            sort(vvv.begin(),vvv.end(),str_ct_d$);
        }
        else
        {
            m["~ddir~"]="b";
            sort(vvv.begin(),vvv.end(),str_ct_d);
        }
    }
    else // nick
    {
        if (cc->params["dir"]=="b")
        {
            m["~ndir~"]="f";
            sort(vvv.begin(),vvv.end(),str_ct_n$);
        }
        else
        {
            m["~ndir~"]="b";
            sort(vvv.begin(),vvv.end(),str_ct_n);
        }
    }
    hstring rows;
    int start=atoi(cc->params["start"]);

    for (unsigned i=start;i<vvv.size() && i<start+20;i++)
    {
        map<string,hstring> q;
        q["~start~"]=itostring(start);
        q["~uid~"]=itostring(vvv[i].uid.container);
        q["~nid~"]=itostring(vvv[i].uid.container)+"."+itostring(vvv[i].nid.container);
        q["~date~"]=date2num(vvv[i].last_date);
        q["~nick~"]=vvv[i].nick;
        rows+=make_pair(q,"settings/edit_contacts_row");
    }
    m["~rows~"]=rows;
    m["~start~"]=itostring(start);

    int prev_id=-1,next_id=-1;
    if (start>=20)
    {
        prev_id=start-20;
    }
    if (start+20<vvv.size()) next_id=start+20;

    if (prev_id!=-1) {
        m["~prev~"]="href=\"/settings_edit_contacts?start="+itostring(prev_id)+"&srt="+cc->params["srt"]+"&dir="+cc->params["dir"]+"\"";
    } else {
        m["~prev~"]="";
    }
    if (next_id!=-1) {
        m["~next~"]="href=\"/settings_edit_contacts?start="+itostring(next_id)+"&srt="+cc->params["srt"]+"&dir="+cc->params["dir"]+"\"";
    } else {
        m["~next~"]="";
    }
    cc->html_out+=make_pair(m,"settings/edit_contacts");
}

int srt_arr(const pair<string,string>&a, const pair<string,string>&b)
{
    return a.second<b.second;
}
void url_settings_nicks(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{


    map<string,hstring> m;
    m["~N_ALL~"]="";
    m["~N_SELL~"]="";
    m["~N_NOTFORSELL~"]="";
    string filt=cc->params["filter"];
    int nid=atoi(cc->params["nicks"]);

    if (filt=="all") m["~N_ALL~"]="SELECTED";
    else if (filt=="sell") m["~N_SELL~"]="SELECTED";
    else if (filt=="notsell") m["~N_NOTFORSELL~"]="SELECTED";
    vector<pair<string,string> > ns;
    user_nick unsel;
    bool  unsel_inited=false;
    set<unsigned int> in_list;
    //    map<string,int> nick2id;

    if (cc->params.count("nicks"))
    {
        unsigned int sn=atoi(cc->params["nicks"]);
        PGLW(nick_vec, u,nick_vecs.find_by_id(cc->user_id));

        bool update=cc->params["todo"]=="update";
        if (u->u_nicks.count(sn))
        {
            user_nick &ni=u->u_nicks.find(sn)->second;

            if (update)
            {

                if (cc->params["nickname"]!=ni.name && check_nick(cc->params["nickname"]))
                {
                    if (str_nick(cc->params["nickname"])==str_nick(ni.name))
                    {
                        ni.name=cc->params["nickname"];
                        send_update_g4(nick$change_nick,cc->user_id,ni.id,ni.name);
                    }
                }

                if (strupper(cc->params["to_sale"])=="ON")
                {
                    ni.cost=fabs(atof(cc->params["cost"].c_str()));
                    ni.ready_to_sale=true;
                    send_update_d4(nick$change_cost,cc->user_id,ni.id,ni.cost);
                }
                else
                {
                    if (ni.ready_to_sale)
                    {
                        ni.ready_to_sale=false;
                        send_update_g3(nick$unmark_for_sale,cc->user_id,ni.id);
                    }
                }
            }

            unsel=ni;
            unsel_inited=true;



        }
    }
    {
        PGLR(nick_vec, u,nick_vecs.find_by_id(cc->user_id));

        for (map<unsigned int,user_nick>::const_iterator i=u->u_nicks.begin();i!=u->u_nicks.end();i++)
        {
            if (		(filt=="sell" && i->second.ready_to_sale)
                    ||	(filt=="notsell" && !i->second.ready_to_sale)
                    ||	filt=="all" ||filt==""
               )
            {
                ns.push_back(make_pair(itostring(i->first),i->second.name));
                in_list.insert(i->first);

            }
        }
        sort(ns.begin(),ns.end(),srt_arr);
        if (ns.size() && !in_list.count(unsel.id))
        {
            unsigned int id=atoi(ns.begin()->first);
            if (u->u_nicks.count(id))
            {
                unsel=u->u_nicks.find(id)->second;
                unsel_inited=true;
            }

        }
        if (!ns.size())
        {
            unsel_inited=false;
        }
    }
    m["~nicks~"]=make_select("nicks",ns,itostring(nid),"class=sl onchange='document.nickform.submit();return false;'");

    m["~nickname~"]="";
    m["~ts~"]="";
    m["~cost~"]="";
    m["~error~"]="";

    if (cc->params.count("nicks") && !check_nick(cc->params["nickname"]))
    {
        m["~error~"]=_MSG("incorrectnick");
    }
    if (unsel_inited)
    {
        m["~nickname~"]=unsel.name;
        if (unsel.ready_to_sale)m["~ts~"]="CHECKED";
        m["~cost~"]=get_f22(unsel.cost);

    }

    cc->html_out+=make_pair(m,"settings/nicks");

}
