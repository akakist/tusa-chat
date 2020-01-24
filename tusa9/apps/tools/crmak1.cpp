#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <sys/stat.h>
#include <regex.h>
#include <unistd.h>
#include <set>
#include <sys/stat.h>
//#include "str_lib.h"
using namespace std;
set<string> inc_dirs;
set<string> targets;
set<string> objs;
struct _rxfind_data{
	string str;
	int so;
	int eo;
};
map <string, string> conf;
string exename(const string &s);
string relexename(const string &s);
vector < string > splitTOK(const char *seps, const char *src);

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
bool is_file_exists(const string &pathname)
{

	struct stat st;
	bool res=false;
	
	if(stat(pathname.c_str(),&st))
	{res=false;
	}
	else res=true;
	printf("#stat %s %d\n",pathname.c_str(),stat(pathname.c_str(),&st));
//	logErr2("is_file_exists %s %d",pathname.c_str(),res);
	return res;
	
}

string join(const string &pattern, const vector<string> & arr);
string join(const char* pattern, const vector<string> & arr)
{
	return join((string)pattern,arr);
}

string join(const string &pattern, const vector<string> & arr)
{
    string ret;
    if (arr.size() > 1)
    {
                unsigned int i;
                for (i = 0; i < arr.size() - 1; i++)
                        ret += arr[i] + pattern;
                ret += arr[arr.size() - 1];
    }
    else if(arr.size()==1)
    {
	ret+=arr[0];
    }
    return ret;
}

void check_path_wfn(const string & _pathname)
{
	printf("#check_path_wfn(%s)\n",_pathname.c_str());
	string pathname=_pathname;
	if(!pathname.size())return;
	vector <string> ar=splitTOK("/",pathname.c_str());;
	vector <string> newar;
	newar.clear();
	{for(int i=0;i<ar.size()-1;i++)
	{
		newar.push_back(ar[i]);
	}}
	
	string dir=(pathname[0]=='/'?"/":"")+join("/",newar);
//	logErr2("check dir %s",dir.c_str());

	if(is_file_exists(dir)) return;
	string parts;
	if(pathname[0]=='/')parts="/";
	for(unsigned i=0;i<newar.size();i++)
	{
		string par=parts+newar[i];
		parts+=newar[i]+"/";
		if(/*(!is_file_exists(parts))&&*/(!is_file_exists(par)))
		{
//			logErr2("Creating dir: %s", to_mac_enc(parts).c_str());
			if(mkdir(parts.c_str(),0755))
			{
				printf("#Cannot create dir %s\n",parts.c_str());
				exit(0);
			}		
		}
//		parts+=;
	}
}

string joinexe(const string &pattern, const set<string> & sarr)
{
    string ret;
	vector<string>arr;
	for(set<string>::const_iterator i=sarr.begin();i!=sarr.end();i++)arr.push_back(*i);
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
string joinrelexe(const string &pattern, const set<string> & sarr)
{
    string ret;
	vector<string>arr;
	for(set<string>::const_iterator i=sarr.begin();i!=sarr.end();i++)arr.push_back(*i);
    if (arr.size() > 1)
    {
                unsigned int i;
                for (i = 0; i < arr.size() - 1; i++)
                        ret += exename(arr[i]) + pattern;
                ret += relexename(arr[arr.size() - 1]);
    }
    else if(arr.size()==1)
    {
	ret+=relexename(arr[0]);
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
		printf ("#%s ",((string)"regex "+regexp+": "+erbuf).c_str());
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
set < string > splitTOKs(const char *seps, const char *src)
{
	set < string > res;
	char *s = strdup((char *) src);
	char *token = strtok(s, seps);
	while (token != NULL) {
		res.insert(token);
		token = strtok(NULL, seps);
	}
	free(s);
	return res;
}

void read_config(int argc, char *argv[])
{
	FILE *f = fopen(argv[1], "rb");
	if(f==NULL){printf("#Failled open file %s\n",argv[1]);exit(1);}
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
			 inc_dirs=splitTOKs(" \t",v[1].c_str());
			else if(v[0]=="TARGETS")
			 targets=splitTOKs(" \t",v[1].c_str());
			else if(v[0]=="OBJS")
			 objs=splitTOKs(" \t",v[1].c_str());
			else conf[v[0]]=v[1];
			 
		}
	}
	for (set<string>::iterator i=inc_dirs.begin();i!=inc_dirs.end();i++)
	{
		conf["CFLAGS"]+=" -I"+*i;
		conf["RCFLAGS"]+=" -I"+*i;
	}
}

map <string,string> srcfiles;
string find_srcfile(const string& s)
{
	if(srcfiles.find(s)!=srcfiles.end())
	return srcfiles[s];
	
	for(set<string>::iterator i=inc_dirs.begin();i!=inc_dirs.end();i++)
	{
		string pn=*i+"/"+s;
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
	vector <string> v=splitTOK("./",s.c_str());
	if(v.size()>1)
	{	string s=/*conf["OBJDIR"]+*/"$(OBJDIR)/"+v[v.size()-2]+".o";
//		check_path_wfn(s);
		return s;
	}
	return "";
}
string relobjname(const string &s)
{
	vector <string> v=splitTOK("./",s.c_str());
	if(v.size()>1)
	{
		string s=/*conf["ROBJDIR"]+*/"$(ROBJDIR)/"+v[v.size()-2]+".o";
//		check_path_wfn(s);
		return s;
	}
	return "";
}
string exename(const string &s)
{
	vector <string> v=splitTOK(".",s.c_str());
	if(v.size()==2)
	{
#ifdef __FreeBSD__
		return v[0]+".FreeBSD.exe";
#else
		return v[0]+".exe";
#endif		
		
	}
	return "";
}
string relexename(const string &s)
{
	vector <string> v=splitTOK(".",s.c_str());
	if(v.size()==2)
	{
#ifdef __FreeBSD__
		return v[0]+".release.FreeBSD.exe";
#else
		return v[0]+".release.exe";
#endif		
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
	printf("crmak -- create makefile\nusage: crmak makef.i\nwhere makef.i have format:\
OBJDIR=/tmp/svr\
CFLAGS= -Wall  -I/usr/include/mysql  -c   \\ \
	  -I/usr/local/ssl/include -I../include \
LIBS=/usr/lib/libssl.so.0 /usr/lib/libcrypto.so.0\\ \
	 /usr/lib/libmysqlclient.so -lpthread -lgdbm\
LIBNAME=libpr.a\
INC_DIRS= . ./lib ./http ./udp ./cgi ../chatserver \
TARGETS=msg_server_main.c projektor_main.c\
OBJS=st_stuff.c st_rsa.c \\ \
	storage.c errs.c str_lib.c\\ \
	 packets.c trans.c c_conn.c\\ \
	  wrappers.c  m_containers.c _string.c my_gdbm.c copy_file_common.c\
");
	exit(1);
  }
  
//  
	read_config(argc, argv);
	{string s=conf["ROBJDIR"]+"/kall";
	check_path_wfn(s);
	}
	{
	string s=conf["OBJDIR"]+"/kall";
	check_path_wfn(s);
	}

	set <string> OBJS=objs;
	for(set<string>::iterator i=targets.begin();i!=targets.end();i++)
	{
		objs.insert(*i);
	}
//	printf("\nobjs=%s\n");
	string deps;
	string reldeps;
	vector<string> total_objs;
	printf("\nCFLAGS=%s\n",conf["CFLAGS"].c_str());
	printf("\nRCFLAGS=%s\n",conf["RCFLAGS"].c_str());
	printf("\nLIBS=%s\n",conf["LIBS"].c_str());
	printf("\nRLIBS=%s\n",conf["RLIBS"].c_str());
	printf("\nOBJDIR=%s\n",conf["OBJDIR"].c_str());
	printf("\nROBJDIR=%s\n\n",conf["ROBJDIR"].c_str());
	
	bool err=false;
	for(set<string>::iterator i=objs.begin();i!=objs.end();i++)
	{
		if(i->size()<3)continue;
		string src=find_srcfile(*i);
		if(src.size()==0)
		{
		    fprintf(stderr,"ERROR file %s not found\n",i->c_str());
		    err=true;
		}
	}
	if(err) exit(1);
	for(set<string>::iterator i=objs.begin();i!=objs.end();i++)
	{
		if(i->size()<3)continue;
		string src=find_srcfile(*i);
		if(src.size()==0)
		fprintf(stderr,"ERROR file %s not found\n",i->c_str());
		
		string cpp_cmd=(string)"\n\t c++ "+conf["CFLAGS"]+" -MM "+src+" -o zxc.d";
		fprintf(stderr,"%s\n",cpp_cmd.c_str());
		system(cpp_cmd.c_str());
		
		FILE *f=fopen("zxc.d","rb");
		if(f)
		{
		string body;
		while(!feof(f))
		{
			int c=getc(f);
			if(c!=EOF)body+=c;
		}
		deps+="\n"+conf["OBJDIR"]+"/"+body;
		string cmd=(string)"\t c++ $(CFLAGS) "+find_srcfile(*i)+" -o "+objname(*i);
		total_objs.push_back(objname(*i));
		deps+=cmd+"\n";
		fclose(f);
		unlink("zxc.d");
		}
//		/*string*/ cmd=(string)"\n\t ar -r "+conf["OBJDIR"]+"/"+conf["LIBNAME"]+ " "+objname(objs[i]);
//		deps+=cmd+"\n";
	}
	for(set<string>::iterator i=objs.begin();i!=objs.end();i++)
	{
		if(i->size()<3)continue;
		string cpp_cmd=(string)"\n\t c++ "+conf["RCFLAGS"]+" -MM "+find_srcfile(*i)+" -o zxc.d";
		fprintf(stderr,"%s\n",cpp_cmd.c_str());
		system(cpp_cmd.c_str());
		
		FILE *f=fopen("zxc.d","rb");
		if(f)
		{
		string body;
		while(!feof(f))
		{
			int c=getc(f);
			if(c!=EOF)body+=c;
		}
		reldeps+="\n"+conf["ROBJDIR"]+"/"+body;
		string cmd=(string)"\t c++ $(RCFLAGS) "+find_srcfile(*i)+" -o "+relobjname(*i);
		total_objs.push_back(relobjname(*i));
		reldeps+=cmd+"\n";
		fclose(f);
		unlink("zxc.d");
		}
//		/*string*/ cmd=(string)"\n\t ar -r "+conf["OBJDIR"]+"/"+conf["LIBNAME"]+ " "+objname(objs[i]);
//		deps+=cmd+"\n";
	}
	
	string libpr;
	string rellibpr;
	libpr+="\n"+/*conf["OBJDIR"]+"/"+*/conf["LIBNAME"]+": ";
	rellibpr+="\n"+/*conf["ROBJDIR"]+"/"+*/conf["RLIBNAME"]+": ";
	total_objs.push_back(/*conf["OBJDIR"]+"/"+*/conf["LIBNAME"]);
	total_objs.push_back(/*conf["ROBJDIR"]+"/"+*/conf["RLIBNAME"]);
	for(set<string>::iterator i=OBJS.begin();i!=OBJS.end();i++)
	{
		libpr+="\\\n\t"+ objname(*i);
		rellibpr+="\\\n\t"+relobjname(*i)+" ";
	}
	libpr+="\n";
	rellibpr+="\n";
	libpr+="\t\t ar -r "+/*conf["OBJDIR"]+"/"+*/conf["LIBNAME"]+" ";
	rellibpr+="\t\t ar -r "+/*conf["ROBJDIR"]+"/"+*/conf["RLIBNAME"]+" ";
	for(set<string>::iterator i=OBJS.begin();i!=OBJS.end();i++)
	{
		libpr+=objname(*i)+" ";
		rellibpr+=relobjname(*i)+" ";
	}
	libpr+="\n";
	rellibpr+="\n";
	string all;
	string release;
	all+="all: "+/*conf["OBJDIR"]+"/"+*/conf["LIBNAME"]+" ";
	release+="release: "+/*conf["ROBJDIR"]+"/"+*/conf["RLIBNAME"]+" ";
	for(set<string>::iterator i=targets.begin();i!=targets.end();i++)
	{
		all+=exename(*i)+" ";
		release+=relexename(*i)+" ";
	}
	all+="\n";
	release+="\n";
	string mkall;
	string mkrelease;
	for(set<string>::iterator i=targets.begin();i!=targets.end();i++)
	{
		mkall+=exename(*i)+": "+/*conf["OBJDIR"]+"/"+*/conf["LIBNAME"]+" "+conf["LIBS_DEP"]+" "+objname(*i)+"\n";
		mkall+="\t\tc++ "+objname(*i)+" -o "+exename(*i)+" "+/*conf["OBJDIR"]+"/"+*/conf["LIBNAME"]+" "+conf["LIBS_DEP"]+" $(LIBS) \n";
		mkall+="\t\t strip "+exename(*i)+" \n";
		mkrelease+=relexename(*i)+": "+/*conf["ROBJDIR"]+"/"+*/conf["RLIBNAME"]+" "+conf["RLIBS_DEP"]+" "+relobjname(*i)+"\n";
		mkrelease+="\t\tc++ "+relobjname(*i)+" -o "+relexename(*i)+" "+/*conf["ROBJDIR"]+"/"+*/conf["RLIBNAME"]+" "+conf["RLIBS_DEP"]+" $(RLIBS)\n";
		mkrelease+="\t\t strip "+relexename(*i)+" \n";
	}
	mkall+="\n";
	mkrelease+="\n";
	printf("%s",all.c_str());
	printf("%s",mkall.c_str());
	printf("%s",libpr.c_str());
	printf("%s",deps.c_str());
	printf("\n");
	printf("%s",release.c_str());
	printf("%s",mkrelease.c_str());
	printf("%s",rellibpr.c_str());
	printf("%s",reldeps.c_str());
	printf("\n");
	printf("clean:\n\t rm %s %s z.out kaka.xxx file_dump.cpp TERM* 1 2\n",joinexe(" ",targets).c_str(),joinrelexe(" ",targets).c_str());

	printf("\nboth: all release\n\n\n");

	printf("\ncleanobjs:\n\t rm %s\n\n",join(" ",total_objs).c_str());
	
	printf("\ncleanall: clean cleanobjs\n\n\n");
	return 0;
}
