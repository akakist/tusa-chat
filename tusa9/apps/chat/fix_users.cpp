#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>

string str_nick(const string &n);

void load(cMYSQL *dbh,vector<string>&v, set<string>&s,const string& sql)
{
    v=dbh->select_1_column(sql);
	for(unsigned i=0;i<v.size();i++)
	{
	    s.insert(v[i]);
	}
    
}
int main(int argc,char *argv[])
{

	FILE *f=fopen("clear_users.log","a");
	
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
	
	vector<string> v_users,v_user_profiles,v_ustat;
	set<string> s_users,s_user_profiles,s_ustat;
	load(dbh,v_users,s_users,"select id from users");
	load(dbh,v_user_profiles,s_user_profiles,"select refid from user_profiles");
	load(dbh,v_ustat,s_ustat,"select refid from user_stats");
/*	vector<string> =dbh->select_1_column("select refid from user_profiles");
	set<string> ;
	for(unsigned i=0;i<v_user_profiles.size();i++)
	{
	    s_user_profiles.insert(v_user_profiles[i]);
	}
	*/
	for(unsigned i=0;i<v_user_profiles.size();i++)
	{
	    if(!s_users.count(v_user_profiles[i]))
	    {
		printf("delete from user_profiles where refid=%s;\n",v_user_profiles[i].c_str());
		s_user_profiles.erase(v_user_profiles[i]);
	    }
	}
	for(unsigned i=0;i<v_users.size();i++)
	{
	    if(!s_user_profiles.count(v_users[i]))
	    {
		printf("delete from users where refid=%s\n",v_users[i].c_str());
		s_users.erase(v_users[i]);
		
	    }
	}
	for(unsigned i=0;i<v_ustat.size();i++)
	{
	    if(!s_users.count(v_ustat[i]))
	    {
		printf("delete from user_stats where refid=%s\n",v_ustat[i].c_str());
		s_ustat.erase(v_ustat[i]);
		
	    }
	}
	/*
	
	
	vector<string> vv=dbh->select_1_column("select nick from nicks where nick like 'сергей%'");
	for(unsigned i=0;i<vv.size();i++)
	{
	    printf("%s\n",vv[i].c_str());
	}
	vector<vector<string> > v= dbh->execQ((QUERY)"select refid,login from user_profiles order by refid");
	for(unsigned i=0;i<v.size();i++)
	{
	    if(v[i].size()==2)
	    printf("update user_profiles set upperlogin='%s' where refid=%d;\n",str_nick(v[i][1]).c_str(),atoi(v[i][0]));
	}*/
	return 0;
}
