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
	MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,"chat",0,NULL,0);
	if(!res)
	{
		logErr("chat_sender: mysql_real_connect failed to %s","chat");
		exit(1);
	}
	cMYSQL *dbh=new cMYSQL(_dbh);


	dbh->connected=true;
	string dt="2007-05-04 12:00:00";
	set<string> sv=splitTOKs(" ","  237150  263427  263971   285719  295703   289571   274696 ");
//	int init_uid=285834;
//	set<string> sv;
//	sv.insert(itostring(init_uid));
	while(1)
	{
	    vector<string> v=dbh->select_1_columnQ((QUERY)"select to_uid from credit_log where from_uid in (?) and opcode='manual_transfer' and summa>5000 and dt>'?'"<<join(",",sv)<<dt);
	    printf("%s\n",join(",",v).c_str());
	    int fc=sv.size();
	    for(unsigned i=0;i<v.size();i++)
	    if(atoi(v[i])!=26 && atoi(v[i])!=60792)
	     sv.insert(v[i]);
	    if(fc==sv.size()) break;
	}
	    printf("res: %s\n",join(",",sv).c_str());
	
	return 0;
}
