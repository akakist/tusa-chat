#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <sys/stat.h>
#include <regex.h>
#include <unistd.h>
#include <set>
//#include "str_lib.h"
using namespace std;
vector<string> inc_dirs;
vector<string> targets;
vector<string> objs;
struct _rxfind_data{
	string str;
	int so;
	int eo;
};
map <string, string> conf;
string exename(const string &s);
inline void find(vector < _rxfind_data > &res, const char *regexp, const char *buffer);
string replace_vals(const string& regex,const string& repl, const string &src)
{
    string s;
    vector<_rxfind_data> r;
	string a;
    find(r,regex.c_str(),src.c_str());
	int lpz=0;
    for(unsigned int i=0;i<r.size();i++){
		a+=src.substr(lpz,r[i].so-lpz);
		a+=repl;
		lpz=r[i].eo;
    }
	a+=src.substr(lpz,src.size()-lpz);
	return a;
}
string joinexe(const string &pattern, const vector<string> & arr)
{
    string ret;
    if (arr.size() > 1)
    {
                unsigned int i;
                for (i = 0; i < arr.size() - 1; i++)
                        ret += exename(arr[i]) + pattern;
                ret += exename(arr[arr.size() - 1]);
    }
    else if(arr.size()==1)
    {
	ret+=exename(arr[0]);
    }
    return ret;
}

inline void find(vector < _rxfind_data > &res, const char *regexp, const char *buffer)
{
	int err;
	regex_t re;
	err = regcomp(&re, regexp, REG_EXTENDED);
	regmatch_t pm[10];
	memset(pm, 0, sizeof(regmatch_t));
	if (err) {
		char erbuf[111];
		regerror(err, &re, erbuf, sizeof(erbuf));
		printf ("%s ",((string)"regex "+regexp+": "+erbuf).c_str());
		return;
	}
	int lastpos = 0;
	while (!regexec(&re, buffer + lastpos, 10, pm, 0)) {
		const char *s = buffer + lastpos;
		int lpos=lastpos;
		for (int i = 0; i < 10; i++) {
			if (pm[i].rm_so != -1) {
				int matchlen = pm[i].rm_eo - pm[i].rm_so;
				string fs(&s[pm[i].rm_so], matchlen);
				_rxfind_data fd;
				fd.str = fs;
				fd.so = pm[i].rm_so + lastpos;
				fd.eo = pm[i].rm_eo + lastpos;
				res.push_back(fd);
				lpos=pm[i].rm_eo;
			}else break;
		}
		lastpos += lpos;
	}
	regfree(&re);
}

vector < string > splitTOK(const char *seps, const char *src)
{
	vector < string > res;
	char *s = strdup((char *) src);
	char *token = strtok(s, seps);
	while (token != NULL) {
		res.push_back(token);
		token = strtok(NULL, seps);
	}
	free(s);
	return res;
}

void read_config(int argc, char *argv[])
{
	FILE *f = fopen(argv[1], "rb");
	if(f==NULL){printf("Failled open file %s\n",argv[1]);exit(1);}
	struct stat st;
	stat(argv[1],&st);
	char *buf=(char*)malloc(st.st_size+10);
	fread(buf,1,st.st_size,f);
	fclose(f);
	string s(buf,st.st_size);
	char last='0';
	map <string,string> mumu;
	string susu=replace_vals("\\\\[ \t]*\n","",s);
	s=susu;
/*	FILE *ff=fopen("/tmp/kaka.xxx","wb");
	fwrite(s.c_str(),1,s.size(),ff);
	fclose(ff);*/
	vector <string> lines=splitTOK("\n",s.c_str());
	for(int i=0;i<lines.size();i++)
	{
		vector<string> v;//=splitTOK("=",lines[i].c_str());
		int pos=lines[i].find("=",0);
		if(pos==-1)continue;
		v.push_back(lines[i].substr(0,pos));
		v.push_back(lines[i].substr(pos+1,lines[i].size()));
		//printf("%s-->%s\n",v[0].c_str(),v[1].c_str());

		if(v.size()==2)
		{
			if(v[0]=="INC_DIRS")
			 inc_dirs=splitTOK(" \t",v[1].c_str());
			else if(v[0]=="TARGETS")
			 targets=splitTOK(" \t",v[1].c_str());
			else if(v[0]=="OBJS")
			 objs=splitTOK(" \t",v[1].c_str());
			else conf[v[0]]=v[1];
			 
		}
	}
	for (int i=0;i<inc_dirs.size();i++)
	{
		conf["CFLAGS"]+=" -I"+inc_dirs[i];
	}
}

vector <string> scan_file(const string &file)
{
	vector <string> ret;
	FILE *f = fopen(file.c_str(), "rb");
	if(f==NULL){printf("error open file: \"%s\"",file.c_str());return ret;}
	string s;
	while (!feof(f)) {
		char c=getc(f);
		if(!feof(f))
		s += c;
	}
	fclose(f);
	vector <string> lines=splitTOK("\n",s.c_str());
	for(int i=0;i<lines.size();i++)
	{
		if(lines[i].size()<5)continue;
		vector <_rxfind_data> v;
		v.clear();
		find(v, "[\t ]*#[\t ]*include[\t ]*[\"]([0-9A-Za-z_.]+)[\"]",lines[i].c_str());
		if(v.size())
		{
			vector <string> vv=splitTOK("\"",v[0].str.c_str());
			if(vv.size()==2)
			ret.push_back(vv[1]);
			
		}
	}
	return ret;	
}
map <string,string> srcfiles;
string find_srcfile(const string& s)
{
	if(srcfiles.find(s)!=srcfiles.end())
	return srcfiles[s];
	
	for(int i=0;i<inc_dirs.size();i++)
	{
		string pn=inc_dirs[i]+"/"+s;
		struct stat st;
		if(!stat(pn.c_str(),&st))
		{
			srcfiles[s]=pn;
			return pn;
		}
		else{}
	}
	return "";
}
string objname(const string &s)
{
	vector <string> v=splitTOK(".",s.c_str());
	if(v.size()==2)
	{
		return conf["OBJDIR"]+"/"+v[0]+".o";
	}
	return "";
}
string exename(const string &s)
{
	vector <string> v=splitTOK(".",s.c_str());
	if(v.size()==2)
	{
		return v[0];
	}
	return "";
}
vector <string> find_deps(const string &s/*only filename*/)
{
	
}
int main(int argc, char **argv)
{
  if(argc!=2)
  {
	printf("crmak -- create makefile\nusage: crmak makef.i\nwhere makef.i have format:
OBJDIR=/tmp/svr
CFLAGS= -Wall  -I/usr/include/mysql  -c   \\ 
	  -I/usr/local/ssl/include -I../include 
LIBS=/usr/lib/libssl.so.0 /usr/lib/libcrypto.so.0\\ 
	 /usr/lib/libmysqlclient.so -lpthread -lgdbm
LIBNAME=libpr.a
INC_DIRS= . ./lib ./http ./udp ./cgi ../chatserver 
TARGETS=msg_server_main.c projektor_main.c
OBJS=st_stuff.c st_rsa.c \\ 
	storage.c errs.c str_lib.c\\ 
	 packets.c trans.c c_conn.c\\ 
	  wrappers.c  m_containers.c _string.c my_gdbm.c copy_file_common.c
");
	exit(1);
  }
  
  
	read_config(argc, argv);
	vector <string> OBJS=objs;
	for(int i=0;i<targets.size();i++)
	{
		objs.push_back(targets[i]);
	}
	map < string, vector < string > >m;
	for(int i=0;i<objs.size();i++)
	{
		string pn=find_srcfile(objs[i]);
		if(pn.size()>3)m[objs[i]]=scan_file(pn);
	}
	for (map < string, vector < string > >::iterator i = m.begin(); i != m.end(); i++) 
	{
		for(int j=0;j<i->second.size();j++)
		{
			if(m.find(i->second[j])==m.end())
			{
				string pn=find_srcfile(i->second[j]);
				if(pn.size())m[i->second[j]]=scan_file(pn);
			}
		}
	}
	map < string, map < string, int > >mm;
	for (map < string, vector < string > >::iterator i = m.begin(); i != m.end(); i++) {
		vector < string > kk;
		for (int j = 0; j < (*i).second.size(); j++) {
			string df = (*i).second[j];
			mm[(*i).first][df] = 100;
			for (int k = 0; k < m[df].size(); k++) {
				mm[(*i).first][m[df][k]] = 100;
			}
		}
	}
	string deps;
	for(int i=0;i<objs.size();i++)
	{
		if(objs[i].size()<3)continue;
		deps+="\n"+objname(objs[i])+": "+find_srcfile(objs[i])+" ";
		map<string, int> mv=mm[objs[i]];
		for(map<string, int>::iterator j=mv.begin();j!=mv.end();j++)
		{
			deps+=" "+find_srcfile(j->first);
		}
		deps+=" ./Makefile ";
		string cmd=(string)"\n\t c++ "+conf["CFLAGS"]+" "+find_srcfile(objs[i])+" -o "+objname(objs[i]);
		deps+=cmd+"\n";
//		/*string*/ cmd=(string)"\n\t ar -r "+conf["OBJDIR"]+"/"+conf["LIBNAME"]+ " "+objname(objs[i]);
//		deps+=cmd+"\n";
	}
	
	string libpr;
	libpr+="\n"+conf["OBJDIR"]+"/"+conf["LIBNAME"]+": ";
	for(int i=0;i<OBJS.size();i++)
	{
		libpr+=objname(OBJS[i])+" ";
	}
	libpr+="\n";
	libpr+="\t\t ar -r "+conf["OBJDIR"]+"/"+conf["LIBNAME"]+" ";
	for(int i=0;i<OBJS.size();i++)
	{
		libpr+=objname(OBJS[i])+" ";
	}
	libpr+="\n";
	string all;
	all+="all: "+conf["OBJDIR"]+"/"+conf["LIBNAME"]+" ";
	for(int i=0;i<targets.size();i++)
	{
		all+=exename(targets[i])+" ";
	}
	all+="\n";
	printf("%s",all.c_str());
	string mkall;
	for(int i=0;i<targets.size();i++)
	{
		mkall+=exename(targets[i])+": "+conf["OBJDIR"]+"/"+conf["LIBNAME"]+" "+objname(targets[i])+"\n";
		mkall+="\t\tc++ "+objname(targets[i])+" -o "+exename(targets[i])+" "+conf["OBJDIR"]+"/"+conf["LIBNAME"]+" "+conf["LIBS"]+"\n";
		mkall+="\t\t strip "+exename(targets[i])+" \n";
	}
	mkall+="\n";
	printf("%s",mkall.c_str());
	printf("%s",libpr.c_str());
	printf("%s",deps.c_str());
	printf("\n");
	printf("clean:\n\t rm %s z.out kaka.xxx file_dump.cpp TERM* 1 2\n",joinexe(" ",targets).c_str());
	
	return 0;
}
