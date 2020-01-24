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
	MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,"chat1",0,NULL,0);
	if(!res)
	{
		logErr("chat_sender: mysql_real_connect failed to %s","chat");
		exit(1);
	}
	cMYSQL *dbh=new cMYSQL(_dbh);
	dbh->connected=true;
	
	time_t t=time(NULL)-345600;	//older 4 days
	int u_cnt=0;
	int n_cnt=0;
	int p_cnt=0;
	vector< vector<string> > v=dbh->exec("select id,pass from users");
	for(int i=0;i<v.size();i++){
		dbh->real_query("update users set pass='"+bin2hex(MD5(v[i][1]),0)+"' where id="+v[i][0]);
	}
	}catch(cError e){
		printf("Error: %s\n",e.error_string.c_str());
	}
	return 0;
}
