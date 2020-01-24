#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>

string str_nick(const string &n);


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
	}
	return 0;
}
