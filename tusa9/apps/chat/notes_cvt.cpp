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
#include "mysql_extens.h"
#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include "web_server.h"
#include "message.h"
#include "chatserver_main.h"

#include "get_opts.h"
#include "copy_file.h"
#include "wrappers.h"
#include "file_set.h"
#include "notes.h"
#include "license.h"
#include "levels.h"
#include "server_config.h"
#include "chat_config.h"
#include "user_info.h"

#include "app_con.h"
#include "app_def.h"

#include "user.h"
#include "user_credits.h"


deque<string>nn;
void load(unsigned int & n, const string &s, map<string,string>&m);
void load(int & n, const string &s, map<string,string>&m);
void load_app_configuration();
map<string,string> read_head(const string& fn, bool stop_after_head, string &body);
string att_pathname(unsigned int uid,unsigned int folder,unsigned int msgid);
string notes_homedir(unsigned int uid);
string attach_pn(unsigned int msgid, const string& orig);

string msg_pathname(unsigned int uid,unsigned int msgid);


string homedir(unsigned int uid);
class irc_server;
irc_server *iserver=NULL;

int app_main(int argc,char *argv[])
{
    try{
        //		printf("%d", argc);
        //		exit(1);
        //        if(argc!=3) printf("usage %s db_old db_new\n", argv[0]);
        load_app_configuration();

        MYSQL *_dbh=new MYSQL;
        {
            mysql_init(_dbh);
            MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,"chat",0,NULL,0);
            if(!res)
            {
                logErr("chat_sender: mysql_real_connect failed to %s","chat");
                exit(1);
            }
        }
        cMYSQL *dbh=new cMYSQL(_dbh);




        {
            {
                vector<string  > v=dbh->select_1_columnQ("select id from users");
                logErr2("v.size()==%d\n",v.size());
                for(unsigned iii=0;iii<v.size();iii++)
                {
                    if(iii%50==0) printf("%d\n",iii);
                    //					if(iii%7==0) sleep(2);
                    unsigned int id=atoi(v[iii]);
                    string fn=homedir(id)+"/.notes_profile";

                    map<string,string> m=load_m_file_noerr_no$(fn);
                    if(!m.size()) continue;

                    u_notes un;
                    un.init_from_map(m,id);
                    //                    logErr2("map_folders.size() %d map_msgs.size() %d",un.map_folders.size(),un.map_msgs.size());

                    map<unsigned int,unsigned int> intFLDext;
                    map<unsigned int,unsigned int> intMSGext;


                    dbh->real_queryQ((QUERY)"update user_sets set notes_msg_per_page='?',notes_save_copy='?' where refid='?'"<<un.msg_per_page<<un.save_copy<<id);
                    for(typeof(un.map_msgs.begin())i=un.map_msgs.begin();i!=un.map_msgs.end();i++)
                    {


                        string body;
                        map<string,string>mz=read_head(msg_pathname(id,i->first), false, body);

                        QUERY q;
                        q<<"insert into notes (
                        from_nick_id,to_nick_id,
                        from_uid,to_uid,
                        from_nick,to_nick,
                        refcount,
                        subject,send_date,
                        status,unread,
                        content_length, has_attachment,
                        attachment_filename,attachment_content_length, important,system)
                        values('?','?','?','?','?','?','?','?',FROM_UNIXTIME(?),'?','?','?','?','?','?','?','?')
                        "<<i->second.nfh.from_nick_id<<i->second.nfh.to_nick_id
                        <<i->second.nfh.from_uid<<i->second.nfh.to_uid
                        <<i->second.nfh.from_nick<<i->second.nfh.to_nick
                        <<1
                        <<i->second.nfh.subject<<i->second.nfh.send_date
                        <<i->second.nfh.status<<i->second.nfh.unread
                        <<body.size()<<i->second.nfh.has_attachment
                        <<i->second.nfh.attachment_filename<<i->second.nfh.attachment_content_length
                        <<i->second.nfh.important<<i->second.nfh.system;
                        /*
                        	bool has_attachment;
                        	string attachment_filename;
                        	int attachment_content_length;
                        */						
                        //						printf("%s;\n",q.prepare().c_str());
                        dbh->real_queryQ(q);
                        vector<string> vl=dbh->select_1_row("select LAST_INSERT_ID()");
                        unsigned int msgid;
                        if(vl.size())
                        {
                            msgid=atoi(vl[0]);
                            intMSGext[i->first]=msgid;
                        } else continue;
                        //						printf("%s",body.c_str());
                        dbh->real_query((string)"insert into note_texts (message_id,body) values ("+itostring(msgid)+",'"+MES(body)+"')");
                        if(i->second.nfh.has_attachment)
                        {
                            string from=att_pathname(id,0,i->first);
                            string to=attach_pn(msgid,i->second.nfh.attachment_filename);
                            check_path_wfn(to);
                            unlink(to.c_str());
                            if(link(from.c_str(),to.c_str()))
                            {
                                printf("attachment %d not found\n",i->first);
                            }
                        }

                    }

                    for(typeof(un.map_folders.begin())i=un.map_folders.begin();i!=un.map_folders.end();i++)
                    {
                        /*
                        struct __note_folder
                        {
                        	string name;
                        	set<unsigned int> filter_in;
                        	set<unsigned int> filter_out;
                        	vector<unsigned int> vec_msgs;
                        };

                        */							dbh->real_queryQ((QUERY)"insert into note_folders (uid,name) values(?,'?')"<<id<<i->second.name);
                        vector<string> vl=dbh->select_1_row("select LAST_INSERT_ID()");
                        unsigned int flid;
                        if(vl.size())
                        {
                            flid=atoi(vl[0]);
                            intFLDext[i->first]=flid;
                        } else continue;
                        for(typeof(i->second.vec_msgs.begin())j=i->second.vec_msgs.begin();j!=i->second.vec_msgs.end();j++)
                        {
                            if(intMSGext.count(*j))
                                dbh->real_queryQ((QUERY)"insert into  folder_contents (folder_id,message_id) values(?,?)"<<flid<<intMSGext[*j]);
                            else printf("message %d not found\n",*j);
                        }
                        for(typeof(i->second.filter_in.begin())j=i->second.filter_in.begin();j!=i->second.filter_in.end();j++)
                        {
                            dbh->real_queryQ((QUERY)"insert into  filters_in (folder_id,uid) values(?,?)"<<flid<<*j);
                        }
                        for(typeof(i->second.filter_out.begin())j=i->second.filter_out.begin();j!=i->second.filter_out.end();j++)
                        {
                            dbh->real_queryQ((QUERY)"insert into  filters_out (folder_id,uid) values(?,?)"<<flid<<*j);
                        }


                    }

                }
            }
        }


    }
    catch(cError e)
    {
        printf("Error: %s\n",e.error_string.c_str());
    }
    catch(...)
    {
        printf("Error: unknown\n");
    }
    return 0;
}
