#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>
#include "copy_file.h"
#include "oscar_buffer.h"

string str_nick(const string &n);

struct user_status
{
	string name;
	int pic;
	int id;
	bool disable_invite;
	bool uniq;
};

class user_nick
{
public:
    string name;
    unsigned int id;
	user_nick();
	

	user_nick(const string &n,unsigned int i);
};
int operator < (const user_nick& a, const user_nick& b);

class user_state
{

	public:
	
	enum
	{
		UNDEF=0xffff0000
	};
		unsigned int channel;
		user_status status;
		user_nick nick;

		user_state():nick("undef",UNDEF){channel=UNDEF;status.id=UNDEF;nick.id=UNDEF;}
};


/*oscar_buffer & operator<<(oscar_buffer&b, const user_nick &n)
{//MUTEX_INSPECTOR;
	b<<DWORD_LE(n.id)<<oscar_buffer::L_STR(n.name);
	return b;
}*/
oscar_buffer & operator<<(oscar_buffer&b, const user_nick &n)
{//MUTEX_INSPECTOR;
	b<<DWORD_LE(n.id)<<oscar_buffer::L_STR(n.name);
	return b;
}
oscar_buffer & operator<<(oscar_buffer&b, const user_status &n)
{//MUTEX_INSPECTOR;
	b<<oscar_buffer::L_STR(n.name)<<DWORD_LE(n.pic)<<DWORD_LE(n.id)<<__BYTE(n.disable_invite)<<__BYTE(n.uniq);
	return b;
}
oscar_buffer & operator>>(oscar_buffer&b, user_nick &n)
{//MUTEX_INSPECTOR;
	DWORD_LE id;
	oscar_buffer::L_STR ni;
	b>>id>>ni;
	n.id=id.obj;
	n.name=ni.container;
	return b;
}

oscar_buffer & operator>>(oscar_buffer&b, user_status &n)
{//MUTEX_INSPECTOR;
	oscar_buffer::L_STR name;
	DWORD_LE pic,id;
	__BYTE di,uniq;
	b>>name>>pic>>id>>di>>uniq;
	n.name=name.container;
	n.pic=pic.obj;
	n.id=id.obj;
	n.disable_invite=di.obj;
	n.uniq=uniq.obj;

	return b;
}

/*
oscar_buffer & operator<<(oscar_buffer&b, const string& n)
{//MUTEX_INSPECTOR;
	b<<oscar_buffer::L_STR(n);
	return b;
}
oscar_buffer & operator>>(oscar_buffer&b, string& n)
{//MUTEX_INSPECTOR;
	oscar_buffer::L_STR s;
	b>>s;
	n=s.container;
	return b;
}
*/
oscar_buffer & operator<<(oscar_buffer&b, const user_state& n)
{//MUTEX_INSPECTOR;
	b<<DWORD_LE(n.channel)<<n.status<<n.nick/*<<__BYTE(n.contact_mode)*/;
	return b;
}
oscar_buffer & operator>>(oscar_buffer&b, user_state& n)
{//MUTEX_INSPECTOR;
	DWORD_LE c;
	b>>c;
	n.channel=c.obj;
	b>>n.status>>n.nick;
	return b;
}


string cache_dir(const string & name, unsigned int uid)
{
/*    if(uid<UNREG_BASE)
    {
        logErr2("if(is_unreg_id(uid)) %s",_DMI().c_str());
        throw cError("if(is_unreg_id(uid)) "+_DMI());
    }*/

    char pn[300];
    pn[0]=0;
    string sid=itostring(uid);
    if(uid<100)
    {//MUTEX_INSPECTOR;
        snprintf(pn,sizeof(pn)-1,"%s/%s/0/%02d","/var/chat",name.c_str(),uid);
    }
    else if(uid<10000)
    {//MUTEX_INSPECTOR;
        snprintf(pn,sizeof(pn)-1,"%s/%s/1/%02d/%02d","/var/chat",name.c_str(),uid/100,uid%100);
    }
    else if(uid<1000000)
    {//MUTEX_INSPECTOR;
        int u1=uid/10000;
        int u2=(uid-(u1*10000))/100;
        int u3=uid%100;
        snprintf(pn,sizeof(pn)-1,"%s/%s/2/%02d/%02d/%02d","/var/chat",name.c_str(),u1,u2,u3);
    }
    else if(uid<100000000)
    {//MUTEX_INSPECTOR;
        int u1=uid/1000000;
        int u2=(uid-(u1*1000000))/10000;
        int u3=(uid-(u1*10000))/100;
        int u4=uid%100;
        snprintf(pn,sizeof(pn)-1,"%s/%s/3/%02d/%02d/%02d/%02d","/var/chat",name.c_str(),u1,u2,u3,u4);
    }
    else{
        logErr2("cache_dir id >= UNREG_BASE ");
        throw cError("cache_dir id >= UNREG_BASE");
    }
    return pn;

}
string old_foto_pn(unsigned int pid, const string& ext)
{//MUTEX_INSPECTOR;
	string pn=cache_dir("fotos",pid)+"."+ext;
	return pn;
}					

string new_foto_pn(int uid,unsigned int pid, const string& ext)
{//MUTEX_INSPECTOR;
    string pn=cache_dir("user",uid)+"/photos/"+itostring(pid)+"."+ext;
    return pn;
}
		                                                                                       

user_nick::user_nick(const string &n,unsigned int i)
{
    name=n;
    id=i;
}
user_nick::user_nick()
{
    name="";
    id=user_state::UNDEF;
}

#define setting_autologin		2
#define setting_autochange		4
#define setting_show_eye		8
#define setting_show_hints		16
#define setting_show_stat		32
#define setting_invite_sound	64
#define setting_full_buttons	128

int main(int argc,char *argv[])
{

//	FILE *f=fopen("clear_users.log","a");
	
	MYSQL *_dbh=new MYSQL;
	mysql_init(_dbh);
	MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,"chat",0,NULL,0);
	if(!res)
	{
		logErr("chat_sender: mysql_real_connect failed to %s","chat");
		exit(1);
	}
	cMYSQL *dbh=new cMYSQL(_dbh);


	dbh->connected=true;
	
	vector<vector<string> > v=dbh->exec("select refid,settings from user_sets");
    printf("/*!40000 ALTER TABLE `user_sets` DISABLE KEYS */;\n");
    for(unsigned i=0;i<v.size();i++)
    {
	if(v[i].size()==2)
	{
//	    if(!v[i][1].size()) continue;
	    unsigned int s=atoi(v[i][1]);
	    if(s&setting_autologin) printf("update user_sets set setting_autologin='1' where refid=%d;\n",atoi(v[i][0]));
	    if(s&setting_autochange) printf("update user_sets set setting_autochange='1' where refid=%d;\n",atoi(v[i][0]));
	    if(s&setting_show_eye) printf("update user_sets set setting_show_eye='1' where refid=%d;\n",atoi(v[i][0]));
	    if(s&setting_show_hints) printf("update user_sets set setting_show_hints='1' where refid=%d;\n",atoi(v[i][0]));
	    if(s&setting_show_stat) printf("update user_sets set setting_show_stat='1' where refid=%d;\n",atoi(v[i][0]));
	    if(s&setting_invite_sound) printf("update user_sets set setting_invite_sound='1' where refid=%d;\n",atoi(v[i][0]));
	    if(s&setting_full_buttons) printf("update user_sets set setting_full_buttons='1' where refid=%d;\n",atoi(v[i][0]));


/*	    oscar_buffer b((unsigned char*)v[i][1].data(),v[i][1].size());
	    user_state st;
	    b>>st;
	    printf("update user_sets set last_nick_id=%d where refid=%d;\n",st.nick.id,atoi(v[i][0]));
	    printf("update user_sets set last_nick='%s' where refid=%d;\n",st.nick.name.c_str(),atoi(v[i][0]));*/
/*	    map<unsigned int,user_status> m;
//	    set<unsigned int> s;
	    b>>m;
	    for(typeof(m.begin())j=m.begin();j!=m.end();j++)
	    {
		if(j->first==0) continue;
		if(j->first==1) continue;
		if(j->first==2) continue;
		if(j->first==3) continue;
		if(j->first==4) continue;
		if(j->first==5) continue;
		if(j->first==6) continue;
		if(j->first==7) continue;
		if(j->first==8) continue;
//		if(j->first!=0 && j->first!=1 && j->first!=2 && j->first!=3 && j->first!=4 && j->first!=5 && j->first!=6 && j->first!=7  && j->first!=8  )
		
		printf("insert into user_status (id,uid, name,pic,disable_invite,uniq) values('%d','%d','%s','%d','%d','%d');\n",
		    j->first, atoi(v[i][0]), j->second.name.c_str(),j->second.pic,j->second.disable_invite,j->second.uniq);
	    }
	    */
//	    printf("update user_profile set gender='%s' where refid=%s;\n",v[i][1].c_str(),v[i][0].c_str());
//	    string oldpath=old_foto_pn(atoi(v[i][0]),v[i][2]);
//	    string newpath=new_foto_pn(atoi(v[i][1]),atoi(v[i][0]),v[i][2]);
//	    check_path_wfn( newpath);
//	    printf("ln  %s %s\n",oldpath.c_str(),newpath.c_str());
//	    printf("update nicks set ready_to_sale='1' where id=%s; # %s (%s)\n",v[i][0].c_str(),v[i][1].c_str(),v[i][2].c_str());
	}
    }
    printf("/*!40000 ALTER TABLE `user_sets` ENABLE KEYS */;\n");
    
	
	return 0;
}
