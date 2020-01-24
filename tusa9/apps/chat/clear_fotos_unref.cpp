#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>
#include <sys/types.h>  
#include <sys/stat.h>   
#include <unistd.h>     
#define UNREG_BASE 100000000

bool is_unreg_id(unsigned int id)
{
	if(id>=UNREG_BASE) return true;
	return false;
}

string cache_dir(const string & name, unsigned int uid)
{
    if(is_unreg_id(uid))
    {
        logErr2("if(is_unreg_id(uid)) ");
        throw cError("if(is_unreg_id(uid)) ");
    }

    char pn[300];
    pn[0]=0;
    string sid=itostring(uid);
    if(uid<100)
    {//MUTEX_INSPECTOR;
        snprintf(pn,sizeof(pn)-1,"%s/%s/0/%02d","/var/chat",name.c_str(),uid);
    }
    else if(uid<10000)
    {//MUTEX_INSPECTOR;
        snprintf(pn,sizeof(pn)-1,"%s/%s/1/%02d/%02d","/var/chat",name.c_str(),uid/100,uid%100);
    }
    else if(uid<1000000)
    {//MUTEX_INSPECTOR;
        int u1=uid/10000;
        int u2=(uid-(u1*10000))/100;
        int u3=uid%100;
        snprintf(pn,sizeof(pn)-1,"%s/%s/2/%02d/%02d/%02d","/var/chat",name.c_str(),u1,u2,u3);
    }
    else if(uid<100000000)
    {//MUTEX_INSPECTOR;
        int u1=uid/1000000;
        int u2=(uid-(u1*1000000))/10000;
        int u3=(uid-(u1*10000))/100;
        int u4=uid%100;
        snprintf(pn,sizeof(pn)-1,"%s/%s/3/%02d/%02d/%02d/%02d","/var/chat",name.c_str(),u1,u2,u3,u4);
    }
    else{
        logErr2("cache_dir id >= UNREG_BASE ");
        throw cError("cache_dir id >= UNREG_BASE");
    }
    return pn;

}

string foto_pn(unsigned int pid, const string& ext)
{//MUTEX_INSPECTOR;
	string pn=cache_dir("fotos",pid)+"."+ext;
	return pn;
}					


int main(int argc,char *argv[])
{

    FILE *f=fopen("clear_users.log","a");
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
	vector< vector<string> > v=dbh->execQ((QUERY)"select id,ext from photos");
	for(unsigned i=0;i<v.size();i++)
	{
	    if(v[i].size()==2)
	    {
		string pn=foto_pn(atoi(v[i][0]),v[i][1]);
		struct stat st;
		if(stat(pn.c_str(),&st))
		{
		    printf("#%s FAIL\n",pn.c_str());
		    printf("delete from photos where id=%d;\n",atoi(v[i][0]));
		    
		}
		else 
		printf("#%s OK\n",pn.c_str());
	    }
	}
    }catch(cError e){
        fprintf(f,"Error: %s\n",e.error_string.c_str());
    }
    fclose(f);
    return 0;
}
