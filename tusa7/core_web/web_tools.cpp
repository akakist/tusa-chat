#ifdef __GNUC__
#pragma implementation				// gcc: implement sql_udf.h
#endif

#include "stdafx.h"
#include <sys/types.h>
#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#include <sys/stat.h>
#include <vector>
#include <map>
#include "tcp_server_connection.h"
#include <stdio.h>
#include "_mutex.h"
#include "web_server.h"
#include "errs.h"
#include "str_lib.h"
#include "st_stuff.h"
#include <errno.h>
#include "web_tools.h"
#include "sid_t.h"
#include "des_sid.h"

#include "server_config.h"


string get_name_of_http_code(int code);

m_var<string> SERVERNAME;
string repl_percent(const string & s)
{
    string a;
    for (unsigned int i = 0; i < s.size(); i++) {
        if (s[i] == '%') {
            if (i + 2 > s.size()) {
                break;
            }
            int c1 = u_table[s[i + 1]];
            int c2 = u_table[s[i + 2]];
            i += 2;
            if (c1 > 70 || c2 > 70) {
                continue;
            }
            if (c1 < 48 || c2 < 48) {
                continue;
            }
            if (c1 >= 48 && c1 <= 57) {
                c1 -= 48;
            }
            if (c2 >= 48 && c2 <= 57) {
                c2 -= 48;
            }
            if (c1 >= 65 && c1 <= 70) {
                c1 -= 55;
            }
            if (c2 >= 65 && c2 <= 70) {
                c2 -= 55;
            }
            a += (char) c1 *16 + c2;
        } else {
            if (s[i] == '+') {
                a += " ";
            }
            else {
                a += s[i];
            }
        }
    }
    return a;
}


string make_http_header()
{
    map<string,string> pr;
    return make_http_header(200,pr);
}

string make_http_header(const int code)
{
    map<string,string> pr;
    return make_http_header(code,pr);
}

string make_http_header(map<string,string> &pr)
{
    return make_http_header(200,pr);
}

string make_http_header(const int code,map<string,string> &pr)
{
    string a("HTTP/1.1 ");
    string res=get_name_of_http_code(code);
    a+=itostring(code)+" "+res+"\r\n";
    a+="Server: "+SERVERNAME.get()+"\r\n";
    if (pr["Connection"]=="") {
        pr["Connection"]="close";
    }
    for (map<string,string>::iterator i=pr.begin();i!=pr.end();i++) {
        a+=i->first+": "+i->second+"\r\n";
    }
    return a;
}



string make_select(const string &n,map<string,string> &p,const string &def,const string &add)
{
    string s;
    s="<SELECT name=\""+n+"\" "+add+">\r\n";
    for (map<string,string>::iterator i=p.begin();i!=p.end();i++) {
        s+="<OPTION value=";
        s+=(*i).first;
        if ((*i).first==def) {
            s+=" SELECTED";
        }
        s+=">";
        s+=(*i).second;
        s+="\r\n";
    }
    s+="</SELECT>\r\n";
    return s;
}
string make_select(const string &n,vector<pair<string,string> > &p,const string &def,const string &add)
{
    string s;
    s="<SELECT name=\""+n+"\" "+add+">\r\n";
    for (vector<pair<string,string> >::iterator  i=p.begin();i!=p.end();i++) {
        s+="<OPTION value=";
        s+=(*i).first;
        if ((*i).first==def) {
            s+=" SELECTED";
        }
        s+=">";
        s+=(*i).second;
        s+="\r\n";
    }
    s+="</SELECT>\r\n";
    return s;
}

string make_select(const string &n,map<string,string> &p,const string &def)
{
    return make_select(n,p,def,"");
}
string make_select(const string &n,vector<pair<string,string> >  &p,const string &def)
{
    return make_select(n,p,def,"");
}

string make_select(const string &n,map<string,string> &p)
{
    map<string,string> ::iterator d=p.begin();
    return make_select(n,p,(*d).first,"");
}
string make_select(const string &n,vector<pair<string,string> >  &p)
{
    vector<pair<string,string> >::iterator d=p.begin();
    return make_select(n,p,(*d).first,"");
}

string checked(const bool b)
{
    if (b) {
        return "checked";
    }
    return "";
}

string get_name_of_http_code(int code)
{
    string res;
    switch (code) {
    case 200:
        res="OK";
        break;
    case 203:
        res="Non-Authoritative Information";
        break;
    case 206:
        res="Partial Content";
        break;
    case 302:
        res="Found";
        break;
    case 303:
        res="See Other";
        break;
    case 400:
        res="Bad Request";
        break;
    case 401:
        res="Unauthorized";
        break;
    case 402:
        res="Payment Required";
        break;
    case 403:
        res="Forbidden";
        break;
    case 404:
        res="Not Found";
        break;
    case 405:
        res="Method Not Allowed";
        break;
    case 406:
        res="Not Acceptable";
        break;
    case 500:
        res="Internal Server Error";
        break;
    case 501:
        res="Not Implemented";
        break;
    case 502:
        res="Bad Gateway";
        break;
    case 503:
        res="Service Unavailable";
        break;
    case 505:
        res="HTTP Version not supported";
        break;
    default:
        res="Unknow";
        break;
        break;
    }
    return res;
}
static m_var<int> sid_cnt;
string get_new_sid(unsigned int user_map_key)
{

    return itostring(user_map_key);
#ifdef KALL
    string out = "0";
    if (!user_map_key)
        throw cError("!sid_stuff.user_map_key");
    sid_t sid;
    int sidkey=++sid_cnt;
    sid.user_map_key = sidkey;
    sid.user_map_key1= sidkey;
    out = get_des_hex_sid(sid);
    return out;
#endif
}
string RVfiles(map<string,string>&m, const char *key)
{
    return replace_vals(m,global_config.files_get(key));
}
string RVfiles(map<STRKEY,string>&m, const char *key)
{
    return replace_vals(m,global_config.files_get(key));
}
string RVfiles(const char *key)
{
    return replace_vals(global_config.files_get(key));
}

