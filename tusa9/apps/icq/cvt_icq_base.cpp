#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>
#include <set>
int main()
{
try{
	MYSQL *_dbh=new MYSQL;
	mysql_init(_dbh);
	MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,"icq",0,NULL,0);
	if(!res)
	{
		printf("chat_sender: mysql_real_connect failed to\n");
		exit(1);
	}
	cMYSQL *dbh=new cMYSQL(_dbh);
	dbh->connected=true;
	
	vector<vector<string> > v=dbh->execQ((QUERY)"select uin,parent_uin from icq_contact_items");
	vector<vector<string> > v1=dbh->execQ((QUERY)"select uin,parent_uin from contact_list");
	set<pair<string,string> > contacts;
	set<pair<string,string> > exist_contacts;
	for(unsigned i=0;i<v.size();i++)
	{
	printf("kall\n");
		contacts.insert(pair<string,string>(v[i][0],v[i][1]));
		
	}
	for(unsigned i=0;i<v1.size();i++)
	{
		exist_contacts.insert(pair<string,string>(v[i][0],v[i][1]));
	}
	printf("all\n");
	for(set<pair<string,string> >::iterator i=contacts.begin();i!=contacts.end();i++)
	{
	printf("all1\n");
	
		if(exist_contacts.find(*i)==exist_contacts.end())
		{
			dbh->real_queryQ((QUERY)"insert into contact_list (uin,parent_uin,added) values(?,?,'3')"<<i->first<<i->second);
			printf("inserted %s %s\n",i->first.c_str(),i->second.c_str());
		}
	}
}
catch(cError e)	
{
	printf("\n%s\n",e.error_string.c_str());
}
}