#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <stdio.h>
#include <map>
#include "user.h"
#include "str_lib.h"
#include "st_stuff.h"
#include "errs.h"
#include "message.h"
#include "chat_def.h"
#include "utils.h"
#include "register.h"
#include "irc_server.h"
#include "fotos.h"
#include "html_out.h"
#include "chat_globals.h"
#include "cs_conn_data.h"
#include "contact_vec.h"
#include "update_cmd.h"
#include "user_stat.h"
#include "user_credits.h"

inline void __ui_fio(bool admin, bool hide_fname, bool hide_lname,const string &fname,const string& lname, bool iu, hstring& out)
{
    string n;
    if (!iu) {
        if (fname!="" && (( !hide_lname) || admin)) {
            n=fname;
            if (admin && hide_lname) {
                n<<" "<<_MSG("hidden");
            }
        }
        if (lname!="" && ((!hide_fname) || admin)) {
            n<<" "<<lname;
            if (admin && hide_fname) {
                n<<" "<<_MSG("hidden");
            }
        }
        if (n!="") {
            map<string,hstring>q;
            q["~n~"]=n;
            out+=make_pair(q,"user_info/fio");
//            out<<"<tr><td align=right>"<<_MSG("inreal")<<"&nbsp;</td>" "<td><font class=infn><b>"<<n<<"</b></font></td></tr>\r\n";
        }
    } else {

    }
}
inline void __ui_nicks(const DB_id &zid, bool show_nicks, const string& nick_name, bool logined, bool iu, int gender, const string& cnick, const string& irc_host, hstring& out)
{
    vector<string> nk;
    map<unsigned int,user_nick> vn;
    {
        PGLR(nick_vec, u,nick_vecs.find_by_id(zid));
        vn=u->u_nicks;
    }
    for (map<unsigned int,user_nick>::iterator i=vn.begin();i!=vn.end();i++) {
        if (show_nicks || i->second.ready_to_sale)
        {
            if (str_nick(i->second.name)!=str_nick(nick_name))
            {
                if (!i->second.ready_to_sale || (!logined) ||iu)
                    nk.push_back(i->second.name);
                else
                {
                    string s;
                    s<<" <a href='#' onclick='return do_bnick(\""+itostring(zid.container)+"."+itostring(i->second.id)+"\");'>"<<i->second.name<<"</a>";
                    nk.push_back(s);
                }
            }
        }
    }
    if (show_nicks || nk.size()) {
        string n;
        if (gender==0) {
            n=_MSG("known0");
        }
        else if (gender==1) {
            n=_MSG("known1");
        }
        else if (gender==2) {
            n=_MSG("known2");
        }
        if (!iu) {
            map<string,hstring>q;
            q["~nicks~"]=join(", ",nk);
            if (gender==0)
                out+=make_pair(q,"user_info/nicks_g0");
            else if (gender==1)
                out+=make_pair(q,"user_info/nicks_g1");
            else if (gender==2)
                out+=make_pair(q,"user_info/nicks_g2");
        }
        else {
            string ss=nick_name;
            ss<<" "<<_MSG("justas")<<": "<<join(", ",nk);
            out+=irc_gen_reply2(316,ss,irc_host,cnick);
        }
    }

}
inline void __ui_gender(int gender,bool iu,const string& cnick,const string& nick_name,const string& irc_host,hstring& out)
{
    string n;
    if (gender==0) {
        n=_MSG("sex0");
    }
    else if (gender==1) {
        n=_MSG("sex1");
    }
    else if (gender==2) {
        n=_MSG("sex2");
    }
    if (!iu) {
        map<string,hstring>q;
        q["~n~"]=n;
        out+=make_pair(q,"user_info/gender");
//        out<<"<tr><td align=right width=\"40%\">"<<_MSG("gender")<<"&nbsp;</td>" "<td><font class=infd>"<<n<<"</font></td></tr>\r\n";
    } else {
        string ss;
        ss<<nick_name<<" "<<_MSG("gender")<<": "<<n;
        out<<irc_gen_reply2(316,ss,irc_host,cnick);
    }

}
inline void __ui_birthdate(bool hide_bdate, bool admin, bool iu,int gender,const  string &b_day,const string& b_year, int b_mon, const string& nick_name, const string& irc_host,const string& cnick,hstring& out)
{
    string n;
    if ((!hide_bdate || admin) && (b_day!="" && b_mon!=0 && b_year!="")) {
        string gng;
        if (gender==0) {
            gng=_MSG("born0");
        }
        else if (gender==1) {
            gng=_MSG("born1");
        }
        else if (gender==2) {
            gng=_MSG("born2");
        }
        if (!iu) {
            out<<"<tr><td align=right>"<<gng<<"&nbsp;</td>";
        }
        n="";
        if (b_mon==0 && b_day!="" && b_year!="") {
            n<<b_day<<" "<<_MSG("anymonth")<<" "<<b_year<<" "<<_MSG("year1");
        }
        else if (b_day=="" && b_mon==0) {
            n<<_MSG("lowerin")<<" "<<b_year<<" "<<_MSG("year2");
        }
        else if (b_day=="" && b_year=="") {
            n<<_MSG("lowerin")<<" "<<get_rus_month2(b_mon);
        }
        else if (b_mon==0 && b_year=="") {
            n<<b_day<<" "<<_MSG("number1");
        }
        else if (b_day=="" && b_mon!=0 && b_year!="") {
            n<<_MSG("upperin")<<" "<<get_rus_month2(b_mon)<<" "<<b_year<<" "<<_MSG("year1");
        }
        else {
            if (b_day!="") {
                n<<b_day<<" ";
            }
            if (b_mon!=0) {
                n<<get_rus_month(b_mon);
            }
            if (b_year!="") {
                n<<" "<<b_year<<" "<<_MSG("year1");
            }
        }
        if (admin && hide_bdate) {
            n<<" "<<_MSG("hidden");
        }
        if (!iu) {
            out<<"<td><font class=infd>"<<n<<"</font></td></tr>\r\n";
        } else {
            out+=irc_gen_reply2(316,nick_name+" "+gng+": "+n,irc_host,cnick);
        }
    }

}
hstring make_user_info(const DB_id& zid,const DB_id& uid, bool admin,bool iu,string irc_host,string cnick, bool logined)
{

    hstring out;
    string n;
    string nick_name;
    unsigned int nick_id;
    {
        PGLR(user_set, u,user_sets.find_by_id(zid));
        nick_name=u->last_nick;
        nick_id=u->last_nick_id;
    }

    bool hide_fname;
    bool hide_lname;
    bool hide_bdate;
    bool hide_tel;
    bool hide_email;
    bool hide_icq;
    string fname,lname;
    int gender;

    bool show_nicks,show_level,show_credits;
    string b_day,b_year;
    int b_mon;
    string city;
    string homepage,email,icq,info,tel;
    double credits;
    {
        PGLR(user_credit, u,user_credits.find_by_id(zid));
        credits=u->summa;

    }
    unsigned int level;
    {
        PGLR(user_profile, u,user_profiles.find_by_id(zid));
        fname=u->fname;
        lname=u->lname;
        b_day=u->b_day;
        b_mon=u->b_mon;
        b_year=u->b_year;
        city=u->city;
        homepage=u->homepage;
        email=u->email;
        icq=u->icq;
        info=u->info;
        tel=u->tel;
        level=u->level;
    }
    {
        PGLR(user_set, u,user_sets.find_by_id(zid));
        show_nicks=u->show_nicks;
        show_level=u->show_level;
        show_credits=u->show_credits;
        hide_fname=u->hide_fname;
        hide_lname=u->hide_lname;
        hide_bdate=u->hide_bdate;
        hide_tel=u->hide_tel;
        hide_email=u->hide_email;
        hide_icq=u->hide_icq;
    }
    {
        PGLR(user_profile, u,user_profiles.find_by_id(zid));
        gender=u->get_gender();
    }

    __ui_fio(admin,hide_fname,hide_lname,fname,lname, iu,out);


    __ui_nicks(zid, show_nicks, nick_name,logined, iu, gender, cnick,irc_host,out);

    //gender
    __ui_gender(gender,iu,cnick,nick_name,irc_host,out);


    //born date

    __ui_birthdate(hide_bdate, admin, iu, gender, b_day, b_year, b_mon,nick_name,irc_host,cnick,out);

    //live in...
    if (city!="") {
        if (!iu) {
            out<<"<tr><td align=right>"<<_MSG("livein")<<"&nbsp;</td>" "<td><font class=infd>"<<city<<"</font></td></tr>\r\n";
        } else {
            out<<irc_gen_reply2(316,nick_name+" "+_MSG("livein")+" :"+city,irc_host,cnick);
        }
    }
    //homepage
    if (homepage!="" && homepage!="http://") {
        if (!iu) {
            out<<"<tr><td align=right>"<<_MSG("homepage")<<"&nbsp;</td>" "<td>";
            if (homepage.find("http://", 0)!=-1 || homepage.find("www.",0)!=-1) {
                if (homepage.find("http://", 0)==-1) {
                    out<<"<a href=\"http://"<<homepage<<"\" target=_blank>"<<homepage<<"</a>";
                } else {
                    out<<"<a href=\""<<homepage<<"\" target=_blank>"<<homepage<<"</a>";
                }
            } else {
                out<<homepage;
            }
            out<<"</td></tr>\r\n";
        } else {
            out<<irc_gen_reply2(316,nick_name+" "+_MSG("homepage")+": "+homepage,irc_host,cnick);
        }
    }
    //email
    if (email!="" && ((!hide_email) || admin)) {
        if (!iu) {
            out+="<tr><td align=right>E-Mail&nbsp;</td>" "<td>";
            if (string(email).find("@",0)!=-1) {
                out<<"<a href=\"mailto:"<<email<<"\">"<<email<<"</a>";
            } else {
                out<<email;
            }
            if (admin && hide_email) {
                out<<" "<<_MSG("hidden");
            }
            out<<"</td></tr>\r\n";
        } else {
            string em=email;
            if (admin && hide_email) {
                em<<" "<<_MSG("hidden");
            }
            out+=irc_gen_reply2(316,nick_name+" E-Mail: "+em,irc_host,cnick);
        }
    }
    //icq
    if (icq!="" && ((!hide_icq) || admin)) {
        if (!iu) {
            out<<"<tr valign=top><td align=right>ICQ&nbsp;</td><td><font class=infd>"<<icq;
            int zz=atoi(icq.c_str());
            if (zz!=0) {
                out<<"<img src=\"http://online.mirabilis.com/scripts/online.dll?icq="<<icq<<"&img=5\" width=18 height=18>";
            }
            if (admin && hide_icq) {
                out<<" "<<_MSG("hidden");
            }
            out<<"</font></td></tr>\r\n";
        } else {
            string iq=icq;
            if (admin && hide_icq) {
                iq<<" "<<_MSG("hidden");
            }
            out<<irc_gen_reply2(316,nick_name+" ICQ: "+iq,irc_host,cnick);
        }
    }
    //tel
    if (tel!="" && ((!hide_tel) || admin)) {
        if (!iu) {
            out<<"<tr><td align=right>"<<_MSG("tel")<<"&nbsp;</td>" "<td><font class=infd>"<<tel;
            if (admin && hide_tel) {
                out<<" "<<_MSG("hidden");
            }
            out<<"</font></td></tr>\r\n";
        } else {
            if (admin && hide_tel) {
                tel<<" "<<_MSG("hidden");
            }
            out<<irc_gen_reply2(316,nick_name+" "+_MSG("tel")+": "+tel,irc_host,cnick);
        }
    }
    //level
    if (show_level || admin) {
        if (admin && !show_level) {
            if (!iu) {
                out<<"<tr><td align=right>"<<_MSG("level")<<"&nbsp;</td>" "<td><font class=infd>"<<LEVEL_NAME(level,gender)<<" "<<_MSG("hidden")<<"</font></td></tr>\r\n";
            } else {
                string ss;
                ss<<nick_name<<" "<<_MSG("level")<<": "<<LEVEL_NAME(level,gender)<<" "<<_MSG("hidden");
                out+=irc_gen_reply2(316,ss,irc_host,cnick);
            }
        } else {
            if (!iu) {
                out<<"<tr><td align=right>"<<_MSG("level")<<"&nbsp;</td>" "<td><font class=infd>"<<LEVEL_NAME(level,gender)<<"</font></td></tr>\r\n";
            } else {
                string ss;
                ss<<nick_name<<" "<<_MSG("level")<<": "<<LEVEL_NAME(level,gender);
                out+=irc_gen_reply2(316,ss,irc_host,cnick);
            }
        }
    }
    //credits
    if (show_credits || admin) {
        if (admin && !show_credits) {
            if (!iu) {
                out<<"<tr><td align=right>"<<_MSG("credits")<<"&nbsp;</td>" "<td><font class=infd>"<<get_f22(credits)<<" "<<_MSG("hidden")<<"</font></td></tr>\r\n";
            } else {
                string ss;
                ss<<nick_name<<" "<<_MSG("credits")<<": "<<get_f22(credits)<<" "<<_MSG("hidden");
                out+=irc_gen_reply2(316,ss,irc_host,cnick);
            }
        } else {
            if (!iu) {
                out<<"<tr><td align=right>"<<_MSG("credits")<<"&nbsp;</td>" "<td><font class=infd>"<<get_f22(credits)<<"</font></td></tr>\r\n";
            } else {
                string ss;
                ss<<nick_name<<" "<<_MSG("credits")<<": "<<get_f22(credits);
                out+=irc_gen_reply2(316,ss,irc_host,cnick);
            }
        }
    }
    int cnt;
    {
        PGLR(user_fotos, u,users_fotos.find_by_id(zid));
        cnt=u->fotos.size();
    }
    if (cnt>0) {
        if (!iu) {
            out<<"<tr><td align=center colspan=2><hr class=hr size=2 width=\"100%\">";
            map<string,hstring> q;
            q["~uid~"]=itostring(zid.container);
            if (cnt==1) {
                out+=make_pair(q,"user_info/do_photo1");
            }
            else {
                q["~n~"]=itostring(cnt);
                out+=make_pair(q,"user_info/do_photon");
            }
            out<<"</td></tr>";
        } else {
            out+=irc_gen_reply2(316,nick_name+" photos available from http://"+irc_host+"/userphotos?id="+itostring(zid.container),irc_host,cnick);
        }
    }
    if (cnt==0 && !iu && zid==uid)
    {
        map<string,hstring> q;
        out+=make_pair(q,"user_info/add_photo");

    }
    if (!iu) {
        out<<"<tr><td colspan=2><hr class=hr size=2 width=\"100%\"><font class=infn>";
        out<<str_replace("\r\n","<br>",info)<<"</td></tr>";
    } else {
        if (info.size()) {
            info=str_replace("\r","",info);
            info=str_replace("\n"," ",info);
            out+=irc_gen_reply2(316,nick_name+" says: "+info,irc_host,cnick);
        }
    }
    return out;
}
void url_user_info(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    hstring out;
    bool admin=cc->sub_level>=am_admin;
    int level=cc->sub_level;
    map<string,hstring> m;


    DB_id zid;
    {
        if (cc->params.count("id"))
        {
            zid.container=atoi(cc->params["id"].c_str());
        }
        else if (cc->params.count("ni"))
        {
            zid=all_user_nick_2_DB_id(cc->params["ni"]);
        }
    }
    if (zid.container==0) {

        m["~userinfo~"]="<center>"+_MSG("userleft")+"</center>";
        cc->html_out=make_pair(m,"chat/user_info");
        return;
    }
    user_pair __U(__UU);

    if (cc->params["addcontact"]=="1")
    {
        out_oscar_buffer o;
        o<<user_state::CONTACT_ADD<<user$id(__U)<<zid;
        set_user_state(o);
        {
            PGLW(contact_vec,c,contact_vecs.find_by_id(cc->user_id))
            c->contact.insert(zid);
        }
        send_update_g3(contact$add,cc->user_id,zid.container);

    }
    else if (cc->params["addcontact"]=="0")
    {
        out_oscar_buffer o;
        o<<user_state::CONTACT_REMOVE<<user$id(__U)<<zid;
        set_user_state(o);
        {
            PGLW(contact_vec,c,contact_vecs.find_by_id(cc->user_id))
            c->contact.erase(zid);
        }
        send_update_g3(contact$remove,cc->user_id,zid.container);

    }

    string znick;
    {
        PGLR(user_set,z,user_sets.find_by_id(zid));
        znick=z->last_nick;
    }
    {
        map<string,hstring>q;
        q["~cnick~"]=znick;
        out+=make_pair(q,"user_info/header");
    }
    if (admin) {
        map<string,hstring> q;
        q["~id~"]=itostring(zid.container);
        out+=make_pair(q,"user_info/login_info");
    }
    out += "</td></tr>\r\n";
    out<<make_user_info(zid,cc->user_id,admin,false,"","",cc->user_id.container!=0);
    {
        PGLR(user_profile, z,user_profiles.find_by_id(zid));
        if (z->info != "") {
            out<<"<tr><td align=center colspan=2><hr class=hr size=2 width=\"100%\"></td></tr>";
        }
    }
    bool added=false;
    {
        PGLR(contact_vec,u,contact_vecs.find_by_id(cc->user_id));
        added=u->contact.count(zid);
    }
    if (!added)
    {
        map<string,hstring>q;
        q["~id~"]=itostring(zid.container);
        out+=make_pair(q,"user_info/add_contact");
    }
    else
    {
        map<string,hstring>q;
        q["~id~"]=itostring(zid.container);
        out+=make_pair(q,"user_info/del_contact");
    }


    if (cc->sub_level >= am_spy) {
        PGLR(user_stat,z,user_stats.find_by_id(zid));
        map<string,hstring>q;
        q["~ip~"]=z->last_ip;
        out+=make_pair(q,"user_info/ip");
        if (z->last_pip.size())
        {
            map<string,hstring>qq;
            qq["~pip~"]=z->last_pip;
            out+=make_pair(qq,"user_info/pip");
        }
    }
    if (admin) {
        PTR_getter<chat_user> __ZZ=local_users.get(zid);
        if (__ZZ)
        {
            user_pair __Z(__ZZ);
            {
                __ZC_LOCK;
                map<string,hstring> q;
                q["~ua~"]=z->ua;
                out+=make_pair(q,"user_info/ua");
                if (z->user_type==TYPE_WWW)
                {

                    if (z->www_screen_resolution.size())
                    {
                        map<string,hstring> qq;
                        qq["~sr~"]=z->www_screen_resolution;
                        out+=make_pair(qq,"user_info/sr");
                    }
                }
            }
        }
    }
    {
        map<string,hstring>q;
        out+=make_pair(q,"user_info/footer");
    }
    m["~userinfo~"]=out;
    cc->html_out=make_pair(m,"user_info/user_info");
}

