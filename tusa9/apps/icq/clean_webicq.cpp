#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>

int app_main(int argc, char **argv)
//int main()
{
	MYSQL *_dbh=new MYSQL;
	mysql_init(_dbh);
	MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,"icq",0,NULL,0);
	if(!res)
	{
		logErr("chat_sender: mysql_real_connect failed to %s","chat");
		exit(1);
	}
	cMYSQL *dbh=new cMYSQL(_dbh);
	dbh->connected=true;
	

	vector<vector<string> > v=dbh->exec("select uin,parent_uin from list");
	set<string> uins;
	for(unsigned i=0;i<v.size();i++)
	{
		if(v[i].size()==2)
		{
			uins.insert(v[i][0]);
			uins.insert(v[i][1]);
		}
	}
	for(set<string>::iterator j=uins.begin();j!=uins.end();j++)
	{
		printf("%s\n",j->c_str());
	}
	QUERY q=(QUERY)"delete from wp_info where uin not in (?)" <<join(",",uins);
	printf("kall\n");
	dbh->execQ(q);
	printf("kall2\n");
	
/*	vector< vector<string> > v;
	try{
	v=dbh->exec("select a.id,a.vote_balls,b.id,b.yes from users a,grant_agrees b where a.vote_balls>0 and b.uid=a.id");
	for(int i=0;i<v.size();i++){
		if(v[i].size()!=4) throw cError("select failed");
		if(v[i][3]!="0"){
		    printf("recalced %s grant_agrees record ownered by %s set to %s.\n",v[i][2].c_str(),v[i][0].c_str(),v[i][1].c_str());
		    dbh->real_query("update grant_agrees set yes="+v[i][1]+" where id="+v[i][2]);
		}else{
		    dbh->real_query("update grant_agrees set no="+v[i][1]+" where id="+v[i][2]);
		}
	}*/
/*	}catch(cError e){
		printf("error: %s\n",e.error_string.c_str());
	}*/
	return 0;
}