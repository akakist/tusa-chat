#ifdef __GNUC__
#pragma implementation				// gcc: implement sql_udf.h
#endif
#include "stdafx.h"

#include "db_var.h"
#include "copy_file.h"
#include "file_set.h"
#include <sys/stat.h>
#include "wrappers.h"
#ifndef WIN32
#include <gdbm.h>
#endif
#include "M_MAP.h"
#include "server_config.h"

#include "mysql_extens.h"
db_row::db_row():
        id(0),__last_update_time(time(NULL)),base_container("db_row")
{
}


M_SET<string> erased_gdbms;
M_SET<string> checked_wfn_gdbms;
#ifndef WIN32
class gdbm_myfile: public base_container
{
private:
    string filename;

    int open_mode;
    GDBM_FILE f;
public:
    string get(const string & key);
    void erase(const string & key);
    void put(const string & key, const string &val);
    void sync() {
        if (f)gdbm_sync(f);
    }
    gdbm_myfile(const string& pn, bool erase_old):filename(string(global_config.var_dir)+"/db/"+pn),open_mode(-1),f(0),base_container("gdbm_myfile") {

        if (erase_old)
        {
            if (!erased_gdbms.count(filename))
            {
                unlink(filename.c_str());
                check_path_wfn(filename);
                erased_gdbms.insert(filename);
            }
        }
        if (checked_wfn_gdbms.count(filename))
        {
            check_path_wfn(filename);
            checked_wfn_gdbms.insert(filename);
        }
    }
};

map<string,PTR_getter<gdbm_myfile> > gdbm_tables;
_mutex gdbm_tablesMX("gdbm_tablesMX");
#endif
map < string /*table name */ , _mutex * >table_mutexes;
_mutex table_mutexesMX("table_mutexesMX");

_mutex* select_table_mutex(const string& tbname)
{
    _mutex *m = NULL;
    {
        M_LOCK(table_mutexesMX);
        map < string /*table name */ , _mutex * >::iterator i = table_mutexes.find(tbname);
        if (i == table_mutexes.end()) {
            m = new _mutex("mutex for table_mutexes");
            if (!m)
                throw cError("!m" );
            table_mutexes.insert(pair < string , _mutex * >(tbname, m));
        }
        else
            m = i->second;
    }
    if (!m)
        throw cError("!m " );
    return m;
}

db_id_type db_map_on_id0(const string & tbname, DBMAP_DBTYPE dbtype, DBMAP_IDTYPE idtype)
{


    if (idtype == DBMAP_REFID)
        throw cError(tbname+" idtype==DBMAP_REFID " );
#ifndef __CLAN
    if (dbtype==DBMAP_GDBM)
    {
        string __id=db_get(tbname,"IDGEN",false);
        unsigned int id=0;
        if (__id.size()==sizeof(unsigned int))
        {
            memcpy(&id,__id.data(),sizeof(unsigned int));
        }
        id++;
        db_put(tbname,"IDGEN",string((char*)&id,sizeof(unsigned int)), false);
    }
    else if (dbtype == DBMAP_MYSQL) {
        st_dbh d;
        string s = "insert into " + tbname + " () values ()";
        d.dbh->real_query(s);
        vector < string > v = d.dbh->select_1_row("select LAST_INSERT_ID()");
        if (v.size() == 0) {
            logErr2("last_insert_id failed");
            throw cError(tbname+" last_insert_id failed " );
        }
        unsigned int _id = atoi(v[0]);
        if (_id == 0) {
            logErr2("last_insert_id returned 0");
            throw cError(tbname+" last_insert_id returned 0 " );
        }
        return _id;
    }
    else if (dbtype == DBMAP_PROFILE) {
        throw cError(tbname+" idtype==DBMAP_PROFILE " );
    }
    else
        throw cError(tbname+" unknown type DB_MAP" );
    throw cError(tbname+" must not access here" );
#else
    throw cError(tbname+" must not access here" );
#endif
    return 0;
}
void db_map_on_idN_not_exists(const string &tbname, const db_id_type &id,DBMAP_DBTYPE dbtype,DBMAP_IDTYPE idtype)
{
    if (idtype==DBMAP_AUTOID) throw cError(tbname+" idtype==DBMAP_AUTOID ");
#ifndef __CLAN
    if (dbtype==DBMAP_MYSQL)
    {
        if (id.itype!=db_id_type::TUINT) throw cError("id.itype!=db_id_type::TUINT");
        st_dbh d;
        string s="insert into " + tbname + " (refid) values ("+itostring(id.as_int())+")";
        d.dbh->real_query(s);
    }
#endif
    else if (dbtype==DBMAP_GDBM) {}
    else if (dbtype==DBMAP_PROFILE) {}
    else throw cError(tbname+" unknown dbtype ");
}
db_map_base::db_map_base(const string &tablen,DBMAP_DBTYPE _dbmap_dbtype,DBMAP_IDTYPE _dbmap_idtype):
        table_name(tablen),
        dbmap_dbtype(_dbmap_dbtype),
        dbmap_idtype(_dbmap_idtype),Mutex("db_map_base")
{
}


#ifndef WIN32
string gdbm_myfile::get(const string & key)
{

    string ret;
    int flag;

    if (f&&(open_mode == GDBM_NEWDB ||open_mode == GDBM_WRITER)) {
        gdbm_close(f);
        f = 0;
        open_mode=-1;
    }

    if (open_mode == -1) {
        flag = GDBM_READER;
        f = gdbm_open((char*)filename.c_str(), 512, flag, 0644, NULL);
        if (f)
        {
            open_mode = GDBM_READER;
        }
        else
        {
#ifndef WIN32
            logErr2("cannot open gdbm for reading %s gdbm_errno=%d %s ",filename.c_str(),gdbm_errno,"");
#else
            logErr2("cannot open gdbm for reading %s %s ",filename.c_str(),"");
#endif
        }
    }
    if (f) {
        datum k;
        datum v;
        k.dptr = (char *)key.data();
        k.dsize = key.size();
        v = gdbm_fetch(f, k);
        if (v.dptr) {
            ret = string((char *)v.dptr, v.dsize);
            free((void *)v.dptr);
        }
    }
    if (f)
        gdbm_close(f);
    f = 0;
    open_mode=-1;

    return ret;
}
#endif
#ifndef WIN32
void gdbm_myfile::erase(const string & key)
{
    int flag;

    if (f&&(open_mode == GDBM_NEWDB ||open_mode == GDBM_WRITER)) {
        gdbm_close(f);
        f = 0;
        open_mode=-1;
    }

    if (open_mode == -1) {
        flag = GDBM_READER;
        f = gdbm_open((char*)filename.c_str(), 512, flag, 0644, NULL);
        if (f)
        {
            open_mode = GDBM_READER;
        }
        else
        {
#ifndef WIN32
            logErr2("cannot open gdbm for reading %s gdbm_errno=%d %s ",filename.c_str(),gdbm_errno,"");
#else
            logErr2("cannot open gdbm for reading %s %s ",filename.c_str(),"");
#endif
        }
    }
    if (f) {
        datum k;
        k.dptr = (char *)key.data();
        k.dsize = key.size();
        gdbm_delete(f, k);
    }
    if (f)
        gdbm_close(f);
    f = 0;
    open_mode=-1;
}
#endif
#ifndef WIN32
void gdbm_myfile::put(const string & key, const string & val)
{
    if (f)
    {
        gdbm_close(f);
        f = 0;
        open_mode=-1;
        //logErr2("gdbm_close(f);		f = 0;		open_mode=-1;");
    }

    int flag;
    if (f&& open_mode == GDBM_READER) {
        gdbm_close(f);
        f = 0;
        open_mode=-1;
    }
    if (open_mode == -1) {
        flag=GDBM_WRCREAT;
        f = gdbm_open((char*)filename.c_str(), 512, flag, 0666, NULL);
        if (f)
        {
            open_mode = flag;
        }
        else {
#ifndef WIN32
            logErr2("cannot open gdbm file for writing %s gdbm_errno=%d",filename.c_str(),gdbm_errno);
#else
            logErr2("cannot open gdbm file for writing %s ",filename.c_str());
#endif
        }
    }
    if (f) {
        datum k;
        datum v;
        k.dptr = (char *)key.data();
        k.dsize = key.size();
        v.dptr = (char *)val.data();
        v.dsize = val.size();
        gdbm_store(f, k, v, GDBM_REPLACE);
    }
    else logErr2("!f %s","");
    if (f)gdbm_close(f);
    f = 0;
    open_mode=-1;


}
#endif
#ifndef WIN32
void db_put(const string & tn, const string& key, const string& val, bool erase_old)
{
    PTR_getter<gdbm_myfile> p(NULL);
    {
        M_LOCK(gdbm_tablesMX);
        if (gdbm_tables.find(tn)==gdbm_tables.end())
        {
            gdbm_tables.insert(pair<string,PTR_getter<gdbm_myfile> >(tn,new gdbm_myfile(tn,erase_old)));
        }
        typeof(gdbm_tables.find(tn)) i=gdbm_tables.find(tn);
        if (i==gdbm_tables.end())throw cError("i==gdbm_tables.end() ");
        p=i->second;
    }
    if (p)
    {
        PTR_getter_lock_write<gdbm_myfile> b(p);
        b->put(key,val);
    }
    else
        logErr2("!p %s","");
}
#endif
#ifndef WIN32
string db_get(const string & tn, const string& key, bool erase_old)
{

    PTR_getter<gdbm_myfile> p(NULL);
    {
        M_LOCK(gdbm_tablesMX);
        if (gdbm_tables.find(tn)==gdbm_tables.end())
        {
            gdbm_tables.insert(pair<string,PTR_getter<gdbm_myfile> >(tn,new gdbm_myfile(tn, erase_old)));
        }
        typeof(gdbm_tables.find(tn))i=gdbm_tables.find(tn);
        if (i==gdbm_tables.end())throw cError("i==gdbm_tables.end() ");
        p=i->second;
    }
    if (p)
    {
        PGLW(gdbm_myfile, b,p);
        return b->get(key);
    }
    else
        logErr2("!p %s","");
    return "";

}
#endif
#ifndef WIN32
void db_erase(const string & tn, const string& key, bool erase_old)
{

    PTR_getter<gdbm_myfile> p(NULL);
    {
        M_LOCK(gdbm_tablesMX);
        if (gdbm_tables.find(tn)==gdbm_tables.end())
        {
            gdbm_tables.insert(pair<string,PTR_getter<gdbm_myfile> >(tn,new gdbm_myfile(tn, erase_old)));
        }
        typeof(gdbm_tables.find(tn))i=gdbm_tables.find(tn);
        if (i==gdbm_tables.end())throw cError("i==gdbm_tables.end() ");
        p=i->second;
    }
    if (p)
    {
        PGLW(gdbm_myfile, b,p);
        b->erase(key);
        return;
    }
    else
        logErr2("!p %s","");
    return ;

}
#endif
unsigned int db_id_type::as_int() const
{
    if (itype != TUINT)
        throw cError("itype!=TUINT" );
    unsigned int n;
    if (id.size() != sizeof(n))
        throw cError("id.size()!=sizeof(n)" );
    memcpy(&n, id.data(), sizeof(n));
    return n;
}
string db_id_type::as_string() const
{
    return id;
}

db_id_type::db_id_type( int n)
{
    int nl=0;
    itype = TUINT;
    if (n)
        id.assign((char *)&n, sizeof(n));
    else
        id.assign((char *)&nl, sizeof(nl));
//		id = "";
}
db_id_type::db_id_type( long n)
{
    long nl=0;
    itype = TUINT;
    if (n)
        id.assign((char *)&n, sizeof(n));
    else
        id.assign((char *)&nl, sizeof(nl));
//		id = "";
}
db_id_type::db_id_type(unsigned int n)
{
    itype = TUINT;
    if (n)
        id.assign((char *)&n, sizeof(n));
    else
        id.assign((char *)&n, sizeof(n));
//		id = "";
}
db_id_type::db_id_type(unsigned long n)
{
    itype = TUINT;
    if (n)
        id.assign((char *)&n, sizeof(n));
    else
        id.assign((char *)&n, sizeof(n));
//		id = "";
}
db_id_type::db_id_type(const string & n)
        : id(n), itype(TSTRING)
{
}
db_id_type::db_id_type(IDT t):itype(t)
{
}

db_id_type::db_id_type(const DB_id &n)
{
    itype = TUINT;
    id.assign((char *)&n, sizeof(n));
}
#ifdef __CLAN
void exec_sql(const string &s)
{
}
#else
void exec_sql(const string &s)
{
    st_dbh d;
    d.dbh->real_query(s);

}
#endif
