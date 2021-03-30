#include "stdafx.h"
#include "_mutex.h"
#include <string>
#include <vector>
#include <stdio.h>
#include "_QUERY.h"
#include "mysql_extens.h"
#include "str_lib.h"


string QUERY::prepare()
{
    string first;
    *this>>first;
    string result;
    for (unsigned int i=0;i<first.size();i++)
    {
        if (first[i]!='?') result+=first[i];
        else
        {
            string s;
            *this>>s;
            result+=MES(s);
        }
    }
    return result;
}
QUERY::QUERY()
{
}
QUERY::QUERY(const char* s)
{
    container.push_back(s);
}
QUERY::QUERY(const string &s)
{
    container.push_back(s);
}
QUERY& QUERY::operator>>(string &s)
{
    if (container.size())
    {
        s=*container.begin();
        container.erase(container.begin());
        return *this;
    }
    s="";
    return *this;
}

QUERY & QUERY::operator << (const string & s)
{
    container.push_back(s);
    return *this;
}
QUERY & QUERY::operator << (const char *s)
{
    container.push_back(s);
    return *this;
}
QUERY & QUERY::operator << (unsigned long s)
{
    container.push_back(luitostring(s));
    return *this;
}
QUERY & QUERY::operator << (unsigned int s)
{
    container.push_back(itostring(s));
    return *this;
}
QUERY & QUERY::operator << (int s)
{
    container.push_back(itostring(s));
    return *this;
}
QUERY & QUERY::operator << (double d)
{
    char ss[50];
    snprintf(ss,sizeof(ss)-1,"%f",d);
    container.push_back(ss);
    return *this;
}
QUERY & QUERY::operator << (bool s)
{
    container.push_back(itostring(s));
    return *this;
}
QUERY & QUERY::operator << (time_t s)
{
    container.push_back(itostring(s));
    return *this;
}
QUERY & QUERY::operator << (const set < unsigned int >&s /*setime_t d */ )
{
    vector<string>v;
    for (typeof(s.begin()) i=s.begin();i!=s.end();i++)
    {
        v.push_back(itostring(*i));
    }
    container.push_back(join(" ",v));
    return *this;
}
QUERY & QUERY::operator << (const map < unsigned int, double >&s)
{
    vector<string>v;
    for (typeof(s.begin()) i=s.begin();i!=s.end();i++)
    {
        v.push_back(itostring(i->first));
        char s[100];
        snprintf(s,sizeof(s)-1,"%f",i->second);
        v.push_back(s);
    }
    container.push_back(join(" ",v));
    return *this;
}
st_sqls::st_sqls()
{

}
st_sqls::~st_sqls()
{
    st_dbh d;
    for (unsigned i=0;i<v.size();i++)
    {
        d.dbh->real_query(v[i]);
    }

}
void st_sqls::push_back(QUERY&q)
{
    v.push_back(q.prepare());
}
