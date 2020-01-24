#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>

int main()
{
	string a="zaza";
	for(unsigned int i=0;i<10000;i++) a+="asdads";
	a+="z";
//	string b=bin2hex(MD5(a),0);
	printf("size=%d a='%s'\n asdasdas=%d",a.size(),a.c_str(),atoi(a));
//	printf("size=%d b='%s'\n",a.size(),b.c_str());
	exit(0);

	MYSQL *_dbh=new MYSQL;
	mysql_init(_dbh);
	MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,"chat",0,NULL,0);
	if(!res)
	{
		logErr("chat_sender: mysql_real_connect failed to");
		exit(1);
	}
	cMYSQL *dbh=new cMYSQL(_dbh);
	dbh->connected=true;
	
	vector<string> v=dbh->select_1_columnQ((QUERY)"select id from users");
	printf("%d users\n",v.size());
	for(unsigned int i=0;i<v.size();i++){
		vector<string> vv=dbh->select_1_rowQ((QUERY)"select anick from user_settings where uid=?"<<v[i]);
		if(vv.size()==0){
			printf("user_settings for %s not found. creating it.\n",v[i].c_str());
			dbh->real_queryQ((QUERY)"insert into user_settings (uid,greeting,bye,voting,anick,cstatus,channel,autologin,autochange) values(?, -1, -1, 0, 0, 0, 0, 0, 1)"<<v[i]);
		}
//		unsigned int anick=atoi(dbh->select_1Q((QUERY)"select anick from user_settings where uid=?"<<v[i]));
//		printf("user %s has %d nicks anick=%d\n",v[i].c_str(),vv.size(),anick);
/*		if(anick>=vv.size()){
//			dbh->real_queryQ((QUERY)"update user_settings set anick=0 where uid=?"<<v[i]);
		}else{
			dbh->real_queryQ((QUERY)"update user_settings set anick=? where uid=?"<<vv[anick]<<v[i]);
		}
		if(i%100==0) printf("updated %d of %d users\n",i,v.size());*/
	}
	
	
/*	vector< vector<string> > v=dbh->exec("select id,nick from nicks");
	printf("#nicks selected\n");
	for(int i=0;i<v.size();i++){
		dbh->real_queryQ((QUERY)"update nicks set uppernick='?' where id=?"<<str_nick(v[i][1])<<v[i][0]);
		if(i%100==0){
			printf("updated %d of %d nicks\n",i,v.size());
		}*/
/*
//		printf("select %d\n",i);
		vector<string> did=dbh->select_1_row("select id,uid,nick from nicks where uppernick='"+MES(v[i][1])+"' and id!="+v[i][2]);
//		printf("select %d OK\n",i);
		if(did.size()){
			vector<string> v1=dbh->select_1_column("select nick from nicks where uid="+v[i][3]);
			vector<string> v2=dbh->select_1_column("select nick from nicks where uid="+did[1]);
			printf("#dublicate nick %s. id1=%s id2=%s uid1=%s uid2=%s\n",v[i][0].c_str(),v[i][2].c_str(),did[0].c_str(),v[i][3].c_str(),did[1].c_str());
			printf("#\t user1 nicks: %s\n",join(",",v1).c_str());
			printf("#\t user2 nicks: %s\n",join(",",v2).c_str());
			int id1=atoi(v[i][2]);
			int id2=atoi(did[0]);	//v[i][2].c_str(),did[0].c_str()
			int id;
			if(id1>id2) id=id1;
			if(id1<id2) id=id2;
			printf("delete from nicks where id=%d;\n\n",id);
		}*/
//	}
}