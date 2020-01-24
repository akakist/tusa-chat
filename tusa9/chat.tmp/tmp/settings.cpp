
#include "stdafx.h"
#ifdef _DEBUG
#define New DEBUG_NEW
#endif

#include "_mutex.h"
#include <list>
#include "mutex_inspector.h"
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
#include "html_out.h"

#include "html_out.h"
#include "chat_globals.h"
#include "user_profile.h"
#include <math.h>
#include "chat_thread_event.h"
#include "app_con.h"
#include "user_credits.h"
#ifdef __WITH_LICENSE
#include "license.h"
#endif

int get_used_space(const user_pair& __U);
void url_settings_status(const PTR_getter<chat_user> &__UU,app_connection*cc)
{
    LICENSE_CK(7);
    MUTEX_INSPECTOR;
    st_update stu;
    if (!__UU){ cc->html_out=cc->redirect();return;}
    DB_id cc_user_id=user$id(__UU);
    user_pair __U(__UU);


    bool changed=false;
    bool data=cc->params["DATA"]!="";
    map<string,string> m;
    if (cc->params["new_s"]=="yes"){
        user_status s;
        s.name=_MSG("unnamed");
        s.pic=1;
		s.disable_invite=false;

        {
            {
                
                /*for (map<unsigned int,user_status> ::const_iterator i=u->status.begin();i!=u->status.end();i++)
                {
                    if (i->first>max_id)max_id=i->first;
                }*/
				st_dbh d;
				d.dbh->real_queryQ((QUERY)"insert into user_status (uid,name, pic,disable_invite) values ('?','?','?','?')"<<CONTAINER(cc_user_id)<<s.name<<s.pic<<s.disable_invite);
                s.id=atoi(d.dbh->select_1("select LAST_INSERT_ID()"));
				{
					PGLW(user_profile,u,user$profiles.FindByID(CONTAINER(cc_user_id)));
					u->status.insert(make_pair(s.id,s));
				}
            }
//	    logErr2("S1");
            //__send_update_d3(user_status$update$3,CONTAINER(cc_user_id),s);
        }
        changed=false;
    }

    if (cc->params["remove"]!=""){
        int z=atoi(cc->params["remove"]);

        {
            {
                PGLW(user_profile,u,user$profiles.FindByID(CONTAINER(cc_user_id)));
                u->status.erase(z);
            }
            __send_update_d3(user_status$remove$3,CONTAINER(cc_user_id),z);
        }
        changed=true;
    }

    bool need_location_reload=false;
    if (data){
        PGLW(user_profile,u,user$profiles.FindByID(CONTAINER(cc_user_id)));
        map<unsigned int,user_status>  &st=u->status;
        for (map<unsigned int,user_status> ::const_iterator i=st.begin();i!=st.end();i++)
        {
            if (i->first<=st_na) continue;
            string s=cc->params["st"+itostring(i->first)];
            if (s.size()>35) s=s.substr(0,35);
            s=str_replace("&","&amp;",s);
            s=str_replace("<","&lt;",s);
            s=str_replace(">","&gt;",s);
            s=str_replace("'","",s);
            s=str_replace("\\\\","",s);
            user_status stt;//=i->second;
            stt.id=i->second.id;
            stt.name=s;
            stt.pic=atoi(cc->params["spi"+itostring(i->first)]);
            {
                string ppn=(string)chat_config.status_dir+"/sp"+itostring(stt.pic)+".gif";
                struct stat sta;
                if (stat(ppn.c_str(),&sta)==-1){
                    stt.pic=1;
                }
            }
            stt.disable_invite=strupper(cc->params["sc"+itostring(i->first)])=="ON";
            if (stt.pic>990) stt.pic=1;

            if (st[i->first]!=stt)
            {
                st[i->first]=stt;
                //logErr2("S2");
                __send_update_d3(user_status$update$3,CONTAINER(cc_user_id),stt);
            }
            changed=true;
        }
    }

    {
        if (changed){
        }
        m["~st3~"]=get_user_status_by_id(__U,3).name;
        m["~st4~"]=get_user_status_by_id(__U,4).name;
        m["~st5~"]=get_user_status_by_id(__U,5).name;
        m["~st6~"]=get_user_status_by_id(__U,6).name;
        m["~st7~"]=get_user_status_by_id(__U,7).name;
        m["~st8~"]=get_user_status_by_id(__U,8).name;
        string sts;
        {

            PGLW(user_profile,u,__U.up);
            map<unsigned int,user_status> & st=u->status;



            for (map<unsigned int,user_status> ::const_iterator i=st.begin();i!=st.end();i++)
            {
                if (i->first<=st_na) continue;
                const user_status &s=i->second;
                map<string,string> q;
                q["~i~"]=itostring(i->first);
                q["~name~"]=ESB(s.name);
                q["~picn~"]=itostring(s.pic);
                q["~id~"]=itostring(i->first);
                if (s.disable_invite){
                    q["~checked~"]="checked";
                }else{
                    q["~checked~"]="";
                }
                sts+=RVfiles(q,"settings/status_row");
            }
        }
        m["~userdef~"]=sts;
    }

    if (need_location_reload)
    {
        data_push_back_www(__UU,"<script>window.top.addmessage.location.reload();</script>\n");
    }
    m["~error~"]="";
    if (data){
        m["~error~"]=_MSG("changed2");
    }

    cc->html_out=cc->rvfiles(m,"settings/status");
}

void url_settings_colors(const PTR_getter<chat_user> &__UU,app_connection*cc)
{
    LICENSE_CK(22);
    MUTEX_INSPECTOR;
    st_update stu;
    if (!__UU){ cc->html_out=cc->redirect();return;}
    DB_id cc_user_id=user$id(__UU);
    user_pair __U(__UU);


    map<string,string> m;
    bool data=cc->params["DATA"]!="";
    c_level lv=__LEVELS(user$level(__U));
    set<unsigned int> cps=lv.colors;
    m["~error~"]="";
    {

        if (data){
            unsigned int np=atoi(cc->params["ncolor"]);
            {
                PGLW(chat_user, u,__U.cu);
                if (!cps.count(np)) np=c_packs.get_first_id();
            }
            {
                PGLW(user_profile, u,__U.up);
                if (u->setting_n_color_pack!=np)
                {
                    u->setting_n_color_pack=np;
                    __send_update_d3(user_profile$setting_n_color_pack$3,CONTAINER(cc_user_id),u->setting_n_color_pack);
                }
            }
        }

        m["~error~"]=_MSG("changed2");
    }
    string s;
    string im;
    unsigned int ncolor=user$setting_n_color_pack(__U);
    for (set<unsigned int>::const_iterator  i=cps.begin();i!=cps.end();i++){

        map<string,string> q;
        string name,imagefname,nickstyle;

        if (!c_packs.count(*i)) continue;

        {
            PGLR(__c_pack, c,c_packs.get(*i));
            name=c->name;
            imagefname=c->imagefname;
            nickstyle=c->nickstyle;
        }
        s+="<option value="+itostring(*i)+" style='"+nickstyle+"'";
        if (*i==ncolor){
            s+=" SELECTED";
        }
        s+=">"+name;
        im+="imgnames["+itostring(*i)+"]='"+imagefname+"';\r\n";
    }
    m["~color_packs~"]=s;
    m["~imgnames~"]=im;
    cc->html_out=cc->rvfiles(m,"settings/colors");
}

void url_settings_chat(const PTR_getter<chat_user> &__UU,app_connection*cc)
{
    MUTEX_INSPECTOR;
    LICENSE_CK(21);
    st_update stu;
    if (!__UU){ cc->html_out=cc->redirect();return;}
    DB_id cc_user_id=user$id(__UU);

    user_pair __U(__UU);

    map<string,string> m;
    bool data=cc->params["DATA"]!="";
    string cn=GET_CNICK(__U);

    {
        string st;
        string e;
        bool need_reload=false;
        if (data){
            {
                PGLW(user_profile, u,__U.up);
                bool hide_family_status=strupper(cc->params["hide_fs"])=="ON";
                if (u->hide_family_status!=hide_family_status)
                {
                    u->hide_family_status=hide_family_status;
                    __send_update_d3(user_profile$hide_family_status$3,CONTAINER(cc_user_id),u->hide_family_status);
                }

            }
            {
                PGLW(user_profile, u,__U.up);

                int setting_lpp=atoi(cc->params["setting_lpp"]);
                if (setting_lpp>100 || setting_lpp<=0){setting_lpp=10;}
                if (u->setting_lpp!=setting_lpp)
                {
                    u->setting_lpp=setting_lpp;
                    __send_update_d3(user_profile$setting_lpp$3,CONTAINER(cc_user_id),u->setting_lpp);
                }
                bool setting_autochange=strupper(cc->params["autochange"])=="ON";
                if (setting_autochange!=u->setting_autochange)
                {
                    u->setting_autochange=setting_autochange;
                    __send_update_d3(user_profile$setting_autochange$3,CONTAINER(cc_user_id),u->setting_autochange);

                }





                bool setting_show_credits=strupper(cc->params["showcredits"])=="ON";
                if (setting_show_credits!=u->setting_show_credits)
                {
                    u->setting_show_credits=setting_show_credits;
                    __send_update_d3(user_profile$setting_show_credits$3,CONTAINER(cc_user_id),u->setting_show_credits);

                }


                bool setting_show_stat=strupper(cc->params["showstat"])=="ON";
                if (u->setting_show_stat!=setting_show_stat)
                {
                    u->setting_show_stat=setting_show_stat;
                    __send_update_d3(user_profile$setting_show_stat$3,CONTAINER(cc_user_id),u->setting_show_stat);

                }

                bool setting_invite_sound=strupper(cc->params["inv_sound"])=="ON";
                if (u->setting_invite_sound!=setting_invite_sound)
                {
                    u->setting_invite_sound=setting_invite_sound;
                    __send_update_d3(user_profile$setting_invite_sound$3,CONTAINER(cc_user_id),u->setting_invite_sound);

                }

                bool setting_full_buttons=strupper(cc->params["full_buttons"])=="ON";
                if (u->setting_full_buttons!=setting_full_buttons)
                {
                    u->setting_full_buttons=setting_full_buttons;
                    __send_update_d3(user_profile$setting_full_buttons$3,CONTAINER(cc_user_id),u->setting_full_buttons);

                }

                bool setting_show_nicks=strupper(cc->params["snicks"])=="ON";
                if (u->setting_show_nicks!=setting_show_nicks)
                {
                    u->setting_show_nicks=setting_show_nicks;
                    __send_update_d3(user_profile$setting_show_nicks$3,CONTAINER(cc_user_id),u->setting_show_nicks);
                }

                bool setting_show_level=strupper(cc->params["slevel"])=="ON";
                if (u->setting_show_level!=setting_show_level)
                {
                    u->setting_show_level=setting_show_level;
                    __send_update_d3(user_profile$setting_show_level$3,CONTAINER(cc_user_id),u->setting_show_level);
                }


                unsigned int copt=0;
                if (strupper(cc->params["in_contact"])=="ON")
                    copt|=user_profile::CONTACT_ADD_IN_PRIV;
                if (strupper(cc->params["out_contact"])=="ON")
                    copt|=user_profile::CONTACT_ADD_OUT_PRIV;
                if (copt!=u->contact_options)
                {
                    u->contact_options=copt;
                    __send_update_d3(user_profile$contact_options$3,CONTAINER(cc_user_id),u->contact_options);
                    need_reload=true;
                }
            }
        }
        string s;
        int setting_lpp;
        {
            PGLR(user_profile, u,__U.up);
            setting_lpp=u->setting_lpp;


        }

        m["~setting_lpp~"]=itostring(setting_lpp);
        {
            PGLR(user_profile, u,__U.up);
            m["~h_fs~"]=checked(u->hide_family_status);

        }
        {
            PGLR(user_profile, u,__U.up);
            m["~ac~"]=checked(u->setting_autochange);		//autochange

            m["~sc~"]=checked(u->setting_show_credits);
            m["~ss~"]=checked(u->setting_show_stat);		//show_stat
            m["~sn~"]=checked(u->setting_show_nicks);	//show all nicks?
            m["~sl~"]=checked(u->setting_show_level);	//show level?
            int contact_options=u->contact_options;
            m["~in_contact~"]=checked(contact_options & user_profile::CONTACT_ADD_IN_PRIV);
            m["~out_contact~"]=checked(contact_options & user_profile::CONTACT_ADD_OUT_PRIV);

            m["~is~"]=checked(u->setting_invite_sound);	//invite sound?
            m["~fb~"]=checked(u->setting_full_buttons);	//display full buttons?
        }

        m["~error~"]="";
        if (data){
            m["~error~"]=_MSG("changed2");
        }
        cc->html_out=cc->rvfiles(m,"settings/chat");
    }

}


string get_f22(double dd);
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
    time_t stat_last_date;
    contact_display_struct()
    {
        CONTAINER(uid)=0;
        CONTAINER(nid)=0;
    }
};

int str_ct_d(const contact_display_struct&a, const contact_display_struct&b)
{
    return a.stat_last_date<b.stat_last_date;
}
int str_ct_d$(const contact_display_struct&a, const contact_display_struct&b)
{
    return a.stat_last_date>b.stat_last_date;
}
int str_ct_n(const contact_display_struct&a, const contact_display_struct&b)
{
    return strupper(a.nick)<strupper(b.nick);
}
int str_ct_n$(const contact_display_struct&a, const contact_display_struct&b)
{
    return strupper(a.nick)>strupper(b.nick);
}

void url_settings_edit_contacts(const PTR_getter<chat_user>  &__UU,app_connection *cc)
{
    MUTEX_INSPECTOR;
    LICENSE_CK(12);
    st_update stu;
    if (!__UU){ cc->html_out=cc->redirect();return;}
    DB_id cc_user_id=user$id(__UU);

    user_pair __U(__UU);
    PTR_getter<contact_vec> P_uid_contact_vec=contact_vecs.find_by_id_create(CONTAINER(user$id(__UU)));
    vector<DB_id> rm;
    {
        PGLW(contact_vec, u,P_uid_contact_vec);


        for (hash_set<DB_id> ::const_iterator i=u->contact.begin();i!=u->contact.end();i++)
        {
            if (strupper(cc->params["cid"+itostring(CONTAINER((*i)))])=="ON")
            {
                rm.push_back(*i);
            }
        }
        for (unsigned i=0;i<rm.size();i++)
        {
            u->contact.erase(rm[i]);
            __send_update_d3(contact$remove$3,CONTAINER(cc_user_id),CONTAINER(rm[i]));
        }


    }
    if (rm.size() )
    {

        chat_event_UPDATE_CONTACT_LIST *e=new chat_event_UPDATE_CONTACT_LIST(__UU,T_WWW);LEAKCTL_ADD(e);
        send_chat_event_push_back(e,false);

    }
    map<string,string>m;

    vector<contact_display_struct> vvv;
    vector<DB_id> vsid;
    {
        PGLW(contact_vec, u,P_uid_contact_vec);
        for (hash_set<DB_id> ::const_iterator i=u->contact.begin();i!=u->contact.end();i++)
            vsid.push_back(*i);
        m["~count~"]=itostring(u->contact.size());
    }
    map<DB_id, pair<pair<time_t,string>,DB_id> > ld;

    for (unsigned i=0;i<vsid.size();i++)
    {
        {
            time_t stat_last_date;
            DB_id last_nick_id;CONTAINER(last_nick_id)=0;
            string last_nick;
            {
                PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(vsid[i])));
                stat_last_date=u->stat_last_date;
                last_nick=u->last_nick;
                CONTAINER(last_nick_id)=u->last_nick_id;
            }
            ld[vsid[i]]=make_pair(make_pair(stat_last_date,last_nick),last_nick_id);
        }
    }
    {
        PGLW(contact_vec, u,P_uid_contact_vec);
        for (hash_set<DB_id> ::const_iterator i=u->contact.begin();i!=u->contact.end();i++)
        {
            if (CONTAINER((*i))==0) continue;
            if (*i==cc_user_id) continue;
            contact_display_struct c;
            c.uid=*i;
            {
                c.nick=ld[*i].first.second;
                c.nid=ld[*i].second;
            }
            c.stat_last_date=ld[*i].first.first;
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
    string rows;
    int start=atoi(cc->params["start"]);

    for (unsigned i=start;i<vvv.size() && i<start+20;i++)
    {
        map<string,string> q;
        q["~start~"]=itostring(start);
        q["~uid~"]=itostring(CONTAINER(vvv[i].uid));
        q["~nid~"]=itostring(CONTAINER(vvv[i].uid))+"."+itostring(CONTAINER(vvv[i].nid));
        q["~date~"]=date2num(vvv[i].stat_last_date);
        q["~nick~"]=vvv[i].nick;
        rows+=RVfiles(q,"settings/edit_contacts_row");
    }
    m["~rows~"]=rows;
    m["~start~"]=itostring(start);

    int prev_id=-1,next_id=-1;
    if (start>=20)
    {
        prev_id=start-20;
    }
    if (start+20<vvv.size()) next_id=start+20;

    if (prev_id!=-1){
        m["~prev~"]="href=\"/settings_edit_contacts?start="+itostring(prev_id)+"&srt="+cc->params["srt"]+"&dir="+cc->params["dir"]+"\"";
    }else{
        m["~prev~"]="";
    }
    if (next_id!=-1){
        m["~next~"]="href=\"/settings_edit_contacts?start="+itostring(next_id)+"&srt="+cc->params["srt"]+"&dir="+cc->params["dir"]+"\"";
    }else{
        m["~next~"]="";
    }
    cc->html_out+=cc->rvfiles(m,"settings/edit_contacts");
}

int srt_arr(const pair<string,string>&a, const pair<string,string>&b)
{
    return a.second<b.second;
}
void url_settings_nicks(const PTR_getter<chat_user> &__UU,app_connection *cc)
{
    LICENSE_CK(1);
    st_update stu;
    if (!__UU){ cc->html_out=cc->redirect();return;}
    DB_id cc_user_id=user$id(__UU);


    map<string,string> m;
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
        PGLW(nick_vec, u,nick_vecs.find_by_id_create(CONTAINER(cc_user_id)));

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
                        __send_update_d4(nick$change_nick$4,CONTAINER(cc_user_id),ni.id,ni.name);
                    }
                }

                if (strupper(cc->params["to_sale"])=="ON")
                {
                    ni.cost.container=fabs(atof(cc->params["cost"].c_str()));
                    ni.ready_to_sale=false;
                    __send_update_d4(nick$change_cost$4,CONTAINER(cc_user_id),ni.id,ni.cost);
                }
                else
                {
                    if (ni.ready_to_sale)
                    {
                        ni.ready_to_sale=false;
                        __send_update_d3(nick$unmark_for_sale$3,CONTAINER(cc_user_id),ni.id);
                    }
                }
            }

            unsel=ni;
            unsel_inited=true;



        }
    }
    {
        PGLR(nick_vec, u,nick_vecs.find_by_id_create(CONTAINER(cc_user_id)));

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
        m["~cost~"]=get_f22(unsel.cost.container);

    }

    cc->html_out+=cc->rvfiles(m,"settings/nicks");

}
void url_settings_privs(const PTR_getter<chat_user> &__UU,app_connection *cc)
{
    LICENSE_CK(7);
    st_update stu;
    if (!__UU){ cc->html_out=cc->redirect();return;}
    DB_id cc_user_id=user$id(__UU);
    user_pair __U(__UU);
    map<string,string>m;
    unsigned int lev_id;
    map<unsigned int,c_level> levels=get_all_levels();
    string error;
    DB_id uid;CONTAINER(uid)=0;CONTAINER(uid)=0;
    lev_id=user$level(__U);
    unsigned char gender=user$gender(__U);
    uid=user$id(__UU);
    m["~current_level_name~"]=LEVEL_NAME(lev_id,gender);
    if (cc->params.count("todo"))
    {
        if (cc->params["todo"]=="buy_invis")
        {

            int value=atoi(cc->params["invis_add"]);
            DB_id invis_saler_account;CONTAINER(invis_saler_account)=chat_config.invis_saler_account.get();
            Double ccc;
            ccc.container=value;
            if (!buy_thing(cc_user_id,invis_saler_account,ccc, "buy_invis"))
            {
                error=_MSG("not_enough_credits");
                logErr2("invis_add: not_enough_credits");
            }
            else
            {
                {
                    PGLW(user_profile, u,__U.up);
                    u->bought_invisibility=u->bought_invisibility+value;
                    __send_update_d3(user_profile$bought_invisibility$3,CONTAINER(uid),u->bought_invisibility);
                }

            }
            logErrN("users","%s bought invis (%d)",user$login(__U).c_str(),value);
        }
        if (cc->params["todo"]=="buy_next_level" && error.size()==0)
        {
            string ls=chat_config.levelup_cost;
            Double next_cost;next_cost.container=0;
            vector<string> v=splitTOK(",",ls);
            for (unsigned int i=0;i<v.size();i++)
            {
                vector<string>vv=splitTOK(":",v[i]);
                if (vv.size()==2)
                {
                    if (atoi(vv[0])==lev_id/sub_levels)next_cost.container=atof(vv[1].c_str());
                }
            }
            if (next_cost.container>0)
            {
                if (credit_reminder(cc_user_id).container>=next_cost.container)
                {
                    c_level New_lvl=__LEVELS(atoi(cc->params["nextlevel_select"]));
                    if (New_lvl.id/sub_levels - lev_id/sub_levels>1){
                        error="invalid level";
                        logErr2("nextlevel_select: invalid level");
                    }
                    else{

                        DB_id levelup_saler_account;CONTAINER(levelup_saler_account)=chat_config.levelup_saler_account.get();
                        if (!buy_thing(cc_user_id,levelup_saler_account,next_cost, "levelup"))
                        {
                            error=_MSG("not_enough_credits");
                            logErr2("nextlevel_select: not_enough_credits");
                        }
                        {
                            PGLW(user_profile, u,__U.up);
                            u->level=New_lvl.id;
                            __send_update_d3(user_profile$level$3,CONTAINER(cc_user_id),u->level);
                            m["~current_level_name~"]=LEVEL_NAME(u->level,gender);
                            lev_id=u->level;
                        }
                        logErrN("users","%s bought next level (%d)",user$login(__U).c_str(),New_lvl.id);

                        error=RVfiles("settings/privs_ch_lev_success");
                    }
                } //if(summa>next_cost)
                else{
                    logErr2("nextlevel_select: not_enough_credits");
                    error=RVfiles("settings/privs_no_eno_money");
                    logErr2("no money");
                }
            }//if(next_cost)
            else{
                error=RVfiles("settings/privs_next_nolev");
                logErr2("nextlevel_select: privs_next_nolev");
            }
        }//if(cc->params["todo"]=="buy_next_level")
        if (cc->params["todo"]=="buy_eq_level")
        {
            unsigned int New_lvl=atoi(cc->params["eqlevel_select"]);

            if ((lev_id/sub_levels)!=(New_lvl/sub_levels)) error="invalid level to change";
            else
            {
                if (credit_reminder(cc_user_id).container>=chat_config.change_eqlevel_cost.get().container)
                {
                    c_level lvl=__LEVELS(New_lvl);

                    DB_id change_eqlevel_saler_account;CONTAINER(change_eqlevel_saler_account)=chat_config.change_eqlevel_saler_account.get();
                    if (buy_thing(cc_user_id,change_eqlevel_saler_account,chat_config.change_eqlevel_cost, "eqlevel"))
                    {

                        {PGLW(user_profile, u,__U.up);
                            u->level=lvl.id;
                        }
                        __send_update_d3(user_profile$level$3,CONTAINER(cc_user_id),lvl.id);

                        m["~current_level_name~"]=LEVEL_NAME(lvl.id,gender);
                        lev_id=lvl.id;
                    }
                    error=RVfiles("settings/privs_ch_lev_success");
                    logErrN("users","%s bought eqlevel  (%d)",user$login(__U).c_str(),lvl.id);

                }
                else {
                    error=RVfiles("settings/privs_no_eno_money");
                    logErr2("settings/privs_no_eno_money");
                }

            }
        }//if(cc->params["todo"]=="buy_eq_level")



    }//if(cc->params.count("todo"))


    m["~credits~"]=get_f22(credit_reminder(cc_user_id).container);


    map<string,string> seleqlev;
    for (map<unsigned int,c_level>::const_iterator i=levels.begin();i!=levels.end();i++)
    {

        if ((lev_id/sub_levels==i->first/sub_levels) && (lev_id!=i->first))
        {
            seleqlev[itostring(i->first)]=i->second.name(gender);
        }
    }
    if (lev_id>=chat_config.change_eqlevel_limit) seleqlev.clear();
    if (seleqlev.size())
    {
        map<string,string>q;
        q["~equal_levels~"]=make_select("eqlevel_select",seleqlev);
        q["~change_eqlevel_cost~"]=get_f22(chat_config.change_eqlevel_cost.get().container);
        m["~eq_level_form~"]=RVfiles(q,"settings/privs_ch_eq_level");
    }
    else m["~eq_level_form~"]=RVfiles("settings/privs_ch_eq_nolevel");

    string ls=chat_config.levelup_cost;
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
        map<string,string>q;
        q["~next_level_cost~"]=get_f22(next_cost);
        map<string,string> selnextlev;
        for (map<unsigned int,c_level>::const_iterator i=levels.begin();i!=levels.end();i++)
        {

            if ( (lev_id/sub_levels)+1==i->second.id/sub_levels )
            {
                selnextlev[itostring(i->second.id)]=i->second.name(gender);
            }
        }
        q["~next_level_select~ "]=make_select("nextlevel_select",selnextlev);
        m["~next_level_form~"]=RVfiles(q,"settings/privs_next_lev");
    }
    else m["~next_level_form~"]=RVfiles("settings/privs_next_nolev");

    c_level lv=levels[lev_id];
    unsigned int used_space=get_used_space(__U);
    int invisibility=lv.invisibility;
    int kick_ability=lv.kick_ability;
    int kick_shield=lv.kick_shield;
    {
        PGLR(user_profile,u,__U.up);
        invisibility+=u->bought_invisibility;
    }

    {
        m["~used_space~"]=get_f22(double(used_space)/MB);
        m["~invisibility~"]=itostring(invisibility);
        m["~kick_ability~"]=itostring(kick_ability);
        m["~kick_shield~"]=itostring(kick_shield);
    }
    m["~error~"]=error;
    cc->html_out+=cc->rvfiles(m,"settings/privs");

}
