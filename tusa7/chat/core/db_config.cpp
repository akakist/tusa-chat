#ifdef __GNUC__
#pragma implementation				// gcc: implement sql_udf.h
#endif

#include "stdafx.h"
#include <signal.h>
#include <errno.h>

#include "db_config.h"
#include "str_lib.h"
__db_config db_config;
void __db_config::load_config(const string&pn)
{

    map<string,string>	m=load_m_file(pn);



    if (m.count("dbhost"))
        dbhost=m["dbhost"];
    else
    {
        logErr2("%s: skipped 'dbhost' parameter, using default 'NULL'",pn.c_str());
        dbhost="NULL";
    }

    if (m.count("dbuser"))
        dbuser=m["dbuser"];
    else
    {
        logErr2("%s: skipped 'dbuser' parameter, using default 'NULL'",pn.c_str());
        dbuser="NULL";
    }
    if (m.count("dbpasswd"))
        dbpasswd=m["dbpasswd"];
    else
    {
        logErr2("%s: skipped 'dbpasswd' parameter, using default 'NULL'",pn.c_str());
        dbpasswd="NULL";
    }

    if (m.count("dbname"))
        dbname=m["dbname"];
    else
    {
        logErr2("%s: skipped 'dbname' parameter, using default 'NULL'",pn.c_str());
        dbname="NULL";
    }


    if (m.count("dbsock"))
        dbsock=m["dbsock"];
    else
    {
        logErr2("%s: skipped 'dbsock' parameter, using default 'NULL'",pn.c_str());
        dbsock="NULL";
    }

    if (m.count("dbport"))
        dbport=atoi(m["dbport"]);
    else
    {
        logErr2("%s: skipped 'dbport' parameter, using default '0'",pn.c_str());
        dbport=0;
    }
    if (m.count("dbstart_code"))
        dbstart_code=m["dbstart_code"];
    else
    {
        logErr2("%s: skipped 'dbstart_code' parameter, using default 'SET CHARSET cp1251'",pn.c_str());
        dbstart_code="SET CHARSET cp1251";
    }

    m.erase("dbstart_code");
    m.erase("dbport");
    m.erase("dbsock");
    m.erase("dbname");
    m.erase("dbpasswd");
    m.erase("dbuser");
    m.erase("dbhost");

    print_rest_cfg(m,pn);
}
