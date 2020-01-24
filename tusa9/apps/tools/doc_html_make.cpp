//#include "PROJ_CONFIG.h"
#include "copy_file.h"
#include "st_stuff.h"
#include "mysql_extens.h"
#include <sys/stat.h>
#include "str_lib.h"
#include <vector>
#include <map>
#include "st_stream_str.h"
#include "st_rsa.h"
#include <ctype.h>
int main(int argc, char*argv[])
{
	FILE *f;
	f=fopen(argv[1],"rb");
	while(!feof(f))
	{
	
		char s[300];
		fgets(s,299,f);
		
		string key;
		bool keystarted=false;
		for(unsigned i=0;i<strlen(s);i++)
		{
		
			if(s[i]=='\r'||s[i]=='\n')s[i]=0;
		}
		for(unsigned i=0;i<strlen(s);i++)
		{
			if(isalnum(s[i]))keystarted=true;
			if(s[i]=='.'){keystarted=false;break;}
			if(keystarted)key+=s[i];
		}
		string key_name;
		for(unsigned i=0;i<key.size();i++)
		{
			if(key[i]=='/')key_name+="_";
			else key_name+=key[i];
		}
//		printf("key %s key_name %s\n",key.c_str(),key_name.c_str());
		
//		printf("file %s\n",s);
		string fn=(string)"./"+s;
		FILE *ff=fopen(fn.c_str(),"rb");
		
		if(!ff)perror("fopen");
//		string purpose;
		int idx=0;
		map<int,string> txtlist;
		while(!feof(ff))
		{
			char ss[1300];
			char *pss=ss;
			memset(ss,0,1300);
			fgets(ss,1299,ff);
			if(pss[0]=='*')
			{
				idx++;
				pss++;
			}
			txtlist[idx]+=pss;
//			printf("kall1\n");
		}
		idx++;
		if(txtlist.size())
		{
			printf("<big><a name=%s>%s</a></big><p>
<b>Purpose</b>: %s<br>\n
",key_name.c_str(),key.c_str(),txtlist[0].c_str());
		}
		if(txtlist.size()==1)
		{
			printf("<b>Replacement keys</b>: none<p>\n\n");
		}
		else
		{
		printf("<b>Replacement keys</b>: <ul>\n");
		for(unsigned i=1;i<idx;i++)
		{
			printf("<li> %s\n",txtlist[i].c_str());
		}
		printf("</ul><p>\n\n");
		}
		/*
		vector<string> v=splitTOK("/",s);
		if(!v.size())continue;
		vector<string>vv=splitTOK(".",v[v.size()-1]);
		if(vv.size())continue;
		string key=*/
	}

return 0;
}
