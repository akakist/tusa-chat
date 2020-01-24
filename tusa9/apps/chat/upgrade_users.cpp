#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>
#include <deque>
#include "copy_file.h"
#include <sys/stat.h>
deque<string>nn;


int main(int argc,char *argv[])
{
    try{
        MYSQL *_dbh=new MYSQL;
        mysql_init(_dbh);
        MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,"chat_test",0,NULL,0);
        if(!res)
        {
            logErr("chat_sender: mysql_real_connect failed to %s","chat");
            exit(1);
        }
        cMYSQL *dbh=new cMYSQL(_dbh);
        dbh->connected=true;
try{
		dbh->real_query("drop table user_stats");
}	catch(...)	{}
		string s="create table user_stats (  
		refid int(20) unsigned NOT NULL auto_increment,
	LastDate datetime default NULL,
	LastIP text,  VisCount int(15) default NULL,
  messagecount int(10) NOT NULL default '0',
  timecount int(10) NOT NULL default '0',  kick int(10) unsigned NOT NULL default '0',
  kicked int(10) unsigned NOT NULL default '0',PRIMARY KEY  (refid),
)";
	dbh->real_query(s);

        vector<vector<string> > v=dbh->exec("select id,LastDate,LastIP,VisCount,messagecount,timecount,kick,kicked from users");

        printf("selected %d users\n",v.size());
		
        for(int i=0;i<v.size();i++){
			if(v[i].size()!=8) {continue;}
            unsigned int uid=atoi(v[i][0].c_str());
			printf("%d\n",uid);
			dbh->real_queryQ((QUERY)"insert into user_stats (refid,LastDate,LastIP,VisCount,messagecount,timecount,kick,kicked) values ('?','?','?','?','?','?','?','?')"
			<<v[i][0]
			<<v[i][1]
			<<v[i][2]
			<<v[i][3]
			<<v[i][4]
			<<v[i][5]
			<<v[i][6]
			<<v[i][7]
			);
        }
    }catch(cError e){
        printf("Error: %s\n",e.error_string.c_str());
    }
    return 0;
}
