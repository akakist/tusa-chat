
#include "stdafx.h"
#ifdef _DEBUG
#define New DEBUG_NEW
#endif

#include "_mutex.h"
#include <list>
#include "mutex_inspector.h"
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

#include <sys/stat.h>
#include <sys/types.h>
#include "copy_file.h"
#include "wrappers.h"
#include "web_tools.h"
#include "file_set.h"
#include "levels.h"
#include "server_config.h"

#include "chat_config.h"
#include "app_def.h"

#include "update_cmd.h"
#include "html_out.h"

#include "chat_globals.h"
#include "DR_types.h"
#include "app_con.h"
#ifdef __WITH_LICENSE
#include "license.h"
#endif

string check_reg_map(map<string,string> &m, bool all);
void  fill_map_from_map(map<string,string>&to,map<string,string>&from);
void update_DB_from_reg_map(const DB_id& uid,map<string,string>&m, bool all);
enum REG_RESULT
{
    REG_SUCCESS,
    REG_NICK_EXISTS,
    REG_LOGIN_EXISTS,
};


string register_io(map<string,string> &params)
{
    int res=REG_SUCCESS;
    DB_id uid;CONTAINER(uid)=0;CONTAINER(uid)=0;
    st_dbh d;
    vector<string>v;
    v=d.dbh->select_1_rowQ((QUERY)"select id from nicks where str_nick like '?'"<<str_nick(params["nick"]));
    if (v.size()>0){
        res=REG_NICK_EXISTS;
    }
    if (res==REG_SUCCESS)
    {

        v=d.dbh->select_1_rowQ((QUERY)"select id from tbl_users where login='?'"<<params["login"]);

        if (v.size()>0){
            res=REG_LOGIN_EXISTS;
        }

    }
    if (res==REG_SUCCESS)
    {
        d.dbh->real_queryQ((QUERY)"\
                           insert into tbl_users () values ()");


        vector<string> nv;
        nv=d.dbh->select_1_row("select LAST_INSERT_ID() from tbl_users");
        if (nv.size()!=1){
            throw cError("select() failed. Size different."+_DMI());
        }
        CONTAINER(uid)=atoi(nv[0]);
        {
            d.dbh->real_queryQ((QUERY)"insert DELAYED into nicks (nick,str_nick,uid,banned) values('?','?',?,0)"
                               <<params["nick"]<<str_nick(params["nick"])<<CONTAINER(uid));
        }

    }
    unsigned int nid=atoi(d.dbh->select_1("SELECT LAST_INSERT_ID()"));
    out_oscar_buffer b;
    b<<res;
    if (res==REG_SUCCESS)
        b<<uid;
    return b.as_string();
}
void pre_init_for_info(map<string,string> &m)
{
    map<string,string> g,mon;
    g["0"]=_MSG("sex0");
    g["1"]=_MSG("sex1");
    g["2"]=_MSG("sex2");
    mon["0"]="";
    for (int i=1;i<13;i++){
        mon[lzstring(i)]=get_rus_month(i);
    }
    m["~error~"]="";
    m["~login~"]="";
    m["~nick~"]="";
    m["~pass~"]="";
    m["~fname~"]="";
    m["~lname~"]="";
    m["~gender~"]=make_select("gender",g,"0");
    m["~bd_day~"]="";
    m["~bd_month~"]=make_select("bd_month",mon,"0");
    m["~bd_year~"]="";
    m["~city~"]=_MSG("defcity");
    m["~homepage~"]="http://";
    m["~email~"]="";
    m["~icq~"]="";
    m["~tel~"]="";
    m["~info~"]="";
    m["~h_fname~"]="checked";
    m["~h_lname~"]="checked";
    m["~h_ddmm~"]="checked";
    m["~h_tel~"]="";
    m["~h_email~"]="checked";
    m["~h_icq~"]="checked";
    //m["~h_fs~"]="checked";
}
void url_registration(app_connection*cc)
{
    MUTEX_INSPECTOR;
	st_update stu;

    try{
        LICENSE_CK(5);
        DB_id  _uid;CONTAINER(_uid)=0;
        map<string,string> m;

        m["~error~"]="";
        m["~photo~"]="";
        m["~ephoto~"]="";
        if (cc->params["DATA"]==""){
            pre_init_for_info(m);
            cc->html_out=cc->rvfiles(m,"register");
            return;
        }

        string e;
        {
            e+=check_reg_map(cc->params,true);
            if (cc->params["pass"]!=cc->params["pass2"]){e+=_MSG("passnotmatch");}
            fill_map_from_map(m,cc->params);
            m["~nick~"]=cc->params["nick"];

        }

        if (!check_maty(" "+cc->params["nick"]) || !check_nick(cc->params["nick"]) ){e+=_MSG("incorrectnick");}

        {
            if (e!=""){
                m["~error~"]=e;
                cc->html_out=cc->rvfiles(m,"register");
                return;
            }
        }

        e="";
        if (!cc->params["nick"].size()) e+=_MSG("nicknotentered");
        if (e.size())
        {
            m["~error~"]=e;
            cc->html_out=cc->rvfiles(m,"register");
            return;
        }
        string ioresult=register_io(cc->params);
        oscar_buffer b(ioresult.data(),ioresult.size());
        int reg_result;
        b>>reg_result;
        if (reg_result==REG_NICK_EXISTS)
        {
            e=_MSG("nickexists");
            m["~error~"]=e;
            cc->html_out=cc->rvfiles(m,"register");
            return;

        }
        if (reg_result==REG_LOGIN_EXISTS)
        {
            e=_MSG("loginexists");
            m["~error~"]=e;
            cc->html_out=cc->rvfiles(m,"register");
            return;

        }
        if (reg_result!=REG_SUCCESS)
        {
            throw cError("reg_result!=REG_SUCCESS"+_DMI());
        }

        b>>_uid;

        update_DB_from_reg_map(_uid,cc->params, true);


        {
            PGLW(user_profile, u,user$profiles.FindByID(CONTAINER(_uid)));
			u->reg_date=time(NULL);
			__send_update_d3(user_profile$reg_date$3,CONTAINER(_uid),u->reg_date);

			u->setting_n_color_pack=0;;
			u->level=sub_levels;
			__send_update_d3(user_profile$level$3,CONTAINER(_uid),u->level);
			__send_update_d3(user_profile$setting_n_color_pack$3,CONTAINER(_uid),u->setting_n_color_pack);
		}

        __send_update_d3(user_profile$stat_last_date$3,CONTAINER(_uid),time(NULL));
        {
            cc->html_out=(string)"<html><link rel=stylesheet type=text/css href=/css/main.css><form action='/login' name=f method=POST><input type=hidden name='login' value='"+string(cc->params["login"])+"'><input type=hidden name='pass' value='"+cc->params["pass"]+"'></form><script>document.f.submit();</script>\n</html>";
        }
    }catch (cError e)
    {
        map<string,string> m;
        m["~error~"]=e.what();
        cc->html_out=cc->rvfiles(m,"register");

    }
}

void ck_map_var(string& v,int maxsize)
{
    if (v.size()) v=v.substr(0,maxsize);

    v=str_replace("&","&amp;",v);
    v=str_replace("<","&lt;",v);
    v=str_replace(">","&gt;",v);

}
string check_reg_map(map<string,string> &m, bool all)
{
    string e;
    if (all)
    {
        ck_map_var(m["nick"],16);
        ck_map_var(m["login"],16);
        if (!check_nick(m["nick"])) e+=_MSG("badlogin");
        if (!check_login(m["login"])) e+=_MSG("badnick");
    }
    if(e.size()) return e;
    
    ck_map_var(m["firstname"],20);
    ck_map_var(m["lastname"],20);
    ck_map_var(m["gender"],1);
    int gender=atoi(m["gender"]);
if (gender>2 || gender<0){gender=0;m["gender"]=itostring(gender);}

    ck_map_var(m["bd_day"],2);
    ck_map_var(m["bd_year"],4);
    ck_map_var(m["bd_month"],2);
    int mon=atoi(m["bd_month"]);
    if (mon>12 || mon<0){mon=0;m["bd_month"]=itostring(mon);}
    ck_map_var(m["city"],64);
    ck_map_var(m["homepage"],128);
    ck_map_var(m["email"],32);
    ck_map_var(m["icq"],16);
    ck_map_var(m["tel"],24);
    ck_map_var(m["info"],4096);


    if (all){
        if (m["login"]=="") e+=_MSG("loginnotentered");
    }
    if (m["firstname"]=="") e+=_MSG("fnamenotentered");
    if (m["lastname"]=="") e+=_MSG("lnamenotentered");
    if (all&& (!check_login(m["login"]))) e+=_MSG("badlogin");
    return e;

}

void  fill_map_from_map(map<string,string>&m,map<string,string>&from)
{
    map<string,string> g;
    map<string,string>  mon;
    g["0"]=_MSG("sex0");
    g["1"]=_MSG("sex1");
    g["2"]=_MSG("sex2");
    mon["0"]="";
    for (int i=1;i<13;i++){
        mon[lzstring(i)]=get_rus_month(i);
    }
    m["~login~"]=from["login"];
    m["~pass~"]=from["pass"];
    m["~fname~"]=from["firstname"];
    m["~lname~"]=from["lastname"];
    m["~gender~"]=make_select("gender",g,from["gender"]);
    m["~bd_day~"]=from["bd_day"];
    m["~bd_month~"]=make_select("bd_month",mon,lzstring(atoi(from["bd_month"])));
    m["~bd_year~"]=from["bd_year"];
    m["~city~"]=from["city"];
    m["~homepage~"]=from["homepage"];
    m["~email~"]=from["email"];
    m["~icq~"]=from["icq"];
    m["~tel~"]=from["tel"];
    m["~info~"]=from["info"];
    m["~h_fname~"]=checked(from["h_fname"]);
    m["~h_lname~"]=checked(from["h_lname"]);
    m["~h_ddmm~"]=checked(from["h_ddmm"]);
    m["~h_tel~"]=checked(from["h_tel"]);
    m["~h_email~"]=checked(from["h_email"]);
    m["~h_icq~"]=checked(from["h_icq"]);
    //m["~h_fs~"]=checked(from["h_fs"]);
}
void get_DB_to_map(const PTR_getter<user_profile> &__UP, map<string,string> &m)
{
    {
        PGLR(user_profile, u,__UP);
        m["login"]=u->login;
        m["firstname"]=u->fname;
        m["lastname"]=u->lname;
        m["bd_day"]=u->b_day;
        m["bd_month"]=itostring(u->b_mon);
        m["bd_year"]=u->b_year;
        m["city"]=u->city;
        m["homepage"]=u->homepage;
        m["email"]=u->email;
        m["icq"]=u->icq;
        m["tel"]=u->tel;
        m["info"]=u->info;
        m["gender"]=itostring(u->get_gender());
        m["h_fname"]=u->hide_fname?"ON":"";
        m["h_lname"]=u->hide_lname?"ON":"";
        m["h_ddmm"]=u->hide_bdate?"ON":"";
        m["h_tel"]=u->hide_tel?"ON":"";
        m["h_email"]=u->hide_email?"ON":"";
        m["h_icq"]=u->hide_icq?"ON":"";
        //m["h_fs"]=u->hide_family_status?"ON":"";

    }

}
void update_DB_from_reg_map(const DB_id& uid,map<string,string>&m, bool all)
{
	st_update stu;
	{
		PGLW(user_profile, u,user$profiles.FindByID(CONTAINER(uid)));
		if (all)
		{
			u->pass=strupper(bin2hex(MD5(m["pass"]),10)); __send_update_d3(user_profile$pass$3,CONTAINER(uid),u->pass);
			if (m["login"].size()){
				u->login=m["login"];
				__send_update_d3(user_profile$login$3,CONTAINER(uid),u->login);
			}
		}
		if (m["firstname"].size() && u->fname!=m["firstname"])
		{
			u->fname=m["firstname"];
			__send_update_d3(user_profile$fname$3,CONTAINER(uid),u->fname);
		}
		if (m["lastname"].size() && u->lname!=m["lastname"]){
			u->lname=m["lastname"];
			__send_update_d3(user_profile$lname$3,CONTAINER(uid),u->lname);
		}

		if (u->b_day!=m["bd_day"]){u->b_day=m["bd_day"]; __send_update_d3(user_profile$b_day$3,CONTAINER(uid),u->b_day);}

		if (u->b_mon!=atoi(m["bd_month"])){u->b_mon=atoi(m["bd_month"]); __send_update_d3(user_profile$b_mon$3,CONTAINER(uid),u->b_mon);}

		if (u->b_year!=m["bd_year"]){u->b_year=m["bd_year"]; __send_update_d3(user_profile$b_year$3,CONTAINER(uid),u->b_year);}
		if (u->city!=m["city"]){u->city=m["city"]; __send_update_d3(user_profile$city$3,CONTAINER(uid),u->city);}
		if (u->homepage!=m["homepage"]){u->homepage=m["homepage"];  __send_update_d3(user_profile$homepage$3,CONTAINER(uid),u->homepage);}
		if (u->email!=m["email"]){u->email=m["email"]; __send_update_d3(user_profile$email$3,CONTAINER(uid),u->email);}
		if (u->icq!=m["icq"]){u->icq=m["icq"]; __send_update_d3(user_profile$icq$3,CONTAINER(uid),u->icq);}
		if (u->tel!=m["tel"]){u->tel=m["tel"]; __send_update_d3(user_profile$tel$3,CONTAINER(uid),u->tel);}
		if (u->info!=m["info"]){u->info=m["info"]; __send_update_d3(user_profile$info$3,CONTAINER(uid),u->info);}
		if (u->get_gender()!=atoi(m["gender"]))
		{
			u->set_gender(atoi(m["gender"]));
			__send_update_d3(user_profile$gender$3,CONTAINER(uid),u->get_gender());
		}
		if (u->hide_fname!=(strupper(m["h_fname"])=="ON")){u->hide_fname=(strupper(m["h_fname"])=="ON");	__send_update_d3(user_profile$hide_fname$3,CONTAINER(uid),u->hide_fname); }
		if (u->hide_lname!=(strupper(m["h_lname"])=="ON")){u->hide_lname=(strupper(m["h_lname"])=="ON");	__send_update_d3(user_profile$hide_lname$3,CONTAINER(uid),u->hide_lname); }
		if (u->hide_bdate!=(strupper(m["h_ddmm"])=="ON")){u->hide_bdate=(strupper(m["h_ddmm"])=="ON");	__send_update_d3(user_profile$hide_bdate$3,CONTAINER(uid),u->hide_bdate); }
		if (u->hide_tel!=(strupper(m["h_tel"])=="ON")){u->hide_tel=(strupper(m["h_tel"])=="ON");		__send_update_d3(user_profile$hide_tel$3,CONTAINER(uid),u->hide_tel); }
		if (u->hide_email!=(strupper(m["h_email"])=="ON")){u->hide_email=(strupper(m["h_email"])=="ON");	__send_update_d3(user_profile$hide_email$3,CONTAINER(uid),u->hide_email); }
		if (u->hide_icq!=(strupper(m["h_icq"])=="ON")){u->hide_icq=(strupper(m["h_icq"])=="ON");		__send_update_d3(user_profile$hide_icq$3,CONTAINER(uid),u->hide_icq); }

	}
}


void url_change_info(const PTR_getter<chat_user> &__UU,app_connection*cc)
{
    MUTEX_INSPECTOR;
    LICENSE_CK(3);

    if (!__UU) return;
    user_pair __U(__UU);
    map<string,string> m;

    m["~error~"]="";
    m["~photo~"]="";
    m["~ephoto~"]="";

    if (cc->params["DATA"]==""){
        map<string,string> mu;
        get_DB_to_map(__U.up,mu);
        fill_map_from_map(m,mu);


        m["~pass~"]="";
        m["~lpass~"]="";
        m["~login~"]=user$login(__U);

        cc->html_out=cc->rvfiles(m,"change_info");
        return;
    }
    string e;
    e+=check_reg_map(cc->params,false);
    if (cc->params["lpass"]!=""){
        string db_pass;
        {
            PGLR(user_profile, u,__U.up);
            db_pass=u->pass;
        }
        if (bin2hex(MD5(cc->params["lpass"]),0)!=string(db_pass)){e+=_MSG("badlastpassword");}
        if (cc->params["pass"]!=cc->params["pass2"]){e+=_MSG("passwordsmismatch");}
        if (cc->params["pass"].size()<3){e+=_MSG("passwordisshort");}
    }

    e+=check_reg_map(cc->params,false);
    fill_map_from_map(m,cc->params);
    m["~nick~"]=cc->params["nick"];

    m["~pass~"]="";
    m["~lpass~"]="";
    m["~error~"]=_MSG("changed2");
    if (e!=""){
        m["~error~"]=e;
        map<string,string> mu;
        get_DB_to_map(__U.up,mu);
        fill_map_from_map(m,mu);
        cc->html_out=cc->rvfiles(m,"change_info");
        return;
    }
    update_DB_from_reg_map(user$id(__UU),cc->params, false);
    if (e.size()==0 && cc->params["pass"].size() && cc->params["lpass"].size()) SET_PASS(__U,cc->params["pass"]);


    map<string,string> mu;
    get_DB_to_map(__U.up,mu);
    fill_map_from_map(m,mu);
    cc->html_out=cc->rvfiles(m,"change_info");
}
