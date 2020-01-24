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
	vector< vector<string> > v=dbh->exec("select id,uid,filename from photos order by id");
	for(int i=0;i<v.size();i++){
		string fn="./photos/"+v[i][2];
		struct stat st;
		if (stat(fn.c_str(), &st) == -1) {
			logErr("--Error: Failed to read file %s", fn.c_str());
		}
//		dbh->real_query("update photos set size="+itostring(st.st_size)+" where id="+v[i][0]);
		printf("update photos set size=%d where id=%s;\n",st.st_size,v[i][0].c_str());
	}
		
	}catch(cError e){
		printf("Error: %s\n",e.error_string.c_str());
	}
	return 0;
}