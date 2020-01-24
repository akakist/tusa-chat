#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>
#include <deque>
#include "copy_file.h"
#include <sys/stat.h>
//#include "notes.h"
#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include "mutex_inspector.h"
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <map>
#include <mysql/mysql.h>
#include "mysql_extens.h"
#include "cMYSQL.h"
#include "mysql_extens.h"
#include "_mutex.h"
#include "str_lib.h"





int main(int argc,char *argv[])
{
    try{
        //		printf("%d", argc);
        //		exit(1);
        //        if(argc!=3) printf("usage %s db_old db_new\n", argv[0]);

        MYSQL *_dbh=new MYSQL;
        {
            mysql_init(_dbh);
            MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,"chat",0,NULL,0);
            if (!res)
            {
                logErr("chat_sender: mysql_real_connect failed to %s","chat");
                exit(1);
            }
        }
        cMYSQL *dbh=new cMYSQL(_dbh);




        {
            {
                map<int,set<int > > snotes;
                {
                    vector<vector<string  > > v=dbh->execQ((QUERY)"select message_id,owner_uid from note_texts");
		    fprintf(stderr,"v.size %d\n",v.size());
                    for (unsigned i=0;i<v.size();i++)
                    {
                        if (v[i].size()==2)
                        {
                	vector<vector<string  > > v1=dbh->execQ((QUERY)"select id,owner_uid from notes where id=? and owner_uid=?"<<v[i][0]<<v[i][1]);
			    if(!v1.size())
			    {
                                printf("delete from note_texts where message_id=%d and owner_uid=%d;\n",atoi(v[i][0]),atoi(v[i][1]));
			    }
                            //snotes[atoi(v[i][1])].insert(atoi(v[i][0]));
                        }
                    }
                }
                exit(1);

                
            }
        }


    }
    catch (cError e)
    {
        printf("Error: %s\n",e.error_string.c_str());
    }
    catch (...)
    {
        printf("Error: unknown\n");
    }
    return 0;
}
