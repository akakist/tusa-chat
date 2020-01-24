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

	dbh->real_query("SET CHARSET cp1251");



	dbh->connected=true;

//	vector<>

	vector<string> vUP=dbh->select_1_column("select refid from user_profiles");
	vector<string> vUS=dbh->select_1_column("select refid from user_stats");
	set<unsigned int> sUP;
	set<unsigned int> sUS;
	for(unsigned i=0;i<vUP.size();i++)
	{
	    sUP.insert(atoi(vUP[i]));
	}
	for(unsigned i=0;i<vUS.size();i++)
	{
	    sUS.insert(atoi(vUS[i]));
	}
    FILE *f=fopen("log","wb");
/*	vector<vector<string> > vn=dbh->exec("select id,uid,nick from nicks where banned='0'");
	for(unsigned i=0;i<vn.size();i++)
	{
	    if(vn[i].size()==3)
	    {
		unsigned int uid=atoi(vn[i][1]);
		if(!sUP.count(uid) || !sUS.count(uid) )
		{
		    
		    printf("update nicks set ready_to_sale='1', cost=20 where id=%s and uid=%s; # %s\n",vn[i][0].c_str(),vn[i][1].c_str(),vn[i][2].c_str());
		    fprintf(f,"%s\n",vn[i][2].c_str());
		
		}
	    }
	}
*/	
	// (UNIX_TIMESTAMP(b.last_date)+24*60*60*100)<UNIX_TIMESTAMP(NOW())
	vector<vector<string> > v=dbh->exec("select a.id,a.uid, a.nick, c.login \
    from nicks a, user_stats b, user_profiles c, user_sets s where \
    a.uid=b.refid and b.last_date<'2008-08-01'\
    and s.level<500\
    and c.refid=a.uid \
    and c.refid=s.refid \
    and a.banned=0\
    and a.ready_to_sale='0'\
    order by a.id\
 ");
    for(unsigned i=0;i<v.size();i++)
    {
	if(v[i].size()==4)
	{
	    if(atoi(v[i][1])>1000)
	    {
	    printf("update nicks set ready_to_sale='1', cost=200 where id=%s and uid=%s; # %s (%s)\n",v[i][0].c_str(),v[i][1].c_str(),v[i][2].c_str(),v[i][3].c_str());
	    fprintf(f,"%s\n",v[i][2].c_str());
	    }
	}
	
    }
    fclose(f);
    
	
	return 0;
}
