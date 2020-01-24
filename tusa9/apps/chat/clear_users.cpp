#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include <mysql/mysql.h>
#include "mysql_extens.h"
#include "cMYSQL.h"
#include <time.h>
string str_nick(const string &n);

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
anekdots
banned_country
banned_ip
banned_login
blocked_guid
blocked_ip
blocked_nick
blocked_serials
channels
channels_names
chat_rooms
chat_rooms_admins
client_download
connected_users
contact
contacts
countries
country
country_location
credit_bank
credit_log
credits_transactions
exclude_email
family_filter
fm_client_download
fm_contact
fm_contacts
fm_rooms
fm_user_profile
folder_contents
forum_messages
forum_themes
funnypics
grant_agrees
grant_messages
grant_readden
grant_vote
hints
filters_in	owner_uid
filters_out	owner_uid
histories
*/

/*
contact uid
credits_loans from_user to_user
filters_out owner_uid
filters_in owner_uid
*/
void clean_a(const vector<string> &v);
void clean(const vector<string> &v)
{
    vector<string>  vv;
    for (unsigned i=0;i<v.size();i++)
    {
        vv.push_back(v[i]);
        if (vv.size()>100)
        {
            clean_a(vv);
            vv.clear();
        }
    }
    clean_a(vv);
}
void print_c(int a, int z)
{
    string s;
    for (int i=a; i <= z;i++)
    {
        char c=i;
        s+=c;
    }
    printf("\n%s\n",s.c_str());
    printf("\n%s\n",str_nick(s).c_str());

}
int main(int argc,char *argv[])
{

    FILE *f=fopen("clear_users.log","a");
    try{
        MYSQL *_dbh=new MYSQL;
        mysql_init(_dbh);
        MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,"chat",0,"/tmp/mysql.sock",0);
        if (!res)
        {
            logErr("chat_sender: mysql_real_connect failed to %s","chat");
            exit(1);
        }
        cMYSQL *dbh=new cMYSQL(_dbh);
        dbh->connected=true;


        vector<string> v=dbh->select_1_column("select tbl_users.id from tbl_users where  level<300 and stat_last_date<'2008-01-01' and id>10000 order by id");
//	clean(v);
//	fprintf(stderr,"clean %d users\n",v.size());
        vector<string>v1=dbh->select_1_column("select id from tbl_users where  level<500 and stat_last_date<'2008-06-01' and stat_v_count<3 and id>1000 order by id");
        fprintf(stderr,"clean %d users\n",v.size());

        for (unsigned i=0;i<v1.size();i++)
            v.push_back(v1[i]);
        //v.append(v1);
        clean(v);



        vector<vector<string > > N=dbh->exec("select a.id,a.uid from nicks a, tbl_users  b where a.uid=b.id and b.level<500 and a.last_usage_date<'2008-06-01'");
        fprintf(stderr,"total %d removed nicks\n",N.size());
        for (unsigned i=0;i<N.size();i++)
        {
            if (N[i].size()==2)
                printf("delete from nicks where id=%d and uid=%d;\n",atoi(N[i][0]),atoi(N[i][1]));
        }

        vector<string> va=dbh->select_1_columnQ((QUERY)"select id from tbl_users");
        set<int> sa;
        for (unsigned i=0;i<va.size();i++)
        {
            sa.insert(atoi(va[i]));
        }
        {
            vector<string>  z=dbh->select_1_column("select uid from nicks");
            for (unsigned i=0;i<z.size();i++)
            {
                if (!sa.count(atoi(z[i])))
                    printf("delete from nicks where uid='%s';\n",z[i].c_str());
            }
        }
        {
            vector<string>  z=dbh->select_1_column("select uid from user_status");
            for (unsigned i=0;i<z.size();i++)
            {
                if (!sa.count(atoi(z[i])))
                    printf("delete from user_status where uid='%s';\n",z[i].c_str());
            }
        }
        {
            vector<string>  z=dbh->select_1_column("select uid from photos");
            for (unsigned i=0;i<z.size();i++)
            {
                if (!sa.count(atoi(z[i])))
                    printf("delete from photos where uid='%s';\n",z[i].c_str());
            }
        }
        {
            vector<string>  z=dbh->select_1_column("select owner_uid from notes");
            for (unsigned i=0;i<z.size();i++)
            {
                if (!sa.count(atoi(z[i])))
                    printf("delete from notes where owner_uid='%s';\n",z[i].c_str());
            }
        }
        {
            vector<string>  z=dbh->select_1_column("select owner_uid from note_texts");
            for (unsigned i=0;i<z.size();i++)
            {
                if (!sa.count(atoi(z[i])))
                    printf("delete from note_texts where owner_uid='%s';\n",z[i].c_str());
            }
        }

        {
            vector<string>  z=dbh->select_1_column("select uid from ignores");
            for (unsigned i=0;i<z.size();i++)
            {
                if (!sa.count(atoi(z[i])))
                    printf("delete from ignores where uid='%s';\n",z[i].c_str());
            }
        }
        {
            vector<string>  z=dbh->select_1_column("select uid from contact");
            for (unsigned i=0;i<z.size();i++)
            {
                if (!sa.count(atoi(z[i])))
                    printf("delete from contact where uid='%s';\n",z[i].c_str());
            }
        }
        {
		set<unsigned int> used;
            vector<string>  z=dbh->select_1_column("select cuid from contact");
            for (unsigned i=0;i<z.size();i++)
            {
	    	if(!used.count(atoi(z[i])))
		{
                if (!sa.count(atoi(z[i])))
                    printf("delete from contact where cuid='%s';\n",z[i].c_str());
		    used.insert(atoi(z[i]));
		    
		} 
            }
        }

        {
            vector<string>  z=dbh->select_1_column("select owner_uid from filters_in");
            for (unsigned i=0;i<z.size();i++)
            {
                if (!sa.count(atoi(z[i])))
                    printf("delete from filters_in where owner_uid='%s';\n",z[i].c_str());
            }
        }
        {
            vector<string>  z=dbh->select_1_column("select owner_uid from filters_out");
            for (unsigned i=0;i<z.size();i++)
            {
                if (!sa.count(atoi(z[i])))
                    printf("delete from filters_out where owner_uid='%s';\n",z[i].c_str());
            }
        }

        /*
        	    printf("delete from notes where owner_uid in (%s);\n",join(",",v).c_str());
        	    printf("delete from note_texts where owner_uid in (%s);\n",join(",",v).c_str());
        	    printf("delete from note_folders where uid in (%s);\n",join(",",v).c_str());
        	    printf("delete from ignores where uid in (%s);\n",join(",",v).c_str());
        	    printf("delete from contact where uid in (%s);\n",join(",",v).c_str());
        	    printf("delete from filters_in where owner_uid in (%s);\n",join(",",v).c_str());
        	    printf("delete from filters_out where owner_uid in (%s);\n",join(",",v).c_str());

        */


    }catch (cError e){
        fprintf(f,"Error: %s\n",e.error_string.c_str());
    }
    fclose(f);
    return 0;
}


void clean_a(const vector<string> &v)
{
//        for(unsigned i=0;i<v.size();i++)
    if(v.size()){
//            vector<string> vv=dbh->select_1_columnQ((QUERY)"select nick from nicks where uid=?"<<v[i]);
	
        printf("delete from nicks where uid in (%s);\n",join(",",v).c_str());
//            printf("# %s\n",join(",",vv).c_str());
        printf("delete from user_status where uid in (%s);\n",join(",",v).c_str());
        printf("delete from tbl_users where id in(%s);\n",join(",",v).c_str());
        printf("delete from photos where uid in (%s);\n",join(",",v).c_str());
        printf("delete from notes where owner_uid in (%s);\n",join(",",v).c_str());
        printf("delete from note_texts where owner_uid in (%s);\n",join(",",v).c_str());
        printf("delete from note_folders where uid in (%s);\n",join(",",v).c_str());
        printf("delete from ignores where uid in (%s);\n",join(",",v).c_str());
        printf("delete from contact where uid in (%s);\n",join(",",v).c_str());
        printf("delete from filters_in where owner_uid in (%s);\n",join(",",v).c_str());
        printf("delete from filters_out where owner_uid in (%s);\n",join(",",v).c_str());
    }
    FILE *f=fopen("clear_users.rm","a");

    for (unsigned i=0;i<v.size();i++)
    {
        try{
            fprintf(f,"rm %s -Rf\n",cache_dir("user",atoi(v[i].c_str())).c_str());
        }
        catch (...){}
    }
    fclose(f);


}
