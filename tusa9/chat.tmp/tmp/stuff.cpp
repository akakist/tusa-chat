int get_used_space(const user_pair& __U)
{
    MUTEX_INSPECTOR;
    size_t us=0;
    DB_id uid=user$id(__U);
    {
        __NOTE_LOCK(uid);
        for (map<unsigned int,__note_head>::const_iterator i=u->map_msgs.begin();i!=u->map_msgs.end();i++)
        {
            us+=i->second.nfh.content_length;
            us+=i->second.nfh.attachment_content_length;
        }
    }
    {
        PGLR(user_fotos,u,users_fotos.find_by_id_create(CONTAINER(uid)));
        us+=u->getsize();
    }
    return us;
}
void url_user_info2(const PTR_getter<chat_user> &__UU,app_connection *cc)
{
MUTEX_INSPECTOR;
LICENSE_CK(7);
    string out;
    bool admin=cc->sub_level>=am_admin;
    int level=cc->sub_level;
    map<string,string> m;

    vector<string> ilist,flist;

    DB_id cc_user_id;CONTAINER(cc_user_id)=0;
    if (__UU)cc_user_id=user$id(__UU);

    DB_id zid;CONTAINER(zid)=0;
    if (cc->vurl.size())
    {
        string by=cc->vurl[0];
        cc->vurl.pop_front();
        if (cc->vurl.size())
        {
            string val=cc->vurl[0];
            if (by=="ni")
            {
                zid=all_user_nick_2_DB_id(val);
                if(CONTAINER(zid)==0)
                {
                    zid=get_uid_by_nick(val);

                }
            }
            else if (by=="id")
                CONTAINER(zid)=atoi(val);
        }
    }

    if (CONTAINER(zid)==0)
	{
        m["~userinfo~"]="<center>"+_MSG("userleft")+"</center>";
        cc->html_out=cc->rvfiles(m,"chat/user_info");
		return;
    }
	PTR_getter <user_profile> __PZ=user$profiles.FindByID(CONTAINER(zid));
	if(!__PZ) 
	{
		m["~userinfo~"]="<center>"+_MSG("userleft")+"</center>";
		cc->html_out=cc->rvfiles(m,"chat/user_info");
		return;
	}


    string znick;
    {
        PGLR(user_profile,z,__PZ);
        znick=z->last_nick;
    }
    m["~nick~"]=znick;

    m["~admin~"]="";
	m["~ban~"]="";
    if (admin) {
        map<string,string> q;
        q["~id~"]=itostring(CONTAINER(zid));
        m["~admin~"]=RVfiles(q,"user_info/login_info");
    }
	if(cc->sub_level>=am_killer)
	{
	
		map<string,string> q;
		q["~id~"]=itostring(CONTAINER(zid));
		m["~ban~"]=RVfiles(q,"user_info/ban_uid");
	
	}

    make_user_info2(ilist,zid,admin,cc);
    {
        PGLR(user_profile, z,__PZ);
	string s=z->info;
	s=str_replace("\n","<br>",s); 
//	s=str_replace("\","<p>",s); 
        m["~about~"]=s;

    }

    if (cc->sub_level >= am_spy ) {
        PGLR(user_profile,z,__PZ);
        ilist.push_back("ip");
        ilist.push_back(z->stat_last_ip);

    }
    if (admin) {
        PTR_getter<chat_user> __ZZ=local_users.get$(zid,T_WWW);
        if (__ZZ)
        {
            user_pair __Z(__ZZ);
            {
                __ZC_LOCK;
                ilist.push_back("User-Agent");
                ilist.push_back(z->ua);


                if (z->www_screen_resolution.size())
                {
                    ilist.push_back("Screen resolution");
                    ilist.push_back(z->www_screen_resolution);
                }

            }
        }
    }
    {
        PGLR(user_fotos, u,users_fotos.find_by_id_create(CONTAINER(zid)));
        size_t cnt=u->fotos.size();
        m["~n_photo~"]=itostring(cnt);
        for(map<unsigned int, __foto>::const_iterator i=u->fotos.begin();i!=u->fotos.end();i++)
        {

            flist.push_back(itostring(i->first));
            flist.push_back(i->second.orig_fn);
            flist.push_back(i->second.descr);
        }
    }
    {
        vector<string> fl;
        for(unsigned i=0;i<flist.size();i++)
        {
            fl.push_back("\""+MES(flist[i])+"\"");
        }
	if(fl.size())
	{
	    m["~fotolist~"]="InitFotoList(["+join(",",fl)+"]);\nnphoto="+itostring(ilist.size())+";";
	}
	else
	m["~fotolist~"]="";
	
    }
    {
        vector<string> fl;
        for(unsigned i=0;i<ilist.size();i++)
        {
            fl.push_back("\""+MES(ilist[i])+"\"");
        }
	if(fl.size())
	{
	    m["~infolist~"]="BuildInfoList(["+join(",",fl)+"]);";
	}
	else 
	m["~infolist~"]="";
	
    }

    m["~uid~"]=itostring(CONTAINER(zid));
    cc->html_out=cc->rvfiles(m,"userinfo2/userinfo2");return;
}



void url_user_info(const PTR_getter<chat_user> &__UU,app_connection *cc)
{
MUTEX_INSPECTOR;
LICENSE_CK(11);
st_update stu;
    string out;
    bool admin=cc->sub_level>=am_admin;
    int level=cc->sub_level;
    map<string,string> m;

    DB_id cc_user_id;CONTAINER(cc_user_id)=0;
    if(__UU)cc_user_id=user$id(__UU);

    DB_id zid;CONTAINER(zid)=0;
    if(cc->vurl.size())
    {
        CONTAINER(zid)=atoi(cc->vurl[0]);
        cc->vurl.pop_front();
    }

    if(CONTAINER(zid)==0){
        m["~userinfo~"]="<center>"+_MSG("userleft")+"</center>";
        cc->html_out=cc->rvfiles(m,"chat/user_info");return;
    }
	PTR_getter<user_profile> __PZ=user$profiles.FindByID(CONTAINER(zid));
	if(!__PZ)
	{
		m["~userinfo~"]="<center>"+_MSG("userleft")+"</center>";
		cc->html_out=cc->rvfiles(m,"chat/user_info");
		return;
	}
    user_pair __U(__UU);

    if(cc->params["addcontact"]=="1")
    {
        out_oscar_buffer o;
        o<<zid;       __set_user_state(user_state::CONTACT_ADD,cc_user_id,o);
        chat_event_UPDATE_CONTACT_LIST *e=new chat_event_UPDATE_CONTACT_LIST(__UU,T_WWW);LEAKCTL_ADD(e);
        send_chat_event_push_back(e,false);

        {
            PGLW(contact_vec,c,contact_vecs.find_by_id_create(CONTAINER(cc_user_id)))
            c->contact.insert(zid);
        }
        __send_update_d3(contact$add$3,CONTAINER(cc_user_id),CONTAINER(zid));

    }
    else if(cc->params["addcontact"]=="0")
    {
        out_oscar_buffer o;
        o<<zid;       __set_user_state(user_state::CONTACT_REMOVE,cc_user_id,o);
        chat_event_UPDATE_CONTACT_LIST *e=new chat_event_UPDATE_CONTACT_LIST(__UU,T_WWW);LEAKCTL_ADD(e);
        send_chat_event_push_back(e,false);

        {
            PGLW(contact_vec,c,contact_vecs.find_by_id_create(CONTAINER(cc_user_id)))
            c->contact.erase(zid);
        }
        __send_update_d3(contact$remove$3,CONTAINER(cc_user_id),CONTAINER(zid));

    }

    string znick;
    {
        PGLR(user_profile,z,__PZ);
        znick=z->last_nick;
    }
    {
        map<string,string>q;
        q["~cnick~"]=znick;
        out+=RVfiles(q,"user_info/header");
    }
    if (admin) {

        map<string,string> q;
        q["~id~"]=itostring(CONTAINER(zid));
        out+=RVfiles(q,"user_info/login_info");
    }
	m["~ban~"]="";
	if(cc->sub_level>=am_killer)
	{

		map<string,string> q;
		q["~id~"]=itostring(CONTAINER(zid));
		m["~ban~"]=RVfiles(q,"user_info/ban_uid");

	}

    out += "</td></tr>\r\n";
    string out_www,out_irc;
    make_user_info(zid,cc_user_id,admin,"","",CONTAINER(cc_user_id)!=0,out_www,out_irc);
    out<<out_www;
    {
        PGLR(user_profile, z,__PZ);
        if (z->info != "") {
            out<<"<tr><td align=center colspan=2><hr class=hr size=2 width=\"100%\"></td></tr>";
        }
    }
    bool added=false;
    {
        PGLR(contact_vec,u,contact_vecs.find_by_id_create(CONTAINER(cc_user_id)));
        added=u->contact.count(zid);
    }
    if(!added)
    {
        map<string,string>q;
        q["~id~"]=itostring(CONTAINER(zid));
        out+=RVfiles(q,"user_info/add_contact");
    }
    else
    {
        map<string,string>q;
        q["~id~"]=itostring(CONTAINER(zid));
        out+=RVfiles(q,"user_info/del_contact");
    }


    if (cc->sub_level >= am_spy ) {
        PGLR(user_profile,z,__PZ);
        map<string,string>q;
        q["~ip~"]=z->stat_last_ip;
        out+=RVfiles(q,"user_info/ip");
        
    }
    if (admin) {
        PTR_getter<chat_user> __ZZ=local_users.get$(zid,T_WWW);
        if(__ZZ)
        {
            user_pair __Z(__ZZ);
            {
                __ZC_LOCK;
                map<string,string> q;
                q["~ua~"]=z->ua;
                out+=RVfiles(q,"user_info/ua");

                {

                    if(z->www_screen_resolution.size())
                    {
                        map<string,string> qq;
                        qq["~sr~"]=z->www_screen_resolution;
                        out+=RVfiles(qq,"user_info/sr");
                    }
                }
            }
        }
    }
    {
        map<string,string>q;
        out+=RVfiles(q,"user_info/footer");
    }
    m["~userinfo~"]=out;
    cc->html_out=cc->rvfiles(m,"user_info/user_info");return;
}

void make_user_info2(vector<string>&ilist, const DB_id& zid, bool admin,app_connection *cc)
{
MUTEX_INSPECTOR;

    string n;
    string nick_name;
    unsigned int nick_id;
	PTR_getter <user_profile> __PZ=user$profiles.FindByID(CONTAINER(zid));
	if(__PZ)
    	{
        PGLR(user_profile, u,__PZ);
        nick_name=u->last_nick;
        nick_id=u->last_nick_id;
    	}
    	else
    	{
    		throw cError("err load __P %s %d %s",__FILE__,__LINE__,_DMI().c_str());
    	}
	

    bool hide_fname;
    bool hide_lname;
    bool hide_bdate;
    bool hide_tel;
    bool hide_email;
    bool hide_icq;
    string fname,lname;
    int gender;
	bool hide_family_status;
	string family_status;

    bool setting_show_nicks,setting_show_level,setting_show_credits;
    string b_day,b_year;
    int b_mon;
    string city;
    string homepage,email,icq,info,tel;
    Double credits;
    {
        PGLR(user_profile, u,__PZ);
        credits=u->credit_summa;

    }
    unsigned int level;
    {
        PGLR(user_profile, u,__PZ);
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
		hide_fname=u->hide_fname;
		hide_lname=u->hide_lname;
		hide_bdate=u->hide_bdate;
		hide_tel=u->hide_tel;
		hide_email=u->hide_email;
		hide_icq=u->hide_icq;
		hide_family_status=u->hide_family_status;
		family_status=u->family_status;
    }
    {
        PGLR(user_profile, u,__PZ);
        setting_show_nicks=u->setting_show_nicks;
        setting_show_level=u->setting_show_level;
        setting_show_credits=u->setting_show_credits;
		level=u->level;
    }
    {
        PGLR(user_profile, u,__PZ);
        gender=u->get_gender();
    }

    __ui_fio2(ilist,admin,hide_fname,hide_lname,fname,lname);


    __ui_nicks2(ilist,zid, setting_show_nicks, nick_name, gender, admin);

    //gender
    __ui_gender2(ilist,gender);



    //born date

    __ui_birthdate2(ilist,hide_bdate, admin, gender, b_day, b_year, b_mon);

    //live in...
    if(city.size())
    {
        ilist.push_back(_MSG("livein"));
        ilist.push_back(city);
    }
    //homepage
    if(homepage!="" && homepage!="http://"){


        string s1=_MSG("homepage");
        string s2;
        if(homepage.find("http://", 0)!=-1 || homepage.find("www.",0)!=-1){
            if (homepage.find("http://", 0)==-1){
                s2<<"<a href=\"http://"<<homepage<<"\" target=_blank>"<<homepage<<"</a>";
            }else{
                s2<<"<a href=\""<<homepage<<"\" target=_blank>"<<homepage<<"</a>";
            }
        }else{
            s2<<homepage;
        }
        if(s2.size())
        {
            ilist.push_back(s1);
            ilist.push_back(s2);
        }

    }
    //email
    if(email!="" && ((!hide_email) || admin)) {

        string s1="E-Mail";
        string s2;
        if(string(email).find("@",0)!=-1){
            s2<<"<a href=\"mailto:"<<email<<"\">"<<email<<"</a>";
        }else{
            s2<<email;
        }
        if(admin && hide_email) {
            s2<<" "<<_MSG("hidden");
        }
        if(s2.size())
        {
            ilist.push_back(s1);
            ilist.push_back(s2);
        }
    }
    //icq
    if(icq!="" && ((!hide_icq) || admin)) {
        {
            string s1;
            string s2;
            s1="ICQ";
            int zz=atoi(icq);

            s2<<icq;
            if(admin && hide_icq) {
                s2<<" "<<_MSG("hidden");
            }
            if(s2.size())
            {
                ilist.push_back(s1);
                ilist.push_back(s2);
            }
        }
    }
    //tel
    if(tel!="" && ((!hide_tel) || admin)){

        string s1,s2;
        {
            s1<<_MSG("tel");
            s2<<tel;

            if(admin && hide_tel){
                s2<<" "<<_MSG("hidden");
            }
        }
        if(s2.size())
        {
            ilist.push_back(s1);
            ilist.push_back(s2);
        }

    }
    //level
    if(setting_show_level || admin){
        string s1,s2;
        s1=_MSG("level");
        if(admin && !setting_show_level)
            s2<<LEVEL_NAME(level,gender)<<" "<<_MSG("hidden");
        else
            s2<<LEVEL_NAME(level,gender);
        if(s2.size())
        {
            ilist.push_back(s1);
            ilist.push_back(s2);
        }
    }
    //credits
    if(setting_show_credits || admin){
        string s1,s2;
        s1<<_MSG("credits");
        if(admin && !setting_show_credits){
            s2<<get_f22(credits.container)<<" "<<_MSG("hidden");
        }else{
            s2<<get_f22(credits.container);
        }
		if(s2.size())
		{
			ilist.push_back(s1);
			ilist.push_back(s2);
		}
    }
	if(family_status!="" && ((!hide_family_status) || admin)) {
		{
			string s1;
			string s2;
			s1=_MSG("family_status");
			//int zz=atoi(icq);

			s2<<family_status;
			if(admin && hide_icq) {
				s2<<" "<<_MSG("hidden");
			}
			if(s2.size())
			{
				ilist.push_back(s1);
				ilist.push_back(s2);
			}
		}
	}


}


void url_login(PTR_getter<chat_user> &__UU,app_connection* cc)
{
    CKTIME;
    LICENSE_CK(2);
	st_update stu;
	if (!check_for_max_users()) throw cError("max users reached"+_DMI());
    MUTEX_INSPECTOR;
    string login,pass;
    bool check_pass=true;

    login = cc->params["login"];
    pass = cc->params["pass"];


    map < string, string > m;
    m["~login~"] = login;
    string add_s;

    if ((pass.size() == 0 && check_pass) && login.size() != 0)
    {
        cc->html_out=cc->rvfiles(m,"login/incorrect");
        return;


    }

    if (login.size() > 0 && (pass.size() > 0 || !check_pass) ) {//;	//login with registration

        if (!create_reg_user(__UU, cc,login,pass,check_pass)) {
			{
//				PGLR(chat_user, u,__UU);
//				__cookie_2_DB_id.erase_$(u->www_cookie);
			}
            if (cc->html_out.size()==0)
                cc->html_out=cc->redirect();
            return;
        }
    }
    if (!__UU) {
        cc->html_out=cc->redirect();
        return;
    }

    user_pair __U(__UU);

    {
        __UC_LOCK;
        u->cu_ip=cc->peer_ipaddress;
    }
    DB_id uid=user$id(__UU);
    {
        __send_update_d3(user_profile$stat_last_ip$3,CONTAINER(uid),cc->peer_ipaddress);
        __send_update_d3(common$set_stat_last_ip$3,CONTAINER(uid),cc->peer_ipaddress);
    }
    if (!local_users.count$(uid,T_WWW)) {
        //cc->out_cookies["PHPSESSID"]="0";
		{
			PGLR(chat_user, u,__UU);
			__cookie_2_DB_id.erase_$(u->www_cookie);
		}
        cc->html_out = cc->rvfiles(m, add_s+"login/incorrect");
	//st_dbh d;
	//d.dbh->real_queryQ((QUERY)"delete from chat_session where uid='?'"<<CONTAINER(user$id(__U)));
        return;
    }
    cc->__user_id=uid;

    if (user$level(__U)/sub_levels <am_admin)
    {
        if (!check_for_ipban(cc->peer_ipaddress)) {	//may be banned.
            m["~ip~"] = cc->peer_ipaddress;
            cc->html_out = cc->rvfiles(m, "login/ipbanned");
            logErr2("Attempt to login from BANNED ip address %s [%s]", login.c_str(), cc->peer_ipaddress.c_str());
			{
				PGLR(chat_user, u,__UU);
				__cookie_2_DB_id.erase_$(u->www_cookie);
			}
	st_dbh d;
	d.dbh->real_queryQ((QUERY)"delete from chat_session where uid='?'"<<CONTAINER(user$id(__U)));
            return;
        }

    }


    user_register_all_nicks(uid);
    make_login_out(__UU, cc);
}


static bool create_reg_user(PTR_getter<chat_user> &__UU,app_connection*cc,const string& __login, const string&__pass, bool check_pass)
{
    CKTIME;
    LICENSE_CK(7);
    MUTEX_INSPECTOR;
	st_update stu;
    string login=__login;
    string pass=bin2hex(MD5(__pass),0);
    map<string,string> m;
    m["~login~"]=login;

    if (login.size()>MAX_NICK_SIZE || !check_nick(login) || !check_maty(" "+login) || login.size()==0){
        cc->html_out=RVfiles(m, "login/badnick");
        return false;
    }
    PTR_getter<chat_user> __ZZ(NULL);
    DB_id zid=all_user_nick_2_DB_id(login);
    if (CONTAINER(zid))   __ZZ=local_users.get$(zid,T_WWW);
    bool need_create=true;
    if (__ZZ)
    {

        user_pair __Z(__ZZ);
        string upass;
        {
            PGLR(user_profile, u,__Z.up);
            upass=u->pass;
        }

        if (strupper(upass)==strupper(pass) || !check_pass){
        }else{
            cc->html_out=cc->rvfiles(m,"login/incorrect");

            return false;
        }


        __UU=__ZZ;
        need_create=false;
        user_pair __U(__UU);



        string cookie;
        string old_cookie;
        DB_id __uid=user$id(__UU);
        {
            __UC_LOCK;
            u->erased=false;
            u->cu_ip=cc->peer_ipaddress;

            sid_t st;
            st.user_map_key=CONTAINER(u->db_id);
            st.user_map_key1=rand();
            old_cookie=u->www_cookie;
            u->www_cookie=get_des_hex_sid(st);
            cc->out_cookies.clear();
            cc->out_cookies["PHPSESSID"]=u->www_cookie;
            cookie=u->www_cookie;
        }
//    st_dbh d;
  //  d.dbh->real_queryQ((QUERY)"delete from chat_session where uid='?'"<<CONTAINER(user$id(__U)));
    //d.dbh->real_queryQ((QUERY)"insert into chat_session (cookie,uid,login, last_time) values ('?','?','?',NOW())"<< cookie<<CONTAINER(user$id(__U))<<user$login(__U));
	


        {
            __send_update_d3(user_profile$stat_last_date$3,CONTAINER(__uid),time(NULL));
            __send_update_d3(user_profile$stat_last_ip$3,CONTAINER(__uid),cc->peer_ipaddress);

            __send_update_d3(common$set_stat_last_ip$3,CONTAINER(__uid),cc->peer_ipaddress);

        }
        user_register_all_nicks(__uid);
        local_users.insert$(__UU);
        __cookie_2_DB_id.erase_$(old_cookie);
        string login$,cnick$;
        int level$;
        vector<string> nicks$;
        {
            PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(__uid)));
			login$=u->login;
			level$=u->level;
			cnick$=u->last_nick;
        }
        {
            PGLR(nick_vec,u,nick_vecs.find_by_id_create(CONTAINER(__uid)));
            for (map<unsigned int,user_nick>::const_iterator i=u->u_nicks.begin();i!=u->u_nicks.end();i++)
            {
                nicks$.push_back(i->second.name);
            }
        }

        __cookie_2_DB_id.set_$(cookie,__uid,login$,cnick$,nicks$,level$);
        return true;
    }
    string l_res=login_io(login,pass);
    oscar_buffer b(l_res.data(),l_res.size());
    int log_res;
    b>>log_res;
    if (log_res==LOGIN_INCORRECT)
    {
        cc->html_out=cc->rvfiles(m,"login/incorrect");
        return false;
    }

    if (log_res!=LOGIN_SUCCESS)
    {
        throw cError("log_res!=LOGIN_SUCCESS"+_DMI());
    }


    DB_id uid;CONTAINER(uid)=0;    b>>uid;
    if (CONTAINER(uid)==0)
        logErr2("Error: CONTAINER(uid)==0 %s",_DMI().c_str());
    st_dbh d;
    vector <string> z=d.dbh->select_1_rowQ((QUERY)"select time_cnt,UNIX_TIMESTAMP(time_free),UNIX_TIMESTAMP(time_ban),descr from banned_login where uid='?'"<<CONTAINER(uid));
    if (z.size()!=0){	//login banned.
        MUTEX_INSPECTOR;
        logErr2("Attempt to login by BANNED login %s [%s]",login.c_str(),cc->peer_ipaddress.c_str());
        if (z.size()==4)
        {
            m["~time_cnt~"]=z[0];
            m["~time_free~"]=date2rus(atoi(z[1]));
            m["~time_ban~"]=date2rus(atoi(z[2]));
            m["~reason~"]=z[3];

        }
        cc->html_out=cc->rvfiles(m, "login/loginbanned");
        return false;
    }

    //All OK. Creating registered user.
    if (need_create)
    {
        chat_user*__u=new chat_user(T_WWW,uid);LEAKCTL_ADD(__u);
        __UU=__u;
    }

    {
        PGLW(chat_user, u,__UU);
        u->__user_profile=user$profiles.FindByID(CONTAINER(uid));
    }
    user_pair __U(__UU);
    init_internal_data(__U);

    {
        __send_update_d3(user_profile$stat_last_date$3,CONTAINER(uid),time(NULL));
        __send_update_d2(user_profile$inc_stat_v_count$2,CONTAINER(uid));

    }

    {
        __UC_LOCKW;
        u->db_id=uid;
    }
    logErrN("users","%s (%s) logged in. [%s]",login.c_str(),string(user$login(__U)).c_str(),cc->peer_ipaddress.c_str());
    sid_t st;
    st.user_map_key=CONTAINER(uid);
    st.user_map_key1=rand();
    string cookie=get_des_hex_sid(st);

    string login$,cnick$;
    int level$=0;
    vector<string> nicks$;
    {
        PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(uid)));
		login$=u->login;
		cnick$=u->last_nick;
		level$=u->level;
    }
    {
        PGLR(nick_vec,u,nick_vecs.find_by_id_create(CONTAINER(uid)));
        for (map<unsigned int,user_nick>::const_iterator i=u->u_nicks.begin();i!=u->u_nicks.end();i++)
        {
            nicks$.push_back(i->second.name);
        }
    }

    __cookie_2_DB_id.set_$(cookie,uid, login$,cnick$,nicks$,level$);

    {__UC_LOCK;

        u->cu_ip=cc->peer_ipaddress;
        u->ua=cc->params["USER-AGENT"];
        u->login_date=time(NULL);
        u->last_access_time=time(NULL);
        u->www_unregistered=false;
        u->erased=false;
        u->www_cookie=cookie;
        cc->out_cookies.clear();
        cc->out_cookies["PHPSESSID"]=cookie;

    }
//    st_dbh d;
//    d.dbh->real_queryQ((QUERY)"delete from chat_session where uid='?'"<<CONTAINER(user$id(__U)));
//    d.dbh->real_queryQ((QUERY)"insert into chat_session (cookie,uid,login, last_time) values ('?','?','?',NOW())"<< cookie<<CONTAINER(user$id(__U))<<user$login(__U));
    
    user_register_all_nicks(uid);
    local_users.insert$(__UU);
    cc->init_temp_vars(__UU);
    if (__UU) return true;

    else return false;

}

PTR_getter<chat_user> create_chat_user(const DB_id &uid)
{
    st_dbh d;
    vector<string> v=d.dbh->select_1_rowQ((QUERY)"select cookie from chat_session where uid='?'"<<CONTAINER(uid));
    if (v.size())
    {
        string cookie=v[0];
//		app_connection cc;
        return create_reg_user(uid,cookie);
    }
    return NULL;

}
PTR_getter<chat_user> get_chat_user(const DB_id &uid)
{
    PTR_getter<chat_user> r=local_users.get$(uid,T_WWW);
    if (r) return r;
    st_dbh d;
    vector<string> v=d.dbh->select_1_rowQ((QUERY)"select cookie from chat_session where uid='?'"<<CONTAINER(uid));
    if (v.size())
    {
        string cookie=v[0];
        return create_reg_user(uid,cookie);
    }
    return NULL;

}

PTR_getter<chat_user> create_reg_user(const DB_id&uid,const string& cookie)
{
    MUTEX_INSPECTOR;
    PTR_getter<chat_user> __UU(NULL);

    chat_user*__u=new chat_user(T_WWW,uid);LEAKCTL_ADD(__u);
    __UU=__u;
	PTR_getter<user_profile> __P=user$profiles.FindByID(CONTAINER(uid));
	if(!__P) throw cError("if(!__P) %s %d %s",__FILE__,__LINE__,_DMI().c_str());
    {
        PGLW(chat_user, u,__UU);
        u->__user_profile=user$profiles.FindByID(CONTAINER(uid));
    }
    user_pair __U(__UU);
    init_internal_data(__U);


    {
        __UC_LOCKW;
        u->db_id=uid;
    }

    string login$,cnick$;
    int level$=0;
    vector<string> nicks$;
    {
        PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(uid)));
		login$=u->login;
		cnick$=u->last_nick;
		level$=u->level;
    }
    
    {
        PGLR(nick_vec,u,nick_vecs.find_by_id_create(CONTAINER(uid)));
        for (map<unsigned int,user_nick>::const_iterator i=u->u_nicks.begin();i!=u->u_nicks.end();i++)
        {
            nicks$.push_back(i->second.name);
        }
    }

    __cookie_2_DB_id.set_$(cookie,uid, login$,cnick$,nicks$,level$);

    {__UC_LOCK;

//        u->cu_ip=cc->peer_ipaddress;
//        u->ua=cc->params["USER-AGENT"];
        u->login_date=time(NULL);
        u->last_access_time=time(NULL);
        u->www_unregistered=false;
        u->erased=false;
        u->www_cookie=cookie;

    }
    user_register_all_nicks(uid);
    local_users.insert$(__UU);
    return __UU;

}

void url_settings_nick_buy(const PTR_getter<chat_user> &__UU,app_connection *cc)
{
    LICENSE_CK(15);
    if (!__UU){ cc->html_out=cc->redirect();return;}
    DB_id cc_user_id=user$id(__UU);
	st_update stu;
    user_pair __U(__UU);
    vector<string> __vn=splitTOK(".",cc->params["n"]);

    if (__vn.size()!=2) throw cError("__vn.size()!=2"+_DMI());
    DB_id zid;CONTAINER(zid)=0;CONTAINER(zid)=atoi(__vn[0]);
    unsigned int znid;
    znid=atoi(__vn[1]);
    string nick;
    bool ready_to_sale=false;
    Double cost;
    {
        PGLW(nick_vec,n,nick_vecs.find_by_id_create(CONTAINER(zid)));
        if (!n->u_nicks.count(znid))
            throw cError("if(!n->u_nicks.count(znid))"+_DMI());
        user_nick &un=n->u_nicks[znid];
        nick=un.name;
//		ready_to_sale=un.ready_to_sale;
        cost.container=un.cost.container;
    }

    map<string,string>m;
    m["~n~"]=cc->params["n"];
    m["~nick~"]=nick;
    m["~cost~"]=get_f22(cost.container);
    m["~error~"]="";
    Double summa;summa.container=0;
    {
        PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(cc_user_id)));
		summa=u->credit_summa;
    }
    m["~credits~"]=get_f22(summa.container);
    m["~b_buy~"]="";
    m["~e_buy~"]="";
    if (summa.container<cost.container)
    {
        m["~b_buy~"]="<!--";
        m["~e_buy~"]="-->";
    }
    ready_to_sale=false;
    if (cc->params["todo"]=="buy" && ready_to_sale)
    {

        {
            PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(cc_user_id)));
			if (summa.container<cost.container) throw cError("not enouph credits"+_DMI());
        }
        m["~credits~"]=get_f22(summa.container-fabs(cost.container));

        buy_thing(cc_user_id,zid,cost,"buy_nick");

        map<string,string>qq;

        qq["~nick~"]=nick;
        qq["~cost~"]=get_f22(cost.container);
        send_system_note(zid,RVfiles(qq,"settings/nick_buy_success_note_subj"),RVfiles(qq,"settings/nick_buy_success_note_body"));

//        user_unregister_all_nicks(zid,true);
        __send_update_d3(nick$remove$3,CONTAINER(zid),znid);

        {
            PGLW(nick_vec, n,nick_vecs.find_by_id_create(CONTAINER(zid)));
            n->u_nicks.erase(znid);
        }

        unsigned int newid=0;
        /*{
            PGLW(nick_vec, n,nick_vecs.find_by_id_create(CONTAINER(cc_user_id)));
            if (n->u_nicks.size())
                newid=n->u_nicks.rbegin()->first;
        }*/
		st_dbh dd;
		dd.dbh->real_queryQ((QUERY)"insert into nicks (nick,str_nick,uid,banned,bby,last_usage_date,ready_to_sale) values ('?','?','?','0','0',NOW(),'0')"<<nick<<str_nick(nick)<<CONTAINER(cc_user_id));
		newid=atoi(dd.dbh->select_1("select LAST_INSERT_ID()"));

        //newid++;
        logErrN("users","%s  bought already registered nick '%s'.",user$login(__U).c_str(),nick.c_str());
        //user_unregister_all_nicks(cc_user_id,true);
        Double d;
        user_nick nnn(nick,newid,cc_user_id,false,d);
        {
            PGLW(nick_vec, n,nick_vecs.find_by_id_create(CONTAINER(cc_user_id)));
            n->u_nicks.insert(make_pair(newid,nnn));
        }

        __send_update_d3(nick$add$3,cc_user_id,nnn);



        cc->html_out=cc->rvfiles(m,"settings/nick_buy_success");
        return;

    }
    cc->html_out=cc->rvfiles(m,"settings/nick_buy");
}
void url_chat_addmessage(const PTR_getter<chat_user> &__UU,app_connection*cc)
{
    MUTEX_INSPECTOR;

    if (!__UU){
        logErr2("if(!__UU)");
        return;
    }

    LICENSE_CK(18);
    user_pair __U(__UU);
    map<string,string> m;
    string s;
    unsigned int ulevel=user$level(__U);
    bool hinv=has_inv(__U);

    user_status status=global_state.get_status(user$id(__UU));

    unsigned char gender=user$gender(__U);
    {

        PGLW(user_profile,u,__U.up);
        map<unsigned int,user_status> &st=u->status;
        for (map<unsigned int,user_status>::const_iterator i=st.begin();i!=st.end();i++)
        {

            MUTEX_INSPECTOR;
            if (i->first==st_offinvisible) continue;
            if (i->first==st_invisible && !hinv) continue;
            if (i->first==st_offline) continue;
            s+="<OPTION VALUE="+itostring(i->first);

            if (i->first==status.id)
                s+=" SELECTED";
            string n=i->second.name;
            if (n.size()>16) n=n.substr(0,15)+"...";
            s+=">"+n;
        }
    }
    if (ulevel/sub_levels>=am_admin){
        m["~s_script~"]="";
        m["~es_script~"]="";
        m["~hsys~"]="";
        m["~ehsys~"]="";
        m["~sysmsg~"]="";
        m["~esysmsg~"]="";
    }else{
        m["~s_script~"]="/*";
        m["~es_script~"]="*/";
        m["~hsys~"]="<!--";
        m["~ehsys~"]="-->";
        m["~sysmsg~"]="<!--";
        m["~esysmsg~"]="-->";
    }
    m["~status~"]=s;

    {
        PGLR(chat_user,u,__U.cu);
        m["~msglen~"]=itostring(u->max_msg_len);
        //	m["~cansettopic~"]=itostring(u->privs.count("topic"));
    }
    bool canset=false;
    {
        PGLR(user_profile,u,__U.up);
	canset=u->__privileges.count("$topic");
    }
    if(user$level(__U)>=500)
    	canset=true;
        m["~cansettopic~"]=itostring(canset);
    set<CH_id> uch=global_state.get_user_channel(T_WWW,user$id(__UU));

    DB_id uid=user$id(__U);
    bool moderated=false;
    if (uch.size()!=1)
    {
        MUTEX_INSPECTOR;
        st_dbh d;
        CH_id ch; CONTAINER(ch)=atoi(d.dbh->select_1Q((QUERY)"select last_channel from tbl_users where id=?"<<CONTAINER(user$id(__U))));
        if (!chat_channels.count(ch))
        {
            vector<CH_id> vc=chat_channels._keys();
            if (vc.size())
            {
                ch=vc[0];
                user_state st=global_state.get_user_state(uid);
                st.www_channel_replace(ch);
                global_state.set_user_state(uid,st);
                uch=global_state.get_user_channel(T_WWW,uid);
            }
            else
            {
                cc->html_out=RVfiles("scripts/invalid_channel");
                logErr2("uch.size()!=1 %d",uch.size());
                return;
            }

        }
        //http://tusovka.tomsk.ru/login
    }
    if (uch.size())
    {

        {
            MUTEX_INSPECTOR;

            __CH_LOCK(chat_channels[*uch.begin()]);
            moderated=CH->cd.moderated;
        }
        CH_id c=*uch.begin();
        m["~channel~"]=itostring(CONTAINER(c));
    }


    m["~moderated~"]=checked(moderated);

    cc->html_out=RVfiles(m,"chat/add_message");
}
void CMD_url_chat_enter(command_connection *cc)
{
}
void url_chat_enter(const PTR_getter<chat_user> &__UU,app_connection *cc)
{
    MUTEX_INSPECTOR;

    vector<string> SQL;
    LICENSE_CK(9);
	st_update stu;
    if (!__UU)
    {
        logErr2(" url_chat_enter:: if(!__UU) ");
        return;
    }
    user_pair __U(__UU);
    DB_id uid=user$id(__UU);
    user_state sta=global_state.get_user_state(uid);

    LICENSE_CK(18);
    CH_id channel;CONTAINER(channel)=0;

    {


        unsigned int new_nick_id=sta.nick.id;
        if (cc->params.count("nick"))
        {
            new_nick_id=atoi(cc->params["nick"]);
        }

        if (user$nicks_size(user$id(__UU)) <= 0){
            cc->redirect("/login");
            logErr2("url_chat_enter: return %s %d",__FILE__,__LINE__);
            return;
        }
        sta.nick=GET_NICK(uid,new_nick_id);
        set<CH_id> SCH=sta.get_channel(T_WWW);
        if (SCH.size())
        {
            channel=*SCH.begin();
        }
        if (cc->params.count("channel"))
        {
            CONTAINER(channel)=atoi(cc->params["channel"]);
        }
        if (!chat_channels.count(channel))
        {
            vector<CH_id>chs=chat_channels._keys();//splitTOK(" ,\r\n",chat_config.channel_list.get());

            if (chs.size())channel=chs[0];
        }


        map<string,string> m;
        {
            __UC_LOCKW;

            u->www_offline_time=0;
        }
        sta.www_channel_replace(channel);


        if (has_inv(__U))
        {
            if (cc->params["ininv"]=="on"){

                sta.status=get_user_status_by_id(__U,st_invisible);
                SQL.push_back((string)"last_invis_state='1'");
            }
            else
            {
                if (sta.status.id==st_invisible || sta.status.id==st_offinvisible)
                {
                    sta.status=get_user_status_by_id(__U,st_online);
                }
                SQL.push_back((string)"last_invis_state='0'");
            }
        }
        if (sta.status.id==user_state::UNDEF) sta.status=get_user_status_by_id(__U,st_online);
        if (sta.status.id==st_offline) sta.status=get_user_status_by_id(__U,st_online);
        if (sta.status.id==st_offinvisible) sta.status=get_user_status_by_id(__U,st_invisible);
        if (sta.status.id==st_away) sta.status=get_user_status_by_id(__U,st_online);
        if (sta.status.id==st_na) sta.status=get_user_status_by_id(__U,st_online);
        {
            {
                PGLW(user_profile,u,__U.up);
                if (sta.status.id!=u->last_status_id)
                {
                    __send_update_d3(user_profile$last_status_id$3,CONTAINER(uid),sta.status.id);
                    u->last_status_id=sta.status.id;
                    SQL.push_back((string)"last_status_id='"+itostring(sta.status.id)+"'");

                }
            }
        }

        if (cc->params["showadm"]=="on"){
            PGLW(user_profile, u,__U.up);
            if (!u->setting_show_eye)
            {
                if (u->setting_show_eye!=true)
                {
                    u->setting_show_eye=true;
                    __send_update_d3(user_profile$setting_show_eye$3,CONTAINER(uid),u->setting_show_eye);
                    SQL.push_back((string)"setting_show_eye='"+itostring( u->setting_show_eye)+"'");
                }
            }
        }else{

            PGLW(user_profile, u,__U.up);
            if (u->setting_show_eye)
            {
                if (u->setting_show_eye!=false)
                {
                    u->setting_show_eye=false;
                    __send_update_d3(user_profile$setting_show_eye$3,CONTAINER(uid),u->setting_show_eye);
                    SQL.push_back((string)"setting_show_eye='"+itostring( u->setting_show_eye)+"'");
                }
            }
        }

        unsigned int setting_neye=atoi(cc->params["eye"]);

        if (user$level(__U)/sub_levels<am_sadmin && setting_neye>chat_config.number_of_eyes)
        {
            PGLW(user_profile, u,__U.up);
            setting_neye=0;
        }
        {
            PGLW(user_profile, u,__U.up);
            if (u->setting_neye!=setting_neye)
            {
                u->setting_neye=setting_neye;
                __send_update_d3(user_profile$setting_neye$3,CONTAINER(uid),u->setting_neye);
                SQL.push_back((string)"setting_neye='"+itostring(setting_neye)+"'");
            }
        }
        { __UC_LOCKW;
            u->www_offline_time=0;
            u->www_inchat=true;
        }
    }
    cc->allow_build_response=false;
    if (sta.nick.name=="")
    {

        logErr2("sta.nick.name==\"\" %s %d",__FILE__,__LINE__);
        return;

    }


	bool need_execute=false;
    {
        PGLW(user_profile, u,__U.up);
        if (u->last_nick_id!=sta.nick.id)
        {
            u->last_nick_id=sta.nick.id;
            u->last_nick=sta.nick.name;
            __send_update_d3(user_profile$last_nick$3,CONTAINER(uid),sta.nick.name);
            __send_update_d3(user_profile$last_nick_id$3,CONTAINER(uid),sta.nick.id);
            __send_update_d3(nick$set_last_usage_date$3,CONTAINER(uid),sta.nick.id);
            SQL.push_back((string)"last_nick='"+MES(sta.nick.name)+"'");
            SQL.push_back((string)"last_nick_id='"+itostring(sta.nick.id)+"'");
			need_execute=true;
        }
  
        __send_update_d3(user_profile$last_channel$3,CONTAINER(uid),CONTAINER(channel));
        SQL.push_back((string)"last_channel='"+itostring(CONTAINER(channel))+"'");

    }
	if(need_execute)
	{
		st_dbh d;
		d.dbh->real_queryQ((QUERY)"update nicks set last_usage_date=NOW() where uid=? and id=?"<<CONTAINER(uid)<<sta.nick.id);
	}

    {
        string out="HTTP/1.1 302 Found\r\n";
        out+="Location: /chat/\r\n";
        out+="Connection: close\r\n";
        out+="Server: "+SERVERNAME.get()+"\r\n";
        out+="\r\n";
        reply_socket(cc->socket,out);
    }
    if (SQL.size())
    {
        st_dbh d;
        d.dbh->real_query((string)"update tbl_users set "+join(",",SQL)+" where id="+itostring(CONTAINER(uid)));
    }

}

void url_chat_buttons(const PTR_getter<chat_user> &__UU,app_connection*cc)
{
    MUTEX_INSPECTOR;

    LICENSE_CK(37);
    if (!__UU)
    {
        logErr2("if(!__UU) %s %d",__FILE__,__LINE__);
        return;
    }

    user_pair __U(__UU);
    LICENSE_CK(16);
    map<string,string> m;
    vector<pair<string,string> > c;

    string rm;

    vector<CH_id>chs=chat_channels._keys();//splitTOK(" ,",chat_config.channel_list.get());



    for (unsigned int i=0;i<chs.size();i++){
        //if(chat_channels.count(chs[i]))
        //{
        __CH_LOCK(chat_channels[chs[i]]);
        c.push_back(make_pair(itostring(CONTAINER(chs[i])),CH->cd.name+" (  )"));
        rm+="rooms["+itostring(i)+"]=\""+CH->cd.name+"\";\r\n";
        //}

    }
    m["~rooms~"]=rm;
    m["~level~"]=LEVEL_NAME(user$level(__U),user$gender(__U));
    DB_id uid=user$id(__UU);
    unsigned int cnick=GET_CNICK_ID(__U);
    {
        PGLR(nick_vec,n,nick_vecs.find_by_id_create(CONTAINER(uid)));
        if (!n->u_nicks.count(cnick))
        {
            if (!n->u_nicks.size())
            {
                cnick=n->u_nicks.begin()->first;
            }
        }

    }
    m["~nick~"]=build_nicks_select(uid,"nick",cnick," onchange='ch_nick();' class=bsel");

    CH_id lchan;CONTAINER(lchan)=0;
    {
        PGLR(user_profile, u,__U.up);
        lchan=u->last_channel;
    }
    int chidx=0;
    for (int i=0;i<chs.size();i++)
    {
        if (chs[i]==lchan) chidx=i;
    }
    m["~channel~"]=make_select("channel",c,itostring(chidx)," onchange='ch_room();' class=bsel");
    if (chs.size()==1){
        m["~schannel~"]="<!--";
        m["~eschannel~"]="-->";
    }else{
        m["~schannel~"]="";
        m["~eschannel~"]="";
    }
    if (user$level(__U)/sub_levels>=am_killer ||  u_has_console(__U)){
        m["~adm~"]="";
        m["~eadm~"]="";
    }else{
        m["~adm~"]="<!--";
        m["~eadm~"]="-->";
        m["panel_adm.gif"]="panel.gif";
    }
    cc->html_out=cc->rvfiles(m,"chat/buttonsframe");
}

void url_logout(const PTR_getter<chat_user> &__UU,app_connection*cc)
{
    MUTEX_INSPECTOR;

    bool ok=false;
    if (__UU){
    MUTEX_INSPECTOR;
        user_pair __U(__UU);
        user_destroy(__UU);
        map<string,string> op;

        time_t spent=user$get_spent_time(__U);

        logErrN("users","%s logout. [%s] {%d}",string(user$login(__U)).c_str(),cc->peer_ipaddress.c_str(),spent);

        op["~name~"]=get_full_name(__U);

		{
			PGLR(chat_user, u,__UU);
			__cookie_2_DB_id.erase_$(u->www_cookie);
		}
        cc->html_out=cc->rvfiles(op,"logout");
        ok=true;
    }
    if (ok){
 	   MUTEX_INSPECTOR;
	st_dbh d;
	d.dbh->real_queryQ((QUERY)"delete from chat_session where uid='?'"<<CONTAINER(user$id(__UU)));
        url_index(__UU,cc);
        return;
    }
}
void url_chat_exit(const PTR_getter<chat_user> &__U,app_connection *cc)
{
    MUTEX_INSPECTOR;

    if (!__U){
        return;
    }
    us_PART_CHANNEL(T_WWW,cc->__user_id);
    CONTAINER(cc->__user_id)=0;
//    if(cc->user_unregistered){
//        cc->redirect("/logout");
//    }else{
    cc->redirect(RVfiles("url_login_redirect"));
//    }
}
void url_index(const PTR_getter<chat_user>&__UU, app_connection * cc)
{
    LICENSE_CK(37);
    MUTEX_INSPECTOR;
    if (cc->params["s"] == "1") {
        logErr2("--Info: Set home page from %s", cc->peer_ipaddress.c_str());
    }

    map<string, string > m;
//    m["~news~"] = get_news_for_index(cc) ;//news;
    m["~login~"] = cc->params["login"];
    if (__UU)
    {
//		make_login_out(__UU,cc);
//		return;
    }



//    m["~concurs~"]=get_councurs_table(__UU);
    cc->html_out = cc->rvfiles(m,"index");
}

void url_admin_logininfo(const PTR_getter<chat_user> &__UU,app_connection *cc)
{
	LICENSE_CK(4);
	MUTEX_INSPECTOR;
	if (!__UU){ cc->html_out=cc->redirect();return;}
	DB_id cc_user_id=user$id(__UU);

	user_pair __U(__UU);


	if (cc->sub_level<am_admin){
		return;
	}
	DB_id zid;CONTAINER(zid)=0;CONTAINER(zid)=atoi(cc->params["id"]);

	if (CONTAINER(zid)==0){
		string login=cc->params["login"];
		zid=get_uid_by_login(login);
	}



	if (CONTAINER(zid)==0){
		cc->html_out+="<script>alert('"+_MSG("loginnotfound")+"');window.close();</script>\n";
		return;
	}
	PTR_getter<user_profile> __PZ=user$profiles.FindByID(CONTAINER(zid));
	if(!__PZ)
	{
		cc->html_out+="<script>alert('"+_MSG("loginnotfound")+"');window.close();</script>\n";
		logErr2("SUSPITIOUS ---- %s %d",__FILE__,__LINE__);
		return;
	}
	vector<string> v;
	st_dbh d;
	v=d.dbh->select_1_rowQ((QUERY)"select UNIX_TIMESTAMP(stat_last_date),stat_last_ip,stat_v_count,stat_m_count")
		time_t stat_last_date;
	string stat_last_ip;
	int stat_v_count;
	int stat_m_count;
	time_t stat_t_count;
	unsigned int kick_count;
	unsigned int kicked_count;
	LICENSE_CK(11);
	{
		MUTEX_INSPECTOR;
		PGLR(user_profile,u,__PZ);
		stat_last_date=u->stat_last_date;
		stat_last_ip=u->stat_last_ip;
		stat_v_count=u->stat_v_count;
		stat_m_count=u->stat_m_count;
		stat_t_count=u->stat_t_count;
		kick_count=u->kick_count;
		kicked_count=u->kicked_count;

	}
	DB_id poweshen;CONTAINER(poweshen)=0;
	{
		MUTEX_INSPECTOR;
		PGLR(user_profile, z,__PZ);
		poweshen=z->poweshen;
	}
	map<string,string> m;
	{
		MUTEX_INSPECTOR;
		PGLR(user_profile, z,__PZ);
		if (z->info!=""){
			map<string,string>q;
			m["~hr~"]=RVfiles(q,"admin/login_info_hr");
		}else{
			m["~hr~"]="";
		}
	}
	string oirc;
	make_user_info(zid,cc_user_id,true,"","",CONTAINER(cc_user_id)!=0,oirc);
	m["~userinfo~"]=owww;
	m["~lnick~"]=GET_CNICK_DBID(zid);
	{
		MUTEX_INSPECTOR;
		{
			PGLR(user_profile, z,__PZ);
			m["~vote_balls~"]=itostring(z->vote_balls);
			m["~level~"]=itostring(z->level);
			m["~credits~"]=get_f22(z->credit_summa.container);
			m["~login~"]=z->login;
			m["~id~"]=itostring(CONTAINER(zid));
			if (stat_t_count<3600){
				m["~msgperhour~"]="N/A";
			}else{
				m["~msgperhour~"]=itostring( stat_m_count / (stat_t_count/3600) );
			}
			m["~msgcount~"]=itostring(stat_m_count);
			m["~timecount~"]=make_time(stat_t_count);
			m["~viscount~"]=itostring(stat_v_count);
			m["~regdate~"]=datetime2rus(z->reg_date);
			m["~lastip~"]=stat_last_ip;
			m["~lastdate~"]=datetime2rus(stat_last_date);
			m["~kick~"]=itostring(kick_count);
			m["~kicked~"]=itostring(kicked_count);
			m["~invisibility~"]=itostring(z->bought_invisibility);
		}
		vector<string> n;
		{
			PGLR(nick_vec, z,nick_vecs.find_by_id_create(CONTAINER(zid)));
			for (map<unsigned int,user_nick> ::const_iterator i=z->u_nicks.begin();i!=z->u_nicks.end();i++){
				n.push_back(i->second.name);
			}
			if (cc->sub_level==am_sadmin){
				m["~nicks~"]=join(", ",n);
			}else{
				m["~nicks~"]=itostring(n.size())+" "+_MSG("count");
			}
		}
		if (CONTAINER(poweshen))
			m["~poweshen~"]=GET_CNICK_DBID(poweshen);
		else m["~poweshen~"]="VOTE";
	}
	cc->html_out+=cc->rvfiles(m,"admin/logininfo");
}
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

#include <algorithm>
#include "web_server_data.h"
#include "file_set.h"
#include "copy_file.h"

#include "channels.h"
#include "levels.h"
#include "server_config.h"

#include "chat_config.h"
#include "app_def.h"
#include "update_cmd.h"
#include "user_profile.h"
#include "app_con.h"
#include "web_tools.h"


#ifdef __WITH_LICENSE
#include "license.h"
#endif
#include "user_profile.h"
DB_id get_uid_by_nick(const string& nick);
DB_id get_uid_by_login(const string& );


void url_admin_levelup(const PTR_getter<chat_user>&__UU,app_connection*cc)
{
	LICENSE_CK(6);
	MUTEX_INSPECTOR;
	st_update stu;
	if (!__UU){ cc->html_out=cc->redirect();return;}

	DB_id cc_user_id=user$id(__UU);
	user_pair __U(__UU);

	int levelup_ability=__LEVELS(user$level(__U)).levelup_ability;
	if (levelup_ability==0) return;
	map<string,string> m;
	st_dbh d;
	LICENSE_CK(14);
	if (cc->params["nick"]=="" && cc->params["login"]==""){
		cc->html_out=cc->rvfiles(m,"admin/levelup/levelup_template");
		return;
	}
	m["~nick~"]=cc->params["nick"];
	m["~login~"]=cc->params["login"];
	m["~level~"]=itostring(cc->sub_level);

	if (cc->params["cmd"]=="change"){
		DB_id id;CONTAINER(id)=0;CONTAINER(id)=atoi(cc->params["id"]);
		unsigned int ul=0;
		{
			PGLR(user_profile, up,user$profiles.FindByID(CONTAINER(id)));
			if(up)
			{
				ul=up->level;
			}
		}

		if (levelup_ability>ul){
			unsigned int nl=atoi(cc->params["level"]);
			if (nl<=levelup_ability){
				logErr2("%s (%s) changed level for user %d, set to %d",GET_CNICK_DBID(id).c_str(),user$login(id).c_str(),CONTAINER(id),nl);
				{
					PGLW(user_profile,z,user$profiles.FindByID(CONTAINER(id)));
					z->level=__LEVELS(nl).id;
					__send_update_d3(user_profile$level$3,CONTAINER(id),z->level);
					z->poweshen=cc_user_id;
					__send_update_d3(user_profile$poweshen$3,CONTAINER(id),CONTAINER(cc_user_id));
					z->setting_n_color_pack=0;
					__send_update_d3(user_profile$setting_n_color_pack$3,CONTAINER(cc_user_id),0);
				}
			}
		}
	}
	DB_id zid;CONTAINER(zid)=0;CONTAINER(zid)=0;
	if (cc->params["nick"].size()){
		zid=get_uid_by_nick(cc->params["nick"]);
	}
	if (cc->params["login"].size()){
		zid=get_uid_by_login(cc->params["login"]);
	}

	string rows;
	if (CONTAINER(zid)!=0){
		map<string,string> q;
		q["~id~"]=itostring(CONTAINER(zid));
		unsigned int ul=0;
		string s;
		{
			PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(zid)));
			ul=u->level;
			s="<SELECT name=level"+itostring(CONTAINER(zid));
			if (levelup_ability<ul){
				s+=" DISABLED";
				q["~disabled~"]="DISABLED";
			}else{
				q["~disabled~"]="";
			}
			s+=">";
		}
		{
			PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(zid)));
			q["~login~"]=u->login;

		}
		map<unsigned int, c_level> lvl;
		lvl=LEVELS_GET();
		for (map<unsigned int,c_level>::const_iterator j=lvl.begin();j!=lvl.end();j++){
			if (j->first>levelup_ability) continue;

			s+="<option value="+itostring(j->first);
			if (j->first==ul) s+=" SELECTED";
			s+=">"+j->second.name(0)+"\r\n";
		}
		s+="</SELECT>";
		q["~level~"]=s;
		{
			PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(zid)));
			q["~mcount~"]=itostring(u->stat_m_count);
			q["~tcount~"]=make_time(u->stat_t_count);
		}
		rows+=RVfiles(q,"admin/levelup/levelup_row");
	}
	m["~users~"]=rows;
	cc->html_out=cc->rvfiles(m,"admin/levelup/levelup");
}

#ifdef _DEBUG
#define New DEBUG_NEW
#endif

#include "_mutex.h"
#include <list>
#include "mutex_inspector.h"
#include <time.h>
#include <map>
#include <hash_map>
#include "mysql_extens.h"
#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include "web_server.h"
#include "message.h"
#include "chat_def.h"

#include <algorithm>
#include "web_server_data.h"
#include "file_set.h"
#include "copy_file.h"

#include "channels.h"
#include "levels.h"
#include "server_config.h"

#include "chat_config.h"
#include "app_def.h"
#include "update_cmd.h"
#include "user_profile.h"
#include "app_con.h"
#include "chat_globals.h"

#ifdef __WITH_LICENSE
#include "license.h"
#endif
#include "web_tools.h"
void  fill_map_from_map(map<string,string>&m,map<string,string>&from);
void update_DB_from_reg_map(const DB_id& uid,map<string,string>&m, bool all);
string check_reg_map(map<string,string> &m, bool all);

string homedir(unsigned int uid);
void get_DB_to_map(const PTR_getter<user_profile> &__UP, map<string,string> &m) ;

void url_admin_accounts(const PTR_getter<chat_user>&__UU,app_connection *cc)
{
	LICENSE_CK(12);
	MUTEX_INSPECTOR;
	st_update stu;
	if (!__UU){ cc->html_out=cc->redirect();return;}
	user_pair __U(__UU);
	if (!user__privileges(__U,"$accounts")) return;

	map<string,string> m;
	st_dbh d;
	m["~error~"]="";
	m["~level~"]=itostring(cc->sub_level);
	LICENSE_CK(3);
	if (cc->params["id"].size()){
		DB_id __id;CONTAINER(__id)=0;CONTAINER(__id)=atoi(cc->params["id"]);
		const DB_id id(__id);
		PTR_getter<user_profile> P_uid_user_profile=user$profiles.FindByID(CONTAINER(id));
		if (!P_uid_user_profile)
		{
			map<string,string> K;
			cc->html_out=RVfiles(K,"admin/accounts/alert_rec_not_found");
			return;
		}

		vector<string>	 v=d.dbh->select_1_columnQ((QUERY)"select id from tbl_users where id=?"<<CONTAINER(id));
		{
			if (v.size()==0)
			{
				map<string,string> K;
				cc->html_out=RVfiles(K,"admin/accounts/alert_rec_not_found");
				return;
			}
			PGLR(user_profile,z,P_uid_user_profile);
			if (z->level/sub_levels>cc->sub_level){
				map<string,string> K;
				cc->html_out=RVfiles(K,"admin/accounts/alert_low_level");
				return;
			}

		}
		if (cc->params["DATA"]=="YES"){
			string e;
			if (cc->params["pass"].size()){
				if (cc->params["pass"]!=cc->params["pass2"]){e+=_MSG("passwordsmismatch");}
				if (cc->params["pass"].size()<3){e+=_MSG("passwordisshort");}

				if (e==""){
					{
						PGLW(user_profile, u,P_uid_user_profile);
						u->pass=bin2hex(MD5(cc->params["pass"]),0);
						__send_update_d3(user_profile$pass$3,CONTAINER(id),u->pass);
						m["~error~"]=_MSG("changed2");

					}
				}
			}
		}

		m["~pass~"]="";
		string login;
		{
			PGLW(user_profile, u,P_uid_user_profile);
			login=u->login;
		}
		m["~login~"]=login;
		cc->html_out=RVfiles(m,"admin/accounts/user");
		return;
	}

	if (cc->params["nick"]=="" && cc->params["login"]==""){
		cc->html_out=RVfiles(m,"admin/accounts/template");
		return;
	}
	m["~nick~"]=cc->params["nick"];
	m["~login~"]=cc->params["login"];
	vector<string>  v;

	if (cc->params["nick"].size()){
		st_dbh d;
		v=d.dbh->select_1_columnQ((QUERY)"select uid from nicks where str_nick like '?%'"<<str_nick(cc->params["nick"]));
	}
	if (cc->params["login"].size()){
		st_dbh d;
		v=d.dbh->select_1_columnQ((QUERY)"select id from tbl_users where login like '?%'"<<cc->params["login"]);
	}

	m["~cnt~"]=itostring(v.size());
	string rows;
	for (unsigned int i=0;i<v.size();i++){
		map<string,string> q;
		q["~id~"]=v[i];
		PTR_getter<user_profile> _P=user$profiles.FindByID(atoi(v[i]));
		if(_P){
			PGLR(user_profile,u,_P);
			q["~login~"]=u->login;
			rows+=RVfiles(q,"admin/accounts/row");
		}
	}
	m["~users~"]=rows;
	cc->html_out=RVfiles(m,"admin/accounts/index");
}


void url_admin_zags(const PTR_getter<chat_user> &__UU,app_connection *cc)
{
	LICENSE_CK(12);
	st_update stu;
	if (!__UU){ cc->html_out=cc->redirect();return;}
	user_pair __U(__UU);
	if (!user__privileges(__U,"$zags")){
		return;
	}
	map<string,string> m;
	DB_id zid;CONTAINER(zid)=0;CONTAINER(zid)=0;
	PTR_getter<user_profile> __ZUP(NULL);
	string e;
	m["~fs~"]="";
	m["~uid~"]="";
	m["~nick~"]="";
	m["~error~"]="";
	if (cc->params["todo"]=="search")
	{
		string n=cc->params["nick"];
		if (n.size())
		{
			zid=get_uid_by_nick(n);
			if (CONTAINER(zid))
			{
				if (e.size()==0)
				{
					e="found nick "+n;
				}

				m["~nick~"]=cc->params["nick"];
				m["~uid~"]=itostring(CONTAINER(zid));
				m["~error~"]=(string)"found nick "+=cc->params["nick"]+" uid="+ itostring(CONTAINER(zid));
				__ZUP=user$profiles.FindByID(CONTAINER(zid));
				if (!__ZUP)
				{
					cc->html_out="user not found";return;
				}
				if (__ZUP){
					PGLW(user_profile,u,__ZUP);
					m["~fs~"]=u->family_status;
				}
				cc->html_out=cc->rvfiles(m,"admin/zags/fs");
				return;
			}
		}
	}
	if (cc->params["todo"]=="update")
	{
		if (cc->params["uid"].size())
		{
			CONTAINER(zid)=atoi(cc->params["uid"]);
		}
		else throw cError("undef zid"+_DMI());

		PTR_getter<user_profile> __ZUP=user$profiles.FindByID(CONTAINER(zid));

		if (__ZUP)
		{
			PGLW(user_profile,u,__ZUP);
			u->family_status=cc->params["fs"];
			e="family status updated for nick "+cc->params["nick"];
			__send_update_d3(user_profile$family_status$3,CONTAINER(zid),u->family_status);
		}
		else
		{
			throw cError("err load __P %s %d %s",__FILE__,__LINE__,_DMI().c_str());
		}

		m["~nick~"]=cc->params["nick"];
		m["~uid~"]=itostring(CONTAINER(zid));
		m["~fs~"]==cc->params["fs"];
		m["~error~"]=e;
		cc->html_out=cc->rvfiles(m,"admin/zags/fs");
	}
	m["~error~"]=e;
	m["~fs~"]="";
	m["~nick~"]="";
	m["~uid~"]="";
	cc->html_out=cc->rvfiles(m,"admin/zags/fs");
	if (CONTAINER(zid))
	{
		string n;
		{
			PGLR(user_profile,u,__ZUP);
			m["~nick~"]=u->last_nick;
			n=u->last_nick;
		}
		if (cc->params["fs"].size())
		{
			PGLW(user_profile,u,__ZUP);
			u->family_status=cc->params["fs"];
			e="family status updated for nick "+n;
			__send_update_d3(user_profile$family_status$3,CONTAINER(zid),u->family_status);
		}
		{
			PGLR(user_profile,u,__ZUP);

			m["~fs~"]=u->family_status;
			m["~uid~"]=itostring(CONTAINER(zid));
		}
		if (e.size()==0)
		{
			e="found nick "+n;
		}
	}
	else m["~error~"]="not found";
	m["~error~"]=e;
	cc->html_out=cc->rvfiles(m,"admin/zags/fs");

}
