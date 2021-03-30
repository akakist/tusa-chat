#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <map>

#include "utils.h"
#include <stdio.h>
#include "web_server.h"
#include "user.h"
#include <time.h>
#include "str_lib.h"
#include "_mutex.h"
#include "st_stuff.h"
#include <algorithm>
#include "file_set.h"
#include "levels.h"
#include "chat_colors.h"
#include "chat_def.h"
#include "server_config.h"
#include "chat_config.h"

#include "chat_globals.h"
#define MAX_WORD_SIZE	25
struct tm LOCALTIME(time_t timep);
#ifndef __CLAN
string MESL(const string &s)
{
    string r=MES(s);
    return str_replace("_","\\_",r);
}
#endif

string split_long(const string &s)
{
    vector<string> v=splitTOK(" ",s.c_str());
    string r;
    for (unsigned int i=0;i<v.size();i++) {
        if (v[i].size()>MAX_WORD_SIZE && v[i].find("http://")==-1 && v[i].find("ftp://")==-1) {
            for (unsigned int j=0;j<v[i].size();j+=MAX_WORD_SIZE) {
                r+=v[i].substr(j,MAX_WORD_SIZE)+" ";
            }
        } else {
            r+=v[i]+" ";
        }
    }
    return r;
}

string remove_maty(const string &s)
{
    vector<rxfind_data> r;
    string src=" "+s;
    string ums=" "+str_nick(src);
    find(r,chat_config.bad_words.get().c_str(),ums.c_str());
    if (r.size()==0) {
        return s;
    }
    int lpz=0;
    string a;
    for (unsigned int i=0;i<r.size();i++) {
        int pz=r[i].so-lpz-1;
        if (pz<0) pz=0;
        if (lpz<0) lpz=0;
        a+=src.substr(lpz,pz);
        string rp;
        unsigned char c='#';
        for (unsigned int z=0;z<r[i].str.size();z++) {
            if (z==0 && r[i].str[0]==' ') {
                rp+=" ";
            }
            else {
                rp+=c;
                c++;
                if (c>37) c='#';
            }
        }
        a+=rp;
        lpz=r[i].eo-1;
    }
    a+=src.substr(lpz,src.size()-lpz);
    return a.substr(1,a.size()-1);
}

bool check_maty(const string &ms)
{
    vector<rxfind_data> r;
    string ums=" "+str_nick(ms);
    find(r,chat_config.bad_words.get().c_str(),ums.c_str());
    if (r.size()>0) {
        return false;
    } else {
        return true;
    }
}


string number2text(const int i)
{
    double d=i;
    if (i<KB) {
        return itostring(i)+" b";
    }
    if (i<MB) {
        return fmt_d("%3.1f Kb",d/KB);
    }
    return fmt_d("%3.1f Mb",d/(MB));
}

string remove_tags(const string &s)
{
    string r=s;
    r=str_replace("&","&amp;",r);
    r=str_replace("<","&lt;",r);
    r=str_replace(">","&gt;",r);
    return r;
}

string ES(const string &s)
{
    string e=s;
    e=str_replace("&lt;","<",e);
    e=str_replace("&gt;",">",e);
    e=str_replace("\'","\\\'",e);
    return e;
}

string ESB(const string &s)
{
    string e=s;
    e=str_replace("\"","&quot;",e);
    e=str_replace("<","&lt;",e);
    e=str_replace(">","&gt;",e);
    return e;
}

string remove_spaces(const string &s)
{
    string r;
    for (unsigned int i=0;i<s.size();i++) {
        if (s[i]!=' ')r+=s[i];
    }
    return r;
}

string make_time(time_t t)
{
    return lzstring(t/3600)+":"+lzstring((t%3600)/60)+":"+lzstring(t%60);
}


string nick_for_sort(const string &n)
{
    string r=n;
    int z=atoi(n);
    if (z<10 && r.size()>=2) {
        if (r[0]=='0') {
            r="Î"+r.substr(1,r.size()-1);
        }
        if (r[0]=='3') {
            r="Ç"+r.substr(1,r.size()-1);
        }
    }
    for (unsigned int i=0;i<r.size();i++) {
        unsigned char c=r[i];
        if (c!='`' && c!='_' && c!='-' && c!='=' && c!='$' && c!='*' && c!='+') {
            r=r.substr(i,r.size()-i);
            break;
        }
    }
    if (z<10 && r.size()>=2) {
        if (r[0]=='0') {
            r="Î"+r.substr(1,r.size()-1);
        }
        if (r[0]=='3') {
            r="Ç"+r.substr(1,r.size()-1);
        }
    }
    return r;
}

bool check_login(const string &s)
{
    char *b="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_-=$*+\0x0";
    for (unsigned int i=0;i<s.size();i++) {
        char c=s[i];
        bool found=false;
        for (unsigned int j=0;j<strlen(b);j++) {
            if (b[j]==c) {
                found=true;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

bool check_nick(const string &s)
{
    char *b="`¸¨0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_-=$*àáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞß\0x0";
    int blen=strlen(b);
    for (unsigned int i=0;i<s.size();i++) {
        char c=s[i];
        bool found=false;
        for ( int j=0;j<blen;j++) {
            if (b[j]==c) {
                found=true;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}




string strtime_short(const time_t t)
{
    struct tm q=LOCALTIME(t);
    return lzstring(q.tm_hour)+":"+lzstring(q.tm_min);
}

string strtime(const time_t t)
{
    struct tm q=LOCALTIME(t);
    string a;
    a+=lzstring(q.tm_hour)+":";
    a+=lzstring(q.tm_min)+":";
    a+=lzstring(q.tm_sec);
    return a;
}

string get_rus_month(const int z)
{
    string r;
    switch (z)
    {
    case 1:
        r=_MSG("mon1");
        break;
    case 2:
        r=_MSG("mon2");
        break;
    case 3:
        r=_MSG("mon3");
        break;
    case 4:
        r=_MSG("mon4");
        break;
    case 5:
        r=_MSG("mon5");
        break;
    case 6:
        r=_MSG("mon6");
        break;
    case 7:
        r=_MSG("mon7");
        break;
    case 8:
        r=_MSG("mon8");
        break;
    case 9:
        r=_MSG("mon9");
        break;
    case 10:
        r=_MSG("mon10");
        break;
    case 11:
        r=_MSG("mon11");
        break;
    case 12:
        r=_MSG("mon12");
        break;
    }
    return r;
}

string get_rus_month2(const int z)
{
    string r;
    switch (z)
    {
    case 1:
        r=_MSG("monn1");
        break;
    case 2:
        r=_MSG("monn2");
        break;
    case 3:
        r=_MSG("monn3");
        break;
    case 4:
        r=_MSG("monn4");
        break;
    case 5:
        r=_MSG("monn5");
        break;
    case 6:
        r=_MSG("monn6");
        break;
    case 7:
        r=_MSG("monn7");
        break;
    case 8:
        r=_MSG("monn8");
        break;
    case 9:
        r=_MSG("monn9");
        break;
    case 10:
        r=_MSG("monn10");
        break;
    case 11:
        r=_MSG("monn11");
        break;
    case 12:
        r=_MSG("monn12");
        break;
    }
    return r;
}

string date2rus(const time_t t)
{
    struct tm q=LOCALTIME(t);
    string r;
    r=get_rus_month(q.tm_mon+1);
    return
        itostring(q.tm_mday)+" "+r+", "+itostring(q.tm_year+1900)+" "+_MSG("year1");
}

string datetime2rus_short(const time_t t)
{
    struct tm q=LOCALTIME(t);
    return itostring(q.tm_mday)+" "+get_rus_month(q.tm_mon+1)+", "+strtime_short(t);
}

string datetime2rus(const time_t t)
{
    return date2rus(t)+", "+strtime(t);
}

string date4file(const time_t t)
{
    struct tm q=LOCALTIME(t);
    return itostring(q.tm_year+1900)+"-"+lzstring(q.tm_mon+1)+"-"+lzstring(q.tm_mday);
}

string date2num(const time_t t)
{
    struct tm q=LOCALTIME(t);
    return lzstring(q.tm_mday)+"-"+lzstring(q.tm_mon+1)+"-"+itostring(q.tm_year+1900);
}

string datetime2num(const time_t t)
{
    return date2num(t)+" "+strtime(t);
}

string _nick$(const string &s,const bool priv,const PTR_getter<c_pack> &cp)
{
    map<string,string> m;
    m["~nick~"]=s;
    if (priv) {
        string nickpriv;
        {
            PGLR(c_pack, c,cp);
            {
                nickpriv=c->nickpriv;
            }
        }
        return replace_vals(m,nickpriv);
    }
    else {
        string nick;
        {
            PGLR(c_pack, c,cp);
            {
                nick=c->nick;
            }
        }
        return replace_vals(m,nick);
    }
}

string _badnick$(const string &s,const PTR_getter<c_pack> &cp)
{
    map<string,string> m;
    m["~nick~"]=s;
    string bnick;
    {
        PGLR(c_pack, c,cp);
        {
            bnick=c->bnick;
        }
    }
    return replace_vals(m,bnick);

}

int ansi_strcmp(const string &s1,const string &s2)
{
    int res=0;
    int l1=s1.size()-1;
    int l2=s2.size()-1;
    int i=0;
    while (res==0 && (i<=l1 && i<=l2)) {
        unsigned char z1=s1[i];
        unsigned char z2=s2[i];
        printf("%d-%d : %d-%d %d\n",z1,z2,l_table[z1],l_table[z2],i);
        res=z1-z2;
        i++;
    }
    if (res==0) {
        res=l1-l2;
    }
    return res;
}

static int strsrt(const string &a,const string &b)
{
    return strlower(a)<strlower(b);
}

void str_sort(vector<string> &v)
{
    sort(v.begin(),v.end(),strsrt);
}


string checked(const string &s)
{
    if (strupper(s)=="ON") {
        return "checked";
    }
    return "";
}

string checked(int z)
{
    if (z==0) {
        return "";
    }
    return "checked";
}


int chk(const string &s,int z)
{
    if (strupper(s)!="ON") {
        return z;
    }
    return 0;
}

string replace_links(const string &m)
{
    string res=m;
    {		//replace http:// & ftp://
        vector<rxfind_data> r;
        char *re=
            "http://[0-9,a-z,A-Z,_,/,.,~,;,?,=,:,&,-]+|ftp://[0-9,a-z,A-Z_,-,/,.,@,:]+";
        find(r,re,res.c_str());
        if (r.size()>0) {
            string a;
            int lpz=0;
            for (unsigned int i=0;i<r.size();i++) {
                if (r[i].str.find("\"")==-1 && r[i].str.find("'")==-1)
                {
                    a+=res.substr(lpz,r[i].so-lpz);
                    a+="<a href=\""+r[i].str+"\" target=_blank>"+r[i].str+"</a>";
                }
                lpz=r[i].eo;
            }
            a+=res.substr(lpz,res.size()-lpz);
            res=a;
        }
    }
    return res;
}



time_t get_cur_hour(time_t t)
{
    struct tm tt = LOCALTIME(t);
    time_t r = t - (tt.tm_sec + tt.tm_min * 60);
    return r;
}
time_t get_cur_day(time_t t)
{
    struct tm tt = LOCALTIME(t);
    time_t r = t - (tt.tm_sec + tt.tm_min * 60 + tt.tm_hour * 3600);
    return r;
}
time_t get_cur_week(time_t t)
{
    struct tm tt = LOCALTIME(t);
    unsigned int dweek = tt.tm_wday, dwk;
    switch (dweek) {
    case 0:
        dwk = 6;
        break;
    case 1:
        dwk = 0;
        break;
    case 2:
        dwk = 1;
        break;
    case 3:
        dwk = 2;
        break;
    case 4:
        dwk = 3;
        break;
    case 5:
        dwk = 4;
        break;
    case 6:
        dwk = 5;
        break;
    }
    time_t r = t - (tt.tm_sec + tt.tm_min * 60 + tt.tm_hour * 3600 + (dwk * 24 * 3600));
    return r;

}
time_t get_cur_month(time_t t)
{
    struct tm tt = LOCALTIME(t);
    time_t month = t - (tt.tm_sec + tt.tm_min * 60 + tt.tm_hour * 3600 + ((tt.tm_mday - 1) * 24 * 3600));
    return month;
}
time_t get_cur_year(time_t t)
{
    struct tm tt = LOCALTIME(t);
    time_t year = t - (tt.tm_sec + tt.tm_min * 60 + tt.tm_hour * 3600 + ((tt.tm_yday) * 24 * 3600));
    return year;
}
time_t get_cur_whole(time_t t)
{
    return 1;
}

vector<string> si_2_vs(const set<unsigned int> &s)
{
    vector<string> ret;
    for (set<unsigned int>::const_iterator i=s.begin();i!=s.end();i++)
        ret.push_back(itostring(*i));
    return ret;
}
set<unsigned int> vs_2_si(const vector<string>&v)
{
    set<unsigned int> ret;
    for (unsigned i=0;i<v.size();i++)
        ret.insert(atoi(v[i]));
    return ret;
}
set<unsigned int> s_2_si(const string &s)
{
    set<unsigned int> ret;
    vector<string> v=splitTOK(" \r\n\t",s);
    for (unsigned i=0;i<v.size();i++)
        ret.insert(atoi(v[i]));
    return ret;
}
string si_2_s(const set<unsigned int> &s)
{
    vector<string> ret;
    for (set<unsigned int>::const_iterator i=s.begin();i!=s.end();i++)
        ret.push_back(itostring(*i));
    return join(" ", ret);
}
void add_to_string_set(string &stringset,unsigned int v)
{
    vector<string>vv=splitTOK(" \r\n\t",stringset);
    set<unsigned int >s;
    for (unsigned i=0;i<vv.size();i++)
    {
        unsigned int k=atoi(vv[i]);
        if (k)
            s.insert(k);
    }
    if (v)s.insert(v);
    string out;
    {
        for (set<unsigned int >::iterator i=s.begin();i!=s.end();i++)
        {
            out+=itostring(*i)+" ";
        }
    }
    stringset=out;

}
void remove_from_string_set(string &stringset,unsigned int v)
{
    vector<string>vv=splitTOK(" \r\n\t",stringset);
    set<unsigned int >s;
    for (unsigned i=0;i<vv.size();i++)
    {
        unsigned int k=atoi(vv[i]);
        if (k)
            s.insert(k);
    }
    if (v)s.erase(v);
    string out;
    {
        for (set<unsigned int >::iterator i=s.begin();i!=s.end();i++)
        {
            out+=itostring(*i)+" ";
        }
    }
    stringset=out;

}
string add_to_string_set(const string &stringset,const vector<string> &v)
{
    vector<string>vv=splitTOK(" \r\n\t",stringset);
    for (unsigned i=0;i<v.size();i++)
        vv.push_back(v[i]);
    set<unsigned int >s;
    {
        for (unsigned i=0;i<vv.size();i++)
            s.insert(atoi(vv[i]));
    }
    string out;
    {
        for (set<unsigned int >::iterator i=s.begin();i!=s.end();i++)
        {
            out+=itostring(*i)+" ";
        }
    }
    return out;
}
string remove_from_string_set(const string &stringset,const vector<string> &v)
{
    vector<string>vv=splitTOK(" \r\n\t",stringset);
    set<unsigned int >s;
    for (unsigned i=0;i<vv.size();i++)
        s.insert(atoi(vv[i]));
    {
        for (unsigned i=0;i<v.size();i++)
            s.erase(atoi(v[i]));
    }

    string out;
    {
        for (set<unsigned int >::iterator i=s.begin();i!=s.end();i++)
        {
            out+=itostring(*i)+" ";
        }
    }
    return out;
}
map<unsigned int,double> s_2_mid(const string &s)
{

    map<unsigned int,double> st;
    vector<string> vv=splitTOK(" ",s);
    for (unsigned j=0;j<vv.size();)
    {
        unsigned int first;
        double second;
        if (j<vv.size())
        {
            first=atoi(vv[j]);
            j++;
            if (j<vv.size())
            {
                second=atof(vv[j].c_str());
                j++;
                st[first]=second;
            }
        }
    }
    return st;
}
string get_f22(double dd)
{
    char s[100];
    snprintf(s, sizeof(s) - 1, "%2.2f", dd);
    return s;

}

string redirect()
{

    return "<html><script>window.top.location='/relogin';</script>";
}
