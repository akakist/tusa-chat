#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include <mysql/mysql.h>
#include "mysql_extens.h"
#include "cMYSQL.h"
#include "mysql_extens.h"
#include <time.h>

string str_nick(const string &n);


int main(int argc,char *argv[])
{

//	FILE *f=fopen("clear_users.log","a");
	
	MYSQL *_dbh=new MYSQL;
	mysql_init(_dbh);
	MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,"geoip",0,NULL,0);
	if(!res)
	{
		logErr("chat_sender: mysql_real_connect failed to %s","chat");
		exit(1);
	}
	cMYSQL *dbh=new cMYSQL(_dbh);
	dbh->connected=true;
	char s[10000];
	while(gets(s))
	{
	    vector<string> v=splitTOK(".",s);
	    if(v.size()==4)
	    {
		unsigned int ip=16777216*atoi(v[0]);
		ip+=65536*atoi(v[1]);
		ip+=256*atoi(v[2]);
		ip+=atoi(v[3]);
		char sss[200];
		snprintf(sss,sizeof(sss),"select locId from ip where startIpNum<=%u and endIpNum>=%u",ip,ip);
		printf("%s\n",sss);
		string loc=dbh->select_1(sss);
		logErr2("loc %s",loc.c_str());
	    }
	}


    
	
	return 0;
}
