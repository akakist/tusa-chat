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

        map<int,set<int> > p;
        {
            vector<vector<string> > v1=dbh->execQ((QUERY)"select id,owner_uid from notes");
            for(unsigned i=0;i<v1.size();i++)
            {
                if(v1[i].size()==2)
		{
		    int uid=atoi(v1[i][1]);
		    int nid=atoi(v1[i][0]);
                    p[uid].insert(nid);

		}
            }
        }
        {
            vector<vector<string> > v2=dbh->execQ((QUERY)"select message_id,owner_uid from note_texts");
            for(unsigned i=0;i<v2.size();i++)
            {
                if(v2[i].size()==2)
                {
		    int nid=atoi(v2[i][0]);
		    int uid=atoi(v2[i][1]);
                    if(!p[uid].count(nid))
                    {
                        printf("delete from note_texts where message_id=%d and owner_uid=%d;\n",nid,uid);
                    }
                }

            }
        }

    }catch(cError e){
        printf("Error: %s\n",e.error_string.c_str());
    }
    return 0;
}
