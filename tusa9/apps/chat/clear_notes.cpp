#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>
#include <deque>
deque<string>nn;
int main(int argc,char *argv[])
{
	try{
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
	while(1)
	{
		vector<vector<string> > v=dbh->exec("select notes.id,notes.file_path from notes,users where notes.uid=users.id and notes.sent_date<'2003-06-01' and users.accessmode<40 limit 1000");
		if(!v.size())break;
		vector<string> vr;
		vector<string> vu;
		for(unsigned i=0;i<v.size();i++)
		{
			if(v[i].size()==2)
			{
				vr.push_back(v[i][0]);
				if(v[i][1].size()) vu.push_back(v[i][1]);
			}
		}
		QUERY q;
		q<<"delete from notes where id in (?)"<<join(",",vr);
		printf("%s\n",q.prepare().c_str());
		dbh->real_queryQ((QUERY)"delete from notes where id in (?)"<<join(",",vr));
		for(unsigned i=0;i<vu.size();i++)
		{
			printf("rm /var/chat/notes/%s\n",vu[i].c_str());
			unlink(vu[i].c_str());
		}
		printf("Iterate finished\n");
	}
//	v.insert(v.begin(),v.end());
/*		dbh->real_queryQ((QUERY)"insert into notes_folders (uid,name,cant_remove) values (?,'Входящие',1)"<<v[i]);
		string lid=dbh->select_1("select LAST_INSERT_ID() from notes_folders");
		dbh->real_queryQ((QUERY)"insert into notes_folders (uid,name,cant_remove) values (?,'Отправленные',1)"<<v[i]);
		string lid2=dbh->select_1("select LAST_INSERT_ID() from notes_folders");
		dbh->real_queryQ((QUERY)"insert into notes_filters (uid,fid,to_folder) values (?,0,?)"<<v[i]<<lid);
		dbh->real_queryQ((QUERY)"update notes set folder=? where folder=1 and uid=?"<<lid<<v[i]);
		dbh->real_queryQ((QUERY)"update notes set folder=? where folder=2 and uid=?"<<lid2<<v[i]);
		dbh->real_queryQ((QUERY)"insert into notes (uid,folder,temporary) values (?,?,1)"<<v[i]<<lid);
		dbh->real_queryQ((QUERY)"insert into notes (uid,folder,temporary) values (?,?,1)"<<v[i]<<lid2);
		dbh->real_queryQ((QUERY)"update user_settings set notes_save_copy=1,notes_sent_folder=? where uid=?"<<lid2<<v[i]);
		*/


//		if(i==0) printf("\n\n");
//		if((i%10)==0) printf("updated %d users\r");
//	}
	}catch(cError e){
		printf("Error: %s\n",e.error_string.c_str());
	}
	return 0;
}
