#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>
#include <deque>
#include "copy_file.h"
#include <sys/stat.h>

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

        vector<vector<string> > vfold=dbh->execQ((QUERY)"select id,uid from note_folders");
        map<int,int> mfold;
	map<int,vector<string> > u_flds;
        for(unsigned i=0;i<vfold.size();i++)
        {
            if(vfold[i].size()==2)
            {
                mfold[atoi(vfold[i][0])]=atoi(vfold[i][1]);
		u_flds[atoi(vfold[i][1])].push_back(vfold[i][0]);
            }
        }
        vector<vector<string> > vfc=dbh->execQ((QUERY)"select folder_id,message_id from folder_contents");
        map<int,vector<string> > uid_msgs;

	map<int,set<int> > msg2fld;
        for(unsigned i=0;i<vfc.size();i++)
        {
            if(vfc[i].size()==2)
            {
                int f=atoi(vfc[i][0]);
                int m=atoi(vfc[i][1]);
		msg2fld[m].insert(f);
            }

        }
	for(typeof(msg2fld.begin())i=msg2fld.begin();i!=msg2fld.end();i++)
	{
	    printf("#msg %d flds %d\n",i->first,i->second.size());
	    if(i->second.size()==1)
	    {
		if(mfold.count(*i->second.begin()))
		{
		printf("update notes set owner_folder=%d, owner_uid=%d where id=%d;\n",*i->second.begin(),mfold[*i->second.begin()],i->first);
		printf("update note_texts set owner_uid=%d where message_id=%d;\n",mfold[*i->second.begin()],i->first);
		}
	    }
	    else if(i->second.size()==2)
	    {
		printf("insert into notes  ( select * from notes where id=%d);\n",i->first);
		printf("insert into note_texts  ( select * from note_texts where message_id=%d);\n",i->first);
		for(typeof(i->second.begin())j=i->second.begin();j!=i->second.end();j++)
		{
		    if(mfold.count(*j))
		    {
			printf("update notes set owner_folder=%d, owner_uid=%d where id=%d and owner_uid=0 and owner_folder=0 limit 1;\n",*j,mfold[*j],i->first);
			printf("update note_texts set owner_uid=%d where message_id=%d and owner_uid=0 limit 1;\n",mfold[*j],i->first);
		    }
		}
		
		
	    }
	}
	{
	vector<vector<string> > vfi=dbh->execQ((QUERY)"select folder_id,uid from filters_in");
	for(unsigned i=0;i<vfi.size();i++)
	{
	    if(vfi[i].size()==2)
	    {
		int f=atoi(vfi[i][0]);
		int z=atoi(vfi[i][1]);
		if(mfold.count(f))
		{
		    printf("update filters_in set owner_uid=%d where folder_id=%d and uid=%d;\n",mfold[f],f,z);
		}
	    }
	}
	}
	{
	vector<vector<string> > vfo=dbh->execQ((QUERY)"select folder_id,uid from filters_out");
	for(unsigned i=0;i<vfo.size();i++)
	{
	    if(vfo[i].size()==2)
	    {
		int f=atoi(vfo[i][0]);
		int z=atoi(vfo[i][1]);
		if(mfold.count(f))
		{
		    printf("update filters_out set owner_uid=%d where folder_id=%d and uid=%d;\n",mfold[f],f,z);
		}
	    }
	}
	}

    }catch(cError e){
        printf("Error: %s\n",e.error_string.c_str());
    }
    return 0;
}
