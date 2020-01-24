#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
	

	try{
	MYSQL *_dbh=new MYSQL;
	mysql_init(_dbh);
	MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,"chat",0,NULL,0);
	if(!res)
	{
		logErr("chat: mysql_real_connect failed to %s","chat");
		exit(1);
	}
	cMYSQL *dbh=new cMYSQL(_dbh);
	dbh->connected=true;
	
//	time_t t=time(NULL)-345600;	//older 4 days
	int u_cnt=0;
	int n_cnt=0;
	int p_cnt=0;
	vector<string> v=dbh->select_1_column("select id from users order by id");
	for(int i=0;i<v.size();i++){
		int a=atoi(dbh->select_1("select sum(size) from notes where uid="+v[i]));
		a+=atoi(dbh->select_1("select sum(size) from photos where uid="+v[i]));
		printf("updated for %s set to %d\n",v[i].c_str(),a);
		dbh->real_queryQ((QUERY)"update users set used_space=? where id=?"<<a<<v[i]);
	}
		
	}catch(cError e){
		printf("Error: %s\n",e.error_string.c_str());
	}
	return 0;
}