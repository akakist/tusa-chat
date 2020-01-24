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
    dbh->real_query("SET CHARSET cp1251");
    try{

        {
            try{
                dbh->real_queryQ((QUERY)"alter table user_sets add column   level int(10) unsigned NOT NULL default 100");
            }catch(...){}
		
                vector<vector<string> > v=dbh->execQ((QUERY)"select refid,level from user_profiles");
                for(unsigned i=0;i<v.size();i++)
                {
                    if(v[i].size()==2)
                    {
                        QUERY q=(QUERY)"update user_sets set level=? where refid=?"<<v[i][1]<<v[i][0];
                        printf("%s;\n",q.prepare().c_str());
                        //		dbh->real_queryQ();
                    }
                }
            fprintf(stderr,"level done\n");
            //	 `vote_balls` int(10) default NULL,
        }
        {
            try{
                dbh->real_queryQ((QUERY)"alter table user_sets add column   vote_balls int(10) unsigned NOT NULL default 0");
            }catch(...){}
                vector<vector<string> > v=dbh->execQ((QUERY)"select refid,vote_balls from user_profiles");
                for(unsigned i=0;i<v.size();i++)
                {
                    if(v[i].size()==2)
                    {
                        QUERY q=(QUERY)"update user_sets set vote_balls=? where refid=?"<<atoi(v[i][1])<<atoi(v[i][0]);
                        printf("%s;\n",q.prepare().c_str());
                        //		dbh->real_queryQ();
                    }
                }

            fprintf(stderr,"vote_balls done\n");
        }

        {
            try{
                dbh->real_queryQ((QUERY)"alter table user_sets add column   db_privileges int(10) NOT NULL default 0");
            }catch(...){}
                vector<vector<string> > v=dbh->execQ((QUERY)"select refid,db_privileges from user_profiles");
                for(unsigned i=0;i<v.size();i++)
                {
                    if(v[i].size()==2)
                    {
                        QUERY q=(QUERY)"update user_sets set db_privileges=? where refid=?"<<atoi(v[i][1])<<atoi(v[i][0]);
                        printf("%s;\n",q.prepare().c_str());
                        //		dbh->real_queryQ();
                    }
                }

            fprintf(stderr,"db_privileges done\n");
        }


        {
            try{
                dbh->real_queryQ((QUERY)"alter table user_sets add column   last_www_channel int(10) NOT NULL default 0");
            }catch(...){}
                vector<vector<string> > v=dbh->execQ((QUERY)"select refid,last_channel from user_sets");
                for(unsigned i=0;i<v.size();i++)
                {
                    if(v[i].size()==2)
                    {
                        QUERY q=(QUERY)"update user_sets set last_www_channel=? where refid=?"<<atoi(v[i][1])<<atoi(v[i][0]);
                        printf("%s;\n",q.prepare().c_str());
                        //		dbh->real_queryQ();
                    }
                }

            fprintf(stderr,"last_www_channel done\n");
        }

        {
            try{
                dbh->real_queryQ((QUERY)"alter table user_profiles add column   hide_fname char(1) NOT NULL default '0'");
                dbh->real_queryQ((QUERY)"alter table user_profiles add column   hide_lname char(1) NOT NULL default '0'");
                dbh->real_queryQ((QUERY)"alter table user_profiles add column   hide_bdate char(1) NOT NULL default '0'");
                dbh->real_queryQ((QUERY)"alter table user_profiles add column   hide_tel char(1) NOT NULL default '0'");
                dbh->real_queryQ((QUERY)"alter table user_profiles add column   hide_icq char(1) NOT NULL default '0'");
                dbh->real_queryQ((QUERY)"alter table user_profiles add column   hide_email char(1) NOT NULL default '0'");
            }catch(...){}
                vector<vector<string> > v=dbh->execQ((QUERY)"select refid,hide_fname,hide_lname,hide_bdate,hide_tel,hide_icq,hide_email from user_sets");
                for(unsigned i=0;i<v.size();i++)
                {
                    if(v[i].size()==7)
                    {
                        QUERY q=(QUERY)"update user_profiles set "
                                "hide_fname=?,"
                                "hide_lname=?,"
                                "hide_bdate=?,"
                                "hide_tel =?,"
                                "hide_icq =?,"
                                "hide_email=? where refid=?"
                                <<atoi(v[i][1])
                                <<atoi(v[i][2])
                                <<atoi(v[i][3])
                                <<atoi(v[i][4])
                                <<atoi(v[i][5])
                                <<atoi(v[i][6])
                                <<atoi(v[i][0])
                                ;
                        printf("%s;\n",q.prepare().c_str());
                        //		dbh->real_queryQ();
                    }
                }

            fprintf(stderr,"hide_* done\n");
            {
                try{
                    dbh->real_queryQ((QUERY)"alter table user_profiles add column   bought_invisibility double NOT NULL default '0'");
                }catch(...){}
                vector<vector<string> > v=dbh->execQ((QUERY)"select refid,bought_invisibility from user_sets where bought_invisibility>0");
                for(unsigned i=0;i<v.size();i++)
                {
                    if(v[i].size()==2)
                    {
                        QUERY q=(QUERY)"update user_profiles set bought_invisibility='?' where refid='?'"<<v[i][1]<<v[i][0];
                        printf("%s;\n",q.prepare().c_str());
                        //		dbh->real_queryQ();
                    }
                }

                fprintf(stderr,"bought_invisibility done\n");
            }
            {
                try{
                    dbh->real_queryQ((QUERY)"alter table user_profiles add column    bought_quota int(10) NOT NULL default '0'");
                }catch(...){}
                vector<vector<string> > v=dbh->execQ((QUERY)"select refid,bought_quota from user_sets where bought_quota>0");
                for(unsigned i=0;i<v.size();i++)
                {
                    if(v[i].size()==2)
                    {
                        QUERY q=(QUERY)"update user_profiles set bought_quota='?' where refid='?'"<<v[i][1]<<v[i][0];
                        printf("%s;\n",q.prepare().c_str());
                        //		dbh->real_queryQ();
                    }
                }

                fprintf(stderr,"bought_quota done\n");
            }

        }
                try{
                    dbh->real_queryQ((QUERY)"alter table channels add column  name text NOT NULL default ''");
                    dbh->real_queryQ((QUERY)"alter table channels add column  name2 text NOT NULL default ''");
                }catch(...){}
		    vector<vector<string> >v=dbh->execQ((QUERY)"select cid,lang,name from channels_names");
		    for(unsigned i=0;i<v.size();i++)
		    {
			if(v[i].size()==3)
			{
			    if(v[i][1]=="2")
			    {
				QUERY q=(QUERY)"update channels set name2='?' where id=?"<<v[i][2]<<v[i][0];
                    		printf("%s;\n",q.prepare().c_str());
			    }
			    if(v[i][1]=="")
			    {
				QUERY q=(QUERY)"update channels set name='?' where id=?"<<v[i][2]<<v[i][0];
                    		printf("%s;\n",q.prepare().c_str());
			    }
			}
		    }
		    

	
    }catch(cError e)
    {
        printf("%s\n",e.what());
    }
    return 0;
}
