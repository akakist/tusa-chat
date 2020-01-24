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
	vector< vector<string> > v=dbh->exec("select id,parent,file_name,file_path,size,msg,subj from notes where attach=1 and file_owner=1");
	for(int i=0;i<v.size();i++){
		if(v[i].size()!=7) throw cError("select failed.");
		unsigned int sz=atoi(v[i][4]);
		sz-=v[i][5].size();
		sz-=v[i][6].size();
		dbh->real_queryQ((QUERY)"update notes set attach=1,file_name='?',file_path='?',file_size=? where id=?"<<v[i][2]<<v[i][3]<<sz<<v[i][1]);
		dbh->real_queryQ((QUERY)"update notes set file_size=? where id=?"<<sz<<v[i][0]);
	}
		
	}catch(cError e){
		printf("Error: %s\n",e.error_string.c_str());
	}
	return 0;
}
