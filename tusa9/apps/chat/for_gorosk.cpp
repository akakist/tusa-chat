#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include "utils.h"
#include <time.h>

void main()
{
	MYSQL *_dbh=new MYSQL;
	mysql_init(_dbh);
	MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,DB_NAME,0,NULL,0);
	if(!res)
	{
		logErr("chat_sender: mysql_real_connect failed to %s",DB_NAME);
		exit(1);
	}
	cMYSQL *dbh=new cMYSQL(_dbh);
	dbh->connected=true;
	int year=2001;
	int day=1;
	int month=1;
	int znak=0;
	printf("wwedi znak:");
	scanf("%d",&znak);
	struct tm *ts;
	time_t tt=time(NULL);
	ts=localtime(&tt);
	ts->tm_mon=0;
	ts->tm_mday=1;
	time_t t=mktime(ts);
	for(int c=0;c<368;c++){
		struct tm *q;
		q=localtime(&t);
//		q->tm_mon+=1;
//		q->tm_year+=1970;
		printf("Goroskop for znak %d, day %s",znak,CTIME(&t));
		int e;
		scanf("%d",&e);
		if(e>=10){
			c--;
			continue;
		}
		try{
		dbh->real_query("insert into goroskop (year,month,day,day_descr,day_text,znak)"
				" values("+itostring(q->tm_year+1900)+","+itostring(q->tm_mon+1)+","+itostring(q->tm_mday)+","+itostring(e)+",'',"+itostring(znak)+")");
		}catch(cError e){
			printf("error: %s",e.error_string.c_str());
			exit(0);
		}
		t+=86400;
	}
	
/*	vector< vector<string> > v=dbh->exec("select id,uppernick from nicks");
	for(int i=0;i<v.size();i++){
		dbh->real_query("update nicks set uppernick='"+MES(str_nick(v[i][1]))+"' where id="+v[i][0]);
		printf("%s -> %s\n",v[i][1].c_str(),str_nick(v[i][1]).c_str());
	}
	
  uid int(20) unsigned DEFAULT '0' NOT NULL,
  greeting int(20),
  bye int(20),
  voting int(20),
  anick int(20),
  cstatus int(20),
  channel int(20),
  autologin int(20),
  autochange int(11) DEFAULT '1',
  hints char(1) DEFAULT '1' NOT NULL,
  stat char(1) DEFAULT '1' NOT NULL,
  refresh_users char(1) DEFAULT '1' NOT NULL,
	
//	vector<string> v=dbh->select_1_column("select id from users");
	vector<string> v=dbh->select_1_column("select uid from user_settings");
	for(int i=0;i<v.size();i++){
//		vector<string> q=dbh->select_1_row("select id from user_settings where uid="+v[i]);
		vector<string> q=dbh->select_1_row("select id from users where id="+v[i]);
		if(q.size()==0){
//			printf("not found in user_settings record for %s\n",v[i].c_str());
			printf("delete from user_settings where uid=%s\n",v[i].c_str());
//			printf("INSERT INTO user_settings (uid,greeting,bye,voting,anick,cstatus,channel,autologin,autochange,hints,stat,refresh_users) VALUES (%s,-1,-1,0,0,0,0,0,1,'1','1','1');\n",v[i].c_str());
			continue;
		}
		if(q.size()>1){
			printf("too many settings for id: %s this id is %s",v[i].c_str(),join("",q).c_str());
		}
	}*/
}