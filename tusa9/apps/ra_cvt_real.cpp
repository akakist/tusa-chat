#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include <mysql/mysql.h>
#include "mysql_extens.h"
#include "cMYSQL.h"
#include "mysql_extens.h"
#include <time.h>
#include "DB_id.h"
#include "copy_file.h"
#define LIMIT 1000000
string str_nick(const string &n);
#define TRYOP(nnn) 	try{\
	nnn ; \
	}catch(cError e){printf("\n%s\n",e.what());};
#define SPLITTER "/"
map<string,string> params;
string olddb;
#define OLDDB "chat"
#define NEWDB "newchat"
void load_config()
{
	params.clear();
	FILE *f=fopen(".config","r");
	if(!f) throw cError("Error during reading config file "+string(".config"));
	string data;
	while (!feof(f)){
		char s[1000];
		int z=fread((void*) &s, 1, 990,f);
		s[z]=0;
		data+=s;
	}
	vector<string> v=splitTOK("\r\n",data);
	for(unsigned int i=0;i<v.size();i++){
		string s=v[i];
		if(s.substr(0,1)=="#" || s.size()<=1) continue;
		int pz=s.find("=",0);
		if(pz==1){
			logErr2("---Error in %s on line %d - '=' not found",".config",i);
			continue;
		}
		string key=s.substr(0,pz);
		string val=s.substr(pz+1,s.size()-pz-1);
		printf("'%s' -> '%s'",key.c_str(),val.c_str());
		params[strupper(key)]=val;
	}
}

string cache_dir(const string & name, unsigned int uid)
{

    char pn[300];
    pn[0]=0;
    string sid=itostring(uid);
    if(uid<100)
    {
        snprintf(pn,sizeof(pn)-1,"%s" SPLITTER "%s" SPLITTER "0" SPLITTER "%02d","var/chat",name.c_str(),uid);
    }
    else if(uid<10000)
    {
        snprintf(pn,sizeof(pn)-1,"%s" SPLITTER "%s" SPLITTER "1" SPLITTER "%02d/%02d","var/chat",name.c_str(),uid/100,uid%100);
    }
    else if(uid<1000000)
    {
        int u1=uid/10000;
        int u2=(uid-(u1*10000))/100;
        int u3=uid%100;
        snprintf(pn,sizeof(pn)-1,"%s" SPLITTER "%s" SPLITTER "2" SPLITTER "%02d" SPLITTER "%02d" SPLITTER "%02d","var/chat",name.c_str(),u1,u2,u3);
    }
    else if(uid<100000000)
    {
        int u1=uid/1000000;
        int u2=(uid-(u1*1000000))/10000;
        int u3=(uid-(u1*10000))/100;
        int u4=uid%100;
        snprintf(pn,sizeof(pn)-1,"%s" SPLITTER "%s" SPLITTER "3" SPLITTER "%02d" SPLITTER "%02d" SPLITTER "%02d" SPLITTER "%02d","var/chat",name.c_str(),u1,u2,u3,u4);
    }
    else{
        throw cError("cache_dir id >= UNREG_BASE");
    }
    return pn;

}

void init_sql(cMYSQL *dbh)
{

    TRYOP(dbh->real_query("alter table channels add column read_level int(4) NOT NULL default '0'"));
    TRYOP(dbh->real_query("alter table channels add column write_level int(4) NOT NULL default '0'"));
    TRYOP(dbh->real_query("alter table channels add column irc_name text"));
    TRYOP(dbh->real_query("alter table news add column add_by text NOT NULL default ''"));
    /*    TRYOP(dbh->real_query(""));
        TRYOP(dbh->real_query(""));
        TRYOP(dbh->real_query(""));
        TRYOP(dbh->real_query(""));*/

    dbh->real_query("DROP TABLE IF EXISTS `banned_ip`");
    dbh->real_query("CREATE TABLE `banned_ip` (\
                    `ID` int(20) unsigned NOT NULL auto_increment,\
                    `ip` text,\
                    `proxy` text,\
                    `time_ban` datetime default NULL,\
                    `time_free` datetime default NULL,\
                    `time_cnt` text,\
                    `uid` int(20) unsigned NOT NULL default '0',\
                    PRIMARY KEY  (`ID`),\
                    KEY `uidk` (`uid`)\
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251");\

    dbh->real_query("DROP TABLE IF EXISTS banned_login");
    dbh->real_query("CREATE TABLE banned_login (\
                    ID int(20) unsigned NOT NULL auto_increment,\
                    login text,\
                    time_ban datetime default NULL,\
                    time_free datetime default NULL,\
                    time_cnt text,\
                    uid int(20) unsigned NOT NULL default '0',  \
                    descr text NOT NULL,                        \
                    buid int(11) NOT NULL default '0',          \
                    adm_uid int(11) NOT NULL default '0',       \
                    PRIMARY KEY  (ID),                          \
                    KEY uidk (uid),                           \
                    KEY adm_uid (adm_uid)                     \
                    )");


    dbh->real_query("DROP TABLE IF EXISTS `moderators`");
    dbh->real_query("CREATE TABLE `moderators` (\
                    `uid` int(10) unsigned NOT NULL default '0',\
                    `channel` text NOT NULL,\
                    `clan` int(10) unsigned NOT NULL default '0'\
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251");

    dbh->real_query("DROP TABLE IF EXISTS `bans`");
    dbh->real_query("CREATE TABLE `bans` (\
                    `id` int(10) unsigned NOT NULL default '0',\
                    `type` int(10) unsigned NOT NULL default '0',\
                    `uid` int(10) unsigned NOT NULL default '0',\
                    `adm_uid` int(10) unsigned NOT NULL default '0',\
                    `channel` text NOT NULL,\
                    `descr` text NOT NULL,\
                    `ip` text NOT NULL,\
                    `time_cnt_str` text NOT NULL,\
                    `time_ban_start` datetime NOT NULL default '2007-01-01 00:00:00',\
                    `time_ban_end` datetime NOT NULL default '2007-01-01 00:00:00',\
                    `adm_name` text NOT NULL,\
                    `user_name` text NOT NULL,\
                    `alevel` int(11) NOT NULL default '0',\
                    `ulevel` int(11) NOT NULL default '0'\
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251");

    dbh->real_query("DROP TABLE IF EXISTS `contact`");
    dbh->real_query("CREATE TABLE `contact` (\
                    `uid` int(11) NOT NULL default '0',\
                    `cuid` int(11) NOT NULL default '0',\
                    `flags` int(11) NOT NULL default '0',\
                    KEY `uid` (`uid`),\
                    KEY `cuid` (`cuid`)\
                    )");


    dbh->real_query("DROP TABLE IF EXISTS `credits_loans`");
    dbh->real_query("CREATE TABLE `credits_loans` (\
                    `id` int(20) unsigned NOT NULL auto_increment,\
                    `summa` double NOT NULL default '0',\
                    `from_user` int(20) unsigned NOT NULL default '0',\
                    `to_user` int(20) unsigned NOT NULL default '0',\
                    `to_nick` char(16) NOT NULL default '',\
                    `committed` char(1) NOT NULL default '0',\
                    `pogashen` char(1) NOT NULL default '0',\
                    `create_time` datetime default NULL,\
                    `end_time` datetime default NULL,\
                    `commit_time` datetime default NULL,\
                    PRIMARY KEY  (`id`),\
                    KEY `_fu` (`from_user`),\
                    KEY `_tu` (`to_user`)\
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251");

    ;

    dbh->real_query("DROP TABLE IF EXISTS credit_log");
    dbh->real_query("CREATE TABLE credit_log (\
                    dt datetime default NULL,\
                    from_uid int(11) NOT NULL default '0',\
                    to_uid int(11) NOT NULL default '0',\
                    summa double NOT NULL default '0',\
                    opcode varchar(40) NOT NULL default '',\
                    id int(11) NOT NULL auto_increment,\
                    PRIMARY KEY  (id),\
                    KEY _DT (dt),\
                    KEY __F (from_uid),\
                    KEY __T (to_uid),\
                    KEY __OP (opcode)\
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251");

    dbh->real_query("DROP TABLE IF EXISTS `ignores`");
    dbh->real_query("CREATE TABLE `ignores` (                                \
                    `uid` int(10) unsigned NOT NULL default '0',          \
                    `cuid` int(10) unsigned NOT NULL default '0',         \
                    KEY `uid` (`uid`)                                     \
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251");

    dbh->real_query("DROP TABLE IF EXISTS `pincodes`");
    dbh->real_query("CREATE TABLE `pincodes` (\
                    `v1` int(11) NOT NULL default '0',\
                    `v2` int(11) NOT NULL default '0',\
                    `v3` int(11) NOT NULL default '0',\
                    `full_v` varchar(14) NOT NULL default '0',\
                    `summa` int(11) NOT NULL default '0',\
                    `sent_to_provider` char(1) default '0',\
                    `accepted` char(1) default '0',\
                    `date_accepted` datetime NOT NULL default '2000-01-01 00:00:00',\
                    `date_created` datetime NOT NULL default '2000-01-01 00:00:00',\
                    `accepted_by_uid` int(11) NOT NULL default '0',\
                    `sms` text,\
                    `sent_to` varchar(100) NOT NULL default '',\
                    UNIQUE KEY `full_v` (`full_v`),\
                    KEY `_accepted` (`accepted`),\
                    KEY `_summa` (`summa`),\
                    KEY `_sent_to_provider` (`sent_to_provider`),\
                    KEY `_v1` (`v1`),\
                    KEY `_v2` (`v2`),\
                    KEY `_v3` (`v3`)\
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251");


    dbh->real_query("DROP TABLE IF EXISTS `topics`");
    dbh->real_query("CREATE TABLE `topics` (\
                    `channel` int(11) NOT NULL default '-1',\
                    `topic` blob,\
                    `current_price` double NOT NULL default '0',\
                    `orig_price` double NOT NULL default '0',\
                    `owner` int(11) NOT NULL default '0',\
                    `last_recalc` datetime default '1970-01-01 00:00:00',\
                    `disabled` char(1) NOT NULL default '0',\
                    `set_time` datetime NOT NULL default '0000-00-00 00:00:00',\
                    KEY `__C` (`channel`),\
                    KEY `__LC` (`last_recalc`),\
                    KEY `__D` (`disabled`)\
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251");



    dbh->real_query("DROP TABLE IF EXISTS `user_credits`");
    dbh->real_query("CREATE TABLE `user_credits` (\
                    `refid` int(10) unsigned NOT NULL default '0',\
                    `summa` double NOT NULL default '0',\
                    `last_access` datetime default '0000-00-00 00:00:00',\
                    KEY `_refid` (`refid`)\
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251");




}
void channels(cMYSQL *dbh)
{
    printf("channels\n"); sleep(1);

    dbh->real_query("DROP TABLE IF EXISTS `channels`");
    dbh->real_query("CREATE TABLE `channels` (\
                    `ID` int(20) unsigned NOT NULL auto_increment,\
                    `censored` int(2) default '1',\
                    `save` char(1) default '1',\
                    `move_to_channel` text NOT NULL,\
                    `move` char(1) default '0',\
                    `no_stat` char(1) NOT NULL default '0',\
                    `ext` char(1) NOT NULL default '0',\
                    `read_level` int(4) NOT NULL default '0',\
                    `write_level` int(4) NOT NULL default '0',\
                    `irc_name` text,\
                    `name` text NOT NULL,\
                    `name2` text NOT NULL,\
                    `owner` int(10) unsigned NOT NULL default '0',\
                    PRIMARY KEY  (`ID`)\
                    ) ENGINE=MyISAM  DEFAULT CHARSET=cp1251");

    vector<vector<string> > v=dbh->execQ((QUERY)"select ID,censored,save,no_stat,ext,read_level,write_level from " OLDDB ".channels");
    vector<vector<string> > vn=dbh->execQ((QUERY)"select cid,lang,name from channels_names");
    map<string,map<string,string> > M;
    for (unsigned i=0;i<vn.size();i++)
    {
        if (vn[i].size()==3)
        {
            M[vn[i][0]][vn[i][1]]=vn[i][2];
        }
        else {printf("!if(v[i].size()==3) %s %d\n",__FILE__,__LINE__ );}
    }
    for (unsigned i=0;i<v.size();i++)
    {
        if (v[i].size()==7)
        {
//		vector<string v>
            dbh->real_queryQ((QUERY)"insert into channels (id,censored,save,no_stat,ext,read_level,write_level,name,name2,irc_name)"
                             " values('?','?','?','?','?','?','?','?','?','?') "
                             <<v[i][0]<<v[i][1]<<v[i][2]<<v[i][3]<<v[i][4]<<v[i][5]<<v[i][6]<<M[v[i][0]][""]<<M[v[i][0]]["2"]<<M[v[i][0]]["en"]
                            );
        }
        else {printf("!if(v[i].size()==7) %s %d\n",__FILE__,__LINE__);}
    }

}
void user_status(cMYSQL * dbh)
{

    printf("status...\n");
    dbh->real_query("DROP TABLE IF EXISTS user_status");
    dbh->real_query("CREATE TABLE `user_status` (\
                    `ID` int(10) unsigned NOT NULL default '0',\
                    `uid` int(10) unsigned NOT NULL default '0',\
                    `name` text,\
                    `pic` int(11) default NULL,\
                    `disable_invite` char(1) NOT NULL default '0',\
                    `uniq` char(1) NOT NULL default '0',\
                    KEY `ID` (`ID`),\
                    KEY `uidi` (`uid`)\
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251");
    vector<vector<string> > v=dbh->execQ((QUERY)"select id,uid,name,pic,disable_call,uniq from " OLDDB ".user_status where uid<'?'"<<LIMIT);
    for(unsigned i=0;i<v.size();i++)
    {
        if(v[i].size()!=6){printf("if(v[i].size()!=6)\n");continue;}
        if(i%1000==0)printf("%d (%d)\n",i,v.size());
        dbh->real_queryQ((QUERY)"insert into user_status (id,uid,name,pic,disable_invite,uniq)\
                         values('?','?','?','?','?','?')"<<v[i][0]<<v[i][1]<<v[i][2]<<v[i][3]<<v[i][4]<<v[i][5]);
    }

}

void news(cMYSQL *dbh)
{
    printf("\nnews...\n");
    vector<vector<string> > v=dbh->execQ((QUERY)"select id,add_nid from " OLDDB ".news");
    for(unsigned i=0;i<v.size();i++)
    {
        if(v[i].size()==2)
        {
            if(i%1000==0)
            {
                printf("news %d (%d)\n",i,v.size());
            }
            string n=dbh->select_1Q((QUERY)"select " OLDDB ".nicks.nick from " OLDDB ".nicks where id=?"<<v[i][1]);
            dbh->real_queryQ((QUERY)"update ra.news set " NEWDB ".news.add_by='?' where " NEWDB ".news.id=?"<<n<<v[i][0]);
        }
    }

}
void nicks(cMYSQL *dbh)
{
    printf("\nnicks...\n");
    dbh->real_queryQ((QUERY)"DROP TABLE IF EXISTS `nicks`");
    dbh->real_queryQ((QUERY)"CREATE TABLE `nicks` (\
                     `ID` int(10) unsigned NOT NULL default '0',\
                     `Login` varchar(18) NOT NULL default '0',\
                     `Nick` varchar(17) NOT NULL default '',\
                     `str_nick` varchar(17) NOT NULL default '',\
                     `Banned` int(2) default NULL,\
                     `uid` int(10) NOT NULL default '0',\
                     `bby` int(10) NOT NULL default '0',\
                     `ready_to_sale` char(1) NOT NULL default '0',\
                     `cost` double NOT NULL default '0',\
                     KEY `ID` (`ID`),\
                     KEY `_nick` (`Nick`),\
                     KEY `uidk` (`uid`),\
                     KEY `logink` (`Login`),\
                     KEY `bby_key` (`bby`),\
                     KEY `uppernick_key` (`str_nick`),\
                     KEY `banned_key` (`Banned`),\
                     KEY `ready_to_sale` (`ready_to_sale`)\
                     ) ENGINE=MyISAM DEFAULT CHARSET=cp1251");


    try{
        vector<vector<string> >v=dbh->execQ((QUERY)"select id,login,nick, uppernick,banned,uid,bby from " OLDDB ".nicks where uid<'?'"<<LIMIT);
	
        for(unsigned i=0;i<v.size();i++)
        {
            if(i%1000==0)
            {
                printf("nicks %d (%d)\n",i,v.size());
            }

            if(v[i].size()==7)
            {
                dbh->real_queryQ((QUERY)"insert into nicks (id,login,nick,str_nick,banned,uid,bby) values\
		    ('?','?','?','?','?','?','?')"<<v[i][0]<<v[i][1]<<v[i][2]<<v[i][3]<<v[i][4]<<v[i][5]<<v[i][6]);
            }
            else {printf("!if(v[i].size()==3)");}
        }
    }catch(cError e){printf("\n%s\n",e.what());};

}

void note_folders(cMYSQL *dbh)
{
    dbh->real_query("DROP TABLE IF EXISTS `folder_contents`");

    dbh->real_query("CREATE TABLE `folder_contents` (\
                    `folder_id` int(11) NOT NULL default '0',\
                    `message_id` int(11) NOT NULL default '0',\
                    KEY `_k1` (`folder_id`),\
                    KEY `_k12` (`message_id`)\
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251");
    dbh->real_query("DROP TABLE IF EXISTS note_folders");
    dbh->real_query("CREATE TABLE note_folders ( \
                    id int unsigned NOT NULL default '0', \
                    uid int NOT NULL default '0', \
                    name blob,\
                    KEY _uid (uid), \
                    KEY _id (id) \
                    )");
    vector<vector<string> > v=dbh->execQ((QUERY)"select id,uid,name from " OLDDB ".notes_folders where uid<'?'"<<LIMIT);
    for(unsigned i=0;i<v.size();i++)
    {
        if(v[i].size()==3)
        {
            dbh->real_queryQ((QUERY)"insert into " NEWDB ".note_folders (id,uid,name) values ('?','?','?')"<<v[i][0]<<v[i][1]<<v[i][2]);
            if(i%1000==0)printf("notefolders %d (%d)\n",i,v.size());
        }
        else printf("v[i].size()==3\n");
    }
    vector<vector<string> > vn=dbh->execQ((QUERY)"select id,folder from " OLDDB ".notes where uid<?"<<LIMIT);
    for(unsigned i=0;i<vn.size();i++)
    {
        if(i%1000==0)printf("notfffefolders %d (%d)\n",i,vn.size());
        if(vn[i].size()==2)
        {
            dbh->real_queryQ((QUERY)"insert into folder_contents (message_id,folder_id) values ('?','?')"<<vn[i][0]<<vn[i][1]);
            if(i%1000==0)printf("notefolders %d (%d)\n",i,v.size());
        }
        else printf("vn[i].size()==2\n");

    }

}
void note_texts(cMYSQL *dbh)
{
    dbh->real_query("DROP TABLE IF EXISTS note_texts");
    dbh->real_query("CREATE TABLE note_texts (\
                    message_id int(11) NOT NULL default '0',\
                    body blob,\
                    owner_uid int(10) unsigned NOT NULL default '0',\
                    KEY _kM1 (message_id),\
                    KEY __owner_uid (owner_uid)\
                    )");

    vector<vector<string> > v=dbh->execQ((QUERY)"select id,uid,msg from " OLDDB ".notes where uid<?"<<LIMIT);
    for(unsigned i=0;i<v.size();i++)
    {
        if(i%1000==0)printf("notetexts %d (%d)\n",i,v.size());

        if(v[i].size()==3)
        {
            dbh->real_queryQ((QUERY)"insert note_texts (message_id,owner_uid,body) values ('?','?','?')"<<v[i][0]<<v[i][1]<<v[i][2]);
        }
        else printf("v[i].size()!=3 %s %d\n",__FILE__,__LINE__);
    }
}
/*
 ENGINE=MyISAM DEFAULT CHARSET=cp1251;              
	  
*/
string attach_pn(const DB_id&  uid,unsigned int msgid, const string& orig)
{
    string pn=cache_dir("user",CONTAINER(uid))+"/attach/"+itostring(msgid)+"_"+orig;
    return pn;
}

void notes(cMYSQL *dbh)
{






    dbh->real_query("DROP TABLE IF EXISTS notes");
    dbh->real_query("CREATE TABLE `notes` ( \
                    `id` int(10) unsigned NOT NULL default '0', \
                    `from_nick_id` int(11) NOT NULL default '0', \
                    `to_nick_id` int(11) NOT NULL default '0', \
                    `from_uid` int(11) NOT NULL default '0', \
                    `to_uid` int(11) NOT NULL default '0', \
                    `from_nick` varchar(100) NOT NULL default '',\
                    `to_nick` varchar(100) NOT NULL default '', \
                    `refcount` int(11) NOT NULL default '0', \
                    `subject` blob, \
                    `send_date` datetime default NULL, \
                    `status` char(1) NOT NULL default '0', \
                    `unread` char(1) NOT NULL default '1', \
                    `content_length` int(11) NOT NULL default '0', \
                    `has_attachment` char(1) NOT NULL default '0', \
                    `attachment_filename` text, \
                    `attachment_content_length` int(11) NOT NULL default '0', \
                    `important` char(1) NOT NULL default '0', \
                    `system` char(1) NOT NULL default '0', \
                    `owner_folder` int(10) unsigned NOT NULL default '0', \
                    `owner_uid` int(10) unsigned NOT NULL default '0', \
                    `notify_read` int(10) unsigned NOT NULL default '0', \
                    KEY `owner_folder` (`owner_folder`), \
                    KEY `owner_uid` (`owner_uid`), \
                    KEY `id` (`id`) \
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251; \
                    ");
    vector<string> a=dbh->select_1_columnQ((QUERY)"select uid from " OLDDB ".notes where uid<? group by uid"<<LIMIT);
    for(unsigned i=0;i<a.size();i++)
    {
        printf("%s (%d of %d)\n",a[i].c_str(),i,a.size());
        vector<vector<string> > v=dbh->execQ((QUERY)"select id,uid,from_nick,from_nick_id,to_nick,to_nick_id,subj,\
                                             sent_date,size,important,status,attach,file_name,file_path,\
                                             folder,parent,system,temporary,file_owner,\
                                             file_size,unread from " OLDDB ".notes where uid=?"<<a[i]);
        for(unsigned i=0;i<v.size();i++)
        {
            if(v[i].size()!=21)
            {
                printf("(v[i].size()!=21)\n");
                continue;
            }
            {
                int id			=atoi(v[i][ 0]);
                int uid			=atoi(v[i][ 1]);
                string from_nick	=     v[i][ 2];
                int from_nick_id	=atoi(v[i][ 3]);
                string to_nick		=     v[i][ 4];
                int to_nick_id		=atoi(v[i][ 5]);
                string subj		=     v[i][ 6];
                string sent_date	=     v[i][ 7];
                int size 		=atoi(v[i][ 8]);
                bool important		=atoi(v[i][ 9]);
                int status 		=atoi(v[i][10]);
                bool attach		=atoi(v[i][11]);
                string filename		=     v[i][12];
                string file_path	=     v[i][13];
                int folder		=atoi(v[i][14]);
                int parent		=atoi(v[i][15]);
                int system		=atoi(v[i][16]);
                int temporary		=atoi(v[i][17]);
                int file_owner		=atoi(v[i][18]);
                int file_size		=atoi(v[i][19]);
                int unread		=atoi(v[i][20]);
                dbh->real_queryQ((QUERY)"insert into notes (id,from_nick_id,to_nick_id,from_uid,to_uid,from_nick,to_nick,refcount,\
                                 subject,send_date,status,unread,content_length,has_attachment,attachment_filename,attachment_content_length,\
                                 important,system,owner_folder,owner_uid,notify_read)\
                                 values(\
                                 '?','?','?',\
                                 '?','?','?',\
                                 '?','?','?',\
                                 '?','?','?',\
                                 '?','?','?',\
                                 '?','?','?',\
                                 '?','?','?'\
                                 )\
                                 "<<id<<from_nick_id<<to_nick_id<</*from_uid*/0<</*to_uid*/0<<from_nick<<to_nick<</*refcount*/1
                                 <<subj<<sent_date<<status<<unread<<size<<attach<<filename<<0
                                 <<important<<system<<folder<<uid<<0/*notify_read*/);

                //                dbh->real_queryQ((QUERY)"insert into folder_contents(folder_id,message_id) values ('?','?')"
                //                                 <<id<<folder);
                if(attach)
                {
                    DB_id duid;
                    CONTAINER(duid)=uid;
                    string oldfn="var/chat/notes/"+file_path;
                    string newfn=attach_pn(duid,id, filename);
                    check_path_wfn(newfn);
                    link(oldfn.c_str(),newfn.c_str());
                }
            }


        }



    }
}

string foto_pn(const DB_id& uid,unsigned int pid, const string& ext)
{
    string pn=cache_dir("user",CONTAINER(uid))+"/photos" SPLITTER+itostring(pid)+"."+ext;
    return pn;
}

void photos(cMYSQL *dbh)
{
    //printf("KALL\n");
    dbh->real_query("DROP TABLE IF EXISTS `photos`");
    dbh->real_query("CREATE TABLE `photos` (\
                    `ID` int(10) unsigned NOT NULL default '0',\
                    `filename` text,\
                    `orig_filename` text,\
                    `descr` text,\
                    `sx` int(20) default NULL,\
                    `sy` int(20) default NULL,\
                    `uid` int(20) unsigned NOT NULL default '0',\
                    `size` int(10) NOT NULL default '0',\
                    `ext` text NOT NULL,\
                    `rating` blob NOT NULL,\
                    `rating_result` int(11) NOT NULL default '0',\
                    KEY `ID` (`ID`),\
                    KEY `uidi` (`uid`),\
                    KEY `rating_result` (`rating_result`)\
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251");
    //printf("KALL\n");

    vector<vector<string> >v=dbh->execQ((QUERY)"select id,filename,orig_filename,descr,sx,sy,uid,size from " OLDDB ".photos where uid<?"<<LIMIT);
    for(unsigned i=0;i<v.size();i++)
    {
        printf("photo %d (%d)\n",i,v.size());
        if(v[i].size()==8)
        {
            int id		=atoi(v[i][0]);
            string filename	=     v[i][1];
            string orig_filename=     v[i][2];
            string descr	=     v[i][3];
            int sx		=atoi(v[i][4]);
            int sy		=atoi(v[i][5]);
            int uid		=atoi(v[i][6]);
            int size		=atoi(v[i][7]);
            string ext;
            vector<string>rr=splitTOK(".",filename);
            if(rr.size())
                ext=rr[rr.size()-1];

            dbh->real_queryQ((QUERY)"insert into photos(id,uid,filename,orig_filename,descr,sx,sy,size,ext) values\
                             (\
                             '?','?','?','?',\
                             '?','?','?','?','?'\
                             )"
                             <<id<<uid<<filename<<orig_filename<<descr<<sx<<sy<<size<<ext
                            );
            string oldfn=(string)"var/chat/photos/"+filename;
            DB_id duid;
            CONTAINER(duid)=uid;
            string  newfn=foto_pn(duid,id, ext);
            check_path_wfn(newfn);
            link(oldfn.c_str(),newfn.c_str());
        }
        else printf("v[i].size()==8\n");
    }


}
void users(cMYSQL *dbh)
{
    /*

    */
    /*7722*/
    dbh->real_query("DROP TABLE IF EXISTS `filters_in`");
    dbh->real_query("CREATE TABLE `filters_in` (\
                    `folder_id` int(11) NOT NULL default '0',\
                    `uid` int(11) NOT NULL default '0',\
                    `owner_uid` int(10) unsigned NOT NULL default '0',\
                    KEY `owner_uid` (`owner_uid`)\
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251");

    dbh->real_query("DROP TABLE IF EXISTS `filters_out`");
    dbh->real_query("CREATE TABLE `filters_out` (\
                    `folder_id` int(11) NOT NULL default '0',\
                    `uid` int(11) NOT NULL default '0',\
                    `owner_uid` int(10) unsigned NOT NULL default '0',\
                    KEY `owner_uid` (`owner_uid`)\
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251");

    dbh->real_query("DROP TABLE IF EXISTS `user_stats`");
    dbh->real_query("CREATE TABLE `user_stats` (\
  `refid` int(20) unsigned NOT NULL default '0',\
  `last_date` datetime NOT NULL default '2006-01-01 00:00:00',\
  `last_ip` text NOT NULL,\
  `v_count` int(11) NOT NULL default '0',\
  `m_count` int(10) NOT NULL default '0',\
  `t_count` int(10) NOT NULL default '0',\
  `kick_count` int(10) unsigned NOT NULL default '0',\
  `kicked_count` int(10) unsigned NOT NULL default '0',\
  `last_pip` text NOT NULL,\
  `first_visit_date` datetime NOT NULL default '0000-00-00 00:00:00',\
  PRIMARY KEY  (`refid`)\
) ENGINE=MyISAM DEFAULT CHARSET=cp1251");

    dbh->real_query("DROP TABLE IF EXISTS `user_sets`");
    dbh->real_query("CREATE TABLE `user_sets` (\
                    `refid` int(20) unsigned NOT NULL default '0',\
                    `lpp` int(3) NOT NULL default '0',\
                    `show_nicks` char(1) NOT NULL default '1',\
                    `show_level` char(1) NOT NULL default '1',\
                    `neye` int(3) NOT NULL default '0',\
                    `n_color_pack` int(4) NOT NULL default '0',\
                    `bought_max_nick_count` int(10) NOT NULL default '0',\
                    `contact_mode` char(1) NOT NULL default '0',\
                    `contact_options` int(10) unsigned NOT NULL default '0',\
                    `notes_msg_per_page` int(11) NOT NULL default '20',\
                    `notes_save_copy` char(1) NOT NULL default '0',\
                    `notes_sort` char(1) NOT NULL default '1',\
                    `notes_sort_desc` char(1) NOT NULL default '1',\
                    `poweshen` int(11) NOT NULL default '0',\
                    `binv_last_recalc` datetime NOT NULL default '0000-00-00 00:00:00',\
                    `last_nick_id` int(11) NOT NULL default '0',\
                    `last_nick` text NOT NULL,\
                    `last_channel` int(11) NOT NULL default '0',\
                    `last_status_id` int(11) NOT NULL default '0',\
                    `setting_autologin` char(1) NOT NULL default '0',\
                    `setting_autochange` char(1) NOT NULL default '0',\
                    `setting_show_eye` char(1) NOT NULL default '0',\
                    `setting_show_hints` char(1) NOT NULL default '0',\
                    `setting_show_stat` char(1) NOT NULL default '0',\
                    `setting_invite_sound` char(1) NOT NULL default '0',\
                    `setting_full_buttons` char(1) NOT NULL default '0',\
                    `ul_mode_hide_female` char(1) NOT NULL default '0',\
                    `ul_mode_hide_male` char(1) NOT NULL default '0',\
                    `ul_mode_contacts_only` char(1) NOT NULL default '0',\
                    `show_credits` char(1) NOT NULL default '0',\
		      `level` int(10) unsigned NOT NULL default '100',\
                    `vote_balls` int(10) default NULL,\
                    `db_privileges` int(10) NOT NULL default '0',\
		      `last_www_channel` text NOT NULL,\
		  `primary_photo` int(10) unsigned NOT NULL default '0',\
                    PRIMARY KEY  (`refid`),\
                    KEY `_dp` (`db_privileges`),\
                    KEY `_vb` (`vote_balls`)\
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251\
                    ");



    dbh->real_query("DROP TABLE IF EXISTS `users`");
    dbh->real_query("CREATE TABLE `users` (\
                    `ID` int(10) unsigned NOT NULL auto_increment,\
                    PRIMARY KEY  (`ID`)\
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251;");

    dbh->real_query("DROP TABLE IF EXISTS `user_profiles`");
    dbh->real_query("CREATE TABLE `user_profiles` (\
                    `refid` int(20) unsigned NOT NULL default '0',\
                    `icq` text,\
                    `city` text,\
                    `info` text,\
                    `homepage` text,\
                    `tel` text,\
                    `b_day` varchar(10) NOT NULL default '',\
                    `b_mon` int(3) NOT NULL default '0',\
                    `b_year` varchar(4) NOT NULL default '1980',\
                    `fname` text,\
                    `lname` text,\
                    `email` text,\
                    `reg_date` datetime default NULL,\
                    `level` int(10) unsigned NOT NULL default '100',\
                    `login` varchar(18) NOT NULL default '',\
                    `pass` text,\
                    `upperlogin` varchar(20) NOT NULL default '',\
                    `gender` char(1) NOT NULL default '0',\
                    `has_clan` char(1) NOT NULL default '0',\
                    `hide_fname` char(1) NOT NULL default '0',\
                    `hide_lname` char(1) NOT NULL default '0',\
                    `hide_bdate` char(1) NOT NULL default '0',\
                    `hide_tel` char(1) NOT NULL default '0',\
                    `hide_icq` char(1) NOT NULL default '0',\
                    `hide_email` char(1) NOT NULL default '0',\
                    `bought_invisibility` double NOT NULL default '0',\
                    `bought_quota` int(10) NOT NULL default '0',\
		      `family_status` text NOT NULL,\
		      `hide_family_status` char(1) NOT NULL default '0',\
                    PRIMARY KEY  (`refid`),\
                    KEY `_login` (`login`),\
                    KEY `_rd` (`reg_date`),\
                    KEY `lv` (`level`)\
                    ) ENGINE=MyISAM DEFAULT CHARSET=cp1251;\
                    ");
    vector<vector<string> > vuid=dbh->execQ((QUERY)"select \
                                            id,login,pass,firstname,lastname,\
                                            email,ICQ,City,gender,AddInfo,\
                                            HomePage,BDay,BMonth,BYear,RegDate,\
                                            LastDate,LastIP,Public,VisCount,messagecount,\
                                            timecount,accessmode,LinesPerPage,Tel,vote_balls,\
                                            used_space,privs,lang,kick,kicked,quota \
                                            from " OLDDB ".users where id<?"<<LIMIT);
    for(unsigned i=0;i<vuid.size();i++)
    {
        if(!vuid.size()){printf("if(!vuid.size())\n"); continue;}
        if(i%100==0)
            printf("user %d (%d)\n",i,vuid.size());

        vector<string> vs=dbh->select_1_rowQ((QUERY)
                                             "select greeting,bye,anick,cstatus,channel,show_nicks,show_level,\
                                             notes_sent_folder,notes_msg_per_page,notes_sort_by,notes_save_copy,n_color_pack,settings from " OLDDB ".user_settings\
                                             where uid='?'"<<atoi(vuid[i][0]));
#define setting_autologin		2
#define setting_autochange		4
#define setting_show_eye		8
#define setting_show_hints		16
#define setting_show_stat		32
#define setting_invite_sound	64
#define setting_full_buttons	128

#define h_fname		2
#define h_lname		4
#define h_date		8
#define h_old		16
#define h_tel		32
#define h_email		64
#define h_icq		128


        if(vuid[i].size()!=31)
        {printf("if(vuid[i].size()!=31)\n"); continue;}
        int id		=atoi(vuid[i][ 0]);
        string login	=     vuid[i][ 1];
        string pass	=     vuid[i][ 2];
        string firstname=     vuid[i][ 3];
        string lastname	=     vuid[i][ 4];
        string email	=     vuid[i][ 5];
        string ICQ	=     vuid[i][ 6];
        string City	=     vuid[i][ 7];
        int gender	=atoi(vuid[i][ 8]);
        string AddInfo	=     vuid[i][ 9];
        string HomePage	=     vuid[i][10];
        string BDay	=     vuid[i][11];
        string BMonth	=     vuid[i][12];
        string BYear	=     vuid[i][13];
        string RegDate	=     vuid[i][14];
        string LastDate	=     vuid[i][15];
        string LastIP	=     vuid[i][16];
        int Public	=atoi(vuid[i][17]);
        int VisCount	=atoi(vuid[i][18]);
        int messagecount=atoi(vuid[i][19]);
        int timecount	=atoi(vuid[i][20]);
        int accessmode	=atoi(vuid[i][21]);
        int LinesPerPage=atoi(vuid[i][22]);
        string Tel	=     vuid[i][23];
        int vote_balls	=atoi(vuid[i][24]);
        int used_space	=atoi(vuid[i][25]);
        int privs	=atoi(vuid[i][26]);
        string lang	=     vuid[i][27];
        int kick	=atoi(vuid[i][28]);
        int kicked	=atoi(vuid[i][29]);
        int quota	=atoi(vuid[i][30]);

        if(vs.size()!=13){printf("if(vs.size()!=13)\n");continue;}
        int greeting		=atoi(vs[ 0]);
        int bye			=atoi(vs[ 1]);
        int anick		=atoi(vs[ 2]);
        int cstatus		=atoi(vs[ 3]);
        int channel		=atoi(vs[ 4]);
        int show_nicks		=atoi(vs[ 5]);
        int show_level		=atoi(vs[ 6]);
        int notes_sent_folder	=atoi(vs[ 7]);
        int notes_msg_per_page	=atoi(vs[ 8]);
        int notes_sort_by	=atoi(vs[ 9]);
        int notes_save_copy	=atoi(vs[10]);
        int n_color_pack	=atoi(vs[11]);
        int settings		=atoi(vs[12]);
        dbh->real_queryQ((QUERY)"insert into users (id) values ('?')"<<id);
        dbh->real_queryQ((QUERY)"insert into user_profiles\
                         (refid,icq,city,info,homepage,tel,\
                         b_day,b_mon,b_year,fname,lname,email,reg_date,level,login,pass,\
                         upperlogin,gender,has_clan,\
			 	 hide_fname,hide_lname,hide_bdate,hide_tel,hide_icq,hide_email\
			) values (\
                         '?','?','?','?','?','?','?',\
                         '?','?','?','?','?','?','?',\
                         '?','?','?','?','?','?','?','?','?','?','?'\
                         )"
                         <<id<<ICQ<<City<<AddInfo<<HomePage<<Tel
                         <<BDay<<BMonth<<BYear<<firstname<<lastname<<email<<RegDate<<accessmode*10<<login<<pass
                         <<str_nick(login)<<gender<<0
			 <<!(Public&h_fname)<<!(Public&h_lname)<<!(Public&h_date)<<!(Public&h_tel)<<!(Public&h_icq)<<!(Public&h_email)
                        );
        string lnick=dbh->select_1Q((QUERY)"select nick from " OLDDB ".nicks where id=?"<<anick);
        dbh->real_queryQ((QUERY)"insert into user_sets\
                         (refid,lpp,show_nicks,show_level,\
                         neye,n_color_pack,notes_msg_per_page,notes_save_copy,\
                         last_nick_id,last_nick,last_channel,last_status_id,\
                         setting_autologin,setting_autochange,setting_show_eye,setting_show_hints,\
                         setting_show_stat,setting_invite_sound,setting_full_buttons,\
			 level, vote_balls,db_privileges)\
                         values \
                         (\
                         '?','?','?','?',\
                         '?','?','?','?',\
                         '?','?','?','?',\
                         '?','?','?','?',\
                         '?','?','?','?','?','?'\
                         )"
                         <<id<<LinesPerPage<<show_nicks<<show_level
                         <<0<<n_color_pack<<notes_msg_per_page<<notes_save_copy
                         <<anick<<lnick<<channel<<cstatus
                         <<(settings&setting_autologin)<<(settings&setting_autochange)<<(settings&setting_show_eye)<<(settings&setting_show_hints)
                         <<(settings&setting_show_stat)<<(settings&setting_invite_sound)<<(settings&setting_full_buttons)
			 <<accessmode<<vote_balls<<privs
                        );

        dbh->real_queryQ((QUERY)"insert into user_stats\
                         (refid,last_date,last_ip,v_count,\
                         m_count,t_count,kick_count,kicked_count,last_pip,first_visit_date)\
                         values(\
                         '?','?','?','?',\
                         '?','?','?','?','?','?'\
                         )"
                         <<id<<LastDate<<LastIP<<VisCount
                         <<messagecount<<timecount<<kick<<kicked<<RegDate
                        );
/*
CREATE TABLE `user_stats` (
  `first_visit_date` datetime NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (`refid`)
) ENGINE=MyISAM DEFAULT CHARSET=cp1251;
*/
        int fld_in=atoi(dbh->select_1Q((QUERY)"select to_folder from " OLDDB ".notes_filters where fid=0 and uid=?"<<id));
        //notes_sent_folder
        dbh->real_queryQ((QUERY)"insert into filters_in (folder_id,uid,owner_uid)\
                         values('?','?','?')"<<fld_in<<0<<id);
        dbh->real_queryQ((QUERY)"insert into filters_out (folder_id,uid,owner_uid)\
                         values('?','?','?')"<<notes_sent_folder<<0<<id);
    }
}



int main(int argc,char *argv[])
{
    try{
        //	FILE *f=fopen("clear_users.log","a");

	load_config();
        MYSQL *_dbh=new MYSQL;
        mysql_init(_dbh);
	for(typeof(params.begin())i=params.begin();i!=params.end();i++)
	{
	    printf("==%s->%s\n",i->first.c_str(),i->second.c_str());
	}
//	printf("%d\n",params.count("db_name"));
/*
	return mysql_real_connect(_mysqlp,
		strupper(string(db_config.dbhost))=="NULL"?NULL:string(db_config.dbhost).c_str(),
		strupper(string(db_config.dbuser))=="NULL"?NULL:string(db_config.dbuser).c_str(),
		strupper(string(db_config.dbpasswd))=="NULL"?NULL:string(db_config.dbpasswd).c_str(),
		strupper(string(db_config.dbname))=="NULL"?NULL:string(db_config.dbname).c_str(),
		db_config.dbport,
		strupper(string(db_config.dbsock))=="NULL"?NULL:string(db_config.dbsock).c_str(),
		0);

*/
	const char *dn=(params.count("DB_NAME"))?(params["DB_NAME"].c_str()):NULL;
	printf("\n%s\n",dn);
        MYSQL *res=mysql_real_connect(_dbh,
	params.count("DB_HOST")?params["DB_HOST"].c_str():NULL,
	params.count("DB_USER")?params["DB_USER"].c_str():NULL,
	params.count("DB_PASS")?params["DB_PASS"].c_str():NULL,
	params.count("DB_NAME")?params["DB_NAME"].c_str():NULL,
	0,
	params.count("DB_SOCK")?params["DB_SOCK"].c_str():NULL,
	0);
        if(!res)
        {
            logErr2("chat_sender: mysql_real_connect failed to %s","ra");
            exit(1);
        }
        cMYSQL *dbh=new cMYSQL(_dbh);


        dbh->connected=true;
	printf("KALL %s %d\n",__FILE__,__LINE__);

        dbh->real_query("set charset cp1251");
	printf("KALL %s %d\n",__FILE__,__LINE__);
//	olddb=params["OLD_DB"];
#ifdef NDISABLE__
#endif	
        init_sql(dbh);
	printf("KALL %s %d\n",__FILE__,__LINE__);
	channels(dbh);
	printf("KALL %s %d\n",__FILE__,__LINE__);
        user_status(dbh);
//        news(dbh);
	printf("KALL %s %d\n",__FILE__,__LINE__);
        nicks(dbh);
	printf("KALL %s %d\n",__FILE__,__LINE__);
        note_folders(dbh);
        note_texts(dbh);
	printf("KALL %s %d\n",__FILE__,__LINE__);
        photos(dbh);
        users(dbh);
	printf("KALL %s %d\n",__FILE__,__LINE__);
        photos(dbh);
	printf("KALL %s %d\n",__FILE__,__LINE__);
        notes(dbh);
	channels(dbh);
	printf("KALL %s %d\n",__FILE__,__LINE__);
//	string cks=strupper(dbh->select_1("select md5('zzz')"));
//	dbh->real_queryQ((QUERY)"update user_profiles set pass='?'"<<cks);
	

    }catch(cError e)
    {
        printf("%s",e.what());
    }

    return 0;
}





