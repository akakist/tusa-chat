#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include <mysql/mysql.h>
#include "mysql_extens.h"
#include "cMYSQL.h"
#include "mysql_extens.h"
#include <time.h>
#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "cMYSQL.h"
#include "mysql_extens.h"
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
string str_nick(const string &n);

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
	vector<string>  v=dbh->select_1_column("select n.id from nicks n, tbl_users u where n.banned=0 and n.last_usage_date < '2012-01-01' and n.uid=u.id and u.level<1800 and u.last_nick_id<>n.id and u.id=26 ");
	for(int i=0;i<v.size();i++){
	    
	    vector<string> w;
	    for(int j=0;j<100 && i<v.size();j++,i++)
	    {
		if(atoi(v[i])>1000)
		    w.push_back(v[i]);
	    }
	    printf("delete from nicks where id in (%s);\n",join(",",w).c_str());
	}
		
	}catch(cError e){
		printf("Error: %s\n",e.error_string.c_str());
	}
	return 0;
}
