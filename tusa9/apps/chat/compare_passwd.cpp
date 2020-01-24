#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>

int main()
{
	try{
	MYSQL *_dbh=new MYSQL;
	mysql_init(_dbh);
	MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,"chat",0,NULL,0);
	if(!res)
	{
		printf("chat_sender: mysql_real_connect failed to %s\n","chat");
		exit(1);
	}
	cMYSQL *dbh=new cMYSQL(_dbh);
	dbh->connected=true;

	MYSQL *_dbh1=new MYSQL;
	mysql_init(_dbh1);
	MYSQL *res1=mysql_real_connect(_dbh1,NULL,NULL,NULL,"chat1",0,NULL,0);
	if(!res1)
	{
		printf("chat_sender: mysql_real_connect failed to %s\n","chat1");
		exit(1);
	}
	cMYSQL *dbh1=new cMYSQL(_dbh1);
	dbh1->connected=true;
	
	vector< vector<string> > v=dbh->exec("select id,pass from users order by id");
	vector< vector<string> > v1=dbh1->exec("select id,pass from users order by id");
	for(int i=0;i<v1.size();i++){
		string pass=v[i][1];
		string lpass=v1[i][1];
		string lmd5pass=bin2hex(MD5(lpass),0);
		if(pass!=lmd5pass){
			printf("mismatched for id=%s lpass=%s pass=%s lmd5pass=%s\n",v[i][0].c_str(),lpass.c_str(),pass.c_str(),lmd5pass.c_str());
//			dbh->real_query("update users set pass='"+lmd5pass+"' where id="+v[i][0]);
		}
//		dbh->real_query("update users set pass='"+bin2hex(MD5(v[i][1]),0)+"' where id="+v[i][0]);
	}
	}catch(cError e){
		printf("Error: %s\n",e.error_string.c_str());
	}
	return 0;
}