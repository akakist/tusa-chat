#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>
#include <deque>
#include "copy_file.h"
#include <sys/stat.h>
string cache_dir(const string & name, unsigned int uid)
{

    char pn[300];
    pn[0]=0;
    string sid=itostring(uid);
    if(uid<100)
    {
        snprintf(pn,sizeof(pn)-1,"%s/%s/0/%02d","/var/chat",name.c_str(),uid);
    }
    else if(uid<10000)
    {
        snprintf(pn,sizeof(pn)-1,"%s/%s/1/%02d/%02d","/var/chat",name.c_str(),uid/100,uid%100);
    }
    else if(uid<1000000)
    {
        int u1=uid/10000;
        int u2=(uid-(u1*10000))/100;
        int u3=uid%100;
        snprintf(pn,sizeof(pn)-1,"%s/%s/2/%02d/%02d/%02d","/var/chat",name.c_str(),u1,u2,u3);
    }
    else if(uid<100000000)
    {
        int u1=uid/1000000;
        int u2=(uid-(u1*1000000))/10000;
        int u3=(uid-(u1*10000))/100;
        int u4=uid%100;
        snprintf(pn,sizeof(pn)-1,"%s/%s/3/%02d/%02d/%02d/%02d","/var/chat",name.c_str(),u1,u2,u3,u4);
    }
    else{
//        logErr2("cache_dir id >= UNREG_BASE %s",_DMI().c_str());
//        throw cError("cache_dir id >= UNREG_BASE");
    }
    return pn;

}

string new_attach_pn(unsigned int  uid,unsigned int msgid, const string& orig)
{

    string pn=cache_dir("user",uid)+"/attach/"+itostring(msgid)+"_"+orig;
    return pn;
}
string old_attach_pn(unsigned int  uid,unsigned int msgid, const string& orig)
{

    char pn[300];
    pn[0]=0;
    string sid=itostring(msgid);
    if(msgid<0x100)
    {
        snprintf(pn,sizeof(pn)-1,"%s/attach/0/%02x%s","/var/chat",msgid,orig.c_str());
    }
    else if(msgid<0x10000)
    {
        snprintf(pn,sizeof(pn)-1,"%s/attach/1/%02x/%02x%s","/var/chat",msgid/0x100,msgid%0x100,orig.c_str());
    }
    else if(msgid<0x1000000)
    {
        int u1=msgid/0x10000;
        int u2=(msgid-(u1*0x10000))/0x100;
        int u3=msgid%0x100;
        snprintf(pn,sizeof(pn)-1,"%s/attach/2/%02x/%02x/%02x%s","/var/chat",u1,u2,u3,orig.c_str());
    }
    else if(msgid<0xffffffff)
    {
        int u1=msgid/0x1000000;
        int u2=(msgid-(u1*0x1000000))/0x10000;
        int u3=(msgid-(u1*0x10000))/0x100;
        int u4=msgid%0x100;
        snprintf(pn,sizeof(pn)-1,"%s/attach/2/%02x/%02x/%02x/%02x%s","/var/chat",u1,u2,u3,u4,orig.c_str());
    }
    else{
//        logErr2("attachdir id >= UNREG_BASE %s",_DMI().c_str());
//        throw cError("attachdir id >= UNREG_BASE");
    }
    return pn;

}

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
	vector<vector<string> >v =dbh->execQ((QUERY)"select id,owner_uid,attachment_filename from notes where has_attachment='1'");
	for(int i=0;i<v.size();i++)
	{
	    if(v[i].size()==3)
	    {
		int id=atoi(v[i][0]);
		unsigned int uid;
		uid=atoi(v[i][1]);
		string fn=v[i][2];
		string newpn=new_attach_pn(uid,id,fn);
		string oldpn=old_attach_pn(uid,id,fn);
		check_path_wfn(newpn);
		link(oldpn.c_str(),newpn.c_str());
	    }
	}

    }catch(cError e){
        printf("Error: %s\n",e.error_string.c_str());
    }
    return 0;
}
