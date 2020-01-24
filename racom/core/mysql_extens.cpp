#include "stdafx.h"
#include <string>
#include "str_lib.h"
#include <stdio.h>
#include "mysql_extens.h"
#include "_mutex.h"

#include "file_set.h"
#include "st_stuff.h"
#include "db_config.h"

#ifdef WIN32
#define snprintf _snprintf
#endif
void mysql_extens_cpp() {}

_mutex sql_log_mx("sqlmutex");
FILE *sql_f=NULL;
void sql_log(const string & r)
{
//	logErr2("%s",r.c_str());
    return;
    MUTEX_LOCK kall(sql_log_mx);
    if (sql_f==NULL)
        sql_f=fopen("sql.log","ab");

    fprintf(sql_f,"%s\n",r.c_str());
}

static int UM_mysql_escape_string(char *buf, const char *s, unsigned int sz)
{
    return mysql_escape_string(buf, s,sz);
}

string MysqlEscapeString(const string & _str)
{
    unsigned int sz=_str.size() * 2;
    st_malloc buf(sz);

    int len = mysql_escape_string((char*)buf.buf, _str.c_str(), _str.size());
    string ret((char*)buf.buf, len);
    return ret;
}

vector < vector < string > >cMYSQL::exec(const string & query)
{

    last_query_time=time(NULL);
    vector < vector < string > >rr;
    real_query_no_mutex(query);

    MYSQL_RES *r;
    {
        r= mysql_store_result(mysql);
    }
    if (r == NULL) {
        logErr("mysql_store_result failed: %s %s", mysql_error(mysql), query.c_str());
        error=true;
        err_str="mysql_store_result: Query: " + query + " Error: " + mysql_error(mysql);
        throw cError(cError::E_MYSQL,
                     err_str);
    }
    MYSQL_ROW row;
    int num_fields;
    {
        num_fields = mysql_num_fields(r);
    }

    while (1) {
        {
            row=mysql_fetch_row(r);
        }
        if (!row)break;
        unsigned long *lengths;
        {
            lengths = mysql_fetch_lengths(r);
        }
        vector < string > v;
        for (int i = 0; i < num_fields; i++) {
            string s = "";
            if (row[i]) {
                string a(row[i], lengths[i]);
                s = a;
            }
            v.push_back(s);
        }
        rr.push_back(v);
    }
    {
        mysql_free_result(r);
    }
    query_total_size += query.size();
    query_counter++;

    return rr;
}

void cMYSQL::real_query(const string & query)
{
    //logErr2("cMYSQL::real_query '%s'",query.c_str());
    last_query_time=time(NULL);
    int res;
    {
        res=mysql_real_query(mysql, query.data(), query.size());
        sql_log(query);
    }
    if (res) {
        error=true;
        err_str=(string) "mysql_real_query failed on query:" + query + " Error:" + mysql_error(mysql);
        throw cError(cError::E_MYSQL,
                     err_str);
    }
    query_total_size += query.size();
    query_counter++;
}

void cMYSQL::real_query_no_mutex(const string & query)
{
    last_query_time=time(NULL);
    int res;
    {
        res=mysql_real_query(mysql, query.data(), query.size());
        sql_log(query);
    }
    if (res) {
        error=true;
        string errstr=(string) "mysql_real_query failed on query:" + query + " Error:" + mysql_error(mysql);
        err_str= errstr;
        logErr2("%s",errstr.c_str());
        throw cError(cError::E_MYSQL,
                     errstr);
    }
    {
        query_total_size += query.size();
        query_counter++;
    }
}

cMYSQL::~cMYSQL()
{

    if (connected) {
        logErr2("closing mysql connection");
        mysql_close(mysql);
    }
}

string cMYSQL::select_1(const string & query)
{
    last_query_time=time(NULL);
    string ret;

    vector < vector < string > >res = exec(query);
    if (res.size()) {
        if (res[0].size())
            ret = res[0][0];
    }
    return ret;

}

vector < string > cMYSQL::select_1_column(const string & query)
{
    last_query_time=time(NULL);
    vector < string > ret;
    vector < vector < string > >res = exec(query);
    for (typeof(res.begin()) i = res.begin(); i != res.end(); i++) {
        if ((*i).size())
            ret.push_back((*i)[0]);
    }
    return ret;
}

vector < string > cMYSQL::select_1_row(const string & query)
{
    last_query_time=time(NULL);
    vector < string > ret;
    vector < vector < string > >res = exec(query);
    if (res.size()!=0) {
        for (unsigned int i = 0; i < res[0].size(); i++)
            ret.push_back(res[0][i]);
    }
    return ret;
}
vector < string > cMYSQL::select_1_rowQ(const QUERY & query)
{
    last_query_time=time(NULL);
    QUERY q=query;
    return select_1_row(q.prepare());
}
void cMYSQL::real_queryQ(const QUERY & query)
{
    last_query_time=time(NULL);
    QUERY q=query;
    real_query(q.prepare());
}
vector < string > cMYSQL::select_1_columnQ(const QUERY & query)
{
    last_query_time=time(NULL);
    QUERY q=query;
    return select_1_column(q.prepare());
}
string cMYSQL::select_1Q(const QUERY & query)
{
    last_query_time=time(NULL);
    QUERY q=query;
    return select_1(q.prepare());
}
vector < vector < string > >cMYSQL::execQ(const QUERY & query)
{
    last_query_time=time(NULL);
    QUERY q=query;
    return exec(q.prepare());
}
mysqlLock::mysqlLock(cMYSQL * rd, const string & q)
{

    r = rd;
    r->real_query(q);
};

mysqlLock::~mysqlLock()
{
    r->real_query("UNLOCK TABLES");
}

MYSQL *std_mysql_real_connect(MYSQL *_mysqlp)
{
    return mysql_real_connect(_mysqlp,
                              strupper(string(db_config.dbhost))=="NULL"?NULL:string(db_config.dbhost).c_str(),
                              strupper(string(db_config.dbuser))=="NULL"?NULL:string(db_config.dbuser).c_str(),
                              strupper(string(db_config.dbpasswd))=="NULL"?NULL:string(db_config.dbpasswd).c_str(),
                              strupper(string(db_config.dbname))=="NULL"?NULL:string(db_config.dbname).c_str(),
                              db_config.dbport,
                              strupper(string(db_config.dbsock))=="NULL"?NULL:string(db_config.dbsock).c_str(),
                              0);
}

cMYSQL *std_new_cMYSQL()
{
    MYSQL *_mysqlp=new MYSQL;
    _mysqlp=mysql_init(_mysqlp);
    if (!_mysqlp) {
        logErr2("---Error: mysql_init failed seems not sufficient memory");
        throw cError("mysql_init failed seems not sufficient memory");
    }
    MYSQL *res=std_mysql_real_connect(_mysqlp);
    if (!res) {
        const char *e=mysql_error(_mysqlp);
#ifdef DEBUG
        char errs[200];
        snprintf(errs,sizeof(errs)-1,"mysql_real_connect to '%s' failed [%s]  %s %d",string(db_config.dbname).c_str(),e?e:"mysql error undefined",__FL__);
        logErr2(errs);
        throw cError(errs);
#else
        char errs[200];
        snprintf(errs,sizeof(errs)-1,"mysql_real_connect to '%s' failed [%s]",string(db_config.dbname).c_str(),e?e:"mysql error undefined");
        logErr2(errs);
        throw cError(errs);
#endif
    }
    cMYSQL *mysqlp=new cMYSQL(_mysqlp);
    if (mysqlp==NULL)
    {
        string s("---Error cMYSQL *mysqlp=new cMYSQL(_mysqlp) failed");
        logErr2("%s",s.c_str());
        throw cError(s);
    }
    mysqlp->real_query("SET CHARSET cp1251");
    mysqlp->connected=true;
    return mysqlp;
    return NULL;
}				/*for inheritance only */
_mutex __dbh_set_mutex("__dbh_set_mutex");
set<cMYSQL *> __dbh_set;
vector < string > select_1_row(const string & query)
{
    st_dbh d;
    return d.dbh->select_1_row(query);
}
void real_query(const string & query)
{
    st_dbh d;
    d.dbh->real_query(query);
}
void real_queryQ(const QUERY & query)
{
    st_dbh d;
    d.dbh->real_queryQ(query);
}
vector < vector < string > >exec(const string & query)
{
    st_dbh d;
    return d.dbh->exec(query);
}
vector < vector < string > >execQ(const QUERY & query)
{
    st_dbh d;
    return d.dbh->execQ(query);
}
string select_1(const string & query)
{
    st_dbh d;
    return d.dbh->select_1(query);
}
string select_1Q(const QUERY & query)
{
    st_dbh d;
    return d.dbh->select_1Q(query);
}
vector < string > select_1_column(const string & query)
{
    st_dbh d;
    return d.dbh->select_1_column(query);
}
vector < string > select_1_columnQ(const QUERY & query)
{
    st_dbh d;
    return d.dbh->select_1_columnQ(query);
}
vector < string > select_1_rowQ(const QUERY & query)
{
    st_dbh d;
    return d.dbh->select_1_rowQ(query);
}
st_dbh::~st_dbh()
{

    if (dbh) {
        MUTEX_LOCK kall(__dbh_set_mutex);
        {
            if (dbh->error) {
                logErr2("st_dbh::~st_dbh error %s",dbh->err_str.c_str());
                delete dbh;
            }
            else __dbh_set.insert(dbh);
        }
    }
}
m_var<time_t> last_flush_time(0);
st_dbh::st_dbh():dbh(NULL)
{
    if (time(NULL)-last_flush_time.get()>60)
    {
        last_flush_time=time(NULL);
        MUTEX_LOCK kall(__dbh_set_mutex);
        vector<cMYSQL*> to_close;
        for (typeof(__dbh_set.begin()) i = __dbh_set.begin(); i != __dbh_set.end(); i++) {
            if (1) {
                dbh = (*i);
                if (dbh)
                {
                    if (time(NULL)-dbh->last_query_time>600)
                    {
                        to_close.push_back(dbh);

                    }
                }
            }
        }
        {
            for (unsigned i=0;i<to_close.size();i++)
            {
                logErr2("closed mysql connection 0x%X due timeout",to_close[i]);
                __dbh_set.erase(to_close[i]);
                delete to_close[i];
            }
        }
    }
    {
        MUTEX_LOCK kall(__dbh_set_mutex);
        if (__dbh_set.size()) {
            dbh=*__dbh_set.begin();
            __dbh_set.erase(__dbh_set.begin());
            return;
        }
    }
    dbh = std_new_cMYSQL();

    if (!dbh)
        throw cError("!dbh11");

}
cMYSQL::cMYSQL(MYSQL*m)
{
    mysql=m;
    last_query_time=time(NULL);
    error=false;
    connected=false;
    query_counter=0;
    query_total_size=0;
}
