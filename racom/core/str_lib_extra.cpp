#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <fstream>
#include <iostream>

#include <sys/types.h>
#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#else
#include "wrappers.h"
#endif
#include <vector>
#include <map>
#include <map>
#include <stdio.h>
#include "_mutex.h"
#include "errs.h"
#include "str_lib.h"
#include "st_stuff.h"
#include <errno.h>
#include <regex.h>
#ifndef WIN32
#endif
#include <sys/types.h>
#ifndef WIN32
#include <sys/stat.h>
#endif
#include <stdio.h>
#include <vector>
#include <list>
#include "str_lib.h"
#ifndef WIN32
#include <sys/errno.h>
#endif
#include "errs.h"
#include <cerrno>
#include "str_lib.h"
#include <openssl/md5.h>
#include <zlib.h>
#include "st_stuff.h"

#include <cstdarg>
#include "st_stream_str.h"
#ifdef WIN32
#define snprintf _snprintf
#endif
int load_1_file(string & res, const string & fn);//-1 err

string MD5(const string & s)
{

    unsigned char p[MD5_DIGEST_LENGTH + 10];
    ::MD5((unsigned char *)s.data(), s.size(), (unsigned char *)p);
    string ret((char *)p, MD5_DIGEST_LENGTH);
    return ret;
}
_mutex findMX_("findMX_");

void find(std::vector < rxfind_data > &res, const char *regexp, const char *buffer)
{


    int err;
    regex_t re;
    err = regcomp(&re, regexp, REG_EXTENDED);
    regmatch_t pm[10];
    ::memset(pm, 0, sizeof(regmatch_t));
    if (err) {
        char erbuf[111];
        regerror(err, &re, erbuf, sizeof(erbuf));
        throw cError((std::string)"regex "+regexp+": "+erbuf);
        return;
    }
    size_t lastpos = 0;
    while (!regexec(&re, buffer + lastpos, 10, pm, 0)) {
        const char *s = buffer + lastpos;
        size_t lpos=lastpos;
        for (int i = 0; i < 10; i++) {
            if (pm[i].rm_so != -1) {
                size_t matchlen = pm[i].rm_eo - pm[i].rm_so;
                std::string fs(&s[pm[i].rm_so], matchlen);
                rxfind_data fd;
                fd.str = fs;
                fd.so = pm[i].rm_so + lastpos;
                fd.eo = pm[i].rm_eo + lastpos;
                res.push_back(fd);
                lpos=pm[i].rm_eo;
            } else break;
        }
        lastpos += lpos;
    }
    regfree(&re);
}

/*void find(vector < rxfind_data > &res, const char *regexp, const char *buffer)
{

M_LOCK(findMX_);
	int err;
	boost::regex_t re;
	err = boost::regcomp(&re, regexp, boost::REG_EXTENDED);
	boost::regmatch_t pm[10];
	::memset(pm, 0, sizeof(boost::regmatch_t));
	if (err) {
		char erbuf[111];
		boost::regerror(err, &re, erbuf, sizeof(erbuf));
		throw cError((string)"regex "+regexp+": "+erbuf);
		return;
	}
	int lastpos = 0;
	while (!boost::regexec(&re, buffer + lastpos, 10, pm, 0)) {
		const char *s = buffer + lastpos;
		int lpos=lastpos;
		for (int i = 0; i < 10; i++) {
			if (pm[i].rm_so != -1) {
				int matchlen = pm[i].rm_eo - pm[i].rm_so;
				string fs(&s[pm[i].rm_so], matchlen);
				rxfind_data fd;
				fd.str = fs;
				fd.so = pm[i].rm_so + lastpos;
				fd.eo = pm[i].rm_eo + lastpos;
				res.push_back(fd);
				lpos=pm[i].rm_eo;
			}else break;
		}
		lastpos += lpos;
	}
	boost::regfree(&re);
}
*/
string replace_vals(const string &src)
{
    map<string,string> m;
    return replace_vals(m,src);
}
string replace_vals(map<string,string> &p, const string &src)
{
    if (!p.size())return src;
    string s;
    map<string,string>::iterator it=p.begin();
    s+=it->first;
    it++;
    /*SER: ERROR zdes mozhet byt esli map pustoj*/
    for (/*it*/;it!=p.end();it++) {
        s+="|"+(*it).first;
    }
    vector<rxfind_data> r;
    string a;
    ::find(r,s.c_str(),src.c_str());
    int lpz=0;
    for (unsigned int i=0;i<r.size();i++) {
        a+=src.substr(lpz,r[i].so-lpz);
        a+=p[r[i].str];
        lpz=r[i].eo;
    }
    a+=src.substr(lpz,src.size()-lpz);
    return a;
}

string replace_vals(map<STRKEY ,string> &p, const string &src)
{
    if (!p.size())return src;
    string s;
    map<STRKEY ,string> ::iterator it=p.begin();
    s+=it->first.p;
    it++;
    /*SER: ERROR zdes mozhet byt esli map pustoj*/
    for (/*it*/;it!=p.end();it++) {
        s+=(string)"|"+(*it).first.p;
    }
    vector<rxfind_data> r;
    string a;
    ::find(r,s.c_str(),src.c_str());
    int lpz=0;
    for (unsigned int i=0;i<r.size();i++) {
        a+=src.substr(lpz,r[i].so-lpz);
        char *sss=(char*)r[i].str.c_str();
        if (p.count(sss))
            a+=p.find(sss)->second;
        lpz=r[i].eo;
    }
    a+=src.substr(lpz,src.size()-lpz);
    return a;
}
string replace_re_vals(const map<string,string> &p, const string &__src)
{
    if (!p.size())return __src;
    string worksrc=__src;
    for (map<string,string>::const_iterator i=p.begin();i!=p.end();i++)
    {
        vector<rxfind_data> r;
        ::find(r,i->first.c_str(),worksrc.c_str());
        string a;
        int lpz=0;
        for (unsigned int j=0;j<r.size();j++)
        {

            a+=worksrc.substr(lpz,r[j].so-lpz);
            a+=i->second;
            lpz=r[j].eo;
        }
        a+=worksrc.substr(lpz,worksrc.size()-lpz);
        worksrc=a;

    }

    return worksrc;
}
string str_replace(const string &s,const string &sr,const string &src)
{
    vector<rxfind_data> r;
    ::find(r,s.c_str(),src.c_str());
    int lpz=0;
    string a;
    for (unsigned int i=0;i<r.size();i++) {
        int eo=r[i].so-lpz;
        a+=src.substr(lpz,eo);
        a+=sr;
        lpz=r[i].eo;
    }
    int eo=src.size()-lpz;
    a+=src.substr(lpz,eo);
    return a;
}
#ifndef WIN32
string z_compress(const string& s)
{
    st_stream_str str;
    st_malloc out(s.size()*2+12);
    unsigned long outlen=s.size()*2+12;
    int err=compress((unsigned char*)out.buf,&outlen,(unsigned char*)s.data(),s.size());
    if (err==Z_OK)
    {
        str<=itostring(s.size())<=string ((char*)out.buf,(int)outlen);
        return str.container;
    }
    else
        return "";
}
string z_expand(const string& s)
{
    st_stream_str str;
    str.container=s;
    str.inidx=0;
    string l;
    str>=l;
    string zbody;
    str>=zbody;
    int len=atoi(l.c_str());
    st_malloc out(len+100);
    unsigned long outlen=len+100;
    int err=uncompress((unsigned char*)out.buf,&outlen,(unsigned char*)zbody.data(),zbody.size());
    if (err==Z_OK)
    {
        return string ((char*)out.buf,(int)outlen);
    }
    else
        return "";
}
#endif
