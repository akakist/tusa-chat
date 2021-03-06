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

/*oscar_buffer & operator<<(oscar_buffer&b, const user_nick &n)
{//MUTEX_INSPECTOR;
	b<<DWORD_LE(n.id)<<oscar_buffer::L_STR(n.name);
	return b;
}*/
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

oscar_buffer & operator<<(oscar_buffer&b, const user_status &n)
{//MUTEX_INSPECTOR;
	b<<oscar_buffer::L_STR(n.name)<<DWORD_LE(n.pic)<<DWORD_LE(n.id)<<__BYTE(n.disable_invite)<<__BYTE(n.uniq);
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
	
//	vector<vector<string> > v=dbh->exec("select count(*),cuid from contact,user_profiles where user_profiles.refid=contact.uid and user_profiles.level>499 group by cuid order by 1 desc limit 100");
	vector<vector<string> > v=dbh->exec("select count(*),cuid from contact,\
    user_profiles \
    where user_profiles.refid=contact.uid \
    and user_profiles.level>399 and user_profiles.level<499  group by cuid order by 1 desc limit 100");
	
//    printf("/*!40000 ALTER TABLE `user_status` DISABLE KEYS */;\n");
    for(unsigned i=0;i<v.size();i++)
    {
	if(v[i].size()==2)
	{
	    
	    string nick=dbh->select_1Q((QUERY)"select last_nick from user_sets where refid=?"<<v[i][1]);
	    printf("%d %s (%s)\n",i+1,nick.c_str(),v[i][0].c_str());
//	    printf("update user_profile set gender='%s' where refid=%s;\n",v[i][1].c_str(),v[i][0].c_str());
//	    string oldpath=old_foto_pn(atoi(v[i][0]),v[i][2]);
//	    string newpath=new_foto_pn(atoi(v[i][1]),atoi(v[i][0]),v[i][2]);
//	    check_path_wfn( newpath);
//	    printf("ln  %s %s\n",oldpath.c_str(),newpath.c_str());
//	    printf("update nicks set ready_to_sale='1' where id=%s; # %s (%s)\n",v[i][0].c_str(),v[i][1].c_str(),v[i][2].c_str());
	}
    }
//    printf("/*!40000 ALTER TABLE `user_status` ENABLE KEYS */;\n");
    
	
	return 0;
}
