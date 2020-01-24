#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include <mysql/mysql.h>
#include "mysql_extens.h"
#include "cMYSQL.h"
#include "mysql_extens.h"
#include <time.h>
#include "copy_file.h"

string str_nick(const string &n);


int main(int argc,char *argv[])
{

    //	FILE *f=fopen("clear_users.log","a");
//    if (fork())exit(0);
//    while (1)
    {
        time_t t=time(NULL);
        tm* tt=localtime(&t);
        if (tt->tm_hour!=6)
        {
//            sleep(10); continue;
        }

        MYSQL *_dbh=new MYSQL;
        mysql_init(_dbh);
        MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,"chat",0,NULL,0);
        if (!res)
        {
            logErr("chat_sender: mysql_real_connect failed to %s","chat");
            exit(1);
        }

        cMYSQL *dbh=new cMYSQL(_dbh);


        dbh->connected=true;
        dbh->real_query("SET CHARSET cp1251");
        try{

            {
                string d=date2mysql(time(NULL));
                try{
                    vector< string> v=dbh->select_1_column("show databases");
                    for (unsigned i=0;i<v.size();i++)
                    {
                        dbh->real_query("use "+v[i]);
                        vector<string> vv=dbh->select_1_column("show tables");

                        for (unsigned j=0;j<vv.size();j++)
                        {
                            string pn="/backup/db/"+d+"/"+v[i]+"."+vv[j]+".sql";
                            pn=str_replace(":","_",pn);
                            pn=str_replace(" ","_",pn);
                            check_path_wfn(pn);
                            char s[1000];
                            printf("mysqldump %s %s -r %s\n",v[i].c_str(),vv[j].c_str(),pn.c_str());
//                            system(s);
                        }
                    }
                    printf ("rsync -av /var/chat/user /backup/var/chat/user\n");
                }catch (...){}

                //	 `vote_balls` int(10) default NULL,
            }



        }catch (cError e)
        {
            printf("%s\n",e.what());
        }
//        sleep(3600);
    }
    return 0;
}
