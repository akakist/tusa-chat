#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>

int main()
{
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
	
	time_t t=time(NULL)-345600;	//older 4 days
	vector<string> v=dbh->select_1_column("select id from grant_vote where status!=0 and add_date<='"+date2mysql(t)+"'");
	for(int i=0;i<v.size();i++){
	    dbh->real_query("delete from grant_agrees where gid="+v[i]);
	    dbh->real_query("delete from grant_messages where gid="+v[i]);
	    dbh->real_query("delete from grant_vote where id="+v[i]);
	    dbh->real_query("delete from grant_readden where gid="+v[i]);
	    printf("removed vote id=%s\n",v[i].c_str());
	}
	return 0;
}