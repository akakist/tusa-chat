#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
//#include "mysql_extens.h"
#include <time.h>

string str_nick(const string &n);


int main(int argc,char *argv[])
{
//    char *ss="aG16YSBDIDIyMzM0NQ==";
//    printf("%s",Base64Decode(ss).c_str());
//    exit(1);


	FILE *f=fopen(argv[1],"rb");
	map<string,int> urls;
	map<string,int> ips;
	int ii=0;
	while(!feof(f))
	{
	    ii++;
	    if(ii%10000==0) fprintf(stderr,"%d\n",ii);
	    char s[1000];
	    if(fgets(s,1000,f)==NULL) break;
	    vector<string> v=splitTOK(" ",s);
	    if(v.size())
	    {
		string url=v[0];
		if(url.find("/photos/")!=-1)continue;
		if(url.find("/userphotos/")!=-1)
		{
		    url="/userphotos/";
		}
		if(url.find("/gallery/")!=-1)
		{
		    url="/gallery/";
		}

		if(url.find("/chat_userinfo2/")!=-1)
		{
		    url="/chat_userinfo2/";
		}

		if(url.find("/attach/")!=-1)continue;
		if(url.find("/attachs/")!=-1)continue;
		if(url.find("soap")!=-1)continue;
		if(url.find("_vti_bin")!=-1)continue;
		if(url.find("php")!=-1)continue;
		if(url.find("cgi-bin")!=-1)continue;
		
		if(!urls.count(url))
		{
		    urls[url]=1;
		}
		else urls[url]++;
		string ip=v[v.size()-1];
		if(!ips.count(ip))
		{
		    ips[ip]=1;
		}
		else ips[ip]++;
		
	    }
	    
	
	}
	
	fclose(f);
	for(typeof(urls.begin())i=urls.begin();i!=urls.end();i++)
	{
	    if(i->second>20)
	    printf("%s %d\n",i->first.c_str(),i->second);
	}
	printf("TOTAL IP CNT %d\n",ips.size());
	
	return 0;
}
