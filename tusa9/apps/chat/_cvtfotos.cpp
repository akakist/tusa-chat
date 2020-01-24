#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>
#include "copy_file.h"

string str_nick(const string &n);

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
	
	vector<vector<string> > v=dbh->exec("select id,uid, ext from photos");
    for(unsigned i=0;i<v.size();i++)
    {
	if(v[i].size()==3)
	{
	    string oldpath=old_foto_pn(atoi(v[i][0]),v[i][2]);
	    string newpath=new_foto_pn(atoi(v[i][1]),atoi(v[i][0]),v[i][2]);
	    check_path_wfn( newpath);
	    printf("ln  %s %s\n",oldpath.c_str(),newpath.c_str());
//	    printf("update nicks set ready_to_sale='1' where id=%s; # %s (%s)\n",v[i][0].c_str(),v[i][1].c_str(),v[i][2].c_str());
	}
    }
    
	
	return 0;
}
