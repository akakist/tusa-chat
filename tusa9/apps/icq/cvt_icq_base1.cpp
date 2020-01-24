#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>
#include <set>
int main()
{
	try {
		MYSQL *_dbh = new MYSQL;
		mysql_init(_dbh);
		MYSQL *res = mysql_real_connect(_dbh, NULL, NULL, NULL, "icq", 0, NULL, 0);
		if (!res) {
			printf("chat_sender: mysql_real_connect failed to\n");
			exit(1);
		}
		cMYSQL *dbh = new cMYSQL(_dbh);
		dbh->connected = true;

		vector < vector < string > >v1 = dbh->execQ((QUERY) "select uin,parent_uin from contact_list");
		for (unsigned i = 0; i < v1.size(); i++) {
			if(v1[i].size()==2)
			dbh->real_queryQ((QUERY) "insert into list (uin,parent_uin,type) values (?,?,1)" << v1[i][0] << v1[i][1]);
			printf("%d\n",i);
		}
	}
	catch(cError e) {
		printf("\n%s\n", e.error_string.c_str());
	}
}
