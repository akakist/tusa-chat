#include <stdio.h>
#include <errno.h>
#include "st_stuff.h"
#include "str_lib.h"
#include <mysql/mysql.h>
#include "mysql_extens.h"
#include "cMYSQL.h"
#include <time.h>
void check_path_wfn(const string & _pathname);
string cache_dir(const string & name, unsigned int uid)
{

    char pn[300];
    pn[0]=0;
    string sid=itostring(uid);
    if (uid<100)
    {
        snprintf(pn,sizeof(pn)-1,"%s" "/" "%s" "/" "0" "/" "%02d","/var/chat",name.c_str(),uid);
    }
    else if (uid<10000)
    {
        snprintf(pn,sizeof(pn)-1,"%s" "/" "%s" "/" "1" "/" "%02d/%02d","/var/chat",name.c_str(),uid/100,uid%100);
    }
    else if (uid<1000000)
    {
        int u1=uid/10000;
        int u2=(uid-(u1*10000))/100;
        int u3=uid%100;
        snprintf(pn,sizeof(pn)-1,"%s" "/" "%s" "/" "2" "/" "%02d" "/" "%02d" "/" "%02d","/var/chat",name.c_str(),u1,u2,u3);
    }
    else if (uid<100000000)
    {
        int u1=uid/1000000;
        int u2=(uid-(u1*1000000))/10000;
        int u3=(uid-(u1*10000))/100;
        int u4=uid%100;
        snprintf(pn,sizeof(pn)-1,"%s" "/" "%s" "/" "3" "/" "%02d" "/" "%02d" "/" "%02d" "/" "%02d","/var/chat",name.c_str(),u1,u2,u3,u4);
    }
    else{
        fprintf(stderr,"cache_dir id >= UNREG_BASE %d",uid);
        throw cError("cache_dir id >= UNREG_BASE");
    }
    return pn;

}

/*
*/

string attach_pn(unsigned  uid,unsigned int msgid, const string& orig)
{
    string pn=cache_dir("user",uid)+"/attach/"+itostring(msgid)+"_*";//+orig;
    return pn;
}
string attach2_pn(unsigned  uid,unsigned int msgid, const string& orig)
{
    string pn=cache_dir("user2",uid)+"/attach/"+itostring(msgid)+"_*";//+orig;
    return pn;
}
	
int main(int argc,char *argv[])
{

    FILE *f=fopen("clear_users.log","a");
    try{
        MYSQL *_dbh=new MYSQL;
        mysql_init(_dbh);
        MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,"chat",0,"/tmp/mysql.sock",0);
        if(!res)
        {
            logErr("chat_sender: mysql_real_connect failed to %s","chat");
            exit(1);
        }
        cMYSQL *dbh=new cMYSQL(_dbh);
        dbh->connected=true;
	dbh->real_query("set charset cp1251");

	FILE *f=fopen("clear_attach.sql","wb");
	vector<vector<string > >v=dbh->exec("select owner_uid,id,attachment_filename from notes where attachment_content_length>300000 or send_date<'2009-01-01'");
	int total=0;
	for(unsigned i=0;i<v.size();i++)
	{
	    if(v[i].size()==3)
	    {
		string pn=attach_pn(atoi(v[i][0]),atoi(v[i][1]),(v[i][2]));
	//	string pn2=attach2_pn(atoi(v[i][0]),atoi(v[i][1]),(v[i][2]));
	//	check_path_wfn(pn2);
		printf("rm -f %s\n",pn.c_str());
		fprintf(f,"update notes set has_attachment='0',attachment_content_length='0'  where owner_uid=%d and id=%d;\n",atoi(v[i][0]),atoi(v[i][1]));
		
		
	    }
	}
	fclose(f);

    }catch(cError e){
        fprintf(f,"Error: %s\n",e.error_string.c_str());
    }
    fclose(f);
    return 0;
}
