#ifndef MYSQL_EXTENS__Hjj
#define MYSQL_EXTENS__Hjj
#include <string>
#include <mysql/mysql.h>
#include "_QUERY.h"
#include <ctime>
#include "_mutex.h"
#include <set>
class cMYSQL
{
public:
    int query_counter;
    int query_total_size;
    MYSQL *mysql;
    bool connected;
    bool error;
    string err_str;
    time_t last_query_time;
    cMYSQL(MYSQL*m);
    cMYSQL(): error(false) {
    }
    ~cMYSQL();
    void real_query(const string& query);
    void real_queryQ(const QUERY& query);
    void real_query_no_mutex(const string & query);
    void real_query_no_mutexQ(const QUERY & query);
    vector < vector < string > >exec (const string &query);
    vector < vector < string > >execQ (const QUERY &query);
    string select_1(const string &query);
    string select_1Q(const QUERY &query);
    vector<string> select_1_column(const string &query);
    vector<string> select_1_columnQ(const QUERY &query);
    vector<string> select_1_row(const string &query);
    vector<string> select_1_rowQ(const QUERY &query);
};
struct mysqlLock
{
    cMYSQL *r;
    mysqlLock(cMYSQL *rd, const string &q);
    ~mysqlLock();
};
struct st_dbh
{
    cMYSQL *dbh;
//	bool need_remove;
    st_dbh();
    ~st_dbh();
};

string MysqlEscapeString(const string& _str);
MYSQL *std_mysql_real_connect(MYSQL *_mysqlp);
cMYSQL *std_new_cMYSQL();
extern _mutex __dbh_set_mutex;
extern set<cMYSQL*> __dbh_set;
extern set<cMYSQL*> __dbh_set_backup;
#ifdef NO_DBH_ALLOWED
void real_query(const string& query);
void real_queryQ(const QUERY& query);
void real_query_no_mutex(const string & query);
void real_query_no_mutexQ(const QUERY & query);
vector < vector < string > >exec (const string &query);
vector < vector < string > >execQ (const QUERY &query);
string select_1(const string &query);
string select_1Q(const QUERY &query);
vector<string> select_1_column(const string &query);
vector<string> select_1_columnQ(const QUERY &query);
vector<string> select_1_row(const string &query);
vector<string> select_1_rowQ(const QUERY &query);
#endif
#define MES(a) MysqlEscapeString((a))

#endif
